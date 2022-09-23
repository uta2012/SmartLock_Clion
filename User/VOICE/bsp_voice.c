#include "bsp_voice.h"


/*****************************************************
函数功能：同步头
函数形参：void
函数返回值：void
函数说明：8ms的高电平维持时间 + 1ms低电平维持时间
*****************************************************/
void Voice_Synchronous(void)
{
    VOICE_DATA_H;
    Delay_ms(8);
    VOICE_DATA_L;
    Delay_ms(1);
}

/*****************************************************
函数功能：发送一位1
函数形参：void
函数返回值：void
函数说明：1.5ms的高电平维持时间 + 0.5ms低电平维持时间
*****************************************************/
void Voice_SendH(void)
{
    VOICE_DATA_H;
    Delay_us(1500);
    VOICE_DATA_L;
    Delay_us(500);
}

/*****************************************************
函数功能：发送一位0
函数形参：void
函数返回值：void
函数说明：0.5ms的高电平维持时间 + 1.5ms低电平维持时间
*****************************************************/
void Voice_SendL(void)
{
    VOICE_DATA_H;
    Delay_us(500);
    VOICE_DATA_L;
    Delay_us(1500);
}

/*****************************************************
函数功能：发送指令
函数形参：uint8_t cmd
函数返回值：void
函数说明：
*****************************************************/
void Voice_Sendcmd(uint8_t cmd)
{
    uint8_t i;
    Voice_Synchronous();
    for(i = 0; i < 8; i++)
    {
        if(cmd & 0x80 >> i)
        {
            Voice_SendH();
        }
        else
            Voice_SendL();
    }
    VOICE_DATA_L;
}
