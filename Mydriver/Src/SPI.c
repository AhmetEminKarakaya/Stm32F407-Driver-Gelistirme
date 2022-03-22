#include "SPI.h"

static void SPI_CloseISR_TX(SPI_HandleTypeDef_t *SPI_Handle){

	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_TXEIE);
	SPI_Handle->TxDataSize = 0;
	SPI_Handle->pTxDataAdrr = NULL;
	SPI_Handle->busstate = SPI_BUS_FREE;
}

static void SPI_CloseISR_RX(SPI_HandleTypeDef_t *SPI_Handle){

	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_RXEIE);
	SPI_Handle->RxDataSize = 0;
	SPI_Handle->pRxDataAddr = NULL;
	SPI_Handle->busstateRx = SPI_BUS_FREE;
}

static void SPI_TransmitHelper_16Bits(SPI_HandleTypeDef_t *SPI_Handle){

	SPI_Handle->Instance->DR = *( (uint16_t *)(SPI_Handle->pTxDataAdrr) );
	SPI_Handle->pTxDataAdrr += sizeof(uint16_t);
	SPI_Handle->TxDataSize -=2;
}

static void SPI_TransmitHelper_8Bits(SPI_HandleTypeDef_t *SPI_Handle){

	SPI_Handle->Instance->DR = *( (uint8_t *)(SPI_Handle->pTxDataAdrr) );
	SPI_Handle->pTxDataAdrr += sizeof(uint8_t);
	SPI_Handle->TxDataSize --;

	if(SPI_Handle->TxDataSize == 0){

		SPI_CloseISR_TX(SPI_Handle);
	}
}

static void SPI_ReceiveHelper_16Bits(SPI_HandleTypeDef_t *SPI_Handle){

	SPI_Handle->Instance->DR = *( (uint16_t *)(SPI_Handle->pRxDataAddr) );
	SPI_Handle->pRxDataAddr += sizeof(uint16_t);
	SPI_Handle->RxDataSize -=2;
}
static void SPI_ReceiveHelper_8Bits(SPI_HandleTypeDef_t *SPI_Handle){

	SPI_Handle->Instance->DR = *( (uint8_t *)(SPI_Handle->pRxDataAddr) );
	SPI_Handle->pRxDataAddr += sizeof(uint8_t);
	SPI_Handle->RxDataSize --;

		if(SPI_Handle->RxDataSize == 0){

			SPI_CloseISR_RX(SPI_Handle);
		}
}

/*
 *     @brief: SPI_Init, Configures the SPI Peripheral
 *
 * 	   @param: SPI_Handle = User config  structer
 */


void SPI_Init(SPI_HandleTypeDef_t *SPI_Handle){

	uint32_t tempvalue = 0;

	tempvalue = SPI_Handle->Instance->CR1;

	tempvalue |= (SPI_Handle->Init.BaudRate) | (SPI_Handle->Init.CPHA) | (SPI_Handle->Init.CPOL) | (SPI_Handle->Init.DFF_Format) \
			| (SPI_Handle->Init.Mode) | (SPI_Handle->Init.Frame_Format) | (SPI_Handle->Init.BusConfig) | (SPI_Handle->Init.SSM_Cmd);

	SPI_Handle->Instance->CR1 = tempvalue;
}

/*
 *     @brief: SPI_PeriphCmd, Enable or Disable SPI Peripheral
 *
 * 	   @param: SPI_Handle = User config  structer
 * 	   @param:	stateofSPI = ENABLE or DISABLE
 */

void SPI_PeriphCmd(SPI_HandleTypeDef_t *SPI_Handle, Functional_State_t stateofSPI){

	if(stateofSPI == ENABLE){

		SPI_Handle->Instance->CR1 |= (0x1U << SPI_CR1_SPE);
	}

	else{

		SPI_Handle->Instance->CR1 &= ~(0x1U << SPI_CR1_SPE);
	}
}


/*
 *     @brief: SPI_TransmitData , transmits data to slave mode
 *
 * 	   @param: SPI_Handle = User config  structer
 * 	   @param: pdata = address of data to send
 * 	   @param: sizeOfData = Length of your data in bytes
 */

void SPI_TransmitData(SPI_HandleTypeDef_t *SPI_Handle , uint8_t *pdata , uint16_t sizeOfData){

	if(SPI_Handle->Init.DFF_Format == SPI_DFF_16BITS){

		while(sizeOfData >0 ){

			if(SPI_GetFlagStatus(SPI_Handle, SPI_TXE_Flag)){

				SPI_Handle->Instance->DR = *( (uint16_t *) pdata);

				pdata += sizeof(uint16_t);
				sizeOfData -=2;
			}
		}
	}

	else{

		while(sizeOfData >0 ){

		 if(SPI_GetFlagStatus(SPI_Handle, SPI_TXE_Flag)){

		SPI_Handle->Instance->DR = *pdata;

		pdata += sizeof(uint8_t);
		sizeOfData--;
					}
	     }
	}

	while(SPI_GetFlagStatus(SPI_Handle, SPI_BUSY_Flag));
}

void SPI_ReceiveData(SPI_HandleTypeDef_t *SPI_Handle , uint8_t *pbuffer , uint16_t sizeOfData){

	if(SPI_Handle->Init.DFF_Format == SPI_DFF_16BITS){

		while(sizeOfData > 0 ){

			if(SPI_GetFlagStatus(SPI_Handle, SPI_RXNE_Flag)){

				*( (uint16_t*)pbuffer) = (uint16_t)SPI_Handle->Instance->DR;
				pbuffer += sizeof(uint16_t);
				sizeOfData -=2;
			}
		}
	}

	else{

		while(sizeOfData > 0){

			if(SPI_GetFlagStatus(SPI_Handle, SPI_RXNE_Flag)){

				*(pbuffer) = *((__IO uint8_t*)&SPI_Handle->Instance->DR);
				pbuffer += sizeof(uint8_t);
				sizeOfData --;
		}
	  }

	}
}

void SPI_TransmitData_IT(SPI_HandleTypeDef_t *SPI_Handle , uint8_t *pdata , uint16_t sizeOfData){

		SPI_Bus_Status busState = SPI_Handle->busstate;

		if(busState != SPI_BUS_BUSY_TX){

		SPI_Handle->pTxDataAdrr = (uint8_t *)pdata;
		SPI_Handle->TxDataSize = (uint16_t)sizeOfData;
		SPI_Handle->busstate = SPI_BUS_BUSY_TX;

		if(SPI_Handle->Instance->CR1 & (0x1U << SPI_CR1_DFF)){

			SPI_Handle->TxISRFunction = SPI_TransmitHelper_16Bits;
		}
		else{

			SPI_Handle->TxISRFunction = SPI_TransmitHelper_8Bits;
		}


		SPI_Handle->Instance->CR2 |= (0x1U << SPI_CR2_TXEIE);
		}
}

void SPI_ReceiveData_IT(SPI_HandleTypeDef_t *SPI_Handle , uint8_t *pbuffer , uint16_t sizeOfData){

		SPI_Bus_Status busState = SPI_Handle->busstateRx;

		if(busState != SPI_BUS_BUSY_RX){

			SPI_Handle->pRxDataAddr = (uint8_t*)pbuffer;
			SPI_Handle->RxDataSize = (uint16_t)sizeOfData;
			SPI_Handle->busstateRx = SPI_BUS_BUSY_RX;

			if(SPI_Handle->Instance->CR1 & (0x1U << SPI_CR1_DFF)){

				SPI_Handle->RxISRFunction = SPI_ReceiveHelper_16Bits;
			}

			else{
				SPI_Handle->RxISRFunction = SPI_ReceiveHelper_8Bits;
			}

			SPI_Handle->Instance->CR2 |= (0x1U << SPI_CR2_RXEIE);
		}
}

void SPI_InterruptHandler(SPI_HandleTypeDef_t *SPI_Handle){

	uint8_t interruptSource = 0;
	uint8_t interruptFlag = 0;

	interruptSource = SPI_Handle->Instance->CR2 & (0x1U << SPI_CR2_TXEIE);
	interruptFlag = SPI_Handle->Instance->SR & (0x1U << SPI_SR_TXE);

	if( (interruptSource !=0 ) && (interruptFlag !=0 )){

		SPI_Handle->TxISRFunction(SPI_Handle);
	}

	interruptSource = SPI_Handle->Instance->CR2 & (0x1U << SPI_CR2_RXEIE);
	interruptFlag = SPI_Handle->Instance->SR & (0x1U << SPI_SR_RXNE);

	if( (interruptSource !=0 ) && (interruptFlag !=0 )){

			SPI_Handle->RxISRFunction(SPI_Handle);
		}
}

/*
 *     @brief: SPI_GetFlagStatus , return the flag of SR register
 *
 * 	   @param: SPI_Handle = User config  structer
 * 	   @param: SPI_Flag = flag name of SR register
 *
 */

SPI_FlagStatus_t SPI_GetFlagStatus(SPI_HandleTypeDef_t *SPI_Handle , uint16_t SPI_Flag){

	return  (SPI_Handle->Instance->SR & SPI_Flag ) ? SPI_FLAG_SET : SPI_FLAG_RESET;
}

