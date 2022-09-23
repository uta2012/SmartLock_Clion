#ifndef LCD_H_
#define LCD_H_

#include "stm32f4xx_hal.h"
#include "delay.h"
#include "spi.h"
#include "image.h"



#define LCD_RES_H 	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET)
#define LCD_RES_L 	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET)
#define LCD_CS_H	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)
#define LCD_CS_L	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define LCD_DATA	HAL_GPIO_WritePin(LCD_D_C_GPIO_Port, LCD_D_C_Pin, GPIO_PIN_SET)
#define LCD_COMMAND	HAL_GPIO_WritePin(LCD_D_C_GPIO_Port, LCD_D_C_Pin, GPIO_PIN_RESET)
#define LCD_LED_H	HAL_GPIO_WritePin(LCD_LEDK_GPIO_Port, LCD_LEDK_Pin, GPIO_PIN_SET)
#define LCD_LED_L	HAL_GPIO_WritePin(LCD_LEDK_GPIO_Port, LCD_LEDK_Pin, GPIO_PIN_RESET)




/* 颜色定义开始 */
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE           	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)
/* 颜色定义结束 */

void st7789vm_init(void);
void Display_eng(uint16_t x,uint16_t y,uint16_t font_color,uint16_t back_color,uint8_t fonsize,const uint8_t *eng);
void Display_chi(uint16_t x,uint16_t y,uint16_t font_color,uint16_t back_color,uint8_t fonsize,const uint8_t *chi);
void Display_Pic(uint16_t sx, uint16_t sy, const uint8_t *pic);
#endif //LCD_H_