#include "USART.h"

static void close_USART_ISR(USART_HandleTypedef_t *USART_Handle){

	USART_Handle->pTxBuffer = NULL;
	USART_Handle->TxBufferSize = 0;
	USART_Handle->Txstatus = USART_BUS_FREE;

	USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_TXEIE);
}

static void close_USART_ISR_Rx(USART_HandleTypedef_t *USART_Handle){

	USART_Handle->RxBufferSize = 0;
	USART_Handle->pRxBuffer = NULL;
	USART_Handle->Rxstatus = USART_BUS_FREE;

	USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_RXEIE);
}

static void USART_SendWith_IT(USART_HandleTypedef_t *USART_Handle){


	if((USART_Handle->Init.Wordlength == USART_WORDLENGTH_9Bits)  && (USART_Handle->Init.Parity == USART_PARITY_NONE)){

		uint16_t *p16BitsData = (uint16_t *)(USART_Handle->pTxBuffer);

		USART_Handle->Instance->DR = (uint16_t)(*p16BitsData & (uint16_t)0x01FFU);
		USART_Handle->pTxBuffer += sizeof(uint16_t);
		USART_Handle->TxBufferSize -=2;
	}
	else{

		USART_Handle->Instance->DR = (uint8_t)(*(USART_Handle->pTxBuffer) & (uint8_t)0x00FF);
		USART_Handle->pTxBuffer += sizeof(uint8_t);
		USART_Handle->TxBufferSize--;
	}

	if(USART_Handle->TxBufferSize == 0){

		close_USART_ISR(USART_Handle);
	}
}

static void USART_ReceiveWith_IT(USART_HandleTypedef_t *USART_Handle){

	uint16_t *p16BitsBuffer;
	uint8_t *p8BitsBuffer;

	if((USART_Handle->Init.Wordlength == USART_WORDLENGTH_9Bits)  && (USART_Handle->Init.Parity == USART_PARITY_NONE)){

		p16BitsBuffer = (uint16_t *)USART_Handle->pRxBuffer;
		p8BitsBuffer = NULL;
	}
	else{
		p8BitsBuffer = (uint8_t *)(USART_Handle->pRxBuffer);
		p16BitsBuffer = NULL;
	}

	if(p8BitsBuffer == NULL){

		*p16BitsBuffer = (uint16_t)(USART_Handle->Instance->DR & 0x01FFU);
		USART_Handle->pRxBuffer += sizeof(uint16_t);
		USART_Handle->RxBufferSize -=2;
	}
	else{

		if((USART_Handle->Init.Wordlength == USART_WORDLENGTH_9Bits)  && (USART_Handle->Init.Parity == USART_PARITY_NONE)){
			*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);
			USART_Handle->pRxBuffer++;
			USART_Handle->RxBufferSize--;

		}
		else if ((USART_Handle->Init.Wordlength == USART_WORDLENGTH_8Bits)  && (USART_Handle->Init.Parity == USART_PARITY_NONE)){
			*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);
			USART_Handle->pRxBuffer++;
			USART_Handle->RxBufferSize--;
		}

	   else{
		*p8BitsBuffer = (uint8_t)(USART_Handle->Instance->DR & 0x007FU);
		USART_Handle->pRxBuffer++;
		USART_Handle->RxBufferSize--;
	}
 }

	if(USART_Handle->RxBufferSize == 0){

		close_USART_ISR_Rx(USART_Handle);
	}
}

void USART_Init(USART_HandleTypedef_t *USART_Handle){

	uint32_t periphClock;
	uint32_t mantissapart = 0;
	uint32_t fractionpart = 0;
	uint32_t USART_DIV_Value = 0;
	uint32_t tempvalue = 0;

	uint32_t tempReg = 0;

	tempReg = USART_Handle->Instance->CR1;

	tempReg |= (USART_Handle->Init.Mode) | (USART_Handle->Init.Oversampling) | (USART_Handle->Init.Parity) | (USART_Handle->Init.Wordlength);

	USART_Handle->Instance->CR1 = tempReg;

	/* ******************************************************************************** */

	tempReg = USART_Handle->Instance->CR2;

	tempReg = ~(0x3U << USART_CR2_STOP);

	tempReg |= (USART_Handle->Init.StopBits);

	USART_Handle->Instance->CR2 = tempReg;

	/* ********************************************************************************* */

	tempReg = USART_Handle->Instance->CR3;

	tempReg |= (USART_Handle->Init.HardWareFlowControl);

	USART_Handle->Instance->CR3 = tempReg;

	if(USART_Handle->Instance == USART1  || USART6){

		periphClock = RCC_GetPClock2();
	}

	else{

		periphClock = RCC_GetPClock1();
	}

	if(USART_Handle->Init.Oversampling == USART_OVERSAMPLE_8){

		USART_DIV_Value = __USART_DIV_VALUE_8(periphClock, USART_Handle->Init.BaudRate);
		mantissapart = (USART_DIV_Value / 100U);
		fractionpart = (USART_DIV_Value) - (mantissapart * 100U);

		fractionpart = ( ( (fractionpart * 8U) + 50U) / 100U) & (0x07U);
	}

	else{

		USART_DIV_Value = __USART_DIV_VALUE_16(periphClock, USART_Handle->Init.BaudRate);
		mantissapart = (USART_DIV_Value / 100U);
		fractionpart = (USART_DIV_Value) - (mantissapart * 100U);

		fractionpart = ( ( (fractionpart * 16U) + 50U) / 100U) & (0x0FU);
	}

	tempvalue |= (mantissapart << 4U);
	tempvalue |= (fractionpart << 0U);

	USART_Handle->Instance->BRR = tempvalue;
}

void USART_Transmit(USART_HandleTypedef_t *USART_Handle , uint8_t *pData , uint16_t dataSize){

	uint16_t *data16Bits;

	if( (USART_Handle->Init.Wordlength == USART_WORDLENGTH_9Bits ) & (USART_Handle->Init.Parity == USART_PARITY_NONE)){

		data16Bits = (uint16_t *)pData;
	}

	else{

		data16Bits = NULL;
	}

	while(dataSize > 0){

		while(!(USART_GetFlagStatus(USART_Handle, USART_TXE_Flag)));

		if(data16Bits == NULL){

			USART_Handle->Instance->DR = (uint8_t)(*pData & (0xFFU));
			pData++;
			dataSize--;
		}
		else{

			USART_Handle->Instance->DR = (uint16_t)(*data16Bits & (0x01FFU));
			data16Bits++;
			dataSize -=2;
		}
	}
	while(!(USART_GetFlagStatus(USART_Handle, USART_TC_Flag)));
}

void USART_Receive(USART_HandleTypedef_t *USART_Handle , uint8_t *pBuffer , uint16_t dataSize){

	uint16_t *p16Bitsbuffer;
	uint8_t *p8Bitsbuffer;

	if((USART_Handle->Init.Wordlength == USART_WORDLENGTH_9Bits)  && (USART_Handle->Init.Parity == USART_PARITY_NONE)){

		p16Bitsbuffer = (uint16_t *)pBuffer;
		p8Bitsbuffer = NULL;
	}

	else{
		p8Bitsbuffer = (uint8_t *)pBuffer;
		p16Bitsbuffer = NULL;
	}

	while(dataSize > 0){

		while(!(USART_GetFlagStatus(USART_Handle, USART_RXE_Flag)));

		if(p8Bitsbuffer == NULL){

			*p16Bitsbuffer = (uint16_t)(USART_Handle->Instance->DR & 0x01FFU);
			p16Bitsbuffer++;
			dataSize -=2;
		}

		else{

			if((USART_Handle->Init.Wordlength == USART_WORDLENGTH_9Bits)  && (USART_Handle->Init.Parity != USART_PARITY_NONE)){

				*p8Bitsbuffer = (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);
				p8Bitsbuffer++;
				dataSize--;
			}

			else if((USART_Handle->Init.Wordlength == USART_WORDLENGTH_8Bits)  && (USART_Handle->Init.Parity != USART_PARITY_NONE)){

				*p8Bitsbuffer = (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);
				p8Bitsbuffer++;
				dataSize--;
			}

			else{

				*p8Bitsbuffer = (uint8_t)(USART_Handle->Instance->DR & 0x007FU);
				p8Bitsbuffer++;
				dataSize--;
			}
		}
	}
}

void USART_TransmitData_IT(USART_HandleTypedef_t *USART_Handle , uint8_t *pBuffer , uint16_t dataSize){

	USART_Busstate_t usart_bus_state = USART_Handle->Txstatus;

	if(usart_bus_state != USART_BUS_Tx){

		USART_Handle->pTxBuffer = (uint8_t *)pBuffer;
		USART_Handle->TxBufferSize = (uint16_t)dataSize;
		USART_Handle->Txstatus = USART_BUS_Tx;
		USART_Handle->TxISR_Function = USART_SendWith_IT;

		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_TXEIE);
	}
}

void USART_ReceiveData_IT(USART_HandleTypedef_t *USART_Handle , uint8_t *pBuffer , uint16_t dataSize){

	USART_Busstate_t usart_bus_state = USART_Handle->Rxstatus;

	if(usart_bus_state != USART_BUS_Rx){

		USART_Handle->pRxBuffer = (uint8_t *)pBuffer;
		USART_Handle->RxBufferSize = (uint16_t)dataSize;
		USART_Handle->Rxstatus = USART_BUS_Rx;
		USART_Handle->RxISR_Function = USART_ReceiveWith_IT;

		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_RXEIE);
	}
}

void USART_PeriphCmd(USART_HandleTypedef_t *USART_Handle , Functional_State_t stateofUSART){

	if(stateofUSART == ENABLE){

		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_UE);
	}

	else{

		USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_UE);
	}

}
USART_FlagStatus_t USART_GetFlagStatus(USART_HandleTypedef_t *USART_Handle , uint16_t flagName){

	return ( (USART_Handle->Instance->SR & flagName) ? USART_FLAG_SET : USART_FLAG_RESET);
}

void USART_InterruptHandler(USART_HandleTypedef_t *USART_Handle){

	uint8_t flagValue = 0;
	uint8_t interruptValue = 0;

	flagValue = (uint8_t)((USART_Handle->Instance->SR >> 7U) & 0x1U);
	interruptValue = (uint8_t)( (USART_Handle->Instance->CR1 >> 7U) & 0x1U);

	if(flagValue && interruptValue){

		USART_Handle->TxISR_Function(USART_Handle);
	}

	flagValue = (uint8_t)((USART_Handle->Instance->SR >> 5U) & 0x1U);
	interruptValue = (uint8_t)( (USART_Handle->Instance->CR1 >> 5U) & 0x1U);

	if(flagValue && interruptValue){

		USART_Handle->RxISR_Function(USART_Handle);
	}
}
















