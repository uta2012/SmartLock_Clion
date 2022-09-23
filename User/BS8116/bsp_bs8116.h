#ifndef BS8116_H_
#define BS8116_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "stdio.h"
#include "gpio.h"

#define BS8116_DELAYTIME 5
#define BS8116_WRITEADDRESS  0XA0
#define BS8116_READADDRESS   0XA1

#define BS8116_IIC_SCL  (HAL_GPIO_ReadPin(BS8116_IIC1_SCLK_GPIO_Port, BS8116_IIC1_SCLK_Pin))


#define BS8116_IRQ      (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1))



#define BS8116_IIC_SCL_L  HAL_GPIO_WritePin(BS8116_IIC1_SCLK_GPIO_Port, BS8116_IIC1_SCLK_Pin, GPIO_PIN_RESET)

#define BS8116_IIC_SCL_H  HAL_GPIO_WritePin(BS8116_IIC1_SCLK_GPIO_Port, BS8116_IIC1_SCLK_Pin, GPIO_PIN_SET)

#define BS8116_IIC_SDA_L HAL_GPIO_WritePin(BS8116_IIC1_SDA_GPIO_Port, BS8116_IIC1_SDA_Pin, GPIO_PIN_RESET)

#define BS8116_IIC_SDA_H  HAL_GPIO_WritePin(BS8116_IIC1_SDA_GPIO_Port, BS8116_IIC1_SDA_Pin, GPIO_PIN_SET)

#define BS8116_IIC_SDA  (HAL_GPIO_ReadPin(BS8116_IIC1_SDA_GPIO_Port, BS8116_IIC1_SDA_Pin))



uint8_t Bs8116_ReadKey(void);


void Bs8116_Iic_Port_Init(void);
void Bs8116_Iic_Start(uint8_t nus);
void Bs8116_Iic_Stop(uint8_t nus);
uint8_t Bs8116_Iic_SendByte(uint8_t data,uint8_t nus);
uint8_t Bs8116_Iic_ReceiveByte(uint8_t ack,uint8_t nus);


#endif //BS8116_H_