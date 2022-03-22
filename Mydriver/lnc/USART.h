#ifndef LNC_USART_H_
#define LNC_USART_H_

#include "stm32f407xx.h"

/*
 *  @def_group Mode_Types
 */

#define USART_MODE_Tx                 ( (uint32_t)(0x00000008) )
#define USART_MODE_Rx				  ( (uint32_t)(0x00000004) )
#define USART_MODE_Tx_Rx			  ( (uint32_t)(0x0000000C) )

/*
 * @def_group Wordlength_Types
 */

#define USART_WORDLENGTH_8Bits		  ( (uint32_t)(0x00000000) )
#define USART_WORDLENGTH_9Bits        ( (uint32_t)(0x00001000) )

/*
 * @def_group Parity_Types
 */

#define USART_PARITY_NONE 			  ( (uint32_t)(0x00000000) )
#define USART_PARITY_EVEN			  ( (uint32_t)(0x00000400) )
#define USART_PARITY_ODD			  ( (uint32_t)(0x00000600) )

/*
 * @def_group StopBits_Types
 */

#define USART_STOPBIT_1               ( (uint32_t)(0x00000000) )
#define USART_STOPBIT_Half			  ( (uint32_t)(0x00001000) )
#define USART_STOPBIT_2				  ( (uint32_t)(0x00002000) )
#define USART_STOPBIT_1_Half		  ( (uint32_t)(0x00003000) )

/*
 * @def_group Oversampling_Mode
 */

#define USART_OVERSAMPLE_16           ( (uint32_t)(0x00000000) )
#define USART_OVERSAMPLE_8            ( (uint32_t)(0x00008000) )

/*
 * @def_group HardWareFlowControl_Mode
 */

#define USART_HW_NONE                 ( (uint32_t)(0x00000000) )
#define USART_HW_CTS				  ( (uint32_t)(0x00000200) )
#define USART_HW_RTS				  ( (uint32_t)(0x00000100) )
#define USART_HW_CTS_RTS			  ( (uint32_t)(0x00000300) )

typedef enum {

	USART_FLAG_RESET = 0x0U,
	USART_FLAG_SET = !USART_FLAG_RESET

}USART_FlagStatus_t;

#define __USART_DIV_VALUE_16(__CLOCK__ , __BAUDRATE__)    ( 25U * (uint32_t)(__CLOCK__) ) / ( 4U * (uint32_t)(__BAUDRATE__))
#define __USART_DIV_VALUE_8(__CLOCK__ , __BAUDRATE__)     ( 25U * (uint32_t)(__CLOCK__) ) / ( 2U * (uint32_t)(__BAUDRATE__))

typedef enum{

	USART_BUS_FREE = 0x0U,
	USART_BUS_Tx = 0x1U,
	USART_BUS_Rx = 0x2U

}USART_Busstate_t;

typedef struct{

	uint32_t Mode;                /* Transmission and reception modes @def_group Mode_Types          */
	uint32_t BaudRate;
	uint32_t Parity;			  /* Even and Odd parity @def_group Parity_Types                     */
	uint32_t StopBits;			  /* StopBits modes @def_group StopBits_Types                        */
	uint32_t Oversampling;		  /* Oversampling modes @def_group Oversampling_Mode                 */
	uint32_t Wordlength;          /* 8 Bits & 9 Bits mode @def_group Wordlength_Types                */
	uint32_t HardWareFlowControl; /* HardWareFlowControl modes @def_group HardWareFlowControl_Mode   */

}USART_Init_Typedef_t;

typedef struct  __USART_HandleTypedef_t{

	USART_TypeDef_t *Instance;
	USART_Init_Typedef_t Init;
	uint8_t  *pTxBuffer;
	uint16_t TxBufferSize;
	uint8_t Txstatus;
	void (*TxISR_Function)(struct __USART_HandleTypedef_t *USART_Handle);
	uint8_t *pRxBuffer;
	uint16_t RxBufferSize;
	uint8_t Rxstatus;
	void (*RxISR_Function)(struct __USART_HandleTypedef_t *USART_Handle);

}USART_HandleTypedef_t;

void USART_Init(USART_HandleTypedef_t *USART_Handle);
void USART_Transmit(USART_HandleTypedef_t *USART_Handle , uint8_t *pData , uint16_t dataSize);
void USART_Receive(USART_HandleTypedef_t *USART_Handle , uint8_t *pBuffer , uint16_t dataSize);
void USART_PeriphCmd(USART_HandleTypedef_t *USART_Handle , Functional_State_t stateofUSART);
void USART_TransmitData_IT(USART_HandleTypedef_t *USART_Handle , uint8_t *pBuffer , uint16_t dataSize);
void USART_ReceiveData_IT(USART_HandleTypedef_t *USART_Handle , uint8_t *pBuffer , uint16_t dataSize);
USART_FlagStatus_t USART_GetFlagStatus(USART_HandleTypedef_t *USART_Handle , uint16_t flagName);
void USART_InterruptHandler(USART_HandleTypedef_t *USART_Handle);


#endif /* LNC_USART_H_ */
