#ifndef __VOICE_H_
#define __VOICE_H_

#include "stm32f4xx_hal.h"
#include "delay.h"


#define VOICE_DATA_L  HAL_GPIO_WritePin(VOICE_DATA_GPIO_Port, VOICE_DATA_Pin, GPIO_PIN_RESET)
#define VOICE_DATA_H  HAL_GPIO_WritePin(VOICE_DATA_GPIO_Port, VOICE_DATA_Pin, GPIO_PIN_SET)


#define VOICE_BUSY  (HAL_GPIO_ReadPin(VOICE_BUSY_GPIO_Port, VOICE_BUSY_Pin))


void Voice_Sendcmd(uint8_t cmd);

#endif