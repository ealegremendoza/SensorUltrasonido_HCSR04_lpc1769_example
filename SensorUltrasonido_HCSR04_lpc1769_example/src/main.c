/*
===============================================================================
 Name        : SensorUltrasonido_HCSR04_lpc1769_example.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "headers.h"

void SystemInit(void)
{
	InitPLL();
	SysTick_Init(1000);
	LED_Init();
	SensorUltrasonido_Init();

}
int main(void)
{
	uint32_t medicion=0;
	SystemInit();
    while(1)
    {
    	medicion=SensorUltrasonido_POP();
    	/*	Faltaría filtrar la señal digital	*/
    	printf("M %d cm\n", medicion);
    	if(medicion<5)
    	{
    		GPIO_Set(PIN_LED_2,1);
    	}
    	else
    	{
    		GPIO_Set(PIN_LED_2,0);
    	}
    }
    return 0 ;
}


