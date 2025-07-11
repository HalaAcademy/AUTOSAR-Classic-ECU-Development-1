/**
 * @file Continuous_DMA_Example.c
 * @brief Continuous ADC conversion with DMA example
 * @details Demonstrates continuous ADC conversion with DMA and circular buffer
 * 
 * This example shows:
 * - Continuous conversion mode
 * - DMA-based data transfer
 * - Circular buffer management
 * - Real-time data processing
 * 
 * @author ADC Driver Team
 * @date 2025
 */

#include "Adc.h"
#include <stdio.h>
#include <string.h>

/* Configuration for continuous conversion */
#define BUFFER_SIZE 64
#define NUM_CHANNELS 3

static uint16_t adc_circular_buffer[BUFFER_SIZE * NUM_CHANNELS];
static uint32_t buffer_index = 0;
static uint32_t samples_processed = 0;

/* Data processing callback */
void Continuous_AdcNotification(void)
{
    /* Process new data in ISR context (keep minimal) */
    samples_processed++;
    
    /* Signal main application that new data is available */
    /* This could be a semaphore, flag, or queue notification */
}

/* Process ADC data in main context */
void ProcessAdcData(void)
{
    uint16_t channel_data[NUM_CHANNELS];
    
    /* Get latest samples */
    if (Adc_ReadGroup(ADC_GROUP_1, channel_data) == E_OK)
    {
        printf("Sample %lu: CH0=%d, CH1=%d, CH2=%d\n", 
               samples_processed, 
               channel_data[0], 
               channel_data[1], 
               channel_data[2]);
    }
}

int main(void)
{
    Std_ReturnType ret;
    uint32_t last_sample_count = 0;
    
    /* Initialize ADC driver */
    ret = Adc_Init(NULL);
    if (ret != E_OK)
    {
        printf("ADC initialization failed!\n");
        return -1;
    }
    
    /* Setup circular buffer for continuous conversion */
    ret = Adc_SetupResultBuffer(ADC_GROUP_1, adc_circular_buffer);
    if (ret != E_OK)
    {
        printf("Buffer setup failed!\n");
        return -1;
    }
    
    /* Enable group notification */
    Adc_EnableGroupNotification(ADC_GROUP_1);
    
    /* Start continuous conversion */
    ret = Adc_StartGroupConversion(ADC_GROUP_1);
    if (ret != E_OK)
    {
        printf("Failed to start conversion!\n");
        return -1;
    }
    
    printf("Starting continuous ADC conversion...\n");
    
    /* Main processing loop */
    for (int i = 0; i < 1000; i++)  /* Run for 1000 iterations */
    {
        /* Check if new data is available */
        if (samples_processed > last_sample_count)
        {
            ProcessAdcData();
            last_sample_count = samples_processed;
        }
        
        /* Simulate other work */
        for (volatile int j = 0; j < 10000; j++);
    }
    
    /* Stop continuous conversion */
    Adc_StopGroupConversion(ADC_GROUP_1);
    Adc_DisableGroupNotification(ADC_GROUP_1);
    
    printf("Processed %lu samples total\n", samples_processed);
    
    /* Cleanup */
    Adc_DeInit();
    
    return 0;
}
