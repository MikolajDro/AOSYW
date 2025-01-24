/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file  : b_u585i_iot02a.c
  * @brief : Source file for the BSP Common driver
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
*/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "../Inc/b_u585i_iot02a.h"
#include "usart.h"
/** @defgroup BSP BSP
 * @{
 */

/** @defgroup B_U585I_IOT02A B_U585I_IOT02A
 * @{
 */

/** @defgroup B_U585I_IOT02A_LOW_LEVEL B_U585I_IOT02A LOW LEVEL
 *  @brief This file provides set of firmware functions to manage Leds and push-button
 *         available on STM32U5xx-Nucleo Kit from STMicroelectronics.
 * @{
 */

/**
 * @}
 */

/** @defgroup B_U585I_IOT02A_LOW_LEVEL_Private_Defines B_U585I_IOT02A LOW LEVEL Private Defines
 * @{
 */

/** @defgroup B_U585I_IOT02A_LOW_LEVEL_FunctionPrototypes B_U585I_IOT02A LOW LEVEL Private Function Prototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup B_U585I_IOT02A_LOW_LEVEL_Private_Variables B_U585I_IOT02A LOW LEVEL Private Variables
 * @{
 */

USART_TypeDef* COM_USART[COMn] = {COM1_UART};
UART_HandleTypeDef hcom_uart[COMn];
#if (USE_COM_LOG > 0)
static COM_TypeDef COM_ActiveLogPort;
#endif
static uint32_t IsUsart1MspCbValid = 0;
/**
 * @}
 */

/** @defgroup B_U585I_IOT02A_LOW_LEVEL_Private_Functions B_U585I_IOT02A LOW LEVEL Private Functions
 * @{
 */

static void USART1_MspInit(UART_HandleTypeDef *huart);
static void USART1_MspDeInit(UART_HandleTypeDef *huart);

/**
 * @brief  This method returns the STM32U5xx NUCLEO BSP Driver revision
 * @retval version: 0xXYZR (8bits for each decimal, R for RC)
 */
int32_t BSP_GetVersion(void)
{
  return (int32_t)__B_U585I_IOT02A_BSP_VERSION;
}


/**
 * @brief  Configures COM port.
 * @param  COM: COM port to be configured.
 *              This parameter can be COM1
 * @param  UART_Init: Pointer to a UART_HandleTypeDef structure that contains the
 *                    configuration information for the specified USART peripheral.
 * @retval BSP error code
 */
int32_t BSP_COM_Init(COM_TypeDef COM)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM > COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
     hcom_uart[COM].Instance = COM_USART[COM];
    /* Init the UART Msp */
    USART1_MspInit(&hcom_uart[COM]);
    if(IsUsart1MspCbValid == 0U)
    {
      if(BSP_COM_RegisterDefaultMspCallbacks(COM) != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
  }

  return ret;
}

/**
 * @brief  DeInit COM port.
 * @param  COM COM port to be configured.
 *             This parameter can be COM1
 * @retval BSP status
 */
int32_t BSP_COM_DeInit(COM_TypeDef COM)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM > COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    /* USART configuration */
    hcom_uart[COM].Instance = COM_USART[COM];

    #if (USE_HAL_UART_REGISTER_CALLBACKS == 0U)
      USART1_MspDeInit(&hcom_uart[COM]);
    #endif /* (USE_HAL_UART_REGISTER_CALLBACKS == 0U) */

    if(HAL_UART_DeInit(&hcom_uart[COM]) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
  }

  return ret;
}

/**
 * @brief  Configures COM port.
 * @param  huart USART handle
 *               This parameter can be COM1
 * @param  COM_Init Pointer to a UART_HandleTypeDef structure that contains the
 *                  configuration information for the specified USART peripheral.
 * @retval HAL error code
 */

/**
 * @brief Register Default USART1 Bus Msp Callbacks
 * @retval BSP status
 */
int32_t BSP_COM_RegisterDefaultMspCallbacks(COM_TypeDef COM)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM >= COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {

    __HAL_UART_RESET_HANDLE_STATE(&hcom_uart[COM]);

    /* Register default MspInit/MspDeInit Callback */
    if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPINIT_CB_ID, USART1_MspInit) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPDEINIT_CB_ID, USART1_MspDeInit) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else
    {
      IsUsart1MspCbValid = 1U;
    }
  }

  /* BSP status */
  return ret;
}

/**
 * @brief Register USART1 Bus Msp Callback registering
 * @param Callbacks pointer to USART1 MspInit/MspDeInit callback functions
 * @retval BSP status
 */
int32_t BSP_COM_RegisterMspCallbacks (COM_TypeDef COM , BSP_COM_Cb_t *Callback)
{
  int32_t ret = BSP_ERROR_NONE;

  if(COM >= COMn)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    __HAL_UART_RESET_HANDLE_STATE(&hcom_uart[COM]);

    /* Register MspInit/MspDeInit Callbacks */
    if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPINIT_CB_ID, Callback->pMspInitCb) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else if(HAL_UART_RegisterCallback(&hcom_uart[COM], HAL_UART_MSPDEINIT_CB_ID, Callback->pMspDeInitCb) != HAL_OK)
    {
      ret = BSP_ERROR_PERIPH_FAILURE;
    }
    else
    {
      IsUsart1MspCbValid = 1U;
    }
  }

  /* BSP status */
  return ret;
}

/**
 * @brief  Select the active COM port.
 * @param  COM COM port to be activated.
 *             This parameter can be COM1
 * @retval BSP status
 */
int32_t BSP_COM_SelectLogPort(COM_TypeDef COM)
{
  if(COM_ActiveLogPort != COM)
  {
    COM_ActiveLogPort = COM;
  }
  return BSP_ERROR_NONE;
}


struct __FILE
{
  int dummyVar; //Just for the sake of redefining __FILE, we won't we using it anyways ;)
};


#if !defined(__ICCARM__) /* For IAR */
size_t _write(int Handle, const unsigned char *Buf, size_t Bufsize)
{
  int i;

  for(i=0; i<Bufsize; i++)
  {
    (void)HAL_UART_Transmit(&huart1, (uint8_t *)&Buf[i], 1, COM_POLL_TIMEOUT);
  }

  return Bufsize;
}
int __io_putchar (int ch)
{
  (void)HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, COM_POLL_TIMEOUT);
  return ch;
}
#endif /* USE_COM_LOG */
/**
 * @brief  Initializes USART1 MSP.
 * @param  huart USART1 handle
 * @retval None
 */

static void USART1_MspInit(UART_HandleTypeDef* uartHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

    /* Enable Peripheral clock */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA10     ------> USART1_RX
    PA9     ------> USART1_TX
    */
    GPIO_InitStruct.Pin = BUS_USART1_RX_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = BUS_USART1_RX_GPIO_AF;
    HAL_GPIO_Init(BUS_USART1_RX_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = BUS_USART1_TX_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = BUS_USART1_TX_GPIO_AF;
    HAL_GPIO_Init(BUS_USART1_TX_GPIO_PORT, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
}

static void USART1_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA10     ------> USART1_RX
    PA9     ------> USART1_TX
    */
    HAL_GPIO_DeInit(BUS_USART1_RX_GPIO_PORT, BUS_USART1_RX_GPIO_PIN);

    HAL_GPIO_DeInit(BUS_USART1_TX_GPIO_PORT, BUS_USART1_TX_GPIO_PIN);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

