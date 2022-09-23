/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"

#include "bsp_rfid.h"
#include "bsp_lcd.h"
#include "retarget.h"
#include "bsp_at24c04.h"
#include "bsp_motor.h"
#include "bsp_led.h"
#include "bsp_bs8116.h"
#include "bsp_esp32.h"
#include "bsp_voice.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BACKUP_Pin GPIO_PIN_13
#define BACKUP_GPIO_Port GPIOC
#define BACKUP_EXTI_IRQn EXTI15_10_IRQn
#define BS8116_IRQ_Pin GPIO_PIN_1
#define BS8116_IRQ_GPIO_Port GPIOA
#define FLASH_SPI1_CS_Pin GPIO_PIN_4
#define FLASH_SPI1_CS_GPIO_Port GPIOA
#define FLASH_SPI1_SCLK_Pin GPIO_PIN_5
#define FLASH_SPI1_SCLK_GPIO_Port GPIOA
#define FLASH_SPI1_MISO_Pin GPIO_PIN_6
#define FLASH_SPI1_MISO_GPIO_Port GPIOA
#define FLASH_SPI1_MOSI_Pin GPIO_PIN_7
#define FLASH_SPI1_MOSI_GPIO_Port GPIOA
#define VOICE_BUSY_Pin GPIO_PIN_4
#define VOICE_BUSY_GPIO_Port GPIOC
#define VOICE_DATA_Pin GPIO_PIN_5
#define VOICE_DATA_GPIO_Port GPIOC
#define LCD_LEDK_Pin GPIO_PIN_1
#define LCD_LEDK_GPIO_Port GPIOB
#define LCD_RESET_Pin GPIO_PIN_10
#define LCD_RESET_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOB
#define LCD_SPI2_SCLK_Pin GPIO_PIN_13
#define LCD_SPI2_SCLK_GPIO_Port GPIOB
#define LCD_D_C_Pin GPIO_PIN_14
#define LCD_D_C_GPIO_Port GPIOB
#define LCD_SPI2_MOSI_Pin GPIO_PIN_15
#define LCD_SPI2_MOSI_GPIO_Port GPIOB
#define AT24CXX_IIC3_SDA_Pin GPIO_PIN_9
#define AT24CXX_IIC3_SDA_GPIO_Port GPIOC
#define AT24CXX_IIC3_SCK_Pin GPIO_PIN_8
#define AT24CXX_IIC3_SCK_GPIO_Port GPIOA
#define RFID_SPI3_CS_Pin GPIO_PIN_15
#define RFID_SPI3_CS_GPIO_Port GPIOA
#define RFID_SPI3_SCLK_Pin GPIO_PIN_10
#define RFID_SPI3_SCLK_GPIO_Port GPIOC
#define RFID_SPI3_MISO_Pin GPIO_PIN_11
#define RFID_SPI3_MISO_GPIO_Port GPIOC
#define RFID_SPI3_MOSI_Pin GPIO_PIN_12
#define RFID_SPI3_MOSI_GPIO_Port GPIOC
#define RFID_SPI3_RST_Pin GPIO_PIN_2
#define RFID_SPI3_RST_GPIO_Port GPIOD
#define MOTOR_IB_Pin GPIO_PIN_3
#define MOTOR_IB_GPIO_Port GPIOB
#define MOTOR_IA_Pin GPIO_PIN_4
#define MOTOR_IA_GPIO_Port GPIOB
#define BS8116_IIC1_SCLK_Pin GPIO_PIN_6
#define BS8116_IIC1_SCLK_GPIO_Port GPIOB
#define BS8116_IIC1_SDA_Pin GPIO_PIN_7
#define BS8116_IIC1_SDA_GPIO_Port GPIOB
#define LED_R_Pin GPIO_PIN_8
#define LED_R_GPIO_Port GPIOB
#define LED_G_Pin GPIO_PIN_9
#define LED_G_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
