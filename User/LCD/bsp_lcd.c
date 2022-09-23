#include "bsp_lcd.h"



/*
**********************************************************************
函数功能：spi数据交换的函数(主机发送一个字节数据给从机，并且读取从机发送过来的一个字节数据)
函数形参：主机要发送给从机的数据
函数返回值：主机读到从机数据
备注：数据位8bit  先高后低的顺序
**********************************************************************
*/
void SPI2TransferByte(uint8_t data)
{
    //uint8_t buf = 0;
    //HAL_SPI_Receive(&hspi2, &buf, 1, 0xFF);
    HAL_SPI_Transmit(&hspi2, &data, 1, 0xFF);
    //return buf;
}


/*
**********************************************************************
函数功能：发送命令到LCD屏
函数形参：uint8_t data
函数返回值：
备注：
**********************************************************************
*/
void st7789vm_write_command(uint8_t data)
{
    LCD_CS_L;//先拉低片选
    LCD_COMMAND;//表示发送的是命令
    SPI2TransferByte(data);//具体发送的8位 命令
    LCD_CS_H;//拉高片选
}


/*
**********************************************************************
函数功能：发送8位数据到LCD屏
函数形参：uint8_t data
函数返回值：
备注：
**********************************************************************
*/
void st7789vm_write_command_parameter(uint8_t data)
{
    LCD_CS_L;//先拉低片选
    LCD_DATA;//表示发送的数据
    SPI2TransferByte(data);//具体发送的数据
    LCD_CS_H;//拉高片选
}


/*
**********************************************************************
函数功能：发送16位数据到LCD屏
函数形参：uint16_t data
函数返回值：
备注：
**********************************************************************
*/
void st7789vm_write_data(uint16_t data)
{
    LCD_CS_L;//先拉低片选
    LCD_DATA;//表示发送的数据
    SPI2TransferByte(data >> 8);//先发高8位
    SPI2TransferByte(data & 0xff);//再发低8位
    LCD_CS_H;//拉高片选
}

/*
**********************************************************************
函数功能：设置位置的函数
函数形参：uint16_t data
函数返回值：uint16_t sx -- X轴的起始点
			uint16_t sy -- Y轴的起始点
			uint16_t ex -- X轴的终点
			uint16_t ey -- Y轴的终点
备注：
**********************************************************************
*/
void st7789vm_setpostion(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey)
{
    //设置列地址
    st7789vm_write_command(0X2A);
    st7789vm_write_data(sx);
    st7789vm_write_data(ex);

    //设置行地址
    st7789vm_write_command(0X2B);
    st7789vm_write_data(sy);
    st7789vm_write_data(ey);

    st7789vm_write_command(0X2C);//把数据写入进去
}






/*
**********************************************************************
函数功能：清屏函数
函数形参：uint16_t data
函数返回值：uint16_t sx -- X轴的起始点
			uint16_t sy -- Y轴的起始点
			uint16_t ex -- X轴的终点
			uint16_t ey -- Y轴的终点
			uint16_t color --清屏的颜色
备注：
**********************************************************************
*/
void st7789vm_clear_display(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,uint16_t color)
{
    uint32_t i;
    st7789vm_setpostion(sx,sy,ex,ey);
    for(i = 0; i < 240*240; i++)
    {
        st7789vm_write_data(color);
    }

}


void st7789vm_init(void)
{

    /* 复位ST7789VM驱动器 */
    LCD_RES_L;
    Delay_ms(100);
    LCD_RES_H;
    Delay_ms(100);

    /* start initial sequence */
    st7789vm_write_command(0x36);
    st7789vm_write_command_parameter(0x00);

    st7789vm_write_command(0x3A);
    st7789vm_write_command_parameter(0x05);

    st7789vm_write_command(0xB2);
    st7789vm_write_command_parameter(0x0C);
    st7789vm_write_command_parameter(0x0C);
    st7789vm_write_command_parameter(0x00);
    st7789vm_write_command_parameter(0x33);
    st7789vm_write_command_parameter(0x33);

    st7789vm_write_command(0xB7);
    st7789vm_write_command_parameter(0x35);

    st7789vm_write_command(0xBB);
    st7789vm_write_command_parameter(0x19);

    st7789vm_write_command(0xC0);
    st7789vm_write_command_parameter(0x2C);

    st7789vm_write_command(0xC2);
    st7789vm_write_command_parameter(0x01);

    st7789vm_write_command(0xC3);
    st7789vm_write_command_parameter(0x12);

    st7789vm_write_command(0xC4);
    st7789vm_write_command_parameter(0x20);

    st7789vm_write_command(0xC6);
    st7789vm_write_command_parameter(0x0F);

    st7789vm_write_command(0xD0);
    st7789vm_write_command_parameter(0xA4);
    st7789vm_write_command_parameter(0xA1);

    st7789vm_write_command(0xE0);
    st7789vm_write_command_parameter(0xD0);
    st7789vm_write_command_parameter(0x04);
    st7789vm_write_command_parameter(0x0D);
    st7789vm_write_command_parameter(0x11);
    st7789vm_write_command_parameter(0x13);
    st7789vm_write_command_parameter(0x2B);
    st7789vm_write_command_parameter(0x3F);
    st7789vm_write_command_parameter(0x54);
    st7789vm_write_command_parameter(0x4C);
    st7789vm_write_command_parameter(0x18);
    st7789vm_write_command_parameter(0x0D);
    st7789vm_write_command_parameter(0x0B);
    st7789vm_write_command_parameter(0x1F);
    st7789vm_write_command_parameter(0x23);

    st7789vm_write_command(0xE1);
    st7789vm_write_command_parameter(0xD0);
    st7789vm_write_command_parameter(0x04);
    st7789vm_write_command_parameter(0x0C);
    st7789vm_write_command_parameter(0x11);
    st7789vm_write_command_parameter(0x13);
    st7789vm_write_command_parameter(0x2C);
    st7789vm_write_command_parameter(0x3F);
    st7789vm_write_command_parameter(0x44);
    st7789vm_write_command_parameter(0x51);
    st7789vm_write_command_parameter(0x2F);
    st7789vm_write_command_parameter(0x1F);
    st7789vm_write_command_parameter(0x1F);
    st7789vm_write_command_parameter(0x20);
    st7789vm_write_command_parameter(0x23);

    st7789vm_write_command(0x21);
    st7789vm_write_command(0x11);
    st7789vm_write_command(0x29);

    /* 清空屏幕显示 */
    st7789vm_clear_display(0, 0, 239, 239, WHITE);

    /* 开启背光 */
    LCD_LED_H;
}

/*
**********************************************************************
函数功能：画点的函数
函数形参：
			uint16_t x -- 起始的x轴
			uint16_t y -- 起始的y轴
			uint16_t font_color -- 字体的颜色
函数返回值：
备注：
**********************************************************************
*/
void Diplay_Onepoint(uint16_t x,uint16_t y,uint16_t font_color)
{
    st7789vm_setpostion(x,y,x,y);//在某一个点开始
    st7789vm_write_data(font_color);
}


/*
**********************************************************************
函数功能：显示单个字符
函数形参：
			uint16_t x -- 起始的x轴
			uint16_t y -- 起始的y轴
			uint16_t font_color -- 字体的颜色
			uint16_t back_color -- 背景的颜色
			uint8_t fonsize -- 字体的大小
			uint8_t *eng -- 显示的数据
函数返回值：
备注：
**********************************************************************
*/
void Display_eng(uint16_t x,uint16_t y,uint16_t font_color,uint16_t back_color,uint8_t fonsize,const uint8_t *eng)
{
    uint8_t i,j,k;
    uint8_t weight = 0;
    weight = fonsize / 2 / 8;//得到一行的字节的数量
    if(fonsize/2 %8)
    {
        weight += 1;
    }
    for(i = 0; i < fonsize; i++)//这个字一共的循环的行数
    {
        for(k = 0; k < weight; k++)
        {
            for(j = 0; j < 8; j++)//这一行需要判断几个位
            {
                if(eng[i*weight+k] & 0x80 >> j)//如果判断到某一位为1则是字体颜色
                {
                    Diplay_Onepoint(x+j+8*k,y+i,font_color);
                }
                else
                {
                    Diplay_Onepoint(x+j+8*k,y+i,back_color);//否则为背景颜色
                }
            }
        }
    }
}

/*
**********************************************************************
函数功能：显示单个中文字符
函数形参：
			uint16_t x -- 起始的x轴
			uint16_t y -- 起始的y轴
			uint16_t font_color -- 字体的颜色
			uint16_t back_color -- 背景的颜色
			uint8_t fonsize -- 字体的大小
			uint8_t *chi -- 显示的数据
函数返回值：
备注：
**********************************************************************
*/
void Display_chi(uint16_t x,uint16_t y,uint16_t font_color,uint16_t back_color,uint8_t fonsize,const uint8_t *chi)
{
    uint8_t i,j,k;
    uint8_t weight = 0;
    weight = fonsize / 8;//得到一行的字节的数量
    if(fonsize%8)
    {
        weight += 1;
    }

    for(i = 0; i < fonsize; i++)//这个字一共的循环的行数
    {
        for(k = 0; k < weight; k ++)//k代表循环完这一行的所有字节
        {
            for(j = 0; j < 8; j++)//这一行需要判断几个位
            {
                if(chi[i*weight+k] & 0x80 >> j)//如果判断到某一位为1则是字体颜色
                {
                    Diplay_Onepoint(x+j+8*k ,y+i,font_color);
                }
                else
                {
                    Diplay_Onepoint(x+j+8*k,y+i,back_color);//否则为背景颜色
                }
            }
        }
    }

}


/*
**********************************************************************
函数功能：清屏函数
函数形参：
			uint16_t sx -- X轴的起始点
			uint16_t sy -- Y轴的起始点
			uint8_t *pic -- 图片数据信息
函数返回值：

备注：
**********************************************************************
*/
void Display_Pic(uint16_t sx, uint16_t sy, const uint8_t *pic)
{
    uint32_t i;
    uint16_t weight = pic[2] << 8 | pic[3];
    uint16_t height = pic[4] << 8 | pic[5];

    st7789vm_setpostion(sx,sy,weight+sx,height+sy);
    for(i = 0; i < weight*height; i++)
    {
        st7789vm_write_data(pic[8+i*2] << 8 | pic[8+i*2+1]);
    }

}