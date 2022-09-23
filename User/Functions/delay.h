/**
  ******************************************************************************
  * @file    delay.h
  * @author  ROG Zephyrus M16
  * @date    11:48 AM 8/19/2022
  * @brief   None.
  *          
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 UTA.
  * All rights reserved.
  *
  * By(UTA personally owned)
  * https://blog.csdn.net/qq_51913390
  *
  ******************************************************************************
  */
/********************************End of Head************************************/


#ifndef DELAY_H_
#define DELAY_H_

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

#include "main.h"

extern void vPortSetupTimerInterrupt( void );


void Delay_us(__IO uint32_t delay);
void Delay_ms(__IO uint32_t ms);


#endif //DELAY_H_

/********************************End of File************************************/