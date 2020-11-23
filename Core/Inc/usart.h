/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "fatfs.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
#define RXBUFLEN 128
#define FORMATOFLOGDIR      ("%s20%02d.%02d.%02d")
typedef enum
{
  IDLE = 0,
  MOUNT,
  WRITE,
  PRINTF,
  READ,
  DELETE,
  REMOVEDIR,
  FORMAT,
  DISKFREE,
  LISTDISK,
}teFUNC;
extern uint8_t RxBuf[RXBUFLEN];
extern uint8_t flag;
void My_UART_IRQHandler(UART_HandleTypeDef *huart);
void DeleteEarlyLog(void);
void CalStorage(void);
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
