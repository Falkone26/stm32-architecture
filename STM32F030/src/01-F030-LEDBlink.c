#include "../includes/stm32f030xx.h"
#include <stdint.h>

void delay(uint32_t maxTime);
void LEDInit();

int main(void)
{
    /*PA5 is the on-board LED that will toggle*/
        
    LEDInit();

    while(1)
    {
      GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);
      delay(500000);
    }
    return 0;
}

void delay(uint32_t maxTime)
{
    for(volatile uint32_t t = 0; t < maxTime; t++);
}

void LEDInit()
{
    GPIO_Handle_t gpioLED;

    gpioLED.pGPIOx = GPIOA;
    gpioLED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
    gpioLED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
    gpioLED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_PP;
    gpioLED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    gpioLED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_FAST_SPEED;

    GPIO_PeriClockControl(GPIOA, ENABLE);

    GPIO_Init(&gpioLED);
}


