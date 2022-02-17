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
int main(void)
{
	SET_BIT(DDRB,3);
	SPI_INTMASTER(0,0,0,16,0);
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
		
		CLEAR_BIT(SPI_Port,3);           
		SPI_Master_WRITE(OUTPUT);
		SET_BIT(SPI_Port,3);           
        _delay_ms(10);
    }
}
