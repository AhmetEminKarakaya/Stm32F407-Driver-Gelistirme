#include "Rcc.h"

const uint8_t AHB_Prescaler[] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 2 ,3 , 4 , 6 , 7 , 8 , 9};
const uint8_t APB_Prescaler[] = { 0 , 0 , 0 , 0 , 1 , 2 , 3 , 4 };

uint32_t RCC_GetSystemClock(){

	uint32_t systemclockcore = 0;
	uint8_t clkSource = 0;

	clkSource = ( (RCC->CFGR >> 2U) & 0x3U);

	switch(clkSource){

	case 1: systemclockcore = 16000000; break;
	case 2: systemclockcore =  8000000; break;

	default : systemclockcore = 16000000;
	}

	return systemclockcore;
}

uint32_t RCC_GetHClock(){

	uint32_t AHB_PeriphClock = 0;
	uint32_t SystemCoreClock = 0;
	uint8_t HPRE_Value = 0;
	uint8_t tempValue = 0;

	SystemCoreClock = RCC_GetSystemClock();

	HPRE_Value = ( (RCC->CFGR >> 4U) & 0xFU);
	tempValue = AHB_Prescaler[HPRE_Value];

	AHB_PeriphClock = (SystemCoreClock >> tempValue);

	return AHB_PeriphClock;
}

uint32_t RCC_GetPClock1(){

	uint32_t APB1_PeriphClock = 0;
	uint32_t Hclock = 0;
	uint8_t HPRE1_Value = 0;
	uint8_t tempvalue = 0;

	Hclock = RCC_GetHClock();

	HPRE1_Value = ( (RCC->CFGR >> 10U ) & 0x7U);

	tempvalue = APB_Prescaler[HPRE1_Value];

	APB1_PeriphClock = ( Hclock >> tempvalue);

	return APB1_PeriphClock;
}

uint32_t RCC_GetPClock2(){

	uint32_t APB2_PeriphClock = 0;
	uint32_t Hclock = 0;
	uint8_t HPRE2_Value = 0;
	uint8_t tempvalue = 0;

	Hclock = RCC_GetHClock();

	HPRE2_Value = ( (RCC->CFGR >> 13U) & 0x7U);

	tempvalue = APB_Prescaler[HPRE2_Value];

	APB2_PeriphClock = (Hclock >> tempvalue);

	return APB2_PeriphClock;
}


