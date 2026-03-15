#include <stdint.h>
#include <string.h>
#include "stm32f446xx.h"

/*
*   PC13 - UserButton
*
*   PA4 - SPI1_NSS
*   PA5 - SPI1_SCLK
*   PA6 - SPI1_MISO    
*   PA7 - SPI1_MOSI
*/

#define BUTTON_PRESSED  1

void SPI1_GPIOInit(void);
void SPI1_Init(void);
void buttonInit(void);

void delay(uint32_t maxTime);

int main(void)
{
    char user_data[] = "SPI is working!";

    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_PeriClockControl(GPIOC, ENABLE);

    SPI_PeriClockControl(SPI1, ENABLE);

    SPI1_GPIOInit();
    SPI1_Init();

    buttonInit();

    SPI_SSOEConfig(SPI1, ENABLE);

    while(1)
    {

        while(GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_13 ));
        //while(!(SPI_FlagStatus(SPI1, SPI_TXE_FLAG)));
        delay(200000);
            
        SPIEnable(SPI1,ENABLE);

        uint8_t dataLen =strlen(user_data);
        SPI_SendData(SPI1, &dataLen, 1);

        SPI_SendData(SPI1, (uint8_t*)user_data, strlen(user_data));

        while(SPI_FlagStatus(SPI1, SPI_BUSY_FLAG));
        
        SPIEnable(SPI1,DISABLE);
    }
    return 0;
}

void SPI1_GPIOInit(void)
{
    GPIO_Handle_t SPIPins;

    SPIPins.pGPIOx = GPIOA;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALT;
    SPIPins.GPIO_PinConfig.GPIO_AltMode= GPIO_AF5;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_FAST_SPEED;

    //SCLK line
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
    GPIO_Init(&SPIPins);

    //MOSI line
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_7;
    GPIO_Init(&SPIPins);

    //MISO line
    //SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_14;
    //GPIO_Init(&SPIPins);

    //NSS line
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
    GPIO_Init(&SPIPins);

}

void SPI1_Init(void)
{
    SPI_Handle_t SPI2Handle;

    SPI2Handle.pSPIx = SPI1;
    SPI2Handle.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI2Handle.SPI_PinConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPI2Handle.SPI_PinConfig.SPI_SClkSpeed = SPI_CLK_SPEED_DIV_8; //Generates 8MHz clock
    SPI2Handle.SPI_PinConfig.SPI_DFF = SPI_DFF_8_BIT;
    SPI2Handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI2Handle.SPI_PinConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPI2Handle.SPI_PinConfig.SPI_SSM = SPI_SSM_DIS;

    SPI_Init(&SPI2Handle);

}

void buttonInit(void)
{
    GPIO_Handle_t userButton;

    userButton.pGPIOx = GPIOC;
    userButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    userButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
    userButton.GPIO_PinConfig.GPIO_PinOPType = GPIO_OUTPUT_PP;
    userButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    userButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_FAST_SPEED;

    GPIO_Init(&userButton);

}

void delay(uint32_t maxTime)
{
    for(volatile uint32_t t = 0; t < maxTime; t++);
}