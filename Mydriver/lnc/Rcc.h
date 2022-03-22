#ifndef LNC_RCC_H_
#define LNC_RCC_H_

#include "stm32f407xx.h"

			/********************  RCC GPIOA Clock Enable   **************************/

#define RCC_GPIOA_CLK_ENABLE()		do{ uint32_t tempvalue = 0;    \
										SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOAEN); \
										tempvalue=READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOAEN);	\
										UNUSED(tempvalue); \
										}while(0)

			/********************  RCC GPIOA Clock Disable   **************************/

#define RCC_GPIOA_CLK_DISABLE()		CLEAR_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOAEN)

			/********************  RCC GPIOB Clock Enable   **************************/

#define RCC_GPIOB_CLK_ENABLE()		do{ uint32_t tempvalue = 0;    \
										SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOBEN); \
										tempvalue=READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOBEN);	\
										UNUSED(tempvalue); \
										}while(0)

			/********************  RCC GPIOB Clock Disable   **************************/

#define RCC_GPIOB_CLK_DISABLE()		CLEAR_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOBEN)

			/********************  RCC GPIOC Clock Enable   **************************/

#define RCC_GPIOC_CLK_ENABLE()		do{ uint32_t tempvalue = 0;    \
										SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOCEN); \
										tempvalue=READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOCEN);	\
										UNUSED(tempvalue); \
										}while(0)

			/********************  RCC GPIOC Clock Disable   **************************/

#define RCC_GPIOC_CLK_DISABLE()		CLEAR_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOCEN)

			/********************  RCC GPIOD Clock Enable   **************************/

#define RCC_GPIOD_CLK_ENABLE()		do{ uint32_t tempvalue = 0;    \
										SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIODEN); \
										tempvalue=READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIODEN);	\
										UNUSED(tempvalue); \
										}while(0)

			/********************  RCC GPIOD Clock Disable   **************************/

#define RCC_GPIOD_CLK_DISABLE()		CLEAR_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIODEN)

			/********************  RCC GPIOE Clock Enable   **************************/

#define RCC_GPIOE_CLK_ENABLE()		do{ uint32_t tempvalue = 0;    \
										SET_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOEEN); \
										tempvalue=READ_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOEEN);	\
										UNUSED(tempvalue); \
										}while(0)

			/********************  RCC GPIOE Clock Disable   **************************/

#define RCC_GPIOE_CLK_DISABLE()		CLEAR_BIT(RCC->AHB1ENR,RCC_AHB1ENR_GPIOEEN)

			/********************  RCC SYSCFG Clock Enable   **************************/

#define RCC_SYSCFG_CLK_ENABLE()		do{ uint32_t tempvalue = 0;    \
										SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN); \
										tempvalue=READ_BIT(RCC->APB2ENR,RCC_APB2ENR_SYSCFGEN);	\
										UNUSED(tempvalue); \
										}while(0)

			/********************  RCC SPI1 Clock Enable   **************************/

#define RCC_SPI1_CLK_ENABLE()       do{ uint32_t tempvalue = 0; \
										SET_BIT(RCC->APB2ENR,RCC_APB2ENR_SPI1); \
										tempvalue = READ_BIT(RCC->APB2ENR,RCC_APB2ENR_SPI1); \
										UNUSED(tempvalue);\
                                        }while(0)

			/********************  RCC SPI1 Clock Disable   **************************/

#define RCC_SPI1_CLK_DISABLE()      CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_SPI1)

			/********************  RCC SPI2 Clock Enable   **************************/

#define RCC_SPI2_CLK_ENABLE()       do{ uint32_t tempvalue = 0; \
										SET_BIT(RCC->APB1ENR,RCC_APB1ENR_SPI2); \
										tempvalue = READ_BIT(RCC->APB1ENR,RCC_APB1ENR_SPI2); \
										UNUSED(tempvalue);\
                                        }while(0)

			/********************  RCC SPI2 Clock Disable   **************************/

#define RCC_SPI2_CLK_DISABLE()		CLEAR_BIT(RCC->APB1ENR,RCC_APB1ENR_SPI2)

			/********************  RCC USART2 Clock Enable   **************************/

#define RCC_USART2_CLK_ENABLE()      do {  uint32_t tempvalue = 0; \
										   SET_BIT(RCC->APB1ENR,RCC_APB1ENR_USART2); \
										   tempvalue = READ_BIT(RCC->APB1ENR,RCC_APB1ENR_USART2); \
										   UNUSED(tempvalue);\
										}while(0)

			/********************  RCC USART2 Clock Disable   **************************/

#define RCC_USART2_CLK_DISABLE()    CLEAR_BIT(RCC->APB1ENR,RCC_APB1ENR_USART2)

			/********************  RCC I2C1 Clock Enable   **************************/

#define RCC_I2C1_CLK_ENABLE()		  do {  uint32_t tempvalue = 0; \
										   SET_BIT(RCC->APB1ENR,RCC_APB1ENR_I2C1); \
										   tempvalue = READ_BIT(RCC->APB1ENR,RCC_APB1ENR_I2C1); \
										   UNUSED(tempvalue);\
										}while(0)

			/********************  RCC I2C1 Clock Disable   **************************/

#define RCC_I2C1_CLK_DISABLE()		CLEAR_BIT(RCC->APB1ENR,RCC_APB1ENR_I2C1)


uint32_t RCC_GetSystemClock();
uint32_t RCC_GetHClock();
uint32_t RCC_GetPClock1();
uint32_t RCC_GetPClock2();


#endif /* LNC_RCC_H_ */
