/**------------------------------------------------------------------------------------------------
 * Archivo con la funciones de las incilaizaciones auxiliares de la libreria
-------------------------------------------------------------------------------------------------*/
#include "app_bsp.h"

void HAL_MspInit( void )
{
    
}

/*This function is called in HAL_ADC_Init*/
void HAL_ADC_MspInit( ADC_HandleTypeDef* hadc )
{
    GPIO_InitTypeDef  GPIO_InitStruct;

    __ADC_CLK_ENABLE();  /*enable adc clock*/
    __GPIOA_CLK_ENABLE(); /*enable clock port where the adc 0 is connected*/
      
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; /*pin in analog mode*/
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
