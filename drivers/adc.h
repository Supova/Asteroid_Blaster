#ifndef ADC_H
#define ADC_H

#include <stdint.h>

/*
 * ADC0, Sample Sequencer 1 — two-channel read
 *   Step 0: AIN0 (PE3) = joystick VRx
 *   Step 1: AIN1 (PE2) = joystick VRy  (END + IE on this step)
 */

void     adc_init(void);
void     adc_read(uint32_t *vrx, uint32_t *vry);

#endif /* ADC_H */
