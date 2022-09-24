#ifndef BSP_MOTOR_H_
#define BSP_MOTOR_H_

#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


extern uint8_t lock_status;//0 is open status,and 1 is close status

#define door_status HAL_GPIO_ReadPin(MCU_WKUP_GPIO_Port, MCU_WKUP_Pin)


void Door_Init(void);
void Open_Door(void);
void Close_Door(void);
//void Pwm_Open_Door(void);
//void Pwm_Close_Door(void);

#endif //BSP_MOTOR_H_