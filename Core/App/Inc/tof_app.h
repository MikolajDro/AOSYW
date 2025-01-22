/*
 * tof_app.h
 *
 *  Created on: Dec 13, 2024
 *      Author: mikol
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_INC_TOF_APP_H_
#define APP_INC_TOF_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include "b_u585i_iot02a.h"
#include "debug.h"
#include "custom_tof_conf.h"



#ifndef USE_CUSTOM_RANGING_VL53L5CX
#define USE_CUSTOM_RANGING_VL53L5CX (1U)
#endif /* Use custom ranging */

#if (USE_CUSTOM_RANGING_VL53L5CX == 1U)
#include "vl53l5cx.h"
#endif /* Use custom ranging */

#if (USE_CUSTOM_RANGING_VL53L5CX == 1U)
#define CUSTOM_VL53L5CX (0)
#endif /* Use custom ranging */

#define RANGING_SENSOR_VL53L5CX_ADDRESS     (VL53L5CX_DEVICE_ADDRESS)
#define RANGING_SENSOR_NB_TARGET_PER_ZONE   (VL53L5CX_NB_TARGET_PER_ZONE)
#define RANGING_SENSOR_MAX_NB_ZONES         (VL53L5CX_MAX_NB_ZONES)

#define RS_PROFILE_4x4_CONTINUOUS          (VL53L5CX_PROFILE_4x4_CONTINUOUS)
#define RS_PROFILE_4x4_AUTONOMOUS          (VL53L5CX_PROFILE_4x4_AUTONOMOUS)
#define RS_PROFILE_8x8_CONTINUOUS          (VL53L5CX_PROFILE_8x8_CONTINUOUS)
#define RS_PROFILE_8x8_AUTONOMOUS          (VL53L5CX_PROFILE_8x8_AUTONOMOUS)

#define RS_IT_DEFAULT        (VL53L5CX_IT_DEFAULT)       /*!< IT if new measurement is ready (no thresholds) */
#define RS_IT_IN_WINDOW      (VL53L5CX_IT_IN_WINDOW)     /*!< IT if distance > thresh_high */
#define RS_IT_OUT_OF_WINDOW  (VL53L5CX_IT_OUT_OF_WINDOW) /*!< IT if distance < LowThreshold OR distance > HighThreshold */
#define RS_IT_BELOW_LOW      (VL53L5CX_IT_BELOW_LOW)     /*!< IT if distance <= LowThreshold */
#define RS_IT_ABOVE_HIGH     (VL53L5CX_IT_ABOVE_HIGH)    /*!< IT if distance > HighThreshold */
#define RS_IT_EQUAL_LOW      (VL53L5CX_IT_EQUAL_LOW)     /*!< IT if distance == LowThreshold */
#define RS_IT_NOT_EQUAL_LOW  (VL53L5CX_IT_NOT_EQUAL_LOW) /*!< IT if distance != LowThreshold */

#define RS_MODE_BLOCKING_CONTINUOUS        (VL53L5CX_MODE_BLOCKING_CONTINUOUS)
#define RS_MODE_BLOCKING_ONESHOT           (VL53L5CX_MODE_BLOCKING_ONESHOT)
#define RS_MODE_ASYNC_CONTINUOUS           (VL53L5CX_MODE_ASYNC_CONTINUOUS)
#define RS_MODE_ASYNC_ONESHOT              (VL53L5CX_MODE_ASYNC_ONESHOT)

#define RANGING_INSTANCES_NBR    (USE_CUSTOM_RANGING_VL53L5CX)

#define RANGING_POWERMODE_ON     (0U)  /*!< run */
#define RANGING_POWERMODE_OFF    (1U)  /*!< standby */


/* Extra defines*/
#define NEW_MEASUREMENT 	(1U)
#define IDLE 				(0U)

#if (RANGING_INSTANCES_NBR == 0U)
#error "No ranging sensor instance has been selected"
#endif /* Use custom ranging */

typedef struct
{
  uint32_t NumberOfZones;
  uint32_t MaxNumberOfTargetsPerZone;
  uint32_t CustomROI;          /*!< Not available: 0, Available: 1 */
  uint32_t ThresholdDetection; /*!< Not available: 0, Available: 1 */
} RANGING_SENSOR_Capabilities_t;

typedef struct
{
  uint32_t RangingProfile;
  uint32_t TimingBudget;   /*!< Expressed in milliseconds */
  uint32_t Frequency;      /*!< Expressed in Hz */
  uint32_t EnableAmbient;  /*<! Enable: 1, Disable: 0 */
  uint32_t EnableSignal;   /*<! Enable: 1, Disable: 0 */
} RANGING_SENSOR_ProfileConfig_t;

typedef struct
{
  uint8_t TopLeftX;   /*!< Top Left x coordinate */
  uint8_t TopLeftY;   /*!< Top Left y coordinate */
  uint8_t BotRightX;  /*!< Bot Right x coordinate */
  uint8_t BotRightY;  /*!< Bot Right y coordinate */
} RANGING_SENSOR_ROIConfig_t;

typedef struct
{
  uint32_t Criteria;
  uint32_t LowThreshold;
  uint32_t HighThreshold;
} RANGING_SENSOR_ITConfig_t;

typedef struct
{
  uint32_t NumberOfTargets;
  uint32_t Distance[RANGING_SENSOR_NB_TARGET_PER_ZONE];  /*!< millimeters */
  uint32_t Status[RANGING_SENSOR_NB_TARGET_PER_ZONE];    /*!< OK: 0, NOK: !0 */
  float_t Ambient[RANGING_SENSOR_NB_TARGET_PER_ZONE];    /*!< kcps / spad */
  float_t Signal[RANGING_SENSOR_NB_TARGET_PER_ZONE];     /*!< kcps / spad */
} RANGING_SENSOR_ZoneResult_t;

typedef struct
{
  uint32_t NumberOfZones;
  RANGING_SENSOR_ZoneResult_t ZoneResult[RANGING_SENSOR_MAX_NB_ZONES];
} RANGING_SENSOR_Result_t;

/** @defgroup RANGING_SENSOR_Driver_structure  Ranging sensor Driver structure
  * @{
  */
typedef struct
{
  int32_t (*Init)(void *);
  int32_t (*DeInit)(void *);
  int32_t (*ReadID)(void *, uint32_t *);
  int32_t (*GetCapabilities)(void *, void *);
  int32_t (*ConfigProfile)(void *, void *);
  int32_t (*ConfigROI)(void *, void *);
  int32_t (*ConfigIT)(void *, void *);
  int32_t (*GetDistance)(void *, void *);
  int32_t (*Start)(void *, uint8_t);
  int32_t (*Stop)(void *);
  int32_t (*SetAddress)(void *, uint16_t);
  int32_t (*GetAddress)(void *, uint16_t *);
  int32_t (*SetPowerMode)(void *, uint32_t);
  int32_t (*GetPowerMode)(void *, uint32_t *);
} RANGING_SENSOR_Drv_t;


/* Variables */
extern int8_t new_data;
extern RANGING_SENSOR_Result_t Result;

/* Functions */
extern void *RANGING_CompObj[RANGING_INSTANCES_NBR];
int32_t RANGING_SENSOR_Init(uint32_t Instance);
int32_t RANGING_SENSOR_DeInit(uint32_t Instance);
int32_t RANGING_SENSOR_ReadID(uint32_t Instance, uint32_t *pId);
int32_t RANGING_SENSOR_GetCapabilities(uint32_t Instance, RANGING_SENSOR_Capabilities_t *pCapabilities);
int32_t RANGING_SENSOR_ConfigProfile(uint32_t Instance, RANGING_SENSOR_ProfileConfig_t *pConfig);
int32_t RANGING_SENSOR_ConfigROI(uint32_t Instance, RANGING_SENSOR_ROIConfig_t *pConfig);
int32_t RANGING_SENSOR_ConfigIT(uint32_t Instance, RANGING_SENSOR_ITConfig_t *pConfig);
int32_t RANGING_SENSOR_GetDistance(uint32_t Instance, RANGING_SENSOR_Result_t *pResult);
int32_t RANGING_SENSOR_Start(uint32_t Instance, uint8_t Mode);
int32_t RANGING_SENSOR_Stop(uint32_t Instance);
int32_t RANGING_SENSOR_SetAddress(uint32_t Instance, uint16_t Address);
int32_t RANGING_SENSOR_GetAddress(uint32_t Instance, uint16_t *pAddress);
int32_t RANGING_SENSOR_SetPowerMode(uint32_t Instance, uint32_t PowerMode);
int32_t RANGING_SENSOR_GetPowerMode(uint32_t Instance, uint32_t *pPowerMode);


/* Example functions */
void TOF_Init(void);
void TOF_Process(void);
RANGING_SENSOR_Result_t* TOF_get_data(void);
void print_result(RANGING_SENSOR_Result_t *Result);

#ifdef __cplusplus
}
#endif


#endif /* APP_INC_TOF_APP_H_ */
