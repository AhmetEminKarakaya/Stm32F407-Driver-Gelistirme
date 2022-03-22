#include "stm32f407xx.h"

/*

static void Led_Config();
static void Button_InterruptConfig();
static void SPI_Config();
static void SPI_GPIO_Config();

SPI_HandleTypeDef_t SPI_Handle;


void EXTI0_IRQHandler(){

	char msgtosend[] = "Hello World\n";

		if(EXTI->PR & 0x1U){

			EXTI->PR |= (0x1U << 0U);

			SPI_TransmitData_IT(&SPI_Handle, (uint8_t*)msgtosend, strlen(msgtosend));
		}
}

void SPI1_IRQHandler(){

	SPI_InterruptHandler(&SPI_Handle);
}

*/
int main(void)
{

	//Led_Config();

	//Button_InterruptConfig();

	//SPI_GPIO_Config();

	//SPI_Config();

	while(1){


	}
}

/*
static void Led_Config(){

	GPIO_InitTypedef_t GPIO_Init_Struct = { 0 };

	RCC_GPIOD_CLK_ENABLE();
	RCC_GPIOA_CLK_ENABLE();

	GPIO_Init_Struct.pinnumber = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_Init_Struct.Mode = GPIO_MODE_OUTPUT;
	GPIO_Init_Struct.Otype = GPIO_OTYPE_PP;
	GPIO_Init_Struct.Speed = GPIO_SPEED_MEDIUM;
	GPIO_Init_Struct.PuPd = GPIO_PUPD_NOPULL;

	GPIO_Init(GPIOD, &GPIO_Init_Struct);

 memset(&GPIO_Init_Struct,0,sizeof(GPIO_Init_Struct));

	GPIO_Init_Struct.pinnumber = GPIO_PIN_0;
	GPIO_Init_Struct.Mode = GPIO_MODE_INPUT;
	GPIO_Init_Struct.PuPd = GPIO_PUPD_PULLDOWN;

	GPIO_Init(GPIOA, &GPIO_Init_Struct);

}
*/
/*
static void Button_InterruptConfig(){

	RCC_SYSCFG_CLK_ENABLE();

	EXTI_Init_TypeDef_t EXTI_Init_Struct = {0};

	EXTI_Line_Config(EXTI_PortSource_GPIOA, EXTI_LineSource_0);


	EXTI_Init_Struct.EXTI_Line_Cmd = ENABLE;
	EXTI_Init_Struct.EXTI_Linenumber = EXTI_LineSource_0;
	EXTI_Init_Struct.Mode = EXTI_Mode_Interrupt;
	EXTI_Init_Struct.TriggerSelect = EXTI_Trigger_Rising;

	EXTI_Init(&EXTI_Init_Struct);

	NVIC_EnableInterrupt(EXTI0_IRQNumber);


}

*/
/*

static void SPI_Config(){

	SPI_HandleTypeDef_t SPI_Handle = { 0 };

	RCC_SPI1_CLK_ENABLE();

	SPI_Handle.Instance = SPI1;
	SPI_Handle.Init.BaudRate = SPI_BAUDRATE_DIV8;
	SPI_Handle.Init.BusConfig = SPI_Bus_FullDuplex;
	SPI_Handle.Init.CPHA = SPI_CPHA_FIRST;
	SPI_Handle.Init.CPOL = SPI_CPOL_LOW;
	SPI_Handle.Init.DFF_Format = SPI_DFF_8BITS;
	SPI_Handle.Init.Frame_Format = SPI_FRAMEFORMAT_MSB;
	SPI_Handle.Init.Mode = SPI_MODE_MASTER;
	SPI_Handle.Init.SSM_Cmd = SPI_SSM_ENABLE;


	SPI_Init(&SPI_Handle);

	NVIC_EnableInterrupt(SPI1_IRQNumber);

	SPI_PeriphCmd(&SPI_Handle, ENABLE);


}

*/
/*
static void SPI_GPIO_Config(){

	GPIO_InitTypedef_t GPIO_Initstructer = { 0 };

	GPIO_Initstructer.pinnumber = GPIO_PIN_5 | GPIO_PIN_7;
	GPIO_Initstructer.Mode = GPIO_MODE_ALTERNATE;
	GPIO_Initstructer.Otype = GPIO_OTYPE_PP;
	GPIO_Initstructer.PuPd = GPIO_PUPD_NOPULL;
	GPIO_Initstructer.Speed = GPIO_SPEED_HIGH;
	GPIO_Initstructer.Alternate = GPIO_AF_5;

	GPIO_Init(GPIOA, &GPIO_Initstructer);
}



*/







