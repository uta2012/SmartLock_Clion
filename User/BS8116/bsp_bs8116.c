#include "bsp_bs8116.h"

/*****************************************************
函数功能：读取按键的信息
函数形参：void
函数返回值：uint8_t
函数说明：
*****************************************************/
uint8_t Bs8116_ReadKey(void)
{
    uint16_t key = 0;
    Bs8116_Iic_Start(BS8116_DELAYTIME);
    if(Bs8116_Iic_SendByte(BS8116_WRITEADDRESS,BS8116_DELAYTIME))
    {
        Bs8116_Iic_Stop(BS8116_DELAYTIME);
        return 1;
    }
    while(!BS8116_IIC_SCL);//等待不忙

    if(Bs8116_Iic_SendByte(0x08,BS8116_DELAYTIME))
    {
        Bs8116_Iic_Stop(BS8116_DELAYTIME);
        return 2;
    }
    while(!BS8116_IIC_SCL);//等待不忙
    Bs8116_Iic_Start(BS8116_DELAYTIME);
    if(Bs8116_Iic_SendByte(BS8116_READADDRESS,BS8116_DELAYTIME))
    {
        Bs8116_Iic_Stop(BS8116_DELAYTIME);
        return 3;
    }
    while(!BS8116_IIC_SCL);//等待不忙
    key = Bs8116_Iic_ReceiveByte(0,BS8116_DELAYTIME);
    key = Bs8116_Iic_ReceiveByte(1,BS8116_DELAYTIME) << 8 | key;
    Bs8116_Iic_Stop(BS8116_DELAYTIME);
    switch(key)
    {
        case 0X8081:return   '1';//1000 0000 1000 0001
        case 0X8480:return   '2';//1000 0100 1000 0000
        case 0X8080:return   '3';//1000 0000 1000 0000
        case 0X8082:return   '4';//1000 1000 1000 1010
        case 0X8880:return   '5';//1000 1000 1000 0000
        case 0X80C0:return   '6';//1000 0000 1100 0000
        case 0X8088:return   '7';//1000 0000 1000 1000
        case 0X8180:return   '8';
        case 0X80A0:return   '9';
        case 0X8084:return   '*';
        case 0X8280:return   '0';
        case 0X8090:return   '#';
    }
    return 0xff;
}



/*****************************************************
函数功能：起始条件
函数形参：uint16_t nus
函数返回值：void
函数说明：	在时钟线处于高电平期间，数据线产生了一个下降沿
*****************************************************/
    void Bs8116_Iic_Start(uint8_t nus)
    {
        BS8116_IIC_SCL_L;
        Delay_us(nus);//保证先是从低电平开始

        BS8116_IIC_SDA_H;
        BS8116_IIC_SCL_H;
        Delay_us(nus);//起始条件的建立时间
        BS8116_IIC_SDA_L;
        Delay_us(nus);//起始条件的保持时间
        BS8116_IIC_SCL_L;
    }

/*****************************************************
函数功能：停止条件
函数形参：uint16_t nus
函数返回值：void
函数说明：在时钟线处于高电平期间，数据线产生了一个上升沿
*****************************************************/
    void Bs8116_Iic_Stop(uint8_t nus)
    {
        BS8116_IIC_SDA_L;
        BS8116_IIC_SCL_H;
        Delay_us(nus);//停止条件的建立时间
        BS8116_IIC_SDA_H;
        Delay_us(nus);//停止和启动条件之间的总线空闲时间
    }

/*****************************************************
函数功能：发送一个应答位
函数形参：	uint8_t ack
			uint16_t nus
函数返回值：void
函数说明：上升沿时接收数据，下降沿时发送数据
*****************************************************/
    void Bs8116_Iic_SendAck(uint8_t ack,uint8_t nus)
    {
        BS8116_IIC_SCL_L;
        if(ack)
        {
            BS8116_IIC_SDA_H;
        }
        else
        {
            BS8116_IIC_SDA_L;
        }
        Delay_us(nus);//数据的准备时间
        BS8116_IIC_SCL_H;
        Delay_us(nus);//接收方接收数据需要的时间
//	BS8116_IIC_SCL_L;
//	Delay_us(nus);//保证周期的完整
    }

/*****************************************************
函数功能：接收一个应答位
函数形参：	uint16_t nus
函数返回值：void
函数说明：
*****************************************************/
    uint8_t Bs8116_Iic_ReceiveAck(uint8_t nus)
    {
        BS8116_IIC_SDA_H;//断开输出电路
        uint8_t ack = 0;
        BS8116_IIC_SCL_L;
        Delay_us(nus);//数据的准备时间
        BS8116_IIC_SCL_H;
        if(BS8116_IIC_SDA)
        {
            ack = 1;
        }
        Delay_us(nus);//接收方接收数据需要的时间
//	BS8116_IIC_SCL_L;
//	Delay_us(nus);//保证周期的完整
        return ack;
    }

/*****************************************************
函数功能：发送一个字节并接收一个应答位
函数形参：
			uint8_t data
			uint16_t nus
函数返回值：uint8_t
函数说明：
*****************************************************/
    uint8_t Bs8116_Iic_SendByte(uint8_t data,uint8_t nus)
    {
        uint8_t ack;
        uint8_t i;
        for(i = 0; i < 8; i++)
        {
            BS8116_IIC_SCL_L;
            if(data & 0x80 >>i)
            {
                BS8116_IIC_SDA_H;
            }
            else
                BS8116_IIC_SDA_L;
            Delay_us(nus);//数据的准备时间
            BS8116_IIC_SCL_H;
            Delay_us(nus);//接收方接收数据需要的时间
        }
        ack = Bs8116_Iic_ReceiveAck(nus);
        return ack;
    }

/*****************************************************
函数功能：接收一个字节并发送一个应答位
函数形参：
			uint8_t ack
			uint8_t nus
函数返回值：uint8_t
函数说明：
*****************************************************/
    uint8_t Bs8116_Iic_ReceiveByte(uint8_t ack,uint8_t nus)
    {
        uint8_t i;
        uint8_t buf = 0;
        BS8116_IIC_SDA_H;//断开输出电路
        for(i = 0; i < 8; i++)
        {
            BS8116_IIC_SCL_L;
            Delay_us(nus);//数据的准备时间
            BS8116_IIC_SCL_H;
            buf <<= 1;//空出最低位
            if(BS8116_IIC_SDA)
            {
                buf |= 1;
            }
            Delay_us(nus);//接收方接收数据需要的时间
        }
        Bs8116_Iic_SendAck(ack,nus);
        return buf;
    }





void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == BS8116_IRQ_Pin)
    {

        printf("%d\n",Bs8116_ReadKey());
    }

}



