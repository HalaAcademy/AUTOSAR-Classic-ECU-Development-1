/**
 * @file Hardware_Trigger_Example.c
 * @brief Hardware-triggered ADC conversion example
 * @details Demonstrates ADC conversion triggered by hardware events (timer, external)
 * 
 * This example shows:
 * - Hardware trigger configuration
 * - Timer-based triggering
 * - Synchronized data acquisition
 * - Event-driven processing
 * 
 * @author ADC Driver Team
 * @date 2025
 */

#include "Adc.h"
#include <stdio.h>

/* Configuration for hardware-triggered conversion */
#define TRIGGER_BUFFER_SIZE 16
#define TRIGGER_CHANNELS 2

static uint16_t trigger_buffer[TRIGGER_BUFFER_SIZE * TRIGGER_CHANNELS];
static uint32_t trigger_count = 0;
static boolean trigger_complete = FALSE;

/* Hardware trigger notification */
void HwTrigger_AdcNotification(void)
{
    trigger_count++;
    
    /* Check if we've collected enough samples */
    if (trigger_count >= TRIGGER_BUFFER_SIZE)
    {
        trigger_complete = TRUE;
    }
}

/* Process triggered data */
void ProcessTriggeredData(void)
{
    uint16_t sample_data[TRIGGER_CHANNELS];
    
    printf("=== Hardware Trigger Results ===\n");
    
    for (int i = 0; i < TRIGGER_BUFFER_SIZE; i++)
    {
        sample_data[0] = trigger_buffer[i * TRIGGER_CHANNELS + 0];
        sample_data[1] = trigger_buffer[i * TRIGGER_CHANNELS + 1];
        
        printf("Trigger %d: CH0=%d, CH1=%d\n", i, sample_data[0], sample_data[1]);
    }
    
    printf("Total triggers: %lu\n", trigger_count);
}

int main(void)
{
    Std_ReturnType ret;
    
    /* Initialize ADC driver */
    ret = Adc_Init(NULL);
    if (ret != E_OK)
    {
        printf("ADC initialization failed!\n");
        return -1;
    }
    
    /* Setup buffer for hardware-triggered group */
    ret = Adc_SetupResultBuffer(ADC_GROUP_2, trigger_buffer);
    if (ret != E_OK)
    {
        printf("Buffer setup failed!\n");
        return -1;
    }
    
    /* Enable group notification */
    Adc_EnableGroupNotification(ADC_GROUP_2);
    
    /* Configure hardware trigger (implementation-specific) */
    /* This would typically involve timer or external trigger setup */
    printf("Configuring hardware trigger...\n");
    
    /* Start hardware-triggered conversion */
    ret = Adc_StartGroupConversion(ADC_GROUP_2);
    if (ret != E_OK)
    {
        printf("Failed to start conversion!\n");
        return -1;
    }
    
    printf("Waiting for hardware triggers...\n");
    
    /* Wait for triggers to complete */
    while (!trigger_complete)
    {
        /* Wait for hardware triggers */
        /* In real implementation, this could be event-driven */
        
        /* Show progress */
        if (trigger_count > 0 && (trigger_count % 4) == 0)
        {
            printf("Triggers received: %lu/%d\n", trigger_count, TRIGGER_BUFFER_SIZE);
        }
        
        /* Simulate other work */
        for (volatile int i = 0; i < 50000; i++);
    }
    
    /* Process collected data */
    ProcessTriggeredData();
    
    /* Stop hardware-triggered conversion */
    Adc_StopGroupConversion(ADC_GROUP_2);
    Adc_DisableGroupNotification(ADC_GROUP_2);
    
    /* Cleanup */
    Adc_DeInit();
    
    return 0;
}
