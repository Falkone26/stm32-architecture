#include "stm32f446xx.h"
#include <stdint.h>
#include <stm32f446xx_gpio_driver.h>

void delay(uint32_t maxTime);
void LEDInit();
void buttonInit();

int main(void)
{   

    /*PA5 is the on-board LED that will toggle*/
    /*PC13 is the on-board user button*/
    
    LEDInit();
    buttonInit();

    while(1)
    {
        
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

void buttonInit()
{
    GPIO_Handle_t userButton;

    userButton.pGPIOx = GPIOC;
    userButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
    userButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    userButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_FAST_SPEED;
    userButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

    GPIO_PeriClockControl(GPIOC, ENABLE);

    GPIO_Init(&userButton);

    //IRQ configuration
    GPIO_IRQPriorityConfig(IRQ_NO_EXTI5_10, NVIC_IRQ_PRI_15);
    GPIO_IRQInterruptConfig(IRQ_NO_EXTI5_10, ENABLE);
}

void EXTI15_10_IRQHandler(void)
{
    GPIO_IRQHandling(GPIO_PIN_13);
    GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);
    delay(250000);
}
