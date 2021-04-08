/*
 * SensorUltrasonido_hcsr04.h
 *
 *  Created on: 19 mar. 2021
 *      Author: eze
 */

#ifndef SENSORULTRASONIDO_HCSR04_H_
#define SENSORULTRASONIDO_HCSR04_H_
#include "headers.h"

/* para operar pclksel*/
#define PCLK_TIMER0	2

#define PIN_SENSORULTRASONIDO_TRIG	0,5	//	salida
#define	PIN_SENSORULTRASONIDO_ECHO	0,4	//	entrada
#define	PIN_LED_RED	0,22
#define	PIN_LED_2	0,10

#define TAMANIO_SENSOR_BUFFER 30

extern unsigned int SystemCoreClock;
void SensorUltrasonido_Init(void);
void TIMER2_Init(void);
void LED_Init(void);
void TIMER2_IRQHandler(void);

void SensorUltrasonido_Disparo(void);
void SensorUltrasonido_PUSH (uint32_t dato);
uint32_t SensorUltrasonido_POP (void);

#endif /* SENSORULTRASONIDO_HCSR04_H_ */
