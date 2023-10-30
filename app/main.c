/**
 * @file    main.c
 * @brief   **Template Application entry point**
 *
 * The main file is the entry point of the application or any user code, please provide the 
 * proper description of this file according to your own implementation
 * This Demo app only blinks an LED connected to PortA Pin 5
 *
 * @note    Only the files inside folder app will be take them into account when the 
 *          doxygen runs by typing "make docs", index page is generated in
 *          Build/doxigen/html/index.html
 */
/**
 * @brief   **Application entry point**
 *
 * Ptovide the proper description for function main according to your own
 * implementation
 *
 * @retval  None
 */
//---------------------------------------------------------------------------------------------------
#include "app_bsp.h"
#include <stdio.h>

ADC_HandleTypeDef       AdcHandler;      /*adc handler estructure*/
ADC_ChannelConfTypeDef  sChanConfig;     /*adc channel configuration structure*/

extern void initialise_monitor_handles(void);

int main(void) 
{
    uint32_t value;        /*variable to store the adc conversion*/

    HAL_Init();           /*init HAL library*/

    /*Enable semihosting only to display adc lecture*/
    initialise_monitor_handles();
    printf("Hola semihosting\n\r");
    
    /* Conversion time is given by::
      Tcon = ( Tsampling + Tconv ) / ADC clock 
      Tcon = ( AdcHandler.Init.SamplingTimeCommon1 + AdcHandler.Init.Resolution ) / ( APB Clock / AdcHandler.Init.ClockPrescaler )
      Tcon = ( 1.5 + 8.5 ) / 8MHz = 1.25us */
    AdcHandler.Instance                   = ADC1;
    AdcHandler.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV2;   /*APB clock divided by two*/
    AdcHandler.Init.Resolution            = ADC_RESOLUTION8b;           /*8 bit resolution with a Tconv of 8.5*/
    AdcHandler.Init.ScanConvMode          = ADC_SCAN_SEQ_FIXED;         /*scan adc channels from 0 to 16 in that order*/
    AdcHandler.Init.DataAlign             = ADC_DATAALIGN_RIGHT;        /*data converter is right alightned*/
    AdcHandler.Init.SamplingTimeCommon1   = ADC_SAMPLETIME_1CYCLE_5;    /*sampling time of 1.5*/
    AdcHandler.Init.ExternalTrigConv      = ADC_SOFTWARE_START;         /*software trigger*/
    AdcHandler.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;        /*only applicable on ISR*/
    AdcHandler.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;   /*data will be overwriten in case is not read it*/
    /*apply ADC configuration*/
    HAL_ADC_Init( &AdcHandler );
    
    /*config adc channel number 0*/
    sChanConfig.Channel = ADC_CHANNEL_0;
    sChanConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
    sChanConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
    /*apply channel configuration*/
    HAL_ADC_ConfigChannel( &AdcHandler, &sChanConfig );

    /*Apply internal calibration*/
    HAL_ADCEx_Calibration_Start( &AdcHandler );
    
    while (1)
    {
        HAL_ADC_Start( &AdcHandler );                /*trigger conversion*/
        HAL_ADC_PollForConversion( &AdcHandler, 1u );/*wait untill conversion is performed, around 1.25us*/
        value = HAL_ADC_GetValue( &AdcHandler );     /*read the digital value*/

        printf( "Pot value: %lu\r\n", value );      /*print the adc value*/
        
        HAL_Delay( 1000u );                           /*retardo de 100ms*/
    }
}