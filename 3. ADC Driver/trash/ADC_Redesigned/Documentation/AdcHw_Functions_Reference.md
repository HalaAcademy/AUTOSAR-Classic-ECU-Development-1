# ADC Hardware Layer (AdcHw) Functions Reference

## Overview

This document provides a comprehensive reference for all ADC Hardware Layer (AdcHw) functions, their purpose, parameters, and where they are called within the ADC driver architecture.

## Table of Contents

1. [Function Categories](#function-categories)
2. [Initialization Functions](#initialization-functions)
3. [Conversion Control Functions](#conversion-control-functions)
4. [Result Handling Functions](#result-handling-functions)
5. [Status Functions](#status-functions)
6. [Interrupt Functions](#interrupt-functions)
7. [Queue Management Functions](#queue-management-functions)
8. [DMA Functions](#dma-functions)
9. [Channel Configuration Functions](#channel-configuration-functions)
10. [Deferred Processing Functions](#deferred-processing-functions)
11. [Validation Functions](#validation-functions)
12. [Utility Functions](#utility-functions)
13. [Streaming Functions](#streaming-functions)
14. [Internal Static Functions](#internal-static-functions)
15. [Function Usage Summary](#function-usage-summary)
16. [Missing or Problematic Functions](#missing-or-problematic-functions)

## Function Categories

The ADC Hardware Layer contains **44 functions** organized into the following categories:

- **🟢 Actively Used**: 17 functions
- **🟡 Internally Used Only**: 15 functions  
- **🔴 Not Yet Implemented/Called**: 12 functions

---

## Initialization Functions

### AdcHw_Init()
```c
Std_ReturnType AdcHw_Init(Adc_HwUnitType HwUnitId);
```
**Purpose**: Initialize ADC hardware module  
**Called From**: `Adc.c:Adc_Init()` (line 100)  
**Status**: 🟢 **Actively Used**  
**Description**: Initializes the specified ADC hardware unit, configures clocks, hardware module, NVIC, and performs calibration.

### AdcHw_DeInit()
```c
Std_ReturnType AdcHw_DeInit(Adc_HwUnitType HwUnitId);
```
**Purpose**: Deinitialize ADC hardware module  
**Called From**: `Adc.c:Adc_DeInit()` (line 149)  
**Status**: 🟢 **Actively Used**  
**Description**: Stops conversions, disables interrupts, resets ADC module, and cleans up runtime data.

### AdcHw_ConfigureGroup()
```c
Std_ReturnType AdcHw_ConfigureGroup(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Configure ADC hardware module for a specific group  
**Called From**: Internal calls in `AdcHw_StartSwConversion()` and `AdcHw_StartHwConversion()`  
**Status**: 🟡 **Internally Used**  
**Description**: Configures hardware settings based on group requirements, including channels and DMA if enabled.

---

## Conversion Control Functions

### AdcHw_StartSwConversion()
```c
Std_ReturnType AdcHw_StartSwConversion(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Start software-triggered conversion  
**Called From**: `Adc.c:Adc_StartGroupConversion()` (line 230)  
**Status**: 🟢 **Actively Used**  
**Description**: Initiates software-triggered ADC conversion for the specified group. Handles queue management if hardware unit is busy.

### AdcHw_StopSwConversion()
```c
Std_ReturnType AdcHw_StopSwConversion(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Stop software-triggered conversion  
**Called From**: `Adc.c:Adc_StopGroupConversion()` (line 271)  
**Status**: 🟢 **Actively Used**  
**Description**: Stops ongoing software-triggered conversion and manages queue for next pending conversion.

### AdcHw_StartHwConversion()
```c
Std_ReturnType AdcHw_StartHwConversion(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Start hardware-triggered conversion  
**Called From**: 
- `Adc.c:Adc_StartGroupConversion()` (line 238)
- `Adc.c:Adc_EnableHardwareTrigger()` (line 374)  
**Status**: 🟢 **Actively Used**  
**Description**: Configures and starts hardware-triggered ADC conversion with external trigger sources.

### AdcHw_StopHwConversion()
```c
Std_ReturnType AdcHw_StopHwConversion(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Stop hardware-triggered conversion  
**Called From**: 
- `Adc.c:Adc_StopGroupConversion()` (line 279)
- `Adc.c:Adc_DisableHardwareTrigger()` (line 405)  
**Status**: 🟢 **Actively Used**  
**Description**: Disables hardware triggers and stops ongoing hardware-triggered conversions.

---

## Result Handling Functions

### AdcHw_ReadResult()
```c
Std_ReturnType AdcHw_ReadResult(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId, Adc_ValueGroupType* ResultPtr);
```
**Purpose**: Read conversion result  
**Called From**: `Adc.c:Adc_ReadGroup()` (line 327)  
**Status**: 🟢 **Actively Used**  
**Description**: Reads conversion results from the specified group and copies them to the provided buffer.

### AdcHw_ReadStreamingResults()
```c
Std_ReturnType AdcHw_ReadStreamingResults(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId, Adc_ValueGroupType* ResultPtr, Adc_StreamNumSampleType NumSamples);
```
**Purpose**: Read streaming results  
**Called From**: **Not implemented yet**  
**Status**: 🔴 **Not Yet Implemented**  
**Description**: Future function for reading streaming conversion results.

---

## Status Functions

### AdcHw_GetGroupRuntimeStatus()
```c
Adc_StatusType AdcHw_GetGroupRuntimeStatus(Adc_GroupType GroupId);
```
**Purpose**: Get private ADC group runtime status  
**Called From**: 
- `Adc.c:Adc_DeInit()` (lines 136, 137)
- `Adc.c:Adc_StartGroupConversion()` (line 187)
- `Adc.c:Adc_ReadGroup()` (lines 313, 314)
- `Adc.c:Adc_EnableHardwareTrigger()` (line 364)
- `Adc.c:Adc_GetGroupStatus()` (line 481)  
**Status**: 🟢 **Actively Used**  
**Description**: Returns the current runtime status of the specified ADC group.

### AdcHw_SetGroupRuntimeStatus()
```c
void AdcHw_SetGroupRuntimeStatus(Adc_GroupType GroupId, Adc_StatusType GroupStatus);
```
**Purpose**: Set private ADC group runtime status  
**Called From**: **Internal use only**  
**Status**: 🟡 **Internally Used**  
**Description**: Updates the runtime status of the specified ADC group.

### AdcHw_GetGroupRuntimeSampCounter()
```c
void AdcHw_GetGroupRuntimeSampCounter(Adc_GroupType GroupId);
```
**Purpose**: Get sample counter  
**Called From**: `Adc.c:Adc_GetStreamingSamplesCount()` (line 528)  
**Status**: 🟢 **Actively Used**  
**Description**: Returns the current sample counter for streaming operations.

### AdcHw_ResetGroupRuntime()
```c
Std_ReturnType AdcHw_ResetGroupRuntime(Adc_GroupType GroupId);
```
**Purpose**: Reset group runtime parameters  
**Called From**: **Not called yet**  
**Status**: 🔴 **Not Yet Used**  
**Description**: Resets all runtime data for the specified group to initial state.

### AdcHw_ResetHwRuntime()
```c
Std_ReturnType AdcHw_ResetHwRuntime(Adc_HwUnitType HwUnitId);
```
**Purpose**: Reset hardware runtime parameters  
**Called From**: **Not called yet**  
**Status**: 🔴 **Not Yet Used**  
**Description**: Resets all runtime data for the specified hardware unit.

### AdcHw_IsUnitBusy()
```c
boolean AdcHw_IsUnitBusy(Adc_HwUnitType HwUnitId);
```
**Purpose**: Check if hardware unit is busy  
**Called From**: `Adc.c:Adc_GetHwUnitStatus()` (line 581)  
**Status**: 🟢 **Actively Used**  
**Description**: Returns whether the specified hardware unit is currently busy with conversions.

### AdcHw_GetCurrentChannel()
```c
Adc_ChannelType AdcHw_GetCurrentChannel(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Get current converting channel  
**Called From**: **Not called yet**  
**Status**: 🔴 **Not Yet Used**  
**Description**: Returns the currently converting channel for the specified group.

---

## Interrupt Functions

### AdcHw_InterruptHandler()
```c
void AdcHw_InterruptHandler(Adc_HwUnitType HwUnitId);
```
**Purpose**: ADC interrupt service routine  
**Called From**: `Adc.c:Adc_IsrHandler()` (line 634)  
**Status**: 🟢 **Actively Used**  
**Description**: Handles ADC end-of-conversion interrupts, reads results, and manages channel sequencing.

### AdcHw_DmaInterruptHandler()
```c
void AdcHw_DmaInterruptHandler(Adc_HwUnitType HwUnitId);
```
**Purpose**: DMA interrupt service routine  
**Called From**: **ISR (external)**  
**Status**: 🟢 **Actively Used**  
**Description**: Handles DMA transfer complete interrupts for ADC conversions.

### AdcHw_EnableInterrupt()
```c
Std_ReturnType AdcHw_EnableInterrupt(Adc_HwUnitType HwUnitId, uint8 InterruptType);
```
**Purpose**: Enable ADC interrupts  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Enables specified ADC interrupt types (EOC, DMA_TC, etc.).

### AdcHw_DisableInterrupt()
```c
Std_ReturnType AdcHw_DisableInterrupt(Adc_HwUnitType HwUnitId, uint8 InterruptType);
```
**Purpose**: Disable ADC interrupts  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Disables specified ADC interrupt types.

---

## Queue Management Functions
*Available when `ADC_ENABLE_QUEUING == STD_ON`*

### AdcHw_AddToQueue()
```c
Std_ReturnType AdcHw_AddToQueue(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Add group to conversion queue  
**Called From**: Called internally when unit busy  
**Status**: 🟡 **Internally Used**  
**Description**: Adds a group to the conversion queue when hardware unit is busy.

### AdcHw_RemoveFromQueue()
```c
Std_ReturnType AdcHw_RemoveFromQueue(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Remove group from conversion queue  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Removes a group from the conversion queue.

### AdcHw_GetNextGroupFromQueue()
```c
Adc_GroupType AdcHw_GetNextGroupFromQueue(Adc_HwUnitType HwUnitId);
```
**Purpose**: Get next group from queue  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Returns the next group to be processed from the queue.

### AdcHw_IsGroupInQueue()
```c
Adc_GroupType AdcHw_IsGroupInQueue(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Check if group is in queue  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Returns the index of the group in queue or ADC_INVALID_GROUP_ID if not found.

### AdcHw_ClearQueue()
```c
Std_ReturnType AdcHw_ClearQueue(Adc_HwUnitType HwUnitId);
```
**Purpose**: Clear conversion queue  
**Called From**: **Not called yet**  
**Status**: 🔴 **Not Yet Used**  
**Description**: Clears all groups from the conversion queue.

---

## DMA Functions
*Available when `ADC_ENABLE_DMA == STD_ON`*

### AdcHw_InitDma()
```c
Std_ReturnType AdcHw_InitDma(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Initialize DMA for ADC conversion  
**Called From**: Called internally during group config  
**Status**: 🟡 **Internally Used**  
**Description**: Initializes DMA channels for ADC data transfer.

### AdcHw_DeInitDma()
```c
Std_ReturnType AdcHw_DeInitDma(Adc_HwUnitType HwUnitId);
```
**Purpose**: Deinitialize DMA for ADC conversion  
**Called From**: Called internally during deinit  
**Status**: 🟡 **Internally Used**  
**Description**: Deinitializes DMA channels used for ADC.

### AdcHw_EnableDma()
```c
Std_ReturnType AdcHw_EnableDma(Adc_HwUnitType HwUnitId);
```
**Purpose**: Enable DMA for ADC conversion  
**Called From**: **Not implemented yet**  
**Status**: 🔴 **Not Yet Implemented**  
**Description**: Enables DMA transfer for ADC conversions.

### AdcHw_DisableDma()
```c
Std_ReturnType AdcHw_DisableDma(Adc_HwUnitType HwUnitId);
```
**Purpose**: Disable DMA for ADC conversion  
**Called From**: **Not implemented yet**  
**Status**: 🔴 **Not Yet Implemented**  
**Description**: Disables DMA transfer for ADC conversions.

---

## Channel Configuration Functions

### AdcHw_ConfigureChannels()
```c
Std_ReturnType AdcHw_ConfigureChannels(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Configure ADC channels for a group  
**Called From**: Called internally in `AdcHw_ConfigureGroup()`  
**Status**: 🟡 **Internally Used**  
**Description**: Configures all channels in the specified group for conversion.

### AdcHw_ConfigureChannel()
```c
Std_ReturnType AdcHw_ConfigureChannel(ADC_TypeDef* ADCx, Adc_ChannelType ChannelId, uint8 Rank, Adc_SamplingTimeType SampleTime);
```
**Purpose**: Configure a single ADC channel  
**Called From**: Called internally in `AdcHw_ConfigureChannels()`  
**Status**: 🟡 **Internally Used**  
**Description**: Configures a single channel with rank and sampling time settings.

---

## Deferred Processing Functions

### AdcHw_MainFunction()
```c
void AdcHw_MainFunction(void);
```
**Purpose**: Main function for deferred processing  
**Called From**: `Adc.c:Adc_MainFunction()` (line 623)  
**Status**: 🟢 **Actively Used**  
**Description**: Processes completed conversions in main context to minimize ISR execution time.

### AdcHw_ProcessCompletedConversions()
```c
void AdcHw_ProcessCompletedConversions(Adc_HwUnitType HwUnitId);
```
**Purpose**: Process completed conversions  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Handles completed conversion processing in deferred context.

### AdcHw_HandleGroupCompletion()
```c
void AdcHw_HandleGroupCompletion(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Handle group completion  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Handles group completion logic and notification callbacks.

---

## Validation Functions

### AdcHw_ValidateHwUnit()
```c
boolean AdcHw_ValidateHwUnit(Adc_HwUnitType HwUnitId);
```
**Purpose**: Validate hardware unit ID  
**Called From**: Called internally throughout  
**Status**: 🟡 **Internally Used**  
**Description**: Validates if the hardware unit ID is within valid range.

### AdcHw_ValidateGroup()
```c
boolean AdcHw_ValidateGroup(Adc_GroupType GroupId);
```
**Purpose**: Validate group ID  
**Called From**: Called internally throughout  
**Status**: 🟡 **Internally Used**  
**Description**: Validates if the group ID is within valid range.

### AdcHw_ValidateChannel()
```c
boolean AdcHw_ValidateChannel(Adc_ChannelType ChannelId);
```
**Purpose**: Validate channel ID  
**Called From**: Called internally throughout  
**Status**: 🟡 **Internally Used**  
**Description**: Validates if the channel ID is within valid range.

---

## Utility Functions

### AdcHw_GetHwChannelNumber()
```c
uint8 AdcHw_GetHwChannelNumber(Adc_ChannelType ChannelId);
```
**Purpose**: Convert ADC channel ID to hardware channel number  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Maps logical channel ID to physical hardware channel number.

### AdcHw_GetHwSampleTime()
```c
uint32 AdcHw_GetHwSampleTime(Adc_SamplingTimeType SampleTime);
```
**Purpose**: Convert sampling time to hardware register value  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Converts sampling time enumeration to hardware register value.

### AdcHw_GetHwTriggerSource()
```c
uint32 AdcHw_GetHwTriggerSource(Adc_TriggerSourceType TriggerSource);
```
**Purpose**: Get hardware trigger source  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Maps trigger source enumeration to hardware trigger configuration.

---

## Streaming Functions
*Available when `ADC_ENABLE_STREAMING == STD_ON`*

### AdcHw_ConfigureStreamingBuffer()
```c
Std_ReturnType AdcHw_ConfigureStreamingBuffer(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId, Adc_ValueGroupType* BufferPtr, uint16 BufferSize, Adc_StreamBufferModeType BufferMode);
```
**Purpose**: Configure streaming buffer  
**Called From**: **Not implemented yet**  
**Status**: 🔴 **Not Yet Implemented**  
**Description**: Configures buffer for streaming ADC conversions.

### AdcHw_StartStreaming()
```c
Std_ReturnType AdcHw_StartStreaming(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Start streaming conversion  
**Called From**: **Not implemented yet**  
**Status**: 🔴 **Not Yet Implemented**  
**Description**: Starts streaming ADC conversions.

### AdcHw_StopStreaming()
```c
Std_ReturnType AdcHw_StopStreaming(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Stop streaming conversion  
**Called From**: **Not implemented yet**  
**Status**: 🔴 **Not Yet Implemented**  
**Description**: Stops streaming ADC conversions.

### AdcHw_GetStreamingStatus()
```c
Std_ReturnType AdcHw_GetStreamingStatus(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId, uint16* FilledSamples);
```
**Purpose**: Get streaming buffer status  
**Called From**: **Not implemented yet**  
**Status**: 🔴 **Not Yet Implemented**  
**Description**: Returns the status of streaming buffer and filled samples count.

---

## Internal Static Functions

### AdcHw_ConfigureHwModule()
```c
static inline Std_ReturnType AdcHw_ConfigureHwModule(Adc_HwUnitType HwUnitId);
```
**Purpose**: Configure hardware module  
**Called From**: Called internally in `AdcHw_Init()`  
**Status**: 🟡 **Internally Used**  
**Description**: Configures ADC hardware module with default settings.

### AdcHw_ConfigureClocks()
```c
static inline Std_ReturnType AdcHw_ConfigureClocks(Adc_HwUnitType HwUnitId);
```
**Purpose**: Configure clocks  
**Called From**: Called internally in `AdcHw_Init()`  
**Status**: 🟡 **Internally Used**  
**Description**: Enables and configures ADC clocks.

### AdcHw_ConfigureNvic()
```c
static Std_ReturnType AdcHw_ConfigureNvic(Adc_HwUnitType HwUnitId);
```
**Purpose**: Configure NVIC  
**Called From**: Called internally in `AdcHw_Init()`  
**Status**: 🟡 **Internally Used**  
**Description**: Configures NVIC for ADC interrupts.

### AdcHw_HandleChannelSequencing()
```c
static void AdcHw_HandleChannelSequencing(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Handle channel sequencing  
**Called From**: Called internally in ISR  
**Status**: 🟡 **Internally Used**  
**Description**: Manages multi-channel conversion sequencing in interrupt context.

### AdcHw_ProcessGroupCompletion()
```c
static void AdcHw_ProcessGroupCompletion(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Process group completion  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Handles group completion processing and notifications.

### AdcHw_StartNextConversion()
```c
static void AdcHw_StartNextConversion(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Start next conversion  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Initiates the next conversion in a sequence.

### AdcHw_HandleBufferWrapping()
```c
static inline void AdcHw_HandleBufferWrapping(Adc_HwUnitType HwUnitId, Adc_GroupType GroupId);
```
**Purpose**: Handle buffer wrapping  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Manages circular buffer wrapping for continuous conversions.

### AdcHw_CallNotification()
```c
static void AdcHw_CallNotification(Adc_GroupType GroupId);
```
**Purpose**: Call notification callback  
**Called From**: Called internally  
**Status**: 🟡 **Internally Used**  
**Description**: Invokes user notification callbacks when enabled.

### AdcHw_GetCurrentTime()
```c
static uint32 AdcHw_GetCurrentTime(void);
```
**Purpose**: Get current time for performance monitoring  
**Called From**: Called internally for monitoring  
**Status**: 🟡 **Internally Used**  
**Description**: Returns current time for ISR performance monitoring.

---

## Function Usage Summary

| Category | Count | Status |
|----------|-------|--------|
| **Actively Used** | 17 | 🟢 |
| **Internally Used Only** | 15 | 🟡 |
| **Not Yet Implemented/Called** | 12 | 🔴 |
| **Total Functions** | **44** | |

### Actively Used Functions (17)
Functions directly called from the main ADC driver layer and essential for operation.

### Internally Used Functions (15)
Functions used within the hardware layer for abstraction and internal operations.

### Not Yet Implemented Functions (12)
Functions declared but not yet implemented or called, including streaming and some DMA functions.

---

## Missing or Problematic Functions

### 1. AdcHw_IsValidHwUnit() 
**Issue**: Called in `Adc.c:572` but not defined  
**Solution**: Should use `AdcHw_ValidateHwUnit()` instead  
**Location**: `Adc.c:Adc_GetHwUnitStatus()`

### 2. DMA Functions
**Issue**: Partially implemented  
**Status**: `AdcHw_InitDma()` and `AdcHw_DeInitDma()` exist but `AdcHw_EnableDma()` and `AdcHw_DisableDma()` are not implemented  
**Impact**: DMA functionality is incomplete

### 3. Streaming Functions
**Issue**: Declared but not implemented  
**Functions**: 
- `AdcHw_ConfigureStreamingBuffer()`
- `AdcHw_StartStreaming()`
- `AdcHw_StopStreaming()`
- `AdcHw_GetStreamingStatus()`  
**Impact**: Streaming mode not available

### 4. Reset Functions
**Issue**: Declared but not used  
**Functions**:
- `AdcHw_ResetGroupRuntime()`
- `AdcHw_ResetHwRuntime()`  
**Impact**: No runtime reset capability

### 5. Queue Clear Function
**Issue**: Declared but not used  
**Function**: `AdcHw_ClearQueue()`  
**Impact**: No way to clear pending queue

---

## Implementation Priority

### High Priority (Critical for Operation)
1. Fix `AdcHw_IsValidHwUnit()` function name mismatch
2. Complete DMA enable/disable functions
3. Implement reset functions for error recovery

### Medium Priority (Enhanced Functionality)
1. Implement streaming functions for continuous operation
2. Add queue clear functionality
3. Complete utility functions

### Low Priority (Performance Optimization)
1. Enhance performance monitoring
2. Add power management functions
3. Implement advanced synchronization features

---

## Conclusion

The ADC Hardware Layer provides a comprehensive abstraction for ADC operations with 44 functions covering initialization, conversion control, result handling, status management, and advanced features. While most core functionality is implemented and actively used, some advanced features like streaming and complete DMA support require further implementation to achieve full functionality.

The architecture successfully separates hardware-specific operations from the main driver logic, making the code maintainable and portable across different hardware platforms.
