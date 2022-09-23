#include "bsp_esp32.h"


void ESP_Init(void)
{
//    HAL_GPIO_WritePin(ESP_01S_EN_GPIO_Port, ESP_01S_EN_Pin, GPIO_PIN_SET);
//    HAL_Delay(50);
//    HAL_GPIO_WritePin(ESP_01S_RST_GPIO_Port, ESP_01S_RST_Pin, GPIO_PIN_RESET);
//    HAL_Delay(50);
//    HAL_GPIO_WritePin(ESP_01S_RST_GPIO_Port, ESP_01S_RST_Pin, GPIO_PIN_SET);
    char cmd[1024] = {0};
    strcpy(cmd, "AT\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0xFF);
    HAL_Delay(1000);


    strcpy(cmd, "AT+RESTORE\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0xFF);
    HAL_Delay(2000);


    strcpy(cmd, "AT+CWMODE=1\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0xFF);
    HAL_Delay(1000);

    strcpy(cmd, "AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0xFF);
    HAL_Delay(1000);

    strcpy(cmd, "AT+CWJAP=\"GDOU-045\",\"abc123456\"\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0xFF);
    HAL_Delay(5000);

    strcpy(cmd, "AT+CIPSNTPCFG=1,8,\"ntp1.aliyun.com\"\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0xFF);
    HAL_Delay(1000);

    strcpy(cmd, "AT+MQTTUSERCFG=0,1,\"NULL\",\"ESP_8266&hnpjzh7bv2r\",\"2434f933fbf998f5a448d0b81eb367ca652a55e76d87c5527dd7d3483eab6c04\",0,0,\"\"\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0xFF);
    HAL_Delay(1000);

    strcpy(cmd, "AT+MQTTCLIENTID=0,\"hnpjzh7bv2r.ESP_8266|securemode=2\\,signmethod=hmacsha256\\,timestamp=1663569205448|\"\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0xFF);
    HAL_Delay(1000);

    strcpy(cmd, "AT+MQTTCONN=0,\"a1Py84SEWWJ.iot-as-mqtt.cn-shanghai.aliyuncs.com\",1883,1\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0xFF);
    strcpy(cmd, "+MQTTCONNECTED:0,1,\"iot-06z00fu5hrbf7c5.mqtt.iothub.aliyuncs.com\",\"1883\",\"\",1\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0xFF);
    HAL_Delay(5000);

    strcpy(cmd, "AT+MQTTSUB=0,\"/hnpjzh7bv2r/ESP_8266/user/MyTopic\",1\r\n");
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd) , 0xFF);
    HAL_Delay(5000);
}



uint8_t a;
uint8_t b;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART2)
    {

        HAL_UART_Transmit(&huart1, &b, 1, 0);
        HAL_UART_Receive_IT(&huart2, &b, 1);
    }

//    if(huart->Instance == USART1)
//    {
//
//        HAL_UART_Transmit(&huart1, &a, 1, 0);
//        HAL_UART_Receive_IT(&huart1, &a, 1);
//    }


}




