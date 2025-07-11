/**
 * @file Multi_Group_Example.c
 * @brief Multi-group ADC conversion example
 * @details Demonstrates managing multiple ADC groups with different configurations
 * 
 * This example shows:
 * - Multiple group management
 * - Different conversion modes per group
 * - Priority handling
 * - Resource sharing
 * 
 * @author ADC Driver Team
 * @date 2025
 */

#include "Adc.h"
#include <stdio.h>

/* Configuration for multiple groups */
#define GROUP0_CHANNELS 1  /* Single channel, high priority */
#define GROUP1_CHANNELS 4  /* Multi-channel, medium priority */
#define GROUP2_CHANNELS 2  /* Dual channel, low priority */

static uint16_t group0_buffer[GROUP0_CHANNELS];
static uint16_t group1_buffer[GROUP1_CHANNELS];
static uint16_t group2_buffer[GROUP2_CHANNELS];

/* Group status tracking */
static boolean group0_complete = FALSE;
static boolean group1_complete = FALSE;
static boolean group2_complete = FALSE;

/* Group-specific notifications */
void Group0_AdcNotification(void)
{
    printf("Group 0 (high priority) conversion complete\n");
    group0_complete = TRUE;
}

void Group1_AdcNotification(void)
{
    printf("Group 1 (medium priority) conversion complete\n");
    group1_complete = TRUE;
}

void Group2_AdcNotification(void)
{
    printf("Group 2 (low priority) conversion complete\n");
    group2_complete = TRUE;
}

/* Process results from each group */
void ProcessGroupResults(void)
{
    Std_ReturnType ret;
    
    /* Process Group 0 results */
    if (group0_complete)
    {
        ret = Adc_ReadGroup(ADC_GROUP_0, group0_buffer);
        if (ret == E_OK)
        {
            printf("Group 0 result: %d\n", group0_buffer[0]);
        }
        group0_complete = FALSE;
    }
    
    /* Process Group 1 results */
    if (group1_complete)
    {
        ret = Adc_ReadGroup(ADC_GROUP_1, group1_buffer);
        if (ret == E_OK)
        {
            printf("Group 1 results: %d, %d, %d, %d\n", 
                   group1_buffer[0], group1_buffer[1], 
                   group1_buffer[2], group1_buffer[3]);
        }
        group1_complete = FALSE;
    }
    
    /* Process Group 2 results */
    if (group2_complete)
    {
        ret = Adc_ReadGroup(ADC_GROUP_2, group2_buffer);
        if (ret == E_OK)
        {
            printf("Group 2 results: %d, %d\n", 
                   group2_buffer[0], group2_buffer[1]);
        }
        group2_complete = FALSE;
    }
}

int main(void)
{
    Std_ReturnType ret;
    int conversion_cycle = 0;
    
    /* Initialize ADC driver */
    ret = Adc_Init(NULL);
    if (ret != E_OK)
    {
        printf("ADC initialization failed!\n");
        return -1;
    }
    
    /* Setup buffers for all groups */
    ret = Adc_SetupResultBuffer(ADC_GROUP_0, group0_buffer);
    if (ret != E_OK)
    {
        printf("Group 0 buffer setup failed!\n");
        return -1;
    }
    
    ret = Adc_SetupResultBuffer(ADC_GROUP_1, group1_buffer);
    if (ret != E_OK)
    {
        printf("Group 1 buffer setup failed!\n");
        return -1;
    }
    
    ret = Adc_SetupResultBuffer(ADC_GROUP_2, group2_buffer);
    if (ret != E_OK)
    {
        printf("Group 2 buffer setup failed!\n");
        return -1;
    }
    
    /* Enable notifications for all groups */
    Adc_EnableGroupNotification(ADC_GROUP_0);
    Adc_EnableGroupNotification(ADC_GROUP_1);
    Adc_EnableGroupNotification(ADC_GROUP_2);
    
    printf("Starting multi-group ADC conversions...\n");
    
    /* Main conversion loop */
    for (conversion_cycle = 0; conversion_cycle < 10; conversion_cycle++)
    {
        printf("\n=== Conversion Cycle %d ===\n", conversion_cycle + 1);
        
        /* Start all groups (priority will be handled by driver) */
        Adc_StartGroupConversion(ADC_GROUP_0);  /* High priority */
        Adc_StartGroupConversion(ADC_GROUP_1);  /* Medium priority */
        Adc_StartGroupConversion(ADC_GROUP_2);  /* Low priority */
        
        /* Wait for all conversions to complete */
        while (!group0_complete || !group1_complete || !group2_complete)
        {
            /* Process any completed groups */
            ProcessGroupResults();
            
            /* Check group status */
            if (Adc_GetGroupStatus(ADC_GROUP_0) == ADC_STREAM_COMPLETED)
                group0_complete = TRUE;
            if (Adc_GetGroupStatus(ADC_GROUP_1) == ADC_STREAM_COMPLETED)
                group1_complete = TRUE;
            if (Adc_GetGroupStatus(ADC_GROUP_2) == ADC_STREAM_COMPLETED)
                group2_complete = TRUE;
        }
        
        /* Process final results */
        ProcessGroupResults();
        
        /* Delay between cycles */
        for (volatile int i = 0; i < 100000; i++);
    }
    
    /* Stop all groups */
    Adc_StopGroupConversion(ADC_GROUP_0);
    Adc_StopGroupConversion(ADC_GROUP_1);
    Adc_StopGroupConversion(ADC_GROUP_2);
    
    /* Disable notifications */
    Adc_DisableGroupNotification(ADC_GROUP_0);
    Adc_DisableGroupNotification(ADC_GROUP_1);
    Adc_DisableGroupNotification(ADC_GROUP_2);
    
    printf("\nMulti-group conversion complete!\n");
    
    /* Cleanup */
    Adc_DeInit();
    
    return 0;
}
