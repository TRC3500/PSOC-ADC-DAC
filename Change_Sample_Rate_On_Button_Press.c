#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Declare variables
    uint8 adcResult;
    WaveDAC8_1_Start();       // Start WaveDAC to produce sine wave
    ADC_SAR_1_Start();        // Start A to D converter module
    ADC_SAR_1_StartConvert(); // Start doing conversions
    VDAC8_1_Start();          // Start VDAC
    int a = 200;
    int Pin = 0;
    int CountUpDown = 0;
    for (;;)
    {
        //****************************************************************************************
        // Switch push code
        // Code in the following section is used to set the sampling rate. Each time the switch is pushed, the sampling rate changes.
        // Sampling starts 5000 samples/S and then drops to 1000 samples/S
        if (Pin == 0)
        {
            if (Pin_3_Read() == 0) // Is switch pushed?
            {
                if (CountUpDown == 0)
                {
                    a = a + 200; // Yes so add to delay
                    Pin = 1;     // Set Pin to switch pushed.
                    if (a > 800)
                    {
                        CountUpDown = 1;
                    }
                }
                else
                {
                    a = a - 200;
                    Pin = 1;
                    if (a <= 200)
                    {
                        CountUpDown = 0;
                    }
                }
            }
        }
        if (Pin_3_Read() == 1) // See if switch released
        {
            Pin = 0; // If switch released, reset Pin to not pushed.
        }
        //*****************************************************************************************
        if (ADC_SAR_1_IsEndConversion(ADC_SAR_1_RETURN_STATUS) != 0) // Has it finished current conversion
        {
            adcResult = ADC_SAR_1_GetResult8(); // Yes, so get 8 bit result
            VDAC8_1_SetValue(adcResult);        // Send result back out to DAC
            CyDelayUs(a);                       // Delay a while
        }
    }
}