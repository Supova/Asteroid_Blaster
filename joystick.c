// main.c
// KY-023 Joystick Test with Direction Detection - TM4C123GH6PM
// Pure register access, no TivaWare
// VRx -> PE3 (AIN0), VRy -> PE2 (AIN1), SW -> PF4

#include "TM4C123GH6PM.h"
#include <stdint.h>

// Thresholds (12-bit ADC, center ~2047)
#define JOY_HIGH 3000
#define JOY_LOW 1000

typedef enum {
    DIR_CENTER,
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP_LEFT,
    DIR_UP_RIGHT,
    DIR_DOWN_LEFT,
    DIR_DOWN_RIGHT
} JoyDir;

//-----------------------------------------------------------
// Delay
//-----------------------------------------------------------
void delay_ms(uint32_t ms) {
    uint32_t i;
    for (i = 0; i < ms * 5333; i++)
        __asm("NOP");
}

//-----------------------------------------------------------
// UART0 Init - PA0=RX, PA1=TX, 115200 @ 16MHz PIOSC
//-----------------------------------------------------------
void UART0_Init(void) {
    SYSCTL->RCGCUART |= (1 << 0);
    SYSCTL->RCGCGPIO |= (1 << 0);
    while (!(SYSCTL->PRGPIO & (1 << 0)))
        ;

    GPIOA->AFSEL |= (1 << 0) | (1 << 1);
    GPIOA->PCTL &= ~(0xFF);
    GPIOA->PCTL |= (0x11);
    GPIOA->DEN |= (1 << 0) | (1 << 1);
    GPIOA->AMSEL &= ~((1 << 0) | (1 << 1));

    UART0->CTL &= ~(1 << 0);             // Disable UART
    UART0->CC = 0x5;                     // Clock source = PIOSC (16MHz)
    UART0->IBRD = 8;                     // 16MHz / (16 * 115200) = 8.68
    UART0->FBRD = 44;                    // 0.68 * 64 + 0.5 = 44
    UART0->LCRH = (0x3 << 5) | (1 << 4); // 8-bit, FIFO enabled
    UART0->CTL |= (1 << 0) | (1 << 8) | (1 << 9);
}

void UART0_SendChar(char c) {
    while (UART0->FR & (1 << 5))
        ;
    UART0->DR = c;
}

void UART0_SendStr(const char *s) {
    while (*s)
        UART0_SendChar(*s++);
}

void UART0_SendIntW(uint32_t n, int width) {
    char buf[12];
    int len = 0, i;
    uint32_t tmp = n;
    if (tmp == 0) {
        buf[len++] = '0';
    } else {
        while (tmp > 0) {
            buf[len++] = '0' + (tmp % 10);
            tmp /= 10;
        }
    }
    for (i = len; i < width; i++)
        UART0_SendChar(' ');
    for (i = len - 1; i >= 0; i--)
        UART0_SendChar(buf[i]);
}

//-----------------------------------------------------------
// ADC0 Init - PE3 (AIN0) = VRx, PE2 (AIN1) = VRy
//-----------------------------------------------------------
void ADC_Init(void) {
    SYSCTL->RCGCADC |= (1 << 0);
    SYSCTL->RCGCGPIO |= (1 << 4);
    while (!(SYSCTL->PRGPIO & (1 << 4)))
        ;

    GPIOE->AFSEL |= (1 << 2) | (1 << 3);
    GPIOE->DEN &= ~((1 << 2) | (1 << 3));
    GPIOE->AMSEL |= (1 << 2) | (1 << 3);

    ADC0->ACTSS &= ~(1 << 1);
    ADC0->EMUX &= ~(0xF << 4);
    ADC0->SSMUX1 = (0) | (1 << 4); // Step0=AIN0, Step1=AIN1
    ADC0->SSCTL1 = (0x6 << 4);     // Step1: IE + END
    ADC0->ACTSS |= (1 << 1);
}

void ADC_Read(uint32_t *vrx, uint32_t *vry) {
    uint32_t timeout = 100000;

    ADC0->PSSI |= (1 << 1);
    while (!(ADC0->RIS & (1 << 1)) && timeout--)
        ; // wont hang forever
    *vrx = ADC0->SSFIFO1 & 0xFFF;
    *vry = ADC0->SSFIFO1 & 0xFFF;
    ADC0->ISC |= (1 << 1);
}

//-----------------------------------------------------------
// SW Init - PF4 input with pull-up
//-----------------------------------------------------------
void SW_Init(void) {
    SYSCTL->RCGCGPIO |= (1 << 5);
    while (!(SYSCTL->PRGPIO & (1 << 5)))
        ;

    GPIOF->LOCK = 0x4C4F434B;
    GPIOF->CR |= (1 << 4);
    GPIOF->DIR &= ~(1 << 4);
    GPIOF->PUR |= (1 << 4);
    GPIOF->DEN |= (1 << 4);
    GPIOF->AMSEL &= ~(1 << 4);
}

//-----------------------------------------------------------
// Direction Detection
//-----------------------------------------------------------
JoyDir Joystick_GetDir(uint32_t vrx, uint32_t vry) {
    uint8_t left = (vrx > JOY_HIGH); // was < JOY_LOW
    uint8_t right = (vrx < JOY_LOW); // was > JOY_HIGH
    uint8_t up = (vry > JOY_HIGH);
    uint8_t down = (vry < JOY_LOW);

    if (up && left)
        return DIR_UP_LEFT;
    else if (up && right)
        return DIR_UP_RIGHT;
    else if (down && left)
        return DIR_DOWN_LEFT;
    else if (down && right)
        return DIR_DOWN_RIGHT;
    else if (up)
        return DIR_UP;
    else if (down)
        return DIR_DOWN;
    else if (left)
        return DIR_LEFT;
    else if (right)
        return DIR_RIGHT;
    else
        return DIR_CENTER;
}

const char *Dir_ToString(JoyDir dir) {
    switch (dir) {
    case DIR_UP:
        return "UP        ";
    case DIR_DOWN:
        return "DOWN      ";
    case DIR_LEFT:
        return "LEFT      ";
    case DIR_RIGHT:
        return "RIGHT     ";
    case DIR_UP_LEFT:
        return "UP-LEFT   ";
    case DIR_UP_RIGHT:
        return "UP-RIGHT  ";
    case DIR_DOWN_LEFT:
        return "DOWN-LEFT ";
    case DIR_DOWN_RIGHT:
        return "DOWN-RIGHT";
    default:
        return "CENTER    ";
    }
}

//-----------------------------------------------------------
// Main
//-----------------------------------------------------------
int main(void) {
    UART0_Init();
    ADC_Init();
    SW_Init();

    UART0_SendStr("KY-023 Joystick Test\r\n");
    UART0_SendStr("--------------------\r\n");

    uint32_t vrx, vry;
    uint8_t sw;
    JoyDir dir;

    while (1) {
        ADC_Read(&vrx, &vry);
        sw = (GPIOF->DATA & (1 << 4)) ? 0 : 1;
        dir = Joystick_GetDir(vrx, vry);

        UART0_SendStr("VRx: ");
        UART0_SendIntW(vrx, 4);
        UART0_SendStr(" | VRy: ");
        UART0_SendIntW(vry, 4);
        UART0_SendStr(" | SW: ");
        UART0_SendChar('0' + sw);
        UART0_SendStr(" | Dir: ");
        UART0_SendStr(Dir_ToString(dir));
        UART0_SendStr("\r\n");

        delay_ms(20);
    }
}