#include "bsp_led.h"


void LED_Blink(void)
{
    HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
    HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);

    Delay_ms(1000);
}


