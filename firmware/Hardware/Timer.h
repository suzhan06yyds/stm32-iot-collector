#ifndef __TIMER_H
#define __TIMER_H

#include <stdio.h>
extern uint8_t flag_10hz;
void Timer_Init(void);
void TIM2_IRQHandler(void);

#endif
