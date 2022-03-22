#include "GPIO.h"


void GPIO_Init(GPIO_TypeDef_t *GPIOx, GPIO_InitTypedef_t *GPIO_ConfigStruct){

	uint32_t position;
	uint32_t fakeposition = 0;
	uint32_t lastposition = 0;

	for(position=0; position<16; position++){


		/* Mode Config */

		fakeposition = (0x1 << position);
		lastposition = (uint32_t)(GPIO_ConfigStruct->pinnumber) & fakeposition;

		if(fakeposition == lastposition){

			uint32_t tempValue = GPIOx->MODER;

			tempValue &= ~(0x3U << (position*2));
			tempValue |= (GPIO_ConfigStruct->Mode << (position*2));

			GPIOx->MODER = tempValue;


		if(GPIO_ConfigStruct->Mode == GPIO_MODE_OUTPUT || GPIO_ConfigStruct->Mode == GPIO_MODE_ALTERNATE){

			/* Otype Config */

			tempValue = GPIOx->OTYPER;
			tempValue &= ~(0x1U << position);
			tempValue |= (GPIO_ConfigStruct->Otype << position);

			GPIOx->OTYPER =tempValue;

			/* Ospeed config */

			tempValue = GPIOx->OSPEEDR;
			tempValue &= ~(0x3U << (position*2));
			tempValue |= (GPIO_ConfigStruct->Speed << (position*2));

			GPIOx->OSPEEDR = tempValue;
		}

		/* Push Pull Config */

		tempValue = GPIOx->PUPDR;
		tempValue &= ~(0x3U << (position*2));
		tempValue |= (GPIO_ConfigStruct->PuPd << (position*2));

		GPIOx->PUPDR = tempValue;

		if(GPIO_ConfigStruct->Mode == GPIO_MODE_ALTERNATE){

			tempValue = GPIOx->AFR[position >> 3U];
			tempValue &= ~(0xF << ( (position & 0x7U)*4));
			tempValue |= (GPIO_ConfigStruct->Alternate << ( (position & 0x7U)*4));
			GPIOx->AFR[position >> 3U] = tempValue;
		}
	  }
	}
}

/*
 *     @brief: GPIO_WritePin makes pin High or Low
 *
 * 	   @param: GPIOx = GPIO port base address
 * 	   @param: pinNumber = Gpio pin numbers 0-15
 *     @param: pinstate = GPIO_Pin_Set or GPIO_Pin_Reset
 */


void GPIO_WritePin(GPIO_TypeDef_t *GPIOx,uint16_t pinNumber, GPIO_Pin_State_t pinState){

	if(pinState == GPIO_Pin_Reset){

	GPIOx->BSRR = pinNumber;
	}
	else{

		GPIOx->BSRR = (pinNumber + 16U);
	}
}

/*
 *     @brief: GPIO_ReadPin reads pin
 *
 * 	   @param: GPIOx = GPIO port base address
 * 	   @param: pinNumber = Gpio pin numbers 0-15
 */

GPIO_Pin_State_t GPIO_ReadPin(GPIO_TypeDef_t *GPIOx,uint16_t pinNumber){

	GPIO_Pin_State_t bitStatus = GPIO_Pin_Reset;

	if((GPIOx->IDR & pinNumber) != (uint32_t)GPIO_Pin_Reset){

		bitStatus = GPIO_Pin_Set;
	}
	return bitStatus;
}

/*
 *     @brief: GPIO_LockPin locks pin
 *
 * 	   @param: GPIOx = GPIO port base address
 * 	   @param: pinNumber = Gpio pin numbers 0-15
 */

void GPIO_LockPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber){

	uint32_t temp = (0x1U << 16U) | pinNumber;

	GPIOx->LCKR = temp;          // WR LCKR[16] = â€˜1â€™ + LCKR[15:0]
	GPIOx->LCKR = pinNumber;	 // WR LCKR[16] = â€˜0â€™ + LCKR[15:0]
	GPIOx->LCKR = temp;			 // WR LCKR[16] = â€˜1â€™ + LCKR[15:0]
	temp = GPIOx->LCKR;			 // Read Lock Register
}
