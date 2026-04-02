#ifndef CRITICAL_SECTION_H
#define CRITICAL_SECTION_H

#include "cmsis_compiler.h"

static inline void hal_critical_enter(void) { __disable_irq(); }
static inline void hal_critical_exit(void)  { __enable_irq();  }

#endif /* CRITICAL_SECTION_H */
