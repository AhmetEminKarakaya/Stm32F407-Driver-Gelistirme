#include "EXTI.h"

/*
 *     @brief: EXTI_Init for valid GPIO port and valid
 *
 * 	   @param: EXTI_Initstructer = user config structer
 */

void EXTI_Init(EXTI_Init_TypeDef_t *EXTI_Initstructer){

	uint32_t tempval = 0;

	tempval = (uint32_t)(EXTI_BASE_ADDR);

	EXTI->IMR &= ~(0x1U << EXTI_Initstructer->EXTI_Linenumber);
	EXTI->EMR &= ~(0x1U << EXTI_Initstructer->EXTI_Linenumber);

	if(EXTI_Initstructer->EXTI_Line_Cmd != DISABLE){

		tempval += EXTI_Initstructer->Mode;

		*( (__IO uint32_t *) tempval) |= (0x1U << EXTI_Initstructer->EXTI_Linenumber);

		tempval = (uint32_t)(EXTI_BASE_ADDR);

		EXTI->RTSR &= ~(0x1U << EXTI_Initstructer->EXTI_Linenumber);
		EXTI->FTSR &= ~(0x1U << EXTI_Initstructer->EXTI_Linenumber);

		if(EXTI_Initstructer->TriggerSelect == EXTI_Trigger_RF){

			EXTI->RTSR |= (0x1 << EXTI_Initstructer->EXTI_Linenumber);
			EXTI->FTSR |= (0x1 << EXTI_Initstructer->EXTI_Linenumber);
		}
		else{

			tempval += EXTI_Initstructer->TriggerSelect;

			*( (__IO uint32_t *) tempval) |= (0x1U << EXTI_Initstructer->EXTI_Linenumber);
		}
	}

	else{

		tempval = (uint32_t)(EXTI_BASE_ADDR);

		tempval += EXTI_Initstructer->Mode;

		*( (__IO uint32_t *) tempval) &= (0x1U << EXTI_Initstructer->EXTI_Linenumber);
	}

}

/*
 *     @brief: EXTI_Line_Config, configures the port and pin for SYSCFG
 *
 * 	   @param: PortSource = Port A-I @def_groups PORT_VALUES
 * 	   @param: EXTI_LineSource = Line Numbers @def_groups EXTI_Line_Values
 */

void EXTI_Line_Config(uint8_t PortSource , uint8_t EXTI_LineSource){

	uint32_t tempvalue;

	tempvalue = SYSCFG->EXTICR[EXTI_LineSource >> 2U];
	tempvalue &= ~(0xFU << (EXTI_LineSource & 0x3U) * 4);
	tempvalue = (PortSource << (EXTI_LineSource & 0x3U) * 4);
	SYSCFG->EXTICR[EXTI_LineSource >> 2U] = tempvalue;
}

/*
 *     @brief: NVIC_EnableInterrupt
 *
 * 	   @param: IRQNumber = IRQ Number of Line
 *
 */


void NVIC_EnableInterrupt(IRQ_Number_TypeDef IRQNumber){

	uint32_t tempval = 0;

	tempval = *( (IRQNumber >> 5U ) + NVIC_ISER0);
	tempval &= ~(0x1U << (IRQNumber & 0x1FU));
	tempval |= (0x1U << (IRQNumber & 0x1FU));

	*( (IRQNumber >> 5U) + NVIC_ISER0 ) = tempval;
}
