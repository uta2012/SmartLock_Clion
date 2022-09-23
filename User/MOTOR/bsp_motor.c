#include "bsp_motor.h"



void Door_Init(void)
{
    HAL_GPIO_WritePin(MOTOR_IB_GPIO_Port, MOTOR_IB_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_IA_GPIO_Port, MOTOR_IA_Pin, GPIO_PIN_RESET);

    Open_Door();
    HAL_Delay(200);
    Close_Door();
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
