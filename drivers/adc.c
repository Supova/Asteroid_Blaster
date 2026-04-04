#include "adc.h"
#include "TM4C123.h"

/* Clock enable bits */
#define ADC0_EN   (1 << 0)
#define GPIOE_EN  (1 << 4)

/* PE2 = AIN1 (VRy), PE3 = AIN0 (VRx) */
#define PE2       (1 << 2)
#define PE3       (1 << 3)

/* ADC sequencer 1 (SS1) — 4-sample sequencer, we use 2 steps */
#define SS1       (1 << 1)

/* SSCTL1: step 1 gets IE (interrupt enable) + END bits */
#define STEP1_IE_END  (0x6 << 4)

/* ADC result ready flag for SS1 */
#define SS1_RIS   (1 << 1)

void adc_init(void) {
    /* Enable clocks */
    SYSCTL->RCGCADC  |= ADC0_EN;
    SYSCTL->RCGCGPIO |= GPIOE_EN;
    while (!(SYSCTL->PRGPIO & GPIOE_EN))
        ;

    /* Configure PE2 and PE3 as analog inputs */
    GPIOE->AFSEL |=  PE2 | PE3;
    GPIOE->DEN   &= ~(PE2 | PE3);   // disable digital
    GPIOE->AMSEL |=  PE2 | PE3;     // enable analog

    /* Configure SS1: software-triggered, 2 steps */
    ADC0->ACTSS  &= ~SS1;           // disable SS1 before config
    ADC0->EMUX   &= ~(0xF << 4);   // SS1 trigger = software
    ADC0->SSMUX1  = (0) | (1 << 4); // step0=AIN0(VRx), step1=AIN1(VRy)
    ADC0->SSCTL1  = STEP1_IE_END;   // step1: interrupt + end of sequence
    ADC0->ACTSS  |= SS1;            // re-enable SS1
}

void adc_read(uint32_t *vrx, uint32_t *vry) {
    ADC0->PSSI |= SS1;                              // trigger conversion
    while (!(ADC0->RIS & SS1_RIS))                 // wait for sequence done
        ;
    *vrx = ADC0->SSFIFO1 & 0xFFF;                  // first sample: AIN0
    *vry = ADC0->SSFIFO1 & 0xFFF;                  // second sample: AIN1
    ADC0->ISC |= SS1_RIS;                          // clear interrupt flag
}
