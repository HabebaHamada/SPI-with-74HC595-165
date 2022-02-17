/*
 * 74HC595 Shift Register.c
 *
 * Created: 2/16/2022 7:54:00 PM
 * Author: HABEBA HAMADA
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "spi.h"        
#include "BIT Macros.h" 

//Definition for Master initializing
#define  DATA_ORDER     0
#define  CLOCK_POLARITY 0
#define  CLOCK_PHASE    0
#define  CLOCK_RATE     16
#define  SPEED_DOUBLE   0

#define EN1   3  //Definition for Latch pin in 74HC595
int main(void)
{
	SET_BIT(SPI_Direction,EN1);
	SPI_INTMASTER(DATA_ORDER,CLOCK_POLARITY,CLOCK_PHASE,CLOCK_RATE,SPEED_DOUBLE);
	char OUTPUT;
	
    while(1)
    {
		//Read Digital Data From 74HC165 
		
		SET_BIT(SPI_Port,SS);           
		SPI_Master_WRITE(0X00);
		CLEAR_BIT(SPI_Port,SS);            
		OUTPUT=SPI_MASTER_READ();
		_delay_ms(10);
		
		//Output Digital Data To 74HC595
		
		CLEAR_BIT(SPI_Port,EN1);           
		SPI_Master_WRITE(OUTPUT);
		SET_BIT(SPI_Port,EN1);           
        _delay_ms(10);
    }
}
