/**
 * @file Simple_Oneshot_Example.c
 * @brief Simple ADC one-shot conversion example
 * @details Demonstrates basic ADC usage with one-shot conversion mode
 * 
 * This example shows:
 * - Basic ADC initialization
 * - Single channel one-shot conversion
 * - Result reading and error handling
 * 
 * @author ADC Driver Team
 * @date 2025
 */

#include "Adc.h"
#include <stdio.h>

/* Example configuration - single channel */
static uint16_t adc_result_buffer[1];

/* Simple notification callback */
void Simple_AdcNotification(void)
{
    printf("ADC conversion complete! Result: %d\n", adc_result_buffer[0]);
}

int main(void)
{
    Std_ReturnType ret;
    
    /* Initialize ADC driver */
    ret = Adc_Init(NULL);  /* Use default configuration */
    if (ret != E_OK)
    {
        printf("ADC initialization failed!\n");
        return -1;
    }
    
    /* Setup group for single channel conversion */
    ret = Adc_SetupResultBuffer(ADC_GROUP_0, adc_result_buffer);
    if (ret != E_OK)
    {
        printf("Buffer setup failed!\n");
        return -1;
    }
    
    /* Enable group notification */
    Adc_EnableGroupNotification(ADC_GROUP_0);
    
    /* Start one-shot conversion */
    ret = Adc_StartGroupConversion(ADC_GROUP_0);
    if (ret != E_OK)
    {
        printf("Failed to start conversion!\n");
        return -1;
    }
    
    /* Wait for conversion to complete */
    while (Adc_GetGroupStatus(ADC_GROUP_0) != ADC_STREAM_COMPLETED)
    {
        /* Wait or do other work */
    }
    
    /* Read result */
    ret = Adc_ReadGroup(ADC_GROUP_0, adc_result_buffer);
    if (ret != E_OK)
    {
        printf("Failed to read result!\n");
        return -1;
    }
    
    printf("Final result: %d\n", adc_result_buffer[0]);
    
    /* Cleanup */
    Adc_StopGroupConversion(ADC_GROUP_0);
    Adc_DisableGroupNotification(ADC_GROUP_0);
    Adc_DeInit();
    
    return 0;
}
