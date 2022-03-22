#ifndef LNC_EXTI_H_
#define LNC_EXTI_H_

#include "stm32f407xx.h"

/*
 * @def_groups PORT_VALUES
 */

#define EXTI_PortSource_GPIOA 		( (uint8_t) (0x0) )
#define EXTI_PortSource_GPIOB 		( (uint8_t) (0x1) )
#define EXTI_PortSource_GPIOC 		( (uint8_t) (0x2) )
#define EXTI_PortSource_GPIOD 		( (uint8_t) (0x3) )
#define EXTI_PortSource_GPIOE 		( (uint8_t) (0x4) )
#define EXTI_PortSource_GPIOF 		( (uint8_t) (0x5) )
#define EXTI_PortSource_GPIOG 		( (uint8_t) (0x6) )
#define EXTI_PortSource_GPIOH 		( (uint8_t) (0x7) )

/*
 * @def_group EXTI_Line_Values
 */

#define EXTI_LineSource_0          	( (uint8_t) (0x0) )
#define EXTI_LineSource_1          	( (uint8_t) (0x1) )
#define EXTI_LineSource_2          	( (uint8_t) (0x2) )
#define EXTI_LineSource_3          	( (uint8_t) (0x3) )
#define EXTI_LineSource_4          	( (uint8_t) (0x4) )
#define EXTI_LineSource_5          	( (uint8_t) (0x5) )
#define EXTI_LineSource_6          	( (uint8_t) (0x6) )
#define EXTI_LineSource_7          	( (uint8_t) (0x7) )
#define EXTI_LineSource_8          	( (uint8_t) (0x8) )
#define EXTI_LineSource_9          	( (uint8_t) (0x9) )
#define EXTI_LineSource_10          ( (uint8_t) (0xA) )
#define EXTI_LineSource_11          ( (uint8_t) (0xB) )
#define EXTI_LineSource_12          ( (uint8_t) (0xC) )
#define EXTI_LineSource_13          ( (uint8_t) (0xD) )
#define EXTI_LineSource_14          ( (uint8_t) (0xE) )
#define EXTI_LineSource_15          ( (uint8_t) (0xF) )

/*
 * @def EXTI_MODE
 */

#define EXTI_Mode_Interrupt   (0x00U);
#define EXTI_Mode_Event       (0x04U);

/*
 * @def EXTI_Trigger
 */

#define EXTI_Trigger_Rising   (0x08U)
#define EXTI_Trigger_Falling  (0x0CU)
#define EXTI_Trigger_RF       (0x10U)

typedef struct{

	uint8_t EXTI_Linenumber;		         /* EXTI Line number for GPIO pin @def=EXTI_Line_Values */
	uint8_t TriggerSelect;
	uint8_t Mode;
	Functional_State_t EXTI_Line_Cmd;        /* Mask or unmask the line number                      */


}EXTI_Init_TypeDef_t;

void EXTI_Init(EXTI_Init_TypeDef_t *EXTI_Initstructer);
void EXTI_Line_Config(uint8_t PortSource , uint8_t EXTI_LineSource);
void NVIC_EnableInterrupt(IRQ_Number_TypeDef IRQNumber);

#endif /* LNC_EXTI_H_ */
