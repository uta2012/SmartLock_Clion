#include "bsp_rfid.h"

//
// M1卡分为16个扇区，每个扇区由四个块（块0、块1、块2、块3）组成
// 将16个扇区的64个块按绝对地址编号为：0~63
// 第0个扇区的块0（即绝对地址0块），用于存放厂商代码，已经固化不可更改
// 每个扇区的块0、块1、块2为数据块，可用于存放数据
// 每个扇区的块3为控制块（绝对地址为:块3、块7、块11.....）包括密码A，存取控制、密码B等




uint8_t CardId[4];//卡号
uint8_t CardType[2];//卡类型
uint8_t writeDataBuf[16]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0,1,2,3,4,0xff,0xff,0xff}; //写入的数据
uint8_t KEY[6]={0xff,0xff,0xff,0xff,0xff,0xff}; //卡密码-初始密码--白卡的出厂密码--



/*
**********************************************************************
函数功能：spi数据交换的函数(主机发送一个字节数据给从机，并且读取从机发送过来的一个字节数据)
函数形参：主机要发送给从机的数据
函数返回值：主机读到从机数据
备注：数据位8bit  先高后低的顺序
**********************************************************************
*/


void SPI3TransferByte(uint8_t data)
{
    //uint8_t buff;
    HAL_SPI_Transmit(&hspi3, &data, 1, 0xFF);
    //HAL_SPI_Receive(&hspi3, &buff, 1, 0xFF);
    //return buff;
}

uint8_t SPI3ReceiveByte(void)
{
    uint8_t buff;
//    HAL_SPI_Transmit(&hspi3, &data, 1, 0xFF);
    HAL_SPI_Receive(&hspi3, &buff, 1, 0xFF);
    return buff;
}



//读RC632寄存器
//Address:寄存器地址
uint8_t ReadRawRC(uint8_t Address)
{
	uint8_t ucAddr;
	uint8_t ucResult=0;
	RIFD_CS_RESET();
	ucAddr = ((Address<<1)&0x7E)|0x80;

	SPI3TransferByte(ucAddr);
	ucResult=SPI3ReceiveByte();
	RIFD_CS_SET();
	return ucResult;
}


//写RC632寄存器
//Address[IN]:寄存器地址
//value[IN]:写入的值
void WriteRawRC(uint8_t Address, uint8_t value)
{  
    uint8_t ucAddr;

	RIFD_CS_RESET();
    ucAddr = ((Address<<1)&0x7E);//0111 1110

	SPI3TransferByte(ucAddr);
	SPI3TransferByte(value);
	RIFD_CS_SET();
}

//清寄存器位
void ClearBitMask(uint8_t reg,uint8_t mask)// 0000 1000
{
    char   tmp = 0x0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg, tmp & ~mask);  // clear bit mask
} 

//置RC522寄存器位
//reg[IN]:寄存器地址
//mask[IN]:置位值
void SetBitMask(uint8_t reg,uint8_t mask)
{
    char   tmp = 0x0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg,tmp | mask);  // set bit mask
}


//复位RC522
char PcdReset(void)
{
	RIFD_RES_SET();
	Delay_us(2);

    RIFD_RES_RESET();
	Delay_us(2);
	
	RIFD_RES_SET();
	Delay_us(2);
	WriteRawRC(CommandReg,PCD_RESETPHASE);
	WriteRawRC(CommandReg,PCD_RESETPHASE);
	Delay_us(2);
    
	WriteRawRC(ModeReg,0x3D);            //和Mifare卡通讯，CRC初始值0x6363
	WriteRawRC(TReloadRegL,30);           
	WriteRawRC(TReloadRegH,0);
	WriteRawRC(TModeReg,0x8D);
	WriteRawRC(TPrescalerReg,0x3E);
	
	WriteRawRC(TxAutoReg,0x40);//必须要
   
   return MI_OK;
	
}

//关闭天线
void PcdAntennaOff(void)
{
	ClearBitMask(TxControlReg, 0x03);
}

//开启天线
void PcdAntennaOn(void)
{
    uint8_t   i;
    i = ReadRawRC(TxControlReg);
    if (!(i & 0x03))
    {
        SetBitMask(TxControlReg, 0x03);
    }
}


void Reset_RC522(void)
{
	PcdReset();       //功    能：复位RC522
	PcdAntennaOff();  //关闭天线
	PcdAntennaOn();   //开启天线
}    

//设置RC522工作模式
char M500PcdConfigISOType(uint8_t type)
{
   if (type == 'A')                     //ISO14443_A
   { 
			ClearBitMask(Status2Reg,0x08);
			WriteRawRC(ModeReg,0x3D);//3F
			WriteRawRC(RxSelReg,0x86);//84
			WriteRawRC(RFCfgReg,0x7F);   //4F
			WriteRawRC(TReloadRegL,30);//tmoLength);// TReloadVal = 'h6a =tmoLength(dec) 
			WriteRawRC(TReloadRegH,0);
			WriteRawRC(TModeReg,0x8D);
			WriteRawRC(TPrescalerReg,0x3E);
			Delay_us(2);
			PcdAntennaOn();
   }
   else{ return 1; }
   
   return MI_OK;
}

void RFID_Init(void)
{

	Reset_RC522();
	M500PcdConfigISOType('A');
}

/*******************************************************************
* 函数名：     PcdComMF522()
* 功能描述 ：  通过RC522和ISO14443卡通讯
* 作者：         谢国卿 
* 参数说明:   Command[IN]:RC522命令字
							pIn [IN]:通过RC522发送到卡片的数据
							InLenByte[IN]:发送数据的字节长度
							pOut [OUT]:接收到的卡片返回数据
							*pOutLenBit[OUT]:返回数据的位长度
* 返回值说明：
* 修改记录：
* 其他：
*******************************************************************/
char PcdComMF522(uint8_t   Command,
                 uint8_t *pIn ,
                 uint8_t   InLenByte,
                 uint8_t *pOut ,
                 uint8_t *pOutLenBit)
{
    char   status = MI_ERR;
    uint8_t   irqEn   = 0x00;
    uint8_t   waitFor = 0x00;
    uint8_t   lastBits;
    uint8_t   n;
    uint16_t   i;
    switch (Command)
    {
        case PCD_AUTHENT:
                    irqEn   = 0x12;
                    waitFor = 0x10;
                    break;
		case PCD_TRANSCEIVE:
                    irqEn   = 0x77;
                    waitFor = 0x30;
                    break;
		default:	break;
    }
   
    WriteRawRC(ComIEnReg,irqEn|0x80);
    ClearBitMask(ComIrqReg,0x80);	//清所有中断位
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);	 	//清FIFO缓存
    
    for (i=0; i<InLenByte; i++)
    {   WriteRawRC(FIFODataReg, pIn [i]);    }
    WriteRawRC(CommandReg, Command);	  
//   	 n = ReadRawRC(CommandReg);
    
    if (Command == PCD_TRANSCEIVE)
    {    SetBitMask(BitFramingReg,0x80);  }	 //开始传送
    										 
      i = 600;//根据时钟频率调整，操作M1卡最大等待时间25ms
// 	  i = 100000;
    do 
    {
        n = ReadRawRC(ComIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitFor));
    ClearBitMask(BitFramingReg,0x80);

    if (i!=0)
    {    
        if(!(ReadRawRC(ErrorReg)&0x1B))
        {
            status = MI_OK;
            if (n & irqEn & 0x01)
            {   status = MI_NOTAGERR;   }
            if (Command == PCD_TRANSCEIVE)
            {
               	n = ReadRawRC(FIFOLevelReg);
              	lastBits = ReadRawRC(ControlReg) & 0x07;
                if (lastBits)
                {   *pOutLenBit = (n-1)*8 + lastBits;   }
                else
                {   *pOutLenBit = n*8;   }
                if (n == 0)
                {   n = 1;    }
                if (n > MAXRLEN)
                {   n = MAXRLEN;   }
                for (i=0; i<n; i++)
                {   pOut [i] = ReadRawRC(FIFODataReg);    }
            }
        }
        else
        {   status = MI_ERR;   }
        
    }
   

    SetBitMask(ControlReg,0x80);           // stop timer now
    WriteRawRC(CommandReg,PCD_IDLE); 
    return status;
}

/*******************************************************************
* 函数名：     PcdRequest()
* 功能描述 ：   	寻卡
* 作者：         谢国卿 
*参数说明: req_code[IN]:寻卡方式
                0x52 = 寻感应区内所有符合14443A标准的卡
                0x26 = 寻未进入休眠状态的卡
           pTagType[OUT]：卡片类型代码
                0x4400 = Mifare_UltraLight
                0x0400 = Mifare_One(S50)
                0x0200 = Mifare_One(S70)
                0x0800 = Mifare_Pro(X)
                0x4403 = Mifare_DESFire
* 返回值说明：成功返回MI_OK
* 修改记录：
* 其他：
*******************************************************************/               
char PcdRequest(uint8_t req_code,uint8_t *pTagType)
{
	char   status;  
	uint8_t   unLen;
	uint8_t   ucComMF522Buf[MAXRLEN];

	ClearBitMask(Status2Reg,0x08);
	WriteRawRC(BitFramingReg,0x07);
	SetBitMask(TxControlReg,0x03);
 
	ucComMF522Buf[0] = req_code;

	status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen);

	if ((status == MI_OK) && (unLen == 0x10))
	{    
		*pTagType     = ucComMF522Buf[0];
		*(pTagType+1) = ucComMF522Buf[1];
	}
	else
	{   status = MI_ERR;   }
   
	return status;
}


/*******************************************************************
* 函数名：     PcdAnticoll()
* 功能描述 ：   防冲撞
* 作者：         谢国卿 
* 参数说明：     pSnr[OUT]:卡片序列号，4字节
* 返回值说明：   成功返回MI_OK
* 修改记录：
* 其他：
*******************************************************************/
char PcdAnticoll(uint8_t *pSnr)
{
    char   status;
    uint8_t   i,snr_check=0;
    uint8_t   unLen;
    uint8_t   ucComMF522Buf[MAXRLEN];
    

    ClearBitMask(Status2Reg,0x08);
    WriteRawRC(BitFramingReg,0x00);
    ClearBitMask(CollReg,0x80);
 
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);

    if (status == MI_OK)
    {
    	 for (i=0; i<4; i++)
         {   
             *(pSnr+i)  = ucComMF522Buf[i];
             snr_check ^= ucComMF522Buf[i];
         }
         if (snr_check != ucComMF522Buf[i])
         {   status = MI_ERR;    }
    }
    
    SetBitMask(CollReg,0x80);
    return status;
}

/*******************************************************************
* 函数名：     CalulateCRC()
* 功能描述 ：  用MF522计算CRC16函数
* 作者：         谢国卿 
*参数说明: 
* 返回值说明： 
* 修改记录：
* 其他：
*******************************************************************/
void CalulateCRC(uint8_t *pIn ,uint8_t   len,uint8_t *pOut )
{
    uint8_t   i,n;
    ClearBitMask(DivIrqReg,0x04);
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);
    for (i=0; i<len; i++)
    {   WriteRawRC(FIFODataReg, *(pIn +i));   }
    WriteRawRC(CommandReg, PCD_CALCCRC);
    i = 0xFF;
    do 
    {
        n = ReadRawRC(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));
    pOut [0] = ReadRawRC(CRCResultRegL);
    pOut [1] = ReadRawRC(CRCResultRegM);
}

/*******************************************************************
* 函数名：     PcdSelect()
* 功能描述 ：   选定卡片
* 作者：         谢国卿 
* 参数说明：     pSnr[IN]:卡片序列号，4字节
* 返回值说明：   成功返回MI_OK
* 修改记录：
* 其他：
*******************************************************************/
char PcdSelect(const uint8_t *pSnr)
{
    char   status;
    uint8_t   i;
    uint8_t   unLen;
    uint8_t   ucComMF522Buf[MAXRLEN];
    
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x70;
    ucComMF522Buf[6] = 0;
    for (i=0; i<4; i++)
    {
    	ucComMF522Buf[i+2] = *(pSnr+i);
    	ucComMF522Buf[6]  ^= *(pSnr+i);
    }
    CalulateCRC(ucComMF522Buf,7,&ucComMF522Buf[7]);
  
    ClearBitMask(Status2Reg,0x08);

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,9,ucComMF522Buf,&unLen);
    
    if ((status == MI_OK) && (unLen == 0x18))
    {   status = MI_OK;  }
    else
    {   status = MI_ERR;    }

    return status;
}


void print_info(unsigned char *p,int cnt)
{
  int i;
  for(i=0;i<cnt;i++)
  {
		if(!i)
			printf("0x%02X ",p[i]);
		else
			printf("%02X ",p[i]);
  }
  printf("\r\n");
}

/**********************************************
**函数功能：寻卡--防冲撞--选卡

**参数说明: 
pTagType[OUT]：卡片类型代码(做输出参数)
**                0x4400 = Mifare_UltraLight
**                0x0400 = Mifare_One(S50)
**                0x0200 = Mifare_One(S70)
**                0x0800 = Mifare_Pro(X)
**                0x4403 = Mifare_DESFire
pSnr[OUT]:卡片序列号，4字节(做输出参数)

**返回值：成功返回MI_OK
**作者：weihao Mo
**********************************************/
uint8_t Identificate_Card(uint8_t *pTagType, uint8_t *pSnr)
{
  uint8_t status=MI_ERR;
	uint8_t STA=0;

   if(PcdRequest(PICC_REQALL,pTagType)==MI_OK)//寻卡成功
   {
      STA |=0x01;
      if(PcdAnticoll(pSnr)==MI_OK)/*防冲撞成功*/
      {
				STA |=0x02;
		
        if(PcdSelect(pSnr)==MI_OK)//选卡成功
        {
					STA |=0x04;
        }
      }
   }
	 
	 
	 if(STA==0x07)
		 status=MI_OK;
	 
  return status;
}

/*******************************************************************
* 函数名：     PcdAuthState()
* 功能描述 ：   验证卡片密码
* 作者：         
*参数说明: auth_mode[IN]: 密码验证模式
                 0x60 = 验证A密钥
                 0x61 = 验证B密钥 
								addr[IN]：块地址
								pKey[IN]：密码
								pSnr[IN]：卡片序列号，4字节
* 返回值说明：   成功返回MI_OK
* 修改记录：
* 其他：
*******************************************************************/             
char PcdAuthState(uint8_t  auth_mode,uint8_t addr,uint8_t *pKey,uint8_t *pSnr)
{
    char   status;
    uint8_t   unLen;
		uint8_t	 ucComMF522Buf[MAXRLEN];

    ucComMF522Buf[0] = auth_mode;
    ucComMF522Buf[1] = addr;
    memcpy(&ucComMF522Buf[2], pKey, 6); 
    memcpy(&ucComMF522Buf[8], pSnr, 4); 
    
    status = PcdComMF522(PCD_AUTHENT,ucComMF522Buf,12,ucComMF522Buf,&unLen);
    if ((status != MI_OK) || (!(ReadRawRC(Status2Reg) & 0x08)))
    {   status = MI_ERR;   }
    
    return status;
}

/*******************************************************************
* 函数名：     PcdWrite()
* 功能描述 ：   写数据到M1卡一块
* 作者：          
*参数说明: addr[IN]：块地址
           p [OUT]：读出的数据，16字节
* 返回值说明：   成功返回MI_OK
* 修改记录：
* 其他：
*******************************************************************/                  
char PcdWrite(uint8_t   addr,uint8_t *p )
{
    char   status;
    uint8_t   unLen;
    uint8_t   i,ucComMF522Buf[MAXRLEN];
    
    ucComMF522Buf[0] = PICC_WRITE;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
 
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {   status = MI_ERR;   }
        
    if (status == MI_OK)
    {
        //memcpy(ucComMF522Buf, p , 16);
        for (i=0; i<16; i++)
        {    
        	ucComMF522Buf[i] = *(p +i);   
        }
        CalulateCRC(ucComMF522Buf,16,&ucComMF522Buf[16]);

        status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,18,ucComMF522Buf,&unLen);
        if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
        {   status = MI_ERR;   }
    }
    
    return status;
}


/*
功能：写数据到指定块
参数：
uint8_t   auth_mode ：验证密码的类型。（分为PICC_AUTHENT1A和PICC_AUTHENT1B）
uint8_t   addr      ：数据存放的地址。每个扇区的0、1、2块是存放数据。3是存放密码。
一般填：0、1、2 、4、5、6、8、9、10----
uint8_t *Src_Key    ：原密码
uint8_t *data       ：新写入的数据
uint8_t *pSnr       ：卡号

数据一般格式：uint8_t writeDataBuf[16]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}; //写入的金额；

*/
uint8_t WriteCardData(uint8_t auth_mode,uint8_t addr,uint8_t *Src_Key,uint8_t *data,uint8_t *pSnr)
{
  int status=MI_ERR;

  /*1. 寻卡--防冲撞--选卡*/
  status=Identificate_Card(CardType,pSnr); 
  /*2. 验证卡密码*/
  if(status==MI_OK)
  {
    status =PcdAuthState(0x60,addr/4*4+3,Src_Key,pSnr);   //验证卡片密码 形参参数：验证方式，块地址，密码，卡许列号
  }
  if(status==MI_OK)
  {
    printf("密码验证成功!\r\n");
  }
  /*3. 写数据到卡*/
  if(status==MI_OK)
  {
    status=PcdWrite(addr,data); //写数据到第addr块，data入的数据值。
  }
  if(status==MI_OK)
  {
    printf("数据写入OK!\r\n");
  }
  return status;
}

/*******************************************************************
* 函数名：     PcdRead()
* 功能描述 ：   读取M1卡一块数据
* 作者：         谢国卿 
*参数说明: addr[IN]：块地址
           p [OUT]：读出的数据，16字节
* 返回值说明：   成功返回MI_OK
* 修改记录：
* 其他：
*******************************************************************/ 
char PcdRead(uint8_t addr,uint8_t *p)
{
    char   status;
    uint8_t   unLen;
    uint8_t   i,ucComMF522Buf[MAXRLEN];

    ucComMF522Buf[0] = PICC_READ;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf,2,&ucComMF522Buf[2]);
   
    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,4,ucComMF522Buf,&unLen);
    if ((status == MI_OK) && (unLen == 0x90))
 //   {   memcpy(p , ucComMF522Buf, 16);   }
    {
        for (i=0; i<16; i++)
        {    *(p +i) = ucComMF522Buf[i];   }
    }
    else
    {   status = MI_ERR;   }
    
    return status;
}

/*
功能：读数据到指定块
参数：
uint8_t   auth_mode ：验证密码的类型。（分为PICC_AUTHENT1A和PICC_AUTHENT1B）
uint8_t   addr      ：数据存放的地址。每个扇区的0、1、2块是存放数据。3是存放密码。
一般填：0、1、2 、4、5、6、8、9、10
uint8_t *Src_Key    ：原密码
uint8_t *data       ：读出的数据
uint8_t *pSnr       ：卡号

数据一般格式：uint8_t writeDataBuf[16]={255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255}; //写入的金额；

*/
uint8_t ReadCardData(uint8_t auth_mode,uint8_t addr,uint8_t *Src_Key,uint8_t *data,uint8_t *pSnr)
{
  int status;
	
  /*1. 寻卡--防冲撞--选卡*/
  status=Identificate_Card(CardType,pSnr);  
  /*2. 验证卡密码*/
  if(status==MI_OK)
  {
		printf("卡类型:");
		print_info(CardType,2);//打印类型
		printf("卡号:");
		print_info(pSnr,4);//打印卡号		
		
    status=PcdAuthState(auth_mode,addr/4*4+3,Src_Key,pSnr);   //验证卡片密码 形参参数：验证方式，块地址，密码，卡许列号
    printf("验证卡密码成功\r\n");
  }
  /*3. 读出数据*/
  if(status==MI_OK)
  {
    status=PcdRead(addr,data); //从第addr块读出数据值。
  }
  if(status==MI_OK)
  {
    printf("数据读出成功!\r\n");
  }
  return status;
}

