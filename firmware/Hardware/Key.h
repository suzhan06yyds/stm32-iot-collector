#ifndef __KEY_H
#define __KEY_H

extern volatile uint8_t key1_flag;
extern volatile uint8_t key2_flag;
void Key_Init(void);
void EXTI1_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif
