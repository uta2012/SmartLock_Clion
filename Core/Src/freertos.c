/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId LCDHandle;
osThreadId RFIDHandle;
osThreadId LEDHandle;
osThreadId DoorHandle;
osThreadId ESP32Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void LCD_entry(void const * argument);
void RFID_entry(void const * argument);
void LED_entry(void const * argument);
void Door_entry(void const * argument);
void ESP32_entry(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityAboveNormal, 0, 512);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of LCD */
  osThreadDef(LCD, LCD_entry, osPriorityIdle, 0, 128);
  LCDHandle = osThreadCreate(osThread(LCD), NULL);

  /* definition and creation of RFID */
  osThreadDef(RFID, RFID_entry, osPriorityIdle, 0, 512);
  RFIDHandle = osThreadCreate(osThread(RFID), NULL);

  /* definition and creation of LED */
  osThreadDef(LED, LED_entry, osPriorityIdle, 0, 256);
  LEDHandle = osThreadCreate(osThread(LED), NULL);

  /* definition and creation of Door */
  osThreadDef(Door, Door_entry, osPriorityHigh, 0, 512);
  DoorHandle = osThreadCreate(osThread(Door), NULL);

  /* definition and creation of ESP32 */
  osThreadDef(ESP32, ESP32_entry, osPriorityIdle, 0, 512);
  ESP32Handle = osThreadCreate(osThread(ESP32), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  UBaseType_t task1, task2, task3, task4, task5, task6;
  /* Infinite loop */
  for(;;)
  {

    task1 = uxTaskGetStackHighWaterMark(NULL);
    task2 = uxTaskGetStackHighWaterMark(LCDHandle);
    task3 = uxTaskGetStackHighWaterMark(RFIDHandle);
    task4 = uxTaskGetStackHighWaterMark(LEDHandle);
    task5 = uxTaskGetStackHighWaterMark(DoorHandle);
    task6 = uxTaskGetStackHighWaterMark(ESP32Handle);

    printf("task1 : %ld\ntask2 : %ld\ntask3 : %ld\ntask4 : %ld\ntask5 : %ld\ntask6 : %ld\n",
             task1, task2, task3, task4, task5, task6);
    osDelay(30000);



  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_LCD_entry */
/**
* @brief Function implementing the LCD thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LCD_entry */
void LCD_entry(void const * argument)
{
  /* USER CODE BEGIN LCD_entry */
    uint8_t eng[] ={
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFC,0x1F,0xFC,
            0x10,0x08,0x30,0x10,0x20,0x10,0x20,0x20,0x00,0x20,0x00,0x40,0x00,0x40,0x00,0x40,
            0x00,0x80,0x00,0x80,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x03,0x00,0x03,0x00,
            0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"7",0*/
    };


    uint8_t chi[] = {

            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x04,0x00,0x9B,0xFC,0x3E,0x90,0x08,0x24,
            0x90,0x08,0x24,0xA0,0x08,0x24,0xA3,0xC8,0x24,0xA2,0x48,0x24,0xA2,0x48,0x24,0xA2,
            0x48,0x24,0x92,0x48,0x24,0x92,0x48,0x24,0x9A,0x48,0x3C,0x9B,0xC8,0x24,0xDA,0x48,
            0x20,0xB0,0x08,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x80,0x08,0x00,0x80,0x08,0x00,
            0x80,0x78,0x00,0x80,0x10,0x00,0x00,0x00,/*"啊",0*/


    };

  /* Infinite loop */
  for(;;)
  {
    Display_eng(100, 100, RED,WHITE,32,eng);
    Display_chi(150,150,RED,WHITE,24,chi);

    //Display_Pic(0,0,gImage_123456);

    osDelay(3000);
  }
  /* USER CODE END LCD_entry */
}

/* USER CODE BEGIN Header_RFID_entry */
/**
* @brief Function implementing the RFID thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RFID_entry */
void RFID_entry(void const * argument)
{
  /* USER CODE BEGIN RFID_entry */
  uint8_t card_id[4] = {0}; //�?�ID
  uint8_t CT[4] = {0}; //�?�类型

  /* Infinite loop */
  for(;;)
  {
      if(PcdRequest(PICC_REQALL, CT) == MI_OK)//寻�?��?功
      {
          if(PcdAnticoll(card_id) == MI_OK)
          {
              printf("card_type:");
              print_info(CT, 4);
              printf("\r\n");
              printf("card_id:");
              print_info(card_id, 4);
              printf("\r\n");
              Open_Door();
              Close_Door();
          }
      }





      osDelay(1000);
  }
  /* USER CODE END RFID_entry */
}

/* USER CODE BEGIN Header_LED_entry */
/**
* @brief Function implementing the LED thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED_entry */
void LED_entry(void const * argument)
{
  /* USER CODE BEGIN LED_entry */
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
    HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
//    Delay_ms(1000);
//    LED_Blink();
    osDelay(1000);
  }
  /* USER CODE END LED_entry */
}

/* USER CODE BEGIN Header_Door_entry */
/**
* @brief Function implementing the Door thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Door_entry */
void Door_entry(void const * argument)
{
  /* USER CODE BEGIN Door_entry */
  /* Infinite loop */
  for(;;)
  {
    //Open_Door();
    //osDelay(300);
    //Close_Door();


    osDelay(3000);
  }
  /* USER CODE END Door_entry */
}

/* USER CODE BEGIN Header_ESP32_entry */
/**
* @brief Function implementing the ESP32 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ESP32_entry */
void ESP32_entry(void const * argument)
{
  /* USER CODE BEGIN ESP32_entry */
    char cmd[1024] = {0};
    strcpy(cmd, "AT\r\n");
  /* Infinite loop */
  for(;;)
  {


    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0x10);
    osDelay(3000);
  }
  /* USER CODE END ESP32_entry */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */