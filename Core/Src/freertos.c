/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "sdio.h"
#include "ffex.h"
#include "crc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 2048);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  HAL_UART_Receive_DMA(&huart1, RxBuf, sizeof(RxBuf));
  uint8_t str[] = "Hello World!";
  uint8_t file[32] = {0};
  UINT wbyte = 0;
  BYTE work[_MAX_SS] = {0};
  FRESULT res = 0;
  strcat(strcat((char *)file, (char *)SDPath), "1.txt");
  /* Infinite loop */
  for(;;)
  {
    switch(flag)
    {
      case MOUNT:
      {
        flag = IDLE;
        res = f_mount(&SDFatFS, SDPath, 1); printf("mount:%d\r\n", res);
        res = f_mount(NULL, SDPath, 1); printf("unmount:%d\r\n", res);
        break;
      }
      case WRITE:
      {
        flag = IDLE;
        res = f_mount(&SDFatFS, SDPath, 1); printf("mount:%d\r\n", res);
        res = f_open(&SDFile, (char *)file, FA_OPEN_ALWAYS | FA_WRITE); printf("open:%d\r\n", res);
        res = f_write(&SDFile, str, sizeof(str), &wbyte); printf("write:%d\r\n", res);
        res = f_close(&SDFile); printf("close:%d\r\n", res);
        res = f_mount(NULL, SDPath, 1); printf("unmount:%d\r\n", res);
        printf("[%s]\r\n", file);
        break;
      }
      case PRINTF:
      {
        flag = IDLE;
        res = f_mount(&SDFatFS, SDPath, 1); printf("mount:%d\r\n", res);
        res = f_open(&SDFile, (char *)file, FA_OPEN_ALWAYS | FA_WRITE); printf("open:%d\r\n", res);
        res = f_printf(&SDFile, "20%d:%d:%d.%s", 20, 11, 23, "Monday"); printf("printf:%d\r\n", res);
        res = f_close(&SDFile); printf("close:%d\r\n", res);
        res = f_mount(NULL, SDPath, 1); printf("unmount:%d\r\n", res);
        break;
      }
      case READ:
      {
        flag = IDLE;

        break;
      }
      case DELETE:
      {
        flag = IDLE;
        printf("[%s]\r\n", file);
        res = f_mount(&SDFatFS, SDPath, 1); printf("mount:%d\r\n", res);
        res = f_unlink((char *)file); printf("delete:%d\r\n", res);
        res = f_mount(NULL, SDPath, 1); printf("unmount:%d\r\n", res);
        break;
      }
      case REMOVEDIR:
      {
        flag = IDLE;
        res = f_mount(&SDFatFS, SDPath, 1); printf("mount:%d\r\n", res);
        DeleteEarlyLog();
        res = f_mount(NULL, SDPath, 1); printf("unmount:%d\r\n", res);
        break;
      }
      case FORMAT:
      {
        flag = IDLE;
        res = f_mount(&SDFatFS, SDPath, 1); printf("mount:%d\r\n", res);
        res = f_mkfs(SDPath, FM_EXFAT, 0, work, sizeof(work)); printf("mkfs:%d\r\n", res);
        res = f_mount(NULL, SDPath, 1); printf("unmount:%d\r\n", res);
        break;
      }
      case DISKFREE:
      {
        flag = IDLE;
        res = f_mount(&SDFatFS, SDPath, 1); printf("mount:%d\r\n", res);
        CalStorage();
        res = f_mount(NULL, SDPath, 1); printf("unmount:%d\r\n", res);
        break;
      }
      case LISTDISK:
      {
        flag = IDLE;
        res = f_mount(&SDFatFS, SDPath, 1); printf("mount:%d\r\n", res);
        res = f_list(SDPath); printf("list:%d\r\n", res);
        res = f_mount(NULL, SDPath, 1); printf("unmount:%d\r\n", res);
        break;
      }
      default:
        break;
    }
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    osDelay(125);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void DeleteEarlyLog(void)
{
  FILINFO FileInfo;
  char DeleteDir[32] = {0};
  uint8_t y, m, d;
  for(y=20; y<99; y++)
  {
    for(m=8; m<13; m++)
    {
      for(d=15; d<32; d++)
      {
        memset(DeleteDir, 0, sizeof(DeleteDir));
        sprintf(DeleteDir, FORMATOFLOGDIR, SDPath, y, m, d);
        if(FR_OK == f_stat(DeleteDir, &FileInfo))
        {
          printf("DELETEDIR:%s\t", DeleteDir);
          printf("REMOVEDIR RESULT:%d\r\n", f_deldir(DeleteDir));
          return;
        }
      }
      d = 1;
    }
    m = 1;
  }
}

void CalStorage(void)
{
  DWORD clst = 0;
  FATFS * pFs = &SDFatFS;
  if(FR_OK == f_getfree(SDPath, &clst, &pFs))
  {
    uint32_t TotalSizeKB = (pFs->n_fatent - 2) * pFs->csize / 2;
    uint32_t FreeSizeKB = clst * pFs->csize / 2;
    uint32_t UsedSizeKB = TotalSizeKB - FreeSizeKB;
    double FreePercent = (double)FreeSizeKB / TotalSizeKB * 100;
    double UsedPercent = (double)UsedSizeKB / TotalSizeKB * 100;
    printf("\r\nSDCard Size:%.3lfGB, Used:%.3lfGB, Free:%.3lfGB\r\n", TotalSizeKB*1.0/1024/1024, UsedSizeKB*1.0/1024/1024, FreeSizeKB*1.0/1024/1024);
    printf("\r\nSDCard Used:%.3lf%%, Free:%.3lf%%\r\n", UsedPercent, FreePercent);
  }
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
