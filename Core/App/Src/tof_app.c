/*
 * tof_app.c
 *
 *  Created on: Dec 13, 2024
 *      Author: mikol
 */


/* Includes ------------------------------------------------------------------*/
#include "../Inc/tof_app.h"


/* Defines -------------------------------------------------------------------*/
#define TIMING_BUDGET 		(50U) /* 5 ms < TimingBudget < 100 ms */
#define RANGING_FREQUENCY 	(1U) /* Ranging frequency Hz (shall be consistent with TimingBudget value) */
#define POLLING_PERIOD 		(1000U/RANGING_FREQUENCY) /* refresh rate for polling mode (milliseconds) */

/* Private variables ---------------------------------------------------------*/
#ifndef USE_BARE_DRIVER
static RANGING_SENSOR_Capabilities_t Cap;
#endif

static RANGING_SENSOR_ProfileConfig_t Profile;
RANGING_SENSOR_Result_t Result;

static int32_t status = 0;
volatile uint8_t ToF_EventDetected = 0;

int8_t new_data;


/* Private function prototypes -----------------------------------------------*/

void *RANGING_CompObj[RANGING_INSTANCES_NBR] = {0};

#ifdef USE_BARE_DRIVER
static uint8_t map_target_status(uint8_t status);
static int32_t convert_data_format(VL53L5CX_Object_t *pObj,
                                   VL53L5CX_ResultsData *data, RANGING_SENSOR_Result_t *pResult);
#endif

static void VL53L5CX_TOF_Init(void);
static void VL53L5CX_Process(void);
void print_result(RANGING_SENSOR_Result_t *Result);
#if MY_DEBUG > 2
static void toggle_resolution(void);
static void toggle_signal_and_ambient(void);
static void clear_screen(void);
static void handle_cmd(uint8_t cmd);
static uint8_t get_key(void);
static uint32_t com_has_data(void);
#endif
static void reset_device(void);
static RANGING_SENSOR_Drv_t *CUSTOM_RANGING_Drv[RANGING_INSTANCES_NBR];
static RANGING_SENSOR_Capabilities_t RANGING_SENSOR_Cap[RANGING_INSTANCES_NBR];


#if (USE_CUSTOM_RANGING_VL53L5CX == 1U)
static int32_t VL53L5CX_Probe(uint32_t Instance);
#endif /* Use custom ranging */



/**
  * @brief Initializes the ranging sensor.
  * @param Instance    Ranging sensor instance.
  * @retval BSP status
  */
int32_t RANGING_SENSOR_Init(uint32_t Instance)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else
  {
    reset_device();

    switch (Instance)
    {
#if (USE_CUSTOM_RANGING_VL53L5CX == 1U)
      case CUSTOM_VL53L5CX:
        if (VL53L5CX_Probe(Instance) != BSP_ERROR_NONE)
        {
          ret = BSP_ERROR_NO_INIT;
        }
        else
        {
          ret = BSP_ERROR_NONE;
        }
        break;
#endif /* Use custom ranging */
      default:
        ret = BSP_ERROR_UNKNOWN_COMPONENT;
        break;
    }
  }

  return ret; // @suppress("Return with parenthesis")
}

/**
  * @brief Deinitializes the ranging sensor.
  * @param Instance    Ranging sensor instance.
  * @retval BSP status
  */
int32_t RANGING_SENSOR_DeInit(uint32_t Instance)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->DeInit(RANGING_CompObj[Instance]) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Read the ranging sensor device ID.
  * @param Instance    Ranging sensor instance.
  * @param pId    Pointer to the device ID.
  * @retval BSP status
  */
int32_t RANGING_SENSOR_ReadID(uint32_t Instance, uint32_t *pId)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->ReadID(RANGING_CompObj[Instance], pId) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Get the ranging sensor capabilities.
  * @param Instance    Ranging sensor instance.
  * @param pCapabilities    Pointer to the ranging sensor capabilities.
  * @note This function should be called after the init.
  * @retval BSP status
  */
int32_t RANGING_SENSOR_GetCapabilities(uint32_t Instance, RANGING_SENSOR_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->GetCapabilities(RANGING_CompObj[Instance], pCapabilities) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Set the ranging configuration profile.
  * @param Instance    Ranging sensor instance.
  * @param pConfig    Pointer to the new configuration profile to be applied.
  * @retval BSP status
  */
int32_t RANGING_SENSOR_ConfigProfile(uint32_t Instance, RANGING_SENSOR_ProfileConfig_t *pConfig)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->ConfigProfile(RANGING_CompObj[Instance], pConfig) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Configure the Region of Interest of the ranging sensor.
  * @param Instance    Ranging sensor instance.
  * @param pConfig    Pointer to the ROI configuration struct.
  * @note Should be called only if the device supports CustomROI.
  * @retval BSP status
  */
int32_t RANGING_SENSOR_ConfigROI(uint32_t Instance, RANGING_SENSOR_ROIConfig_t *pConfig)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (RANGING_SENSOR_Cap[Instance].CustomROI == 0)
  {
    ret = BSP_ERROR_FEATURE_NOT_SUPPORTED;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->ConfigROI(RANGING_CompObj[Instance], pConfig) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Configure the IT event generation parameters.
  * @param Instance    Ranging sensor instance.
  * @param pConfig    Pointer to the IT configuration struct.
  * @note The threshold modes can be used only if supported by the device (check the capabilities)
  * @retval BSP status
  */
int32_t RANGING_SENSOR_ConfigIT(uint32_t Instance, RANGING_SENSOR_ITConfig_t *pConfig)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->ConfigIT(RANGING_CompObj[Instance], pConfig) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Get the last distance measurement information.
  * @param Instance    Ranging sensor instance.
  * @param pResult    Pointer to the result struct.
  * @retval BSP status
  */
int32_t RANGING_SENSOR_GetDistance(uint32_t Instance, RANGING_SENSOR_Result_t *pResult)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->GetDistance(RANGING_CompObj[Instance], pResult) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Start ranging.
  * @param Instance    Ranging sensor instance.
  * @param Mode        The desired ranging mode.
  * @retval BSP status
  */
int32_t RANGING_SENSOR_Start(uint32_t Instance, uint8_t Mode)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->Start(RANGING_CompObj[Instance], Mode) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Stop ranging.
  * @param Instance    Ranging sensor instance.
  * @retval BSP status
  */
int32_t RANGING_SENSOR_Stop(uint32_t Instance)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->Stop(RANGING_CompObj[Instance]) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Set The I2C address of the device.
  * @param Instance    Ranging sensor instance.
  * @param Address     New I2C address.
  * @retval BSP status
  */
int32_t RANGING_SENSOR_SetAddress(uint32_t Instance, uint16_t Address)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->SetAddress(RANGING_CompObj[Instance], Address) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Get the I2C address of the device.
  * @param Instance    Ranging sensor instance.
  * @param pAddress    Pointer to the current I2C address.
  * @retval BSP status
  */
int32_t RANGING_SENSOR_GetAddress(uint32_t Instance, uint16_t *pAddress)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->GetAddress(RANGING_CompObj[Instance], pAddress) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Set the power mode.
  * @param Instance    Ranging sensor instance.
  * @param PowerMode    New power mode to be entered.
  * @retval BSP status
  */
int32_t CUSTOM_RANGING_SENSOR_SetPowerMode(uint32_t Instance, uint32_t PowerMode)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->SetPowerMode(RANGING_CompObj[Instance], PowerMode) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Get the power mode.
  * @param Instance    Ranging sensor instance.
  * @param pPowerMode    Pointer to the current power mode.
  * @retval BSP status
  */
int32_t CUSTOM_RANGING_SENSOR_GetPowerMode(uint32_t Instance, uint32_t *pPowerMode)
{
  int32_t ret;

  if (Instance >= RANGING_INSTANCES_NBR)
  {
    ret = BSP_ERROR_WRONG_PARAM;
  }
  else if (CUSTOM_RANGING_Drv[Instance]->GetPowerMode(RANGING_CompObj[Instance], pPowerMode) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

#if (USE_CUSTOM_RANGING_VL53L5CX == 1U)
/**
  * @brief Register Bus IOs if component ID is OK.
  * @param Instance    Ranging sensor instance.
  * @retval BSP status
  */
static int32_t VL53L5CX_Probe(uint32_t Instance)
{
  int32_t ret;
  VL53L5CX_IO_t              IOCtx;
  uint32_t                   id;
  static VL53L5CX_Object_t   VL53L5CXObj;

  /* Configure the ranging sensor driver */
  IOCtx.Address     = RANGING_SENSOR_VL53L5CX_ADDRESS;
  IOCtx.Init        = CUSTOM_VL53L5CX_I2C_INIT;
  IOCtx.DeInit      = CUSTOM_VL53L5CX_I2C_DEINIT;
  IOCtx.WriteReg    = CUSTOM_VL53L5CX_I2C_WRITEREG;
  IOCtx.ReadReg     = CUSTOM_VL53L5CX_I2C_READREG;
  IOCtx.GetTick     = BSP_GetTick;

  if (VL53L5CX_RegisterBusIO(&VL53L5CXObj, &IOCtx) != VL53L5CX_OK)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    CUSTOM_RANGING_Drv[Instance] = (RANGING_SENSOR_Drv_t *) &VL53L5CX_RANGING_SENSOR_Driver;
    RANGING_CompObj[Instance] = &VL53L5CXObj;

    if (VL53L5CX_ReadID(&VL53L5CXObj, &id) != VL53L5CX_OK)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else if (id != VL53L5CX_ID)
    {
      ret = BSP_ERROR_UNKNOWN_COMPONENT;
    }
    else if (CUSTOM_RANGING_Drv[Instance]->Init(RANGING_CompObj[Instance]) != VL53L5CX_OK)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else if (CUSTOM_RANGING_Drv[Instance]->GetCapabilities(RANGING_CompObj[Instance],
                                                           &RANGING_SENSOR_Cap[Instance]) != VL53L5CX_OK)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }

  return ret;
}
#endif /* Use custom ranging */

static void reset_device(void)
{
#if (USE_CUSTOM_RANGING_VL53L5CX == 1U)
  HAL_GPIO_WritePin(CUSTOM_VL53L5CX_LPn_PORT, CUSTOM_VL53L5CX_LPn_PIN, GPIO_PIN_RESET);
  HAL_Delay(2);
  HAL_GPIO_WritePin(CUSTOM_VL53L5CX_LPn_PORT, CUSTOM_VL53L5CX_LPn_PIN, GPIO_PIN_SET);
  HAL_Delay(2);
#endif /* Use custom ranging */
}



void TOF_Init(void)
{
  /* arbitrary wait after XShutdown to allow switch on */
  HAL_Delay(1);

#if MY_DEBUG >= 1
  printf("TOF sensor is initializing.\r\n");
#endif

  BSP_COM_Init(COM1);
  VL53L5CX_TOF_Init();
}

/*
 * LM background task
 */
void TOF_Process(void)
{
  VL53L5CX_Process();

#if MY_DEBUG >= 1
  printf("TOF sensor is sampling.\r\n");
#endif
}

static void VL53L5CX_TOF_Init(void)
{
	status = RANGING_SENSOR_Init(CUSTOM_VL53L5CX);

	if (status != BSP_ERROR_NONE)
	{
		printf("RANGING_SENSOR_Init failed\r\n");
		while (1);
	}
	else
		printf("TOF initialization success!\r\n");


	uint32_t Id;

	RANGING_SENSOR_ReadID(CUSTOM_VL53L5CX, &Id);
	RANGING_SENSOR_GetCapabilities(CUSTOM_VL53L5CX, &Cap);

	Profile.RangingProfile = RS_PROFILE_4x4_CONTINUOUS;
	Profile.TimingBudget = TIMING_BUDGET;
	Profile.Frequency = RANGING_FREQUENCY; /* Ranging frequency Hz (shall be consistent with TimingBudget value) */
	Profile.EnableAmbient = 0; /* Enable: 1, Disable: 0 */
	Profile.EnableSignal = 0; /* Enable: 1, Disable: 0 */

	/* set the profile if different from default one */
	RANGING_SENSOR_ConfigProfile(CUSTOM_VL53L5CX, &Profile);

	status = RANGING_SENSOR_Start(CUSTOM_VL53L5CX, RS_MODE_BLOCKING_CONTINUOUS);

	if (status != BSP_ERROR_NONE)
	{
		printf("RANGING_SENSOR_Start failed\r\n");
		while (1);
	}
}

static void VL53L5CX_Process(void)
{
  uint32_t Id;

  RANGING_SENSOR_ReadID(CUSTOM_VL53L5CX, &Id);
  RANGING_SENSOR_GetCapabilities(CUSTOM_VL53L5CX, &Cap);

  Profile.RangingProfile = RS_PROFILE_4x4_CONTINUOUS;
  Profile.TimingBudget = TIMING_BUDGET;
  Profile.Frequency = RANGING_FREQUENCY; /* Ranging frequency Hz (shall be consistent with TimingBudget value) */
  Profile.EnableAmbient = 0; /* Enable: 1, Disable: 0 */
  Profile.EnableSignal = 0; /* Enable: 1, Disable: 0 */

  /* set the profile if different from default one */
  RANGING_SENSOR_ConfigProfile(CUSTOM_VL53L5CX, &Profile);

  status = RANGING_SENSOR_Start(CUSTOM_VL53L5CX, RS_MODE_BLOCKING_CONTINUOUS);

  while (1)
  {
    /* polling mode */
    status = RANGING_SENSOR_GetDistance(CUSTOM_VL53L5CX, &Result);

    if (status == BSP_ERROR_NONE)
    {
    	new_data = NEW_MEASUREMENT;
#if PRINT_MEASUREMENT == YES
    	print_result(&Result);
#endif
    }
    else
    {
    	new_data = IDLE;
    }

#if MY_DEBUG > 2
    if (com_has_data())
    {
      handle_cmd(get_key());
    }
#endif
  }
}

RANGING_SENSOR_Result_t* TOF_get_data(void)
{
	RANGING_SENSOR_GetDistance(CUSTOM_VL53L5CX, &Result);

	if(status != BSP_ERROR_NONE)
		return NULL;

	return &Result;
}

#if MY_DEBUG > 1

void print_result(RANGING_SENSOR_Result_t *Result)
{
  int8_t i;
  int8_t j;
  int8_t k;
  int8_t l;
  uint8_t zones_per_line;

  zones_per_line = ((Profile.RangingProfile == RS_PROFILE_8x8_AUTONOMOUS) ||
                    (Profile.RangingProfile == RS_PROFILE_8x8_CONTINUOUS)) ? 8 : 4;

  display_commands_banner();

  printf("Cell Format :\n\n");
  for (l = 0; l < RANGING_SENSOR_NB_TARGET_PER_ZONE; l++)
  {
    printf(" \033[38;5;10m%20s\033[0m : %20s\n", "Distance [mm]", "Status");
    if ((Profile.EnableAmbient != 0) || (Profile.EnableSignal != 0))
    {
      printf(" %20s : %20s\n", "Signal [kcps/spad]", "Ambient [kcps/spad]");
    }
  }

  printf("\n\n");

  for (j = 0; j < Result->NumberOfZones; j += zones_per_line)
  {
    for (i = 0; i < zones_per_line; i++) /* number of zones per line */
    {
      printf(" -----------------");
    }
    printf("\n");

    for (i = 0; i < zones_per_line; i++)
    {
      printf("|                 ");
    }
    printf("|\n");

    for (l = 0; l < RANGING_SENSOR_NB_TARGET_PER_ZONE; l++)
    {
      /* Print distance and status */
      for (k = (zones_per_line - 1); k >= 0; k--)
      {
        if (Result->ZoneResult[j + k].NumberOfTargets > 0)
        {
          if ((long)Result->ZoneResult[j + k].Distance[l] < 500)
          {
            printf("| \033[38;5;9m%5ld\033[0m  :  %5ld ",
                   (long)Result->ZoneResult[j + k].Distance[l],
                   (long)Result->ZoneResult[j + k].Status[l]);
          }
          else
          {
            printf("| \033[38;5;10m%5ld\033[0m  :  %5ld ",
                   (long)Result->ZoneResult[j + k].Distance[l],
                   (long)Result->ZoneResult[j + k].Status[l]);
          }
        }
        else
          printf("| %5s  :  %5s ", "X", "X");
      }
      printf("|\n");

      if ((Profile.EnableAmbient != 0) || (Profile.EnableSignal != 0))
      {
        /* Print Signal and Ambient */
        for (k = (zones_per_line - 1); k >= 0; k--)
        {
          if (Result->ZoneResult[j + k].NumberOfTargets > 0)
          {
            if (Profile.EnableSignal != 0)
            {
              printf("| %5ld  :  ", (long)Result->ZoneResult[j + k].Signal[l]);
            }
            else
              printf("| %5s  :  ", "X");

            if (Profile.EnableAmbient != 0)
            {
              printf("%5ld ", (long)Result->ZoneResult[j + k].Ambient[l]);
            }
            else
              printf("%5s ", "X");
          }
          else
            printf("| %5s  :  %5s ", "X", "X");
        }
        printf("|\n");
      }
    }
  }

  for (i = 0; i < zones_per_line; i++)
  {
    printf(" -----------------");
  }
  printf("\n");
}
#endif

#if MY_DEBUG > 2
static void toggle_resolution(void)
{
  RANGING_SENSOR_Stop(CUSTOM_VL53L5CX);

  switch (Profile.RangingProfile)
  {
    case RS_PROFILE_4x4_AUTONOMOUS:
      Profile.RangingProfile = RS_PROFILE_8x8_AUTONOMOUS;
      break;

    case RS_PROFILE_4x4_CONTINUOUS:
      Profile.RangingProfile = RS_PROFILE_8x8_CONTINUOUS;
      break;

    case RS_PROFILE_8x8_AUTONOMOUS:
      Profile.RangingProfile = RS_PROFILE_4x4_AUTONOMOUS;
      break;

    case RS_PROFILE_8x8_CONTINUOUS:
      Profile.RangingProfile = RS_PROFILE_4x4_CONTINUOUS;
      break;

    default:
      break;
  }

  RANGING_SENSOR_ConfigProfile(CUSTOM_VL53L5CX, &Profile);
  RANGING_SENSOR_Start(CUSTOM_VL53L5CX, RS_MODE_BLOCKING_CONTINUOUS);
}

static void toggle_signal_and_ambient(void)
{
  RANGING_SENSOR_Stop(CUSTOM_VL53L5CX);

  Profile.EnableAmbient = (Profile.EnableAmbient) ? 0U : 1U;
  Profile.EnableSignal = (Profile.EnableSignal) ? 0U : 1U;

  RANGING_SENSOR_ConfigProfile(CUSTOM_VL53L5CX, &Profile);
  RANGING_SENSOR_Start(CUSTOM_VL53L5CX, RS_MODE_BLOCKING_CONTINUOUS);
}

static void clear_screen(void)
{
  /* clear Screen : 27 is ESC command */
  printf("%c[2J", 27);
}

static void display_commands_banner(void)
{
  /* clear screen */
  printf("%c[2H", 27);

  printf("VL53L5CX Simple Ranging demo application\n");
#ifdef USE_BARE_DRIVER
  printf("Using direct calls to VL53L5CX bare driver API\n");
#endif
  printf("Polling mode\n");
  printf("----------------------------------------\n\n");

  printf("Use the following keys to control application\n");
  printf(" 'r' : change resolution\n");
  printf(" 's' : enable signal and ambient\n");
  printf(" 'c' : clear screen\n");
  printf("\n");
}

static void handle_cmd(uint8_t cmd)
{
  switch (cmd)
  {
    case 'r':
      toggle_resolution();
      clear_screen();
      break;

    case 's':
      toggle_signal_and_ambient();
      clear_screen();
      break;

    case 'c':
      clear_screen();
      break;

    default:
      break;
  }
}

static uint8_t get_key(void)
{
  uint8_t cmd = 0;

  HAL_UART_Receive(&hcom_uart[COM1], &cmd, 1, HAL_MAX_DELAY);

  return cmd;
}

static uint32_t com_has_data(void)
{
  return __HAL_UART_GET_FLAG(&hcom_uart[COM1], UART_FLAG_RXNE);;
}
#endif

#ifdef USE_BARE_DRIVER
static uint8_t map_target_status(uint8_t status)
{
  uint8_t ret;

  if ((status == 5U) || (status == 9U))
  {
    ret = 0U; /* ranging is OK */
  }
  else if (status == 0U)
  {
    ret = 255U; /* no update */
  }
  else
  {
    ret = status; /* return device status otherwise */
  }

  return ret;
}

static int32_t convert_data_format(VL53L5CX_Object_t *pObj,
                                   VL53L5CX_ResultsData *data, RANGING_SENSOR_Result_t *pResult)
{
  int32_t ret;
  uint8_t i, j;
  uint8_t resolution;
  uint8_t target_status;

  if ((pObj == NULL) || (pResult == NULL))
  {
    ret = VL53L5CX_INVALID_PARAM;
  }
  else if (vl53l5cx_get_resolution(&pObj->Dev, &resolution) != VL53L5CX_STATUS_OK)
  {
    ret = VL53L5CX_ERROR;
  }
  else
  {
    pResult->NumberOfZones = resolution;

    for (i = 0; i < resolution; i++)
    {
      pResult->ZoneResult[i].NumberOfTargets = data->nb_target_detected[i];

      for (j = 0; j < data->nb_target_detected[i]; j++)
      {
        pResult->ZoneResult[i].Distance[j] = (uint32_t)data->distance_mm[(VL53L5CX_NB_TARGET_PER_ZONE * i) + j];

        /* return Ambient value if ambient rate output is enabled */
        if (pObj->IsAmbientEnabled == 1U)
        {
          /* apply ambient value to all targets in a given zone */
          pResult->ZoneResult[i].Ambient[j] = (float_t)data->ambient_per_spad[i];
        }
        else
        {
          pResult->ZoneResult[i].Ambient[j] = 0.0f;
        }

        /* return Signal value if signal rate output is enabled */
        if (pObj->IsSignalEnabled == 1U)
        {
          pResult->ZoneResult[i].Signal[j] =
            (float_t)data->signal_per_spad[(VL53L5CX_NB_TARGET_PER_ZONE * i) + j];
        }
        else
        {
          pResult->ZoneResult[i].Signal[j] = 0.0f;
        }

        target_status = data->target_status[(VL53L5CX_NB_TARGET_PER_ZONE * i) + j];
        pResult->ZoneResult[i].Status[j] = map_target_status(target_status);
      }
    }

    ret = VL53L5CX_OK;
  }

  return ret;
}
static void display_commands_banner(void)
{
  /* clear screen */
  printf("%c[2H", 27);
  printf("----------------------------------------\n\n");
  printf("VL53L5CX Simple Ranging\r\n");
#ifdef USE_BARE_DRIVER
  printf("Using direct calls to VL53L5CX bare driver API\n");
#endif
  printf("----------------------------------------\n\n");
  printf("\n");
}
#endif





#ifdef __cplusplus
}
#endif


