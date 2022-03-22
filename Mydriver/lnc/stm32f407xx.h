#ifndef LNC_STM32F407XX_H_
#define LNC_STM32F407XX_H_

#include <stdint.h>
#include <string.h>
#include <stddef.h>

/*
 * Microprocessor define
 */

#define NVIC_ISER0   ( (uint32_t *) (0xE000E100) )

/*
 *  IRQ Numbers of MCU
 */

typedef enum {

	EXTI0_IRQNumber = 6,
	EXTI1_IRQNumber = 7,
	EXTI2_IRQNumber = 8,
	EXTI3_IRQNumber = 9,
	SPI1_IRQNumber = 35,
	USART2_IRQNumber = 38

}IRQ_Number_TypeDef;

#define __IO volatile

#define SET_BIT(REG,BIT)		((REG) |= (BIT)   )
#define CLEAR_BIT(REG,BIT)      ((REG) &= ~(BIT)  )
#define READ_BIT(REG,BIT)       ((REG) &  (BIT)   )
#define UNUSED(x)				(void)x

typedef enum {

	DISABLE = 0x0U,
	ENABLE  = !DISABLE


}Functional_State_t;

/*
 * Memory Base Address
 */

#define FLASH_BASE_ADDR  (0x08000000UL)		/* Flash base address 1MB */
#define SRAM1_BASE_ADDR  (0x20000000UL)		/* Sram1 base address 112KB */
#define SRAM2_BASE_ADDR  (0x2001C000UL) 	/* Sram2 base address 16KB */

/*
 * Peripheral Base Address
 */

#define PERIPH_BASE_ADDR (0x40000000UL) 				   /* Base address for all peripherals */

#define APB1_BASE_ADDR  PERIPH_BASE_ADDR 				   /* APB1 Bus Domain Base Address */
#define APB2_BASE_ADDR  (PERIPH_BASE_ADDR + 0x00010000UL)  /* APB2 Bus Domain Base Address */
#define AHB1_BASE_ADDR  (PERIPH_BASE_ADDR + 0x00020000UL)  /* AHB1 Bus Domain Base Address */
#define AHB2_BASE_ADDR  (PERIPH_BASE_ADDR + 0x10000000UL)  /* AHB2 Bus Domain Base Address */

/*
 * APB1 Peripheral Base Address
 */

#define TIM2_BASE_ADDR   APB1_BASE_ADDR					/* TIM2 Base Address */
#define TIM3_BASE_ADDR   (APB1_BASE_ADDR + 0x0400UL)	/* TIM3 Base Address */
#define TIM4_BASE_ADDR   (APB1_BASE_ADDR + 0x0800UL)	/* TIM4 Base Address */

#define SPI2_BASE_ADDR   (APB1_BASE_ADDR + 0x3800UL)	/* SPI2 Base Address */
#define SPI3_BASE_ADDR   (APB1_BASE_ADDR + 0x3C00UL)	/* SPI3 Base Address */

#define USART2_BASE_ADDR (APB1_BASE_ADDR + 0x4400UL)	/* USART2 Base Address */
#define USART3_BASE_ADDR (APB1_BASE_ADDR + 0x4800UL)	/* USART3 Base Address */
#define UART4_BASE_ADDR  (APB1_BASE_ADDR + 0x4C00UL)	/* UART4 Base Address */
#define UART5_BASE_ADDR  (APB1_BASE_ADDR + 0x5000UL)	/* UART5 Base Address */

#define I2C1_BASE_ADDR   (APB1_BASE_ADDR + 0x5400UL)	/* I2C1 Base Address */
#define I2C2_BASE_ADDR   (APB1_BASE_ADDR + 0x5800UL)	/* I2C2 Base Address */
#define I2C3_BASE_ADDR   (APB1_BASE_ADDR + 0x5C00UL)	/* I2C3 Base Address */

/*
 * APB2 Peripheral Base Address
 */

#define TIM1_BASE_ADDR   (APB2_BASE_ADDR + 0x0000UL)	/* TIM1 Base Address */
#define TIM8_BASE_ADDR   (APB2_BASE_ADDR + 0x0400UL)	/* TIM8 Base Address */

#define USART1_BASE_ADDR (APB2_BASE_ADDR + 0x1000UL)	/* USART1 Base Address */
#define USART6_BASE_ADDR (APB2_BASE_ADDR + 0x1400UL)	/* USART6 Base Address */

#define SPI1_BASE_ADDR   (APB2_BASE_ADDR + 0x3000UL)	/* SPI1 Base Address */
#define SPI4_BASE_ADDR   (APB2_BASE_ADDR + 0x3400UL)	/* SPI4 Base Address */

#define SYSCFG_BASE_ADDR (APB2_BASE_ADDR + 0x3800UL)	/* SYSCFG Base Address */
#define EXTI_BASE_ADDR   (APB2_BASE_ADDR + 0x3C00UL)	/* EXTI Base Address */

/*
 * AHB1 Peripheral Base Address
 */

#define GPIOA_BASE_ADDR  (AHB1_BASE_ADDR + 0x0000UL)	/*GPIOA Base Address */
#define GPIOB_BASE_ADDR  (AHB1_BASE_ADDR + 0x0400UL)	/*GPIOB Base Address */
#define GPIOC_BASE_ADDR  (AHB1_BASE_ADDR + 0x0800UL)	/*GPIOC Base Address */
#define GPIOD_BASE_ADDR  (AHB1_BASE_ADDR + 0x0C00UL)	/*GPIOD Base Address */
#define GPIOE_BASE_ADDR  (AHB1_BASE_ADDR + 0x1000UL)	/*GPIOE Base Address */
#define GPIOF_BASE_ADDR  (AHB1_BASE_ADDR + 0x1400UL)	/*GPIOF Base Address */
#define GPIOG_BASE_ADDR  (AHB1_BASE_ADDR + 0x1800UL)	/*GPIOG Base Address */
#define GPIOH_BASE_ADDR  (AHB1_BASE_ADDR + 0x1C00UL)	/*GPIOH Base Address */
#define GPIOI_BASE_ADDR  (AHB1_BASE_ADDR + 0x2000UL)	/*GPIOI Base Address */
#define GPIOJ_BASE_ADDR  (AHB1_BASE_ADDR + 0x2400UL)	/*GPIOJ Base Address */
#define GPIOK_BASE_ADDR  (AHB1_BASE_ADDR + 0x2800UL)	/*GPIOK Base Address */

#define RCC_BASE_ADDR    (AHB1_BASE_ADDR + 0x3800UL)	/*RCC Base Address */

/*
 * Peripheral Structure Definitions
 */

typedef struct{

	__IO uint32_t MODER;  	/* GPIO port mode register                  Address:0x0000 */
	__IO uint32_t OTYPER; 	/* GPIO port output type register           Address:0x0004 */
	__IO uint32_t OSPEEDR;	/* GPIO port output speed register          Address:0x0008 */
	__IO uint32_t PUPDR;  	/* GPIO port pull-up/pull-down register     Address:0x000C */
	__IO uint32_t IDR; 	  	/* GPIO port input data register            Address:0x0010 */
	__IO uint32_t ODR;    	/* GPIO port output data register           Address:0x0014 */
	__IO uint32_t BSRR;   	/* GPIO port bit set/reset register         Address:0x0018 */
	__IO uint32_t LCKR;    	/*GPIO port configuration lock register     Address:0x001C */
	__IO uint32_t AFR[2]; 	/* GPIO alternate function low register     Address:0x0020 */

}GPIO_TypeDef_t;

#define GPIOA      ( (GPIO_TypeDef_t *)(GPIOA_BASE_ADDR))
#define GPIOB      ( (GPIO_TypeDef_t *)(GPIOB_BASE_ADDR))
#define GPIOC      ( (GPIO_TypeDef_t *)(GPIOC_BASE_ADDR))
#define GPIOD      ( (GPIO_TypeDef_t *)(GPIOD_BASE_ADDR))
#define GPIOE      ( (GPIO_TypeDef_t *)(GPIOE_BASE_ADDR))
#define GPIOF      ( (GPIO_TypeDef_t *)(GPIOF_BASE_ADDR))
#define GPIOG      ( (GPIO_TypeDef_t *)(GPIOG_BASE_ADDR))
#define GPIOH      ( (GPIO_TypeDef_t *)(GPIOH_BASE_ADDR))
#define GPIOI      ( (GPIO_TypeDef_t *)(GPIOI_BASE_ADDR))
#define GPIOJ      ( (GPIO_TypeDef_t *)(GPIOJ_BASE_ADDR))
#define GPIOK      ( (GPIO_TypeDef_t *)(GPIOK_BASE_ADDR))

/*
 * RCC Structure Definitions
 */

typedef struct{

	__IO uint32_t CR;			/* RCC clock control register       								 Address:0x0000 */
	__IO uint32_t PLLCFGR;		/* RCC PLL configuration register       							 Address:0x0004 */
	__IO uint32_t CFGR;			/* RCC clock configuration register     							 Address:0x0008 */
	__IO uint32_t CIR;			/* RCC clock interrupt register      								 Address:0x000C */
	__IO uint32_t AHB1RSTR;		/* RCC AHB1 peripheral reset register      							 Address:0x0010 */
	__IO uint32_t AHB2RSTR;		/* RCC AHB2 peripheral reset register       						 Address:0x0014 */
	__IO uint32_t AHB3RSTR;		/* RCC AHB3 peripheral reset register       						 Address:0x0018 */
	__IO uint32_t RESERVED0;	/* RCC Reserved  register       									 Address:0x001C */
	__IO uint32_t APB1RSTR;		/* RCC APB1 peripheral reset register       						 Address:0x0020 */
	__IO uint32_t APB2RSTR;		/* RCC APB2 peripheral reset register       						 Address:0x0024 */
	__IO uint32_t RESERVED1[2];	/* RCC Reserved register       								 		 Address:0x0028 */
	__IO uint32_t AHB1ENR;		/* RCC AHB1 peripheral clock register       						 Address:0x0030 */
	__IO uint32_t AHB2ENR;		/* RCC AHB2 peripheral clock enable register       					 Address:0x0034 */
	__IO uint32_t AHB3ENR;		/* RCC AHB3 peripheral clock enable register         				 Address:0x0038 */
	__IO uint32_t RESERVED2;	/* RCC Reserved register      										 Address:0x003C */
	__IO uint32_t APB1ENR;		/* RCC APB1 peripheral clock enable register       					 Address:0x0040 */
	__IO uint32_t APB2ENR;		/* RCC APB2 peripheral clock enable register      					 Address:0x0044 */
	__IO uint32_t RESERVED3[2];	/* RCC Reserved register       								 		 Address:0x0048 */
	__IO uint32_t AHB1LPENR;	/* RCC AHB1 peripheral clock enable in low power mode register       Address:0x0050 */
	__IO uint32_t AHB2LPENR;	/* RCC AHB2 peripheral clock enable in low power mode register       Address:0x0054 */
	__IO uint32_t AHB3LPENR;	/* RCC AHB3 peripheral clock enable in low power mode register       Address:0x0058 */
	__IO uint32_t RESERVED4;	/* RCC clock control register       								 Address:0x005C */
	__IO uint32_t APB1LPENR;	/* RCC APB1 peripheral clock enable in low power mode register       Address:0x0060 */
	__IO uint32_t APB2LPENR;	/* RCC APB2 peripheral clock enabled in low power mode register      Address:0x0064 */
	__IO uint32_t RESERVED5[2];	/* RCC Reserved register       								 		 Address:0x0068 */
	__IO uint32_t BDCR;			/* RCC Backup domain control register       					 	 Address:0x0070 */
	__IO uint32_t CSR;			/* RCC clock control & status register       						 Address:0x0074 */
	__IO uint32_t RESERVED6[2];	/* RCC Reserved register       								         Address:0x0078 */
	__IO uint32_t SSCFGR;		/* RCC spread spectrum clock generation register       				 Address:0x0080 */
	__IO uint32_t PLLI2SCFGR;	/* RCC PLLI2S configuration register      							 Address:0x0084 */

}RCC_Typedef_t;

#define RCC			( (RCC_Typedef_t *)(RCC_BASE_ADDR) )

typedef struct{

	__IO uint32_t MEMRMP;		/* SYSCFG memory remap register 							 Address:0x00 */
	__IO uint32_t PMC;			/* SYSCFG peripheral mode configuration register 			 Address:0x04 */
	__IO uint32_t EXTICR[4];	/* SYSCFG external interrupt configuration register 		 Address:0x08 */
	__IO uint32_t CMPCR;		/* Compensation cell control register  						 Address:0x20 */

}SYSCFG_TypeDef_t;

#define SYSCFG 		( (SYSCFG_TypeDef_t *)(SYSCFG_BASE_ADDR) )

typedef struct {

	__IO uint32_t IMR;			/* Interrupt mask register 									Address:0x00 */
	__IO uint32_t EMR;			/* Event mask register 										Address:0x04 */
	__IO uint32_t RTSR;			/* Rising trigger selection register 						Address:0x08 */
	__IO uint32_t FTSR;			/* Falling trigger selection register 						Address:0x0C */
	__IO uint32_t SWIER;		/* Software interrupt event register 						Address:0x10 */
	__IO uint32_t PR;			/* Pending register 										Address:0x14 */


}EXTI_TypeDef_t;

#define EXTI      ( (EXTI_TypeDef_t*)(EXTI_BASE_ADDR) )

typedef struct{

	__IO uint32_t CR1;			/* SPI control register 1 									Address:0x00 */
	__IO uint32_t CR2;			/* SPI control register 2  									Address:0x04 */
	__IO uint32_t SR;			/* SPI status register 									    Address:0x08 */
	__IO uint32_t DR;			/* SPI data register									    Address:0x0C */
	__IO uint32_t CRCPR;		/* SPI CRC polynomial register								Address:0x10 */
	__IO uint32_t RXCRCR;		/* SPI RX CRC register 									    Address:0x14 */
	__IO uint32_t TXCRCR;		/* SPI TX CRC register 									    Address:0x18 */
	__IO uint32_t I2SCFGR;		/* SPI_I2S configuration register							Address:0x1C */
	__IO uint32_t I2SPR;		/* SPI_I2S prescaler register 								Address:0x20 */

}SPI_TypeDef_t;

#define SPI1                ((SPI_TypeDef_t *) SPI1_BASE_ADDR)
#define SPI2				((SPI_TypeDef_t *) SPI2_BASE_ADDR)
#define SPI3 				((SPI_TypeDef_t *) SPI3_BASE_ADDR)
#define SPI4				((SPI_TypeDef_t *) SPI4_BASE_ADDR)

typedef struct {

	__IO uint32_t SR;			/* USART Status register 									    Address:0x00 */
	__IO uint32_t DR;			/* USART Data register 									        Address:0x04 */
	__IO uint32_t BRR;			/* USART Baud Rate register 									Address:0x08 */
	__IO uint32_t CR1;			/* USART Control 1 register 									Address:0x0C */
	__IO uint32_t CR2;			/* USART Control 2 register 									Address:0x10 */
	__IO uint32_t CR3;			/* USART Control 3 register 									Address:0x14 */
	__IO uint32_t GTPR;			/* USART Guard time and prescaler register 						Address:0x18 */

}USART_TypeDef_t;

#define USART2 				((USART_TypeDef_t *)USART2_BASE_ADDR)
#define USART3				((USART_TypeDef_t *)USART3_BASE_ADDR)
#define UART4				((USART_TypeDef_t *)UART4_BASE_ADDR )
#define UART5				((USART_TypeDef_t *)UART5_BASE_ADDR )
#define USART1              ((USART_TypeDef_t *)USART1_BASE_ADDR)
#define USART6              ((USART_TypeDef_t *)USART6_BASE_ADDR)

typedef struct {

	__IO uint32_t CR1;        /* I2C Control register 1									         Address:0x00 */
	__IO uint32_t CR2;        /* I2C Control register 2									         Address:0x04 */
	__IO uint32_t OAR1; 	  /* I2C Own address register 1									     Address:0x08 */
	__IO uint32_t OAR2;		  /* I2C Own address register 2 									 Address:0x0C */
	__IO uint32_t DR;		  /* I2C Data register									             Address:0x10 */
	__IO uint32_t SR1;		  /* I2C Status register 1									         Address:0x14 */
	__IO uint32_t SR2;		  /* I2C Status register 2									         Address:0x18 */
	__IO uint32_t CCR;		  /* I2C Clock control register									     Address:0x1C */
	__IO uint32_t TRISE;	  /* I2C TRISE register									             Address:0x20 */
	__IO uint32_t FLTR;		  /* I2C FLTR register									             Address:0x24 */

}I2C_TypeDef_t;

#define I2C1				((I2C_TypeDef_t *)I2C1_BASE_ADDR)
#define I2C2				((I2C_TypeDef_t *)I2C2_BASE_ADDR)
#define I2C3				((I2C_TypeDef_t *)I2C3_BASE_ADDR)

/*
 * Bit Definitions
 */

#define RCC_AHB1ENR_GPIOAEN_Pos		(0U)
#define RCC_AHB1ENR_GPIOAEN_Msk		(0x1 << RCC_AHB1ENR_GPIOAEN_Pos)
#define RCC_AHB1ENR_GPIOAEN			RCC_AHB1ENR_GPIOAEN_Msk


#define RCC_AHB1ENR_GPIOBEN_Pos		(1U)
#define RCC_AHB1ENR_GPIOBEN_Msk		(0x1 << RCC_AHB1ENR_GPIOBEN_Pos)
#define RCC_AHB1ENR_GPIOBEN			RCC_AHB1ENR_GPIOBEN_Msk

#define RCC_AHB1ENR_GPIOCEN_Pos		(2U)
#define RCC_AHB1ENR_GPIOCEN_Msk		(0x1 << RCC_AHB1ENR_GPIOCEN_Pos)
#define RCC_AHB1ENR_GPIOCEN			RCC_AHB1ENR_GPIOCEN_Msk

#define RCC_AHB1ENR_GPIODEN_Pos		(3U)
#define RCC_AHB1ENR_GPIODEN_Msk		(0x1 << RCC_AHB1ENR_GPIODEN_Pos)
#define RCC_AHB1ENR_GPIODEN			RCC_AHB1ENR_GPIODEN_Msk

#define RCC_AHB1ENR_GPIOEEN_Pos		(4U)
#define RCC_AHB1ENR_GPIOEEN_Msk		(0x1 << RCC_AHB1ENR_GPIOEEN_Pos)
#define RCC_AHB1ENR_GPIOEEN			RCC_AHB1ENR_GPIOEEN_Msk

#define RCC_APB1ENR_USART2_Pos      (17U)
#define RCC_APB1ENR_USART2_Msk      (0x1 << RCC_APB1ENR_USART2_Pos)
#define RCC_APB1ENR_USART2          RCC_APB1ENR_USART2_Msk

#define RCC_APB2ENR_SYSCFG_Pos      (14U)
#define RCC_APB2ENR_SYSCFG_Msk      (0x1 << RCC_APB2ENR_SYSCFG_Pos)
#define RCC_APB2ENR_SYSCFGEN        RCC_APB2ENR_SYSCFG_Msk

#define RCC_APB2ENR_SPI1_Pos		(12U)
#define RCC_APB2ENR_SPI1_Msk		(0x1U << RCC_APB2ENR_SPI1_Pos)
#define RCC_APB2ENR_SPI1			RCC_APB2ENR_SPI1_Msk

#define RCC_APB1ENR_SPI2_Pos 		(14U)
#define RCC_APB1ENR_SPI2_Msk		(0x1U << RCC_APB1ENR_SPI2_Pos)
#define RCC_APB1ENR_SPI2			RCC_APB1ENR_SPI2_Msk

#define RCC_APB1ENR_I2C1_Pos        (21U)
#define RCC_APB1ENR_I2C1_Msk		(0x1U << RCC_APB1ENR_I2C1_Pos)
#define RCC_APB1ENR_I2C1			RCC_APB1ENR_I2C1_Msk

#define SPI_CR1_SPE					(6U)
#define SPI_SR_TXE					(1U)
#define SPI_SR_Busy					(7U)
#define SPI_SR_RXNE                 (0U)

#define SPI_CR1_DFF 				(11U)

#define SPI_CR2_TXEIE 				(7U)
#define SPI_CR2_RXEIE				(6U)

#define USART_CR2_STOP              (12U)
#define USART_SR_TXE                (7U)
#define USART_SR_RXE                (5U)
#define USART_SR_TC                 (6U)
#define USART_CR1_UE                (13U)
#define USART_CR1_TXEIE				(7U)
#define USART_CR1_RXEIE             (5U)

#define I2C_CR1_PE 					(0U)

/*
 * SPI FlagBits
 */

#define SPI_TXE_Flag                (0x1 << SPI_SR_TXE)
#define SPI_BUSY_Flag				(0x1 << SPI_SR_Busy)
#define SPI_RXNE_Flag				(0x1 << SPI_SR_RXNE)

/*
 * USART_FlagBits
 */

#define USART_TXE_Flag              (0x1 << USART_SR_TXE)
#define USART_TC_Flag               (0x1 << USART_SR_TC)
#define USART_RXE_Flag              (0x1 << USART_SR_RXE)

#include "GPIO.h"
#include "Rcc.h"
#include "EXTI.h"
#include "SPI.h"
#include "USART.h"
#include "I2C.h"


#endif /* LNC_STM32F407XX_H_ *//*
 * stm32f407xx.h
 *
 *  Created on: Mar 2, 2022
 *      Author: ahmet
 */

#ifndef LNC_STM32F407XX_H_
#define LNC_STM32F407XX_H_



#endif /* LNC_STM32F407XX_H_ */
