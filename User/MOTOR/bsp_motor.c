#include "bsp_motor.h"


uint8_t lock_status = 0;//0 is open status,and 1 is close status


void Door_Init(void)
{
    HAL_GPIO_WritePin(MOTOR_IB_GPIO_Port, MOTOR_IB_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IA_GPIO_Port, MOTOR_IA_Pin, GPIO_PIN_RESET);

    Close_Door();
    HAL_Delay(200);
    Open_Door();
}



/*****************************************************
函数功能：开门
函数形参：void
函数返回值：void
函数说明：
*****************************************************/
void Open_Door(void)
{
    HAL_GPIO_WritePin(MOTOR_IA_GPIO_Port, MOTOR_IA_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IB_GPIO_Port, MOTOR_IB_Pin, GPIO_PIN_SET);

    Delay_ms(200);
    HAL_GPIO_WritePin(MOTOR_IA_GPIO_Port, MOTOR_IA_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IB_GPIO_Port, MOTOR_IB_Pin, GPIO_PIN_RESET);

}

/*****************************************************
函数功能：关门
函数形参：void
函数返回值：void
函数说明：
*****************************************************/
void Close_Door(void)
{
    HAL_GPIO_WritePin(MOTOR_IA_GPIO_Port, MOTOR_IA_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(MOTOR_IB_GPIO_Port, MOTOR_IB_Pin, GPIO_PIN_RESET);

    Delay_ms(200);
    HAL_GPIO_WritePin(MOTOR_IA_GPIO_Port, MOTOR_IA_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IB_GPIO_Port, MOTOR_IB_Pin, GPIO_PIN_RESET);
}

///*****************************************************
//函数功能：开门
//函数形参：void
//函数返回值：void
//函数说明：
//*****************************************************/
//void Pwm_Open_Door(void)
//{
//
////    TIM_Cmd(TIM3,ENABLE);
////    Delay_ms(200);
////    TIM_Cmd(TIM3,DISABLE);
//
//}
//
///*****************************************************
//函数功能：关门
//函数形参：void
//函数返回值：void
//函数说明：
//*****************************************************/
//void Pwm_Close_Door(void)
//{
////    TIM_Cmd(TIM2,ENABLE);
////    Delay_ms(200);
////    TIM_Cmd(TIM2,DISABLE);
//}

extern osMessageQId Door_LockHandle;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint8_t i = 1;//1是锁门 0是开门
    if(GPIO_Pin == GPIO_PIN_13)
    {

        xQueueSendToBackFromISR(Door_LockHandle, &i, 0);
    }

}



