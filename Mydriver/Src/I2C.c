#include "I2C.h"


void I2C_Init(I2C1_HandleTypedef_t *I2C_Handle){

	uint32_t pClockValue = 0;

	pClockValue = RCC_GetPClock1();

	if(Check_PClock_Value(pClockValue,I2C_Handle->Init.ClockSpeed) != 1U){

		uint32_t tempReg = 0x0U;
		uint32_t freqValue = 0x0U;

		/**************** ACK State And Stretchin Mode Config  ***********/
		tempReg = I2C_Handle->Instance->CR1;

		tempReg |= (I2C_Handle->Init.ACK_State) | (I2C_Handle->Init.ClockStretch);

		I2C_Handle->Instance->CR1 = tempReg;

		/**************** Frequenct Value And PCLOCK for clock generation  ***********/

		freqValue = I2C_Get_FreqValue(pClockValue);

		tempReg = I2C_Handle->Instance->CR2;

		tempReg |= (freqValue << 0U);

		I2C_Handle->Instance->CR2 = tempReg;

		tempReg = I2C_Handle->Instance->OAR1;

		/**************** Address Configuration  ***********/

		tempReg |= (I2C_Handle->Init.Addressing_Mode);

		if(I2C_Handle->Init.Addressing_Mode == I2C_ADDRMODE_7){

			tempReg |= (I2C_Handle->Init.MyOwnAddress << 1U);
		}

		else{
			tempReg |= (I2C_Handle->Init.MyOwnAddress << 0U);
		}

	}


}


void I2C1_PeriphCmd(I2C_TypeDef_t *I2Cx, Functional_State_t stateofI2C){

	if(stateofI2C == ENABLE){

		I2Cx->CR1 |= (0x1 << I2C_CR1_PE);

	}

	else{

		I2Cx->CR1 &= ~(0x1 << I2C_CR1_PE);

	}


}

