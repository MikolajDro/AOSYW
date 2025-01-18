/**
  ******************************************************************************
  * @file    custom_tof_conf.h
  * @author  IMG SW Application Team
  * @brief   This file contains definitions of the TOF components bus interfaces
  *          for custom boards
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CUSTOM_TOF_CONF_H__
#define __CUSTOM_TOF_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"
#include "b_u585i_iot02a_bus.h"
#include "b_u585i_iot02a_errno.h"
#include "debug.h"

#define USE_CUSTOM_RANGING_VL53L5CX (1U)

#define CUSTOM_VL53L5CX_LPn_PORT    GPIOH
#define CUSTOM_VL53L5CX_LPn_PIN     GPIO_PIN_1

#define CUSTOM_VL53L5CX_I2C_INIT      BSP_I2C2_Init
#define CUSTOM_VL53L5CX_I2C_DEINIT    BSP_I2C2_DeInit
#define CUSTOM_VL53L5CX_I2C_WRITEREG  BSP_I2C2_WriteReg16
#define CUSTOM_VL53L5CX_I2C_READREG   BSP_I2C2_ReadReg16

#ifdef __cplusplus
}
#endif

#endif /* __CUSTOM_TOF_CONF_H__*/
