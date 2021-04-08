/*
 * SensorUltrasonido_hcsr04.c
 *
 *  Created on: 19 mar. 2021
 *      Author: eze
 */
#include "SensorUltrasonido_hcsr04.h"
uint32_t g_distanciaCM = 0;
uint32_t Sensor_Buffer[TAMANIO_SENSOR_BUFFER];
uint32_t IndiceIn=0;
uint32_t IndiceOut=0;
void SensorUltrasonido_Init(void)
{
	GPIO_Func(PIN_SENSORULTRASONIDO_TRIG,FUNC_GPIO);
	GPIO_Dir(PIN_SENSORULTRASONIDO_TRIG,DIR_SALIDA);

	/*	CONFIGURO EL PIN CAP2.0
	 *  El pin CAPn.m es el único que tiene esta funcionalidad 	*/
	GPIO_Func(PIN_SENSORULTRASONIDO_ECHO,FUNC_FUNC3);

	TIMER2_Init();

}
void LED_Init(void)
{
	GPIO_Func(PIN_LED_RED,FUNC_GPIO);
	GPIO_Dir(PIN_LED_RED,DIR_SALIDA);
	GPIO_Set(PIN_LED_RED,0);

	GPIO_Func(PIN_LED_2,FUNC_GPIO);
	GPIO_Dir(PIN_LED_2,DIR_SALIDA);
	GPIO_Set(PIN_LED_2,0);
}

void TIMER2_Init(void)
{
	/*	ALIMENTO EL PERIFERICO */
	PCONP |=1<<22;	// Enciendo el periferico TIMER2
	PCLKSEL1 |=1<<12;	// CCLK -> 100MHz para TIMER2

	/*	RESETEO EL TIMER */
	T2TCR = 2;	//RESET TIMER
	TIMER2.PR=CCLK/1000000-1;// Prescaler = 100-1 (cuenta hasta el 0)

	/*	CONFIGURO EL PIN CAP2.0
	 *  El pin CAPn.m es el único que tiene esta funcionalidad 	*/
	//GPIO_Func(PIN_SENSORULTRASONIDO_ECHO,FUNC_FUNC3);

	T2CCR=0;
	T2CCR|=(0<<0);	//NO Capturo cuando CAP2.0 tiene un flanco ascendente
	T2CCR|=(1<<1);	//SI Capturo cuando CAP2.0 tiene un flanco descendente
	T2CCR|=(1<<2);	//SI Activo la interrupcion

	/*	MATCH0	*/
	T2MR0 = (4-1);//MR0= 500000us	// resto 1 porque contemplo el cero!
	T2MCR = 0;
	T2MCR |= (1<<0)|	//	INT ACTIVADA
			 (0<<1)|	//	RESET DESACTIVADO
			 (0<<2);	//	STOP DESACTIVADO
	/*	MATCH1	*/
	T2MR1 = (10-1);//	MR1= 1000000us // resto 1 porque contemplo el cero!
	T2MCR |= (1<<3)|	//	INT ACTIVADA
			 (0<<4)|	//	RESET DESACTIVADO
			 (0<<5);	//	STOP DESACTIVADO

	/*	Apago el funcionamiento del EMR por las dudas */
	TIMER2.EMR = 0;
	/*	HABILITO INTERRUPCIONES DE LOS MATCH	*/
	T2IR = 0;
	T2IR = (1<<0);
	//T0IR = (1<<0)|(1<<1)|(1<<4);

	/*	INICIO EL TEMPORIZADOR	*/
	T2TCR = 0;
	T2TCR = (1<<0);

	/*	HABILITO INTERRUPCION DEL TIMER0 EN EL LPC	*/
	ISER0 |=1<<3;

}

void TIMER2_IRQHandler(void)
{
	uint32_t Temporal = T2IR;
	uint32_t capture=0;
	if(((Temporal>>0) & 0x01)==0x01)//MR0 interrumpe
	{
		T2IR|= 1 <<0 ;	//BORRO EL FLAG

		//CAMBIAR ESTADO SEÑAL A HIGH
		GPIO_Set(PIN_SENSORULTRASONIDO_TRIG,1);
	}
	if(((Temporal>>1) & 0x01)==0x01)//MR1 interrumpe
	{
		T2IR|= 1 <<1 ;	//BORRO EL FLAG
		GPIO_Set(PIN_SENSORULTRASONIDO_TRIG,0);

	}
	if(((Temporal>>4) & 0x01)==0x01)//CR0 interrumpe
	{
		T2IR|= 1 <<4 ;	//BORRO EL FLAG
		capture=0;
		capture=T2CR0-T2MR0-1;	//leo el valor de TC al momento de la captura
		/*	CALCULOS DE CONVERSION	*/
		//343[m/s[*1000[mm/m]*1/1000000[s/us] = 1/2.92 [mm/us]
		capture*=10;
		capture/=292;
		capture/=2;
		capture-=8;
		SensorUltrasonido_PUSH (capture);
		//printf("c %d cm\n",capture);

		// 	RESETEAR CONTADOR
		T2TCR = 2;	//RESET TIMER
		T2TCR = (1<<0);
	}
}

void SensorUltrasonido_PUSH (uint32_t dato)
{
	Sensor_Buffer[IndiceIn]=dato;
	IndiceIn++;
	IndiceIn%= TAMANIO_SENSOR_BUFFER;
}

uint32_t SensorUltrasonido_POP(void)
{
	uint32_t temporal=0;
	if(IndiceOut!=IndiceIn)
	{
		temporal=Sensor_Buffer[IndiceOut];
		IndiceOut++;
		IndiceOut%=TAMANIO_SENSOR_BUFFER;
	}
	return temporal;
}
