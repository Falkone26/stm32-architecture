#ifndef INC_STM32F030XX_H_
#define INC_STM32F030XX_H_

#include <stdint.h>

#define FLASH_BASEADDR              0x08000000U         /*FLASH Memory 64kB*/
#define SRAM1_BASEADDR              0x20000000U         /*SRAM1 8kB*/
#define ROM                         0x1FFF0000U         /*System Memory 3kB*/
#define SRAM                        SRAM1_BASE_ADDR     

#define PERIPH_BASE                 0x40000000U
#define APB_PERIPH_BASEADDR         PERIPH_BASE            
#define AHB1_PERIPH_BASEADDR        0x40020000U
#define AHB2_PERIPH_BASEADDR        0x48000000U

/*RCC peripheral on the AHB1 Bus*/
#define RCC_BASEADDR                (AHB1_PERIPH_BASEADDR + 0x1000)

/*GPIO peripheral on the AHB2 Bus*/
#define GPIOA_BASEADDR              (AHB2_PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR              (AHB2_PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR              (AHB2_PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR              (AHB2_PERIPH_BASEADDR + 0x0C00)
#define GPIOF_BASEADDR              (AHB2_PERIPH_BASEADDR + 0x1400)

/*-------------------------------------Peripheral Register Structures-----------------------*/

/*GPIO peripheral register structure*/
typedef struct
{
    volatile uint32_t MODER;        /*GPIO port mode register                       Address offset: 0x00*/
    volatile uint32_t OTYPER;       /*GPIO port output type register                Address offset: 0x04*/
    volatile uint32_t OSPEEDR;      /*GPIO port output speed register               Address offset: 0x08*/
    volatile uint32_t PUPDR;        /*GPIO port pull-up/pull-down register          Address offset: 0x0C*/
    volatile uint32_t IDR;          /*GPIO port input data register                 Address offset: 0x10*/
    volatile uint32_t ODR;          /*GPIO port output data register                Address offset: 0x14*/
    volatile uint32_t BSRR;         /*GPIO port bit set/reset register              Address offset: 0x18*/
    volatile uint32_t LCKR;         /*GPIO port configuration lock registe          Address offset: 0x1C*/
    volatile uint32_t AFR[2];       /*GPIO alternate function low/high registers    Address offset: 0x20 & 0x24*/
}GPIO_RegDef_t;

/*RCC peripheral register structure*/
typedef struct
{   
    volatile uint32_t CR;           /*RCC clock control register                     Address offset: 0x00*/
    volatile uint32_t CFGR;         /*RCC clock configuration register               Address offset: 0x04*/
    volatile uint32_t CIR;          /*RCC clock interrupt register                   Address offset: 0x08*/
    volatile uint32_t APB2RSTR;     /*RCC APB2 peripheral reset register             Address offset: 0x0C*/
    volatile uint32_t APB1RSTR;     /*RCC APB1 peripheral reset register             Address offset: 0x10*/
    volatile uint32_t AHBENR;       /*RCC AHB1 peripheral clock enable register      Address offset: 0x14*/
    volatile uint32_t APB2ENR;      /*RCC APB2 peripheral clock enable register      Address offset: 0x18*/
    volatile uint32_t APB1ENR;      /*RCC APB1 peripheral clock enable register      Address offset: 0x1C*/
    volatile uint32_t BDCR;         /*RCC Backup domain control register             Address offset: 0x20*/
    volatile uint32_t CSR;          /*RCC clock control and status register          Address offset: 0x24*/

}RCC_RegDef_t;

#define RCC     ((RCC_RegDef_t*)RCC_BASEADDR)

#define GPIOA   ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB   ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC   ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD   ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOF   ((GPIO_RegDef_t*)GPIOF_BASEADDR)

#define GPIOA_PCLK_EN()     (RCC->AHBENR |= (1<<0))
#define GPIOB_PCLK_EN()     (RCC->AHBENR |= (1<<1)) 
#define GPIOC_PCLK_EN()     (RCC->AHBENR |= (1<<2)) 
#define GPIOD_PCLK_EN()     (RCC->AHBENR |= (1<<3)) 
#define GPIOF_PCLK_EN()     (RCC->AHBENR |= (1<<5)) 

/*Clock disable macros for GPIOx peripherals*/
#define GPIOA_PCLK_DIS()    (RCC->AHBENR &= ~(1<<0))
#define GPIOB_PCLK_DIS()    (RCC->AHBENR &= ~(1<<1)) 
#define GPIOC_PCLK_DIS()    (RCC->AHBENR &= ~(1<<2)) 
#define GPIOD_PCLK_DIS()    (RCC->AHBENR &= ~(1<<3)) 
#define GPIOF_PCLK_DIS()    (RCC->AHBENR &= ~(1<<5))

/*Reset GPIOx peripherals*/
#define GPIOA_REG_RESET()     do{ (RCC->AHBENR |= (1<<0)); (RCC->AHBENR &= ~(1<<0));}while(0)
#define GPIOB_REG_RESET()     do{ (RCC->AHBENR |= (1<<1)); (RCC->AHBENR &= ~(1<<1));}while(0)
#define GPIOC_REG_RESET()     do{ (RCC->AHBENR |= (1<<2)); (RCC->AHBENR &= ~(1<<2));}while(0)
#define GPIOD_REG_RESET()     do{ (RCC->AHBENR |= (1<<3)); (RCC->AHBENR &= ~(1<<3));}while(0)

#define DISABLE 0
#define ENABLE  1
#define GPIO_PIN_SET    ENABLE
#define GPIO_PIN_CLEAR  DISABLE

#include "../includes/stm32f030xx_gpio_driver.h" 

#endif
