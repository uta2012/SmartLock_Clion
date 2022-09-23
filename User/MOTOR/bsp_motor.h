#ifndef BSP_MOTOR_H_
#define BSP_MOTOR_H_

#include "stm32f4xx_hal.h"
#include "gpio.h"



void Door_Init(void);
void Open_Door(void);
void Close_Door(void);
//void Pwm_Open_Door(void);
//void Pwm_Close_Door(void);

#endif //BSP_MOTOR_H_