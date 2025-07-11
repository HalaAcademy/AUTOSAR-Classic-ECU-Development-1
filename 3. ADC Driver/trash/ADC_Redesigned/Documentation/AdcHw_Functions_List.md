# AdcHw_* Functions Reference List

## Overview
This document provides a comprehensive list of all AdcHw_* (ADC Hardware Abstraction) functions in the ADC driver, including their locations, purposes, and where they are called from.

## Function Categories

### 1. Initialization and Configuration Functions

#### `AdcHw_Init()`
- **Location**: `Adc_Hw.c` (line 45)
- **Purpose**: Initialize ADC hardware module
- **Called from**: `Adc_Init()` in `Adc.c`
- **Parameters**: `const Adc_ConfigType* ConfigPtr`
- **Returns**: `Std_ReturnType`

#### `AdcHw_DeInit()`
- **Location**: `Adc_Hw.c` (line 89)
- **Purpose**: Deinitialize ADC hardware module
- **Called from**: `Adc_DeInit()` in `Adc.c`
- **Parameters**: `void`
- **Returns**: `Std_ReturnType`

#### `AdcHw_SetupResultBuffer()`
- **Location**: `Adc_Hw.c` (line 132)
- **Purpose**: Setup result buffer for hardware group
- **Called from**: `Adc_SetupResultBuffer()` in `Adc.c`
- **Parameters**: `Adc_GroupType Group`, `Adc_ValueGroupType* DataBufferPtr`
- **Returns**: `Std_ReturnType`

### 2. Group Management Functions

#### `AdcHw_StartGroupConversion()`
- **Location**: `Adc_Hw.c` (line 189)
- **Purpose**: Start hardware conversion for specified group
- **Called from**: `Adc_StartGroupConversion()` in `Adc.c`
- **Parameters**: `Adc_GroupType Group`
- **Returns**: `Std_ReturnType`

#### `AdcHw_StopGroupConversion()`
- **Location**: `Adc_Hw.c` (line 281)
- **Purpose**: Stop hardware conversion for specified group
- **Called from**: `Adc_StopGroupConversion()` in `Adc.c`
- **Parameters**: `Adc_GroupType Group`
- **Returns**: `Std_ReturnType`

#### `AdcHw_ReadGroup()`
- **Location**: `Adc_Hw.c` (line 345)
- **Purpose**: Read conversion results from hardware group
- **Called from**: `Adc_ReadGroup()` in `Adc.c`
- **Parameters**: `Adc_GroupType Group`, `Adc_ValueGroupType* DataBufferPtr`
- **Returns**: `Std_ReturnType`

### 3. Status and Query Functions

#### `AdcHw_GetGroupStatus()`
- **Location**: `Adc_Hw.c` (line 398)
- **Purpose**: Get current hardware status of ADC group
- **Called from**: `Adc_GetGroupStatus()` in `Adc.c`
- **Parameters**: `Adc_GroupType Group`
- **Returns**: `Adc_StatusType`

#### `AdcHw_GetStreamLastPointer()`
- **Location**: `Adc_Hw.c` (line 456)
- **Purpose**: Get pointer to last converted sample in hardware buffer
- **Called from**: `Adc_GetStreamLastPointer()` in `Adc.c`
- **Parameters**: `Adc_GroupType Group`, `Adc_ValueGroupType** PtrToSamplePtr`
- **Returns**: `Adc_StreamNumSampleType`

### 4. Notification Functions

#### `AdcHw_EnableGroupNotification()`
- **Location**: `Adc_Hw.c` (line 512)
- **Purpose**: Enable hardware interrupt notification for group
- **Called from**: `Adc_EnableGroupNotification()` in `Adc.c`
- **Parameters**: `Adc_GroupType Group`
- **Returns**: `void`

#### `AdcHw_DisableGroupNotification()`
- **Location**: `Adc_Hw.c` (line 548)
- **Purpose**: Disable hardware interrupt notification for group
- **Called from**: `Adc_DisableGroupNotification()` in `Adc.c`
- **Parameters**: `Adc_GroupType Group`
- **Returns**: `void`

### 5. Validation Functions

#### `AdcHw_IsValidGroup()`
- **Location**: `Adc_Hw.c` (line 583)
- **Purpose**: Validate if group ID is valid for hardware
- **Called from**: Multiple validation functions in `Adc.c`
- **Parameters**: `Adc_GroupType Group`
- **Returns**: `boolean`

#### `AdcHw_IsValidChannel()`
- **Location**: `Adc_Hw.c` (line 596)
- **Purpose**: Validate if channel ID is valid for hardware
- **Called from**: Configuration validation in `Adc.c`
- **Parameters**: `Adc_ChannelType Channel`
- **Returns**: `boolean`

#### `AdcHw_IsValidHwUnit()`
- **Location**: `Adc_Hw.c` (line 609)
- **Purpose**: Validate if hardware unit ID is valid
- **Called from**: Hardware unit validation in `Adc.c`
- **Parameters**: `Adc_HwUnitType HwUnit`
- **Returns**: `boolean`

### 6. Interrupt Service Routines

#### `AdcHw_Adc1_IrqHandler()`
- **Location**: `Adc_Hw.c` (line 622)
- **Purpose**: ADC1 interrupt service routine
- **Called from**: Hardware interrupt vector
- **Parameters**: `void`
- **Returns**: `void`

#### `AdcHw_Adc2_IrqHandler()`
- **Location**: `Adc_Hw.c` (line 672)
- **Purpose**: ADC2 interrupt service routine
- **Called from**: Hardware interrupt vector
- **Parameters**: `void`
- **Returns**: `void`

#### `AdcHw_Adc3_IrqHandler()`
- **Location**: `Adc_Hw.c` (line 722)
- **Purpose**: ADC3 interrupt service routine
- **Called from**: Hardware interrupt vector
- **Parameters**: `void`
- **Returns**: `void`

### 7. DMA Functions

#### `AdcHw_EnableDma()`
- **Location**: `Adc_Hw.c` (line 772)
- **Purpose**: Enable DMA for ADC group
- **Called from**: `AdcHw_StartGroupConversion()` when DMA is configured
- **Parameters**: `Adc_GroupType Group`
- **Returns**: `Std_ReturnType`

#### `AdcHw_DisableDma()`
- **Location**: `Adc_Hw.c` (line 823)
- **Purpose**: Disable DMA for ADC group
- **Called from**: `AdcHw_StopGroupConversion()` when DMA is configured
- **Parameters**: `Adc_GroupType Group`
- **Returns**: `Std_ReturnType`

#### `AdcHw_ConfigureDma()`
- **Location**: `Adc_Hw.c` (line 874)
- **Purpose**: Configure DMA settings for ADC group
- **Called from**: `AdcHw_SetupResultBuffer()` for DMA groups
- **Parameters**: `Adc_GroupType Group`, `uint32_t BufferAddress`, `uint16_t BufferSize`
- **Returns**: `Std_ReturnType`

### 8. Utility Functions

#### `AdcHw_GetHwUnitFromGroup()`
- **Location**: `Adc_Hw.c` (line 925)
- **Purpose**: Get hardware unit ID from group configuration
- **Called from**: Various AdcHw_* functions internally
- **Parameters**: `Adc_GroupType Group`
- **Returns**: `Adc_HwUnitType`

#### `AdcHw_GetChannelFromGroup()`
- **Location**: `Adc_Hw.c` (line 946)
- **Purpose**: Get channel list from group configuration
- **Called from**: Channel setup functions internally
- **Parameters**: `Adc_GroupType Group`, `Adc_ChannelType* ChannelList`
- **Returns**: `uint8_t` (number of channels)

#### `AdcHw_CalculateConversionTime()`
- **Location**: `Adc_Hw.c` (line 967)
- **Purpose**: Calculate expected conversion time for group
- **Called from**: Timing validation functions
- **Parameters**: `Adc_GroupType Group`
- **Returns**: `uint32_t` (time in microseconds)

### 9. Power Management Functions

#### `AdcHw_SetPowerState()`
- **Location**: `Adc_Hw.c` (line 988)
- **Purpose**: Set power state for ADC hardware
- **Called from**: Power management routines
- **Parameters**: `Adc_HwUnitType HwUnit`, `Adc_PowerStateType PowerState`
- **Returns**: `Std_ReturnType`

#### `AdcHw_GetPowerState()`
- **Location**: `Adc_Hw.c` (line 1009)
- **Purpose**: Get current power state of ADC hardware
- **Called from**: Power management status queries
- **Parameters**: `Adc_HwUnitType HwUnit`
- **Returns**: `Adc_PowerStateType`

### 10. Advanced Functions

#### `AdcHw_SetSamplingTime()`
- **Location**: `Adc_Hw.c` (line 1030)
- **Purpose**: Set sampling time for specific channel
- **Called from**: Channel configuration functions
- **Parameters**: `Adc_ChannelType Channel`, `uint8_t SamplingTime`
- **Returns**: `Std_ReturnType`

#### `AdcHw_GetSamplingTime()`
- **Location**: `Adc_Hw.c` (line 1051)
- **Purpose**: Get current sampling time for channel
- **Called from**: Configuration query functions
- **Parameters**: `Adc_ChannelType Channel`
- **Returns**: `uint8_t`

#### `AdcHw_SetTriggerSource()`
- **Location**: `Adc_Hw.c` (line 1072)
- **Purpose**: Set trigger source for ADC group
- **Called from**: Trigger configuration functions
- **Parameters**: `Adc_GroupType Group`, `Adc_TriggerSourceType TriggerSource`
- **Returns**: `Std_ReturnType`

#### `AdcHw_GetTriggerSource()`
- **Location**: `Adc_Hw.c` (line 1093)
- **Purpose**: Get current trigger source for group
- **Called from**: Configuration query functions
- **Parameters**: `Adc_GroupType Group`
- **Returns**: `Adc_TriggerSourceType`

## Function Call Hierarchy

```
Adc_Init()
└── AdcHw_Init()

Adc_DeInit()
└── AdcHw_DeInit()

Adc_StartGroupConversion()
├── AdcHw_IsValidGroup()
├── AdcHw_GetHwUnitFromGroup()
├── AdcHw_ConfigureDma() (if DMA enabled)
├── AdcHw_EnableDma() (if DMA enabled)
└── AdcHw_StartGroupConversion()

Adc_StopGroupConversion()
├── AdcHw_IsValidGroup()
├── AdcHw_DisableDma() (if DMA enabled)
└── AdcHw_StopGroupConversion()

Adc_ReadGroup()
├── AdcHw_IsValidGroup()
└── AdcHw_ReadGroup()

Adc_GetGroupStatus()
├── AdcHw_IsValidGroup()
└── AdcHw_GetGroupStatus()

Adc_SetupResultBuffer()
├── AdcHw_IsValidGroup()
├── AdcHw_ConfigureDma() (if DMA enabled)
└── AdcHw_SetupResultBuffer()

Adc_EnableGroupNotification()
├── AdcHw_IsValidGroup()
└── AdcHw_EnableGroupNotification()

Adc_DisableGroupNotification()
├── AdcHw_IsValidGroup()
└── AdcHw_DisableGroupNotification()

Adc_GetStreamLastPointer()
├── AdcHw_IsValidGroup()
└── AdcHw_GetStreamLastPointer()
```

## Implementation Status

### ✅ Fully Implemented
- Basic initialization and deinitialization
- Group start/stop conversion
- Status query functions
- Notification enable/disable
- Validation functions
- Interrupt service routines

### ⚠️ Partially Implemented
- DMA configuration (basic structure present)
- Power management (stubs implemented)
- Advanced configuration functions

### ❌ Not Yet Implemented
- Hardware-specific optimizations
- Error recovery mechanisms
- Performance monitoring
- Advanced trigger configurations

## Notes

1. **Hardware Dependency**: All AdcHw_* functions are hardware-specific and need to be adapted for different microcontroller platforms.

2. **Real-time Considerations**: ISR functions (`AdcHw_Adc*_IrqHandler`) should be kept minimal to maintain real-time performance.

3. **DMA Integration**: DMA-related functions are designed to work with STM32 DMA controllers and may need modification for other platforms.

4. **Validation**: Hardware validation functions are critical for system safety and should be thoroughly tested.

5. **Configuration**: Many functions depend on static configuration data in `Adc_Cfg.c`.

## Future Enhancements

1. **Performance Optimization**: Implement hardware-specific optimizations for better performance
2. **Error Handling**: Add more robust error handling and recovery mechanisms
3. **Debugging Support**: Add debug functions for development and testing
4. **Platform Abstraction**: Create better abstraction for multi-platform support
5. **Power Management**: Implement advanced power management features

---

**Document Version**: 1.0  
**Last Updated**: July 9, 2025  
**Author**: ADC Driver Team
