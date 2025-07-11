/****************************************************************************************
*                                ADC.H                                                  *
****************************************************************************************
* File Name   : Adc.h
* Module      : Analog to Digital Converter (ADC)
* Description : AUTOSAR ADC driver header file 
* Version     : 2.0.0 - Redesigned for clarity and maintainability
* Date        : 2025
* Author      : ADC Driver Team
* Repository  : ADC_Redesigned
****************************************************************************************/

#ifndef ADC_H
#define ADC_H

/****************************************************************************************
*                                 INCLUDE FILES                                        *
****************************************************************************************/
/* Standard AUTOSAR includes */
#include "Std_Types.h"
#include "Adc_Cfg.h"
#include "Adc_Types.h"

/* Hardware specific includes */
#include "stm32f10x_adc.h"

/****************************************************************************************
*                              VERSION INFORMATION                                     *
****************************************************************************************/
/* AUTOSAR specification version information */
#define ADC_VENDOR_ID                   0x0001U /* Vendor ID for ADC driver */ 
#define ADC_MODULE_ID                   0x0037U /* Module ID for ADC driver (37 per AUTOSAR) */
#define ADC_SW_MAJOR_VERSION            2
#define ADC_SW_MINOR_VERSION            0
#define ADC_SW_PATCH_VERSION            0 
#define ADC_AR_RELEASE_MAJOR_VERSION    4
#define ADC_AR_RELEASE_MINOR_VERSION    4
#define ADC_AR_RELEASE_PATCH_VERSION    0

/****************************************************************************************
*                                 ERROR CODES                                          *
****************************************************************************************/
/* Development Errors */
#define ADC_E_UNINIT                    0x0AU   /* ADC driver not initialized */
#define ADC_E_ALREADY_INITIALIZED       0x0dU   /* ADC driver already initialized */
#define ADC_E_PARAM_POINTER             0x14U   /* Incorrect buffer pointer */
#define ADC_E_PARAM_CONFIG              0x1FU   /* Invalid configuration parameter */
#define ADC_E_PARAM_INVALID_GROUP       0x15U   /* Non existing group */
#define ADC_E_WRONG_CONV_MODE           0x16U   /* API called for wrong conversion mode */
#define ADC_E_WRONG_TRIGG_SRC           0x17U   /* API call not allowed for trigger source */
#define ADC_E_NOTIF_CAPABILITY          0x18U   /* Notification function pointer is NULL */
#define ADC_E_BUFFER_UNINIT             0x19U   /* Result buffer pointer not initialized */
#define ADC_E_POWER_STATE_NOT_SUPPORTED 0x1BU   /* Unsupported power state request */
#define ADC_E_PERIPHERAL_NOT_PREPARED   0x1DU   /* ADC not prepared for power state */

/* Runtime Errors */
#define ADC_E_BUSY                      0x0BU   /* ADC busy with another operation */
#define ADC_E_IDLE                      0x0CU   /* ADC group is idle */
#define ADC_E_NOT_DISENGAGED            0x1AU   /* ADC groups not in idle state */
#define ADC_E_TRANSITION_NOT_POSSIBLE   0x1CU   /* Power state transition not possible */
#define ADC_E_TIMEOUT                   0x1EU   /* Operation timeout */
#define ADC_E_QUEUE_FULL                0x20U   /* Conversion queue is full */
#define ADC_E_BUFFER_OVERFLOW           0x21U   /* Result buffer overflow */

/****************************************************************************************
*                              FUNCTION ID CONSTANTS                                   *
****************************************************************************************/
#define ADC_INIT_ID                         0x00U   /* Adc_Init */
#define ADC_DEINIT_ID                       0x01U   /* Adc_DeInit */
#define ADC_SETUP_RESULT_BUFFER_ID          0x0CU   /* Adc_SetupResultBuffer */
#define ADC_START_GROUP_CONVERSION_ID       0x02U   /* Adc_StartGroupConversion */
#define ADC_STOP_GROUP_CONVERSION_ID        0x03U   /* Adc_StopGroupConversion */
#define ADC_READ_GROUP_ID                   0x04U   /* Adc_ReadGroup */
#define ADC_ENABLE_HARDWARE_TRIGGER_ID      0x05U   /* Adc_EnableHardwareTrigger */
#define ADC_DISABLE_HARDWARE_TRIGGER_ID     0x06U   /* Adc_DisableHardwareTrigger */
#define ADC_ENABLE_GROUP_NOTIFICATION_ID    0x07U   /* Adc_EnableGroupNotification */
#define ADC_DISABLE_GROUP_NOTIFICATION_ID   0x08U   /* Adc_DisableGroupNotification */
#define ADC_GET_GROUP_STATUS_ID             0x09U   /* Adc_GetGroupStatus */
#define ADC_GET_STREAM_LAST_POINTER_ID      0x0BU   /* Adc_GetStreamLastPointer */
#define ADC_GET_VERSION_INFO_ID             0x0AU   /* Adc_GetVersionInfo */
#define ADC_SET_POWER_STATE_ID              0x10U   /* Adc_SetPowerState */
#define ADC_GET_CURRENT_POWER_STATE_ID      0x11U   /* Adc_GetCurrentPowerState */
#define ADC_GET_TARGET_POWER_STATE_ID       0x12U   /* Adc_GetTargetPowerState */
#define ADC_PREPARE_POWER_STATE_ID          0x0DU   /* Adc_PreparePowerState */

/* Extended function IDs for redesigned functionality */
#define ADC_START_STREAMING_ID              0x20U   /* Adc_StartStreaming */
#define ADC_STOP_STREAMING_ID               0x21U   /* Adc_StopStreaming */
#define ADC_GET_STREAMING_STATUS_ID         0x22U   /* Adc_GetStreamingStatus */
#define ADC_CALIBRATE_ID                    0x23U   /* Adc_Calibrate */
#define ADC_RESET_QUEUE_ID                  0x24U   /* Adc_ResetQueue */

/****************************************************************************************
*                              INITIALIZATION FUNCTIONS                               *
****************************************************************************************/
/**
 * @brief   Initializes the ADC hardware units and driver
 * @param[in] ConfigPtr Pointer to configuration set
 * @return  void
 * @reqs    SWS_Adc_00365
 */
void Adc_Init(const Adc_ConfigType* ConfigPtr);

/**
 * @brief   Returns all ADC HW Units to power-on reset state
 * @return  void
 * @reqs    SWS_Adc_00366
 */
void Adc_DeInit(void);

/**
 * @brief   Sets up the result buffer for ADC group conversions
 * @param[in] Group Numeric ID of requested ADC channel group
 * @param[in] DataBufferPtr Pointer to result buffer
 * @return  E_OK if successful, E_NOT_OK otherwise
 * @reqs    SWS_Adc_91000
 */
Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group,
                                     Adc_ValueGroupType* DataBufferPtr);

/****************************************************************************************
*                              CONVERSION CONTROL FUNCTIONS                           *
****************************************************************************************/
/**
 * @brief   Starts conversion of all channels in the requested ADC group
 * @param[in] Group Numeric ID of the ADC channel group
 * @return  void
 * @reqs    SWS_Adc_00508
 */
void Adc_StartGroupConversion(Adc_GroupType Group);

/**
 * @brief   Stops conversion of the requested ADC Channel group
 * @param[in] Group Numeric ID of the ADC channel group
 * @return  void
 * @reqs    SWS_Adc_00509
 */
void Adc_StopGroupConversion(Adc_GroupType Group);

/**
 * @brief   Reads the group conversion result of the last completed conversion
 * @param[in] Group Numeric ID of requested ADC channel group
 * @param[out] DataBufferPtr Pointer to buffer for storing results
 * @return  E_OK if results available, E_NOT_OK otherwise
 * @reqs    SWS_Adc_00369
 */
Std_ReturnType Adc_ReadGroup(Adc_GroupType Group,
                             Adc_ValueGroupType* DataBufferPtr);

/****************************************************************************************
*                              HARDWARE TRIGGER FUNCTIONS                             *
****************************************************************************************/
/**
 * @brief   Enables the hardware trigger for the requested ADC Channel group
 * @param[in] Group Numeric ID of the ADC channel group
 * @return  void
 * @reqs    SWS_Adc_91001
 */
void Adc_EnableHardwareTrigger(Adc_GroupType Group);

/**
 * @brief   Disables the hardware trigger for the requested ADC Channel group
 * @param[in] Group Numeric ID of the ADC channel group
 * @return  void
 * @reqs    SWS_Adc_91002
 */
void Adc_DisableHardwareTrigger(Adc_GroupType Group);

/****************************************************************************************
*                              NOTIFICATION FUNCTIONS                                 *
****************************************************************************************/
/**
 * @brief   Enables the notification mechanism for the requested ADC Channel group
 * @param[in] Group Numeric ID of the ADC channel group
 * @return  void
 * @reqs    SWS_Adc_91003
 */
void Adc_EnableGroupNotification(Adc_GroupType Group);

/**
 * @brief   Disables the notification mechanism for the requested ADC Channel group
 * @param[in] Group Numeric ID of the ADC channel group
 * @return  void
 * @reqs    SWS_Adc_91004
 */
void Adc_DisableGroupNotification(Adc_GroupType Group);

/****************************************************************************************
*                              STATUS FUNCTIONS                                       *
****************************************************************************************/
/**
 * @brief   Returns the current status of the requested ADC Channel group
 * @param[in] Group Numeric ID of the ADC channel group
 * @return  Conversion status for the requested group
 * @reqs    SWS_Adc_00374
 */
Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group);

/**
 * @brief   Returns the number of valid samples per channel in result buffer
 * @param[in] Group Numeric ID of the ADC channel group
 * @param[out] PtrToSamplePtr Pointer to result buffer pointer
 * @return  Number of valid samples per channel
 * @reqs    SWS_Adc_00375
 */
Adc_StreamNumSampleType Adc_GetStreamLastPointer(Adc_GroupType Group,
                                                 Adc_ValueGroupType** PtrToSamplePtr);

/****************************************************************************************
*                              STREAMING FUNCTIONS                                    *
****************************************************************************************/
#if (ADC_ENABLE_STREAMING == STD_ON)
/**
 * @brief   Starts streaming conversion for the requested ADC group
 * @param[in] Group Numeric ID of the ADC channel group
 * @param[in] NumSamples Number of samples to collect
 * @param[in] BufferMode Buffer mode (linear or circular)
 * @return  E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType Adc_StartStreaming(Adc_GroupType Group,
                                  Adc_StreamNumSampleType NumSamples,
                                  Adc_StreamBufferModeType BufferMode);

/**
 * @brief   Stops streaming conversion for the requested ADC group
 * @param[in] Group Numeric ID of the ADC channel group
 * @return  E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType Adc_StopStreaming(Adc_GroupType Group);

/**
 * @brief   Gets the current streaming status and filled sample count
 * @param[in] Group Numeric ID of the ADC channel group
 * @param[out] FilledSamples Number of samples currently in buffer
 * @param[out] BufferStatus Buffer status (normal/threshold/full)
 * @return  E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType Adc_GetStreamingStatus(Adc_GroupType Group,
                                      Adc_StreamNumSampleType* FilledSamples,
                                      uint8* BufferStatus);
#endif /* ADC_ENABLE_STREAMING */

/****************************************************************************************
*                              POWER MANAGEMENT FUNCTIONS                             *
****************************************************************************************/
#if (ADC_ENABLE_POWER_MANAGEMENT == STD_ON)
/**
 * @brief   Configures the ADC module to enter the prepared power state
 * @param[out] Result Power state change result
 * @return  E_OK if successful, E_NOT_OK otherwise
 * @reqs    SWS_Adc_00475
 */
Std_ReturnType Adc_SetPowerState(Adc_PowerStateRequestResultType* Result);

/**
 * @brief   Returns the current power state of the ADC HW unit
 * @param[out] CurrentPowerState Current power mode
 * @param[out] Result Service result
 * @return  E_OK if successful, E_NOT_OK otherwise
 * @reqs    SWS_Adc_00476
 */
Std_ReturnType Adc_GetCurrentPowerState(Adc_PowerStateType* CurrentPowerState,
                                        Adc_PowerStateRequestResultType* Result);

/**
 * @brief   Returns the target power state of the ADC HW unit
 * @param[out] TargetPowerState Target power mode
 * @param[out] Result Service result
 * @return  E_OK if successful, E_NOT_OK otherwise
 * @reqs    SWS_Adc_00477
 */
Std_ReturnType Adc_GetTargetPowerState(Adc_PowerStateType* TargetPowerState,
                                       Adc_PowerStateRequestResultType* Result);

/**
 * @brief   Prepares the ADC module for a power state transition
 * @param[in] PowerState Target power state
 * @param[out] Result Preparation result
 * @return  E_OK if successful, E_NOT_OK otherwise
 * @reqs    SWS_Adc_00478
 */
Std_ReturnType Adc_PreparePowerState(Adc_PowerStateType PowerState,
                                     Adc_PowerStateRequestResultType* Result);
#endif /* ADC_ENABLE_POWER_MANAGEMENT */

/****************************************************************************************
*                              UTILITY FUNCTIONS                                      *
****************************************************************************************/
/**
 * @brief   Returns the version information of the ADC driver
 * @param[out] versioninfo Pointer to version information structure
 * @return  void
 * @reqs    SWS_Adc_00376
 */
void Adc_GetVersionInfo(Std_VersionInfoType* versioninfo);

/**
 * @brief   Calibrates the ADC hardware unit
 * @param[in] HwUnit Hardware unit to calibrate
 * @return  E_OK if successful, E_NOT_OK otherwise
 * @note    This function should be called after initialization for optimal accuracy
 */
Std_ReturnType Adc_Calibrate(Adc_HwUnitType HwUnit);

/****************************************************************************************
*                              QUEUE MANAGEMENT FUNCTIONS                             *
****************************************************************************************/
#if (ADC_ENABLE_QUEUING == STD_ON)
/**
 * @brief   Resets the conversion queue for the specified hardware unit
 * @param[in] HwUnit Hardware unit whose queue to reset
 * @return  E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType Adc_ResetQueue(Adc_HwUnitType HwUnit);

/**
 * @brief   Gets the current queue status
 * @param[in] HwUnit Hardware unit ID
 * @param[out] QueuedGroups Number of groups currently queued
 * @param[out] CurrentGroup Currently converting group
 * @return  E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType Adc_GetQueueStatus(Adc_HwUnitType HwUnit,
                                  uint8* QueuedGroups,
                                  Adc_GroupType* CurrentGroup);
#endif /* ADC_ENABLE_QUEUING */

/****************************************************************************************
*                              SAFETY FUNCTIONS                                       *
****************************************************************************************/
/**
 * @brief   Performs a self-test of the ADC module
 * @param[in] HwUnit Hardware unit to test
 * @param[out] TestResult Test result details
 * @return  E_OK if test passed, E_NOT_OK if test failed
 */
Std_ReturnType Adc_SelfTest(Adc_HwUnitType HwUnit, uint32* TestResult);

/**
 * @brief   Resets the ADC hardware unit after an error
 * @param[in] HwUnit Hardware unit to reset
 * @return  E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType Adc_ResetAfterError(Adc_HwUnitType HwUnit);

/****************************************************************************************
*                              DEFERRED PROCESSING FUNCTIONS                          *
****************************************************************************************/
/**
 * @brief   Main function for deferred ADC processing
 * @details This function should be called periodically from the main loop 
 *          to handle ADC interrupt processing deferred from ISR context
 * @return  void
 * @note    Call frequency should be high enough to prevent buffer overflow
 */
void Adc_MainFunction(void);

/**
 * @brief   Fast interrupt handler with minimal processing
 * @param[in] HwUnit ADC hardware unit that triggered the interrupt
 * @details This is the actual ISR that should be called from interrupt vectors.
 *          It performs only critical time-sensitive operations and defers 
 *          complex processing to Adc_MainFunction()
 * @return  void
 */
void Adc_InterruptHandler(Adc_HwUnitType HwUnit);

/****************************************************************************************
*                              DIAGNOSTIC FUNCTIONS                                   *
****************************************************************************************/
#if (ADC_ENABLE_DEBUG_SUPPORT == STD_ON)
/**
 * @brief   Gets diagnostic information about the ADC driver
 * @param[in] HwUnit Hardware unit ID
 * @param[out] DiagInfo Diagnostic information structure
 * @return  E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType Adc_GetDiagnosticInfo(Adc_HwUnitType HwUnit, 
                                     Adc_DiagnosticInfoType* DiagInfo);

/**
 * @brief   Gets performance statistics
 * @param[in] HwUnit Hardware unit ID
 * @param[out] PerfStats Performance statistics structure
 * @return  E_OK if successful, E_NOT_OK otherwise
 */
Std_ReturnType Adc_GetPerformanceStats(Adc_HwUnitType HwUnit,
                                       Adc_PerformanceStatsType* PerfStats);
#endif /* ADC_ENABLE_DEBUG_SUPPORT */

/****************************************************************************************
*                              CALLBACK FUNCTION PROTOTYPES                          *
****************************************************************************************/
/**
 * @brief   Generic conversion complete callback
 * @param[in] Group Group that completed conversion
 * @param[in] Result Conversion result (E_OK/E_NOT_OK)
 * @return  void
 */
typedef void (*Adc_ConversionCompleteCallback)(Adc_GroupType Group, Std_ReturnType Result);

/**
 * @brief   Streaming threshold reached callback
 * @param[in] Group Group that reached threshold
 * @param[in] ThresholdLevel Threshold level reached (0-100%)
 * @return  void
 */
typedef void (*Adc_StreamingThresholdCallback)(Adc_GroupType Group, uint8 ThresholdLevel);

/**
 * @brief   Error callback
 * @param[in] HwUnit Hardware unit where error occurred
 * @param[in] ErrorCode Error code
 * @return  void
 */
typedef void (*Adc_ErrorCallback)(Adc_HwUnitType HwUnit, uint32 ErrorCode);

/****************************************************************************************
*                              INLINE FUNCTIONS                                       *
****************************************************************************************/
// /**
//  * @brief   Check if group ID is valid
//  * @param[in] Group Group ID to validate
//  * @return  TRUE if valid, FALSE if invalid
//  */
// static inline boolean Adc_IsValidGroup(Adc_GroupType Group)
// {
//     return (Group < ADC_MAX_GROUPS) ? TRUE : FALSE;
    
// }

// /**
//  * @brief   Check if hardware unit ID is valid
//  * @param[in] HwUnit Hardware unit ID to validate
//  * @return  TRUE if valid, FALSE if invalid
//  */
// static inline boolean Adc_IsValidHwUnit(Adc_HwUnitType HwUnit)
// {
//     return (HwUnit < ADC_MAX_HW_UNITS) ? TRUE : FALSE;
// }

/**
 * @brief   Check if the ADC driver is initialized
 * @return  TRUE if initialized, FALSE if not
 */
static inline boolean Adc_IsInitialized(void)
{
    return (Adc_DriverState == ADC_STATE_INITIALIZED) ? TRUE : FALSE;
}

/****************************************************************************************
*                              GLOBAL VARIABLES                                       *
****************************************************************************************/
/* Driver state variable */
extern Adc_DriverStateType Adc_DriverState;

/* Runtime performance counters */
#if (ADC_ENABLE_DEBUG_SUPPORT == STD_ON)
extern Adc_PerformanceCountersType Adc_PerformanceCounters;
#endif

/****************************************************************************************
*                              CONSTANTS                                              *
****************************************************************************************/
/* Driver states */
#define ADC_STATE_UNINIT            0x00U
#define ADC_STATE_INITIALIZED       0x01U
#define ADC_STATE_BUSY              0x02U
#define ADC_STATE_ERROR             0x03U

/* Buffer status values */
#define ADC_BUFFER_STATUS_NORMAL    0x00U
#define ADC_BUFFER_STATUS_THRESHOLD 0x01U
#define ADC_BUFFER_STATUS_FULL      0x02U
#define ADC_BUFFER_STATUS_OVERFLOW  0x03U

/* Test result values */
#define ADC_TEST_PASSED             0x00000000UL
#define ADC_TEST_FAILED_CALIB       0x00000001UL
#define ADC_TEST_FAILED_CONV        0x00000002UL
#define ADC_TEST_FAILED_DMA         0x00000004UL

/****************************************************************************************
*                              VALIDATION MACROS                                      *
****************************************************************************************/
#if (ADC_DEV_ERROR_DETECT == STD_ON)
#define ADC_VALIDATE_INIT(ApiId)                                                     \
    if (Adc_DriverState == ADC_STATE_UNINIT) {                                      \
        Det_ReportError(ADC_MODULE_ID, 0, (ApiId), ADC_E_UNINIT);                   \
        return;                                                                      \
    }

#define ADC_VALIDATE_INIT_RETURN(ApiId, RetVal)                                     \
    if (Adc_DriverState == ADC_STATE_UNINIT) {                                      \
        Det_ReportError(ADC_MODULE_ID, 0, (ApiId), ADC_E_UNINIT);                   \
        return (RetVal);                                                             \
    }

#define ADC_VALIDATE_GROUP(Group, ApiId)                                            \
    if (!Adc_IsValidGroup(Group)) {                                                 \
        Det_ReportError(ADC_MODULE_ID, 0, (ApiId), ADC_E_PARAM_INVALID_GROUP);     \
        return;                                                                      \
    }

#define ADC_VALIDATE_GROUP_RETURN(Group, ApiId, RetVal)                             \
    if (!Adc_IsValidGroup(Group)) {                                                 \
        Det_ReportError(ADC_MODULE_ID, 0, (ApiId), ADC_E_PARAM_INVALID_GROUP);     \
        return (RetVal);                                                             \
    }

#define ADC_VALIDATE_POINTER(Ptr, ApiId)                                            \
    if ((Ptr) == NULL_PTR) {                                                        \
        Det_ReportError(ADC_MODULE_ID, 0, (ApiId), ADC_E_PARAM_POINTER);           \
        return;                                                                      \
    }

#define ADC_VALIDATE_POINTER_RETURN(Ptr, ApiId, RetVal)                             \
    if ((Ptr) == NULL_PTR) {                                                        \
        Det_ReportError(ADC_MODULE_ID, 0, (ApiId), ADC_E_PARAM_POINTER);           \
        return (RetVal);                                                             \
    }
#else
#define ADC_VALIDATE_INIT(ApiId)
#define ADC_VALIDATE_INIT_RETURN(ApiId, RetVal)
#define ADC_VALIDATE_GROUP(Group, ApiId)
#define ADC_VALIDATE_GROUP_RETURN(Group, ApiId, RetVal)
#define ADC_VALIDATE_POINTER(Ptr, ApiId)
#define ADC_VALIDATE_POINTER_RETURN(Ptr, ApiId, RetVal)
#endif /* ADC_DEV_ERROR_DETECT */

#endif /* ADC_H */

/****************************************************************************************
*                                 END OF FILE                                          *
****************************************************************************************/
