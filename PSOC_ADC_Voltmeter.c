#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Declare variables
    uint8 adcResult;
    float adcVolts;
    char tmpStr[15];
    UART_1_Start();               // Start the UART
    ADC_SAR_1_Start();            // Start A to D converter module
    ADC_SAR_1_StartConvert();     // Start doing conversions
    WaveDAC8_1_Start();           // Start WaveDAC to produce sine wave
    for (int i = 0; i < 100; i++) // Get 100 samples
    {
        if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_RETURN_STATUS) != 0) // Has it finished current conversion
        {
            adcResult = ADC_SAR_1_GetResult8();             // Yes so get 8 bit result
            adcVolts = ADC_SAR_1_CountsTo_Volts(adcResult); // Convert to volts for display
            sprintf(tmpStr, "%1.1fV ", adcVolts);           // Create text string
            UART_1_PutString(tmpStr);                       // Print string to console
            CyDelay(5);                                     // Delay 5mS (200 samples/S)
            UART_1_WriteTxData(0x20);                       // Place a space between characters
        }
    }
}