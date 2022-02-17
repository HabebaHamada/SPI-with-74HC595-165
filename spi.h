/*
 * SPI DRIVER FOR MASTER ONLY.h
 *
 *  Created on: FEB 9, 2022
 *      Author: Habeba Hamada
 */

#ifndef SPI_H_

#include "BIT Macros.h"
#include <avr/io.h>
#include <stdint.h> 

//Define Used Registers
#define  SPI_Direction         DDRB
#define  SPI_Port              PORTB
#define  SPI_Contorl_Register  SPCR
#define  SPI_Status_Register  SPSR
#define  SPI_Data_Register     SPDR

//Define SPI pins
#define  SS   4
#define  MOSI 5
#define  MISO 6
#define  SCK  7

//Define For SPCR Register PINS
#define  SPIE   7
#define  SPE    6
#define  DORD   5
#define  MSTR   4
#define  CPOL   3
#define  CPHA   2
#define  SPR1   1
#define  SPR0   0

//Define For SPSR Register PINS
#define  SPIF   7
#define  WCOL   6
#define  SPI2X   0



//  Function to initialize SPI Master "without Interrupt"
void SPI_INTMASTER(uint8_t Dataorder,uint8_t CLKpol,uint8_t CLKphase,uint8_t CLKRate,uint8_t SpdDBL)
{
	SPI_Direction|=(1<<MOSI)|(1<<SS)|(1<<SCK);     //SET MOSI,SS,SCK OUTPUT
	SPI_Direction&=(~(1<<MISO));                  //CLEAR MISO INPUT
	
	SPI_Port|=(1<<SS);                          //SET SS HIGH
	
	//SPI Configuration
	
	if (CLKRate==4)
	{
		SPI_Contorl_Register|=(0<<7)|(1<<6)|(READ_BIT(Dataorder,0)<<5)|(1<<4)|(READ_BIT(CLKpol,0)<<3)|(READ_BIT(CLKphase,0)<<2)|(0<<1)|(0<<0);
	} 
	else if(CLKRate==16)
	{
		SPI_Contorl_Register|=(0<<7)|(1<<6)|(READ_BIT(Dataorder,0)<<5)|(1<<4)|(READ_BIT(CLKpol,0)<<3)|(READ_BIT(CLKphase,0)<<2)|(0<<1)|(1<<0);
	}
	else if(CLKRate==64)
	{
		SPI_Contorl_Register|=(0<<7)|(1<<6)|(READ_BIT(Dataorder,0)<<5)|(1<<4)|(READ_BIT(CLKpol,0)<<3)|(READ_BIT(CLKphase,0)<<2)|(1<<1)|(0<<0);
	}
	else if(CLKRate==128)
	{
		SPI_Contorl_Register|=(0<<7)|(1<<6)|(READ_BIT(Dataorder,0)<<5)|(1<<4)|(READ_BIT(CLKpol,0)<<3)|(READ_BIT(CLKphase,0)<<2)|(1<<1)|(1<<0);
	}
	if (READ_BIT(SpdDBL,0)==1)
	{
		SET_BIT(SPI_Status_Register,0);
	} 
	else
	{
		CLEAR_BIT(SPI_Status_Register,0);
	}

	
}

//Function to send and receive data for both master and slave
unsigned char SPI_Tranciever(unsigned char data)
{
	unsigned char buffer;
    SPI_Data_Register=data;                  // Load data into the buffer
	
	while(BIT_IS_CLEAR(SPI_Status_Register,SPIF));	//Wait till transmission complete
	buffer=SPI_Data_Register;
	return buffer;
	
}

//Function to Transmit data From Master
void SPI_Master_WRITE(unsigned char data)
{
	
	SPI_Data_Register=data;        //SERIAL DATA REGISTER
	
	while(BIT_IS_CLEAR(SPI_Status_Register,SPIF));	//Wait till transmission complete 
	
}
// Function to receive data from master 
unsigned char SPI_MASTER_READ()
{

	while(BIT_IS_CLEAR(SPI_Status_Register,SPIF));	//Wait till transmission complete
	
	return SPI_Data_Register;
	
}

#endif
/*  Function to initialize SPI Slave without Interrupt
void SPI_INTSLAVE()
{
	SET_BIT(DDRB,MISO);    // SET MISO OUTPUT
	CLEAR_BIT(DDRB,MOSI);
	CLEAR_BIT(DDRB,SS);
	CLEAR_BIT(DDRB,SCK);   //CLEAR MOSI, SS, SCK INPUT
	SET_BIT(SPCR,SPE);     //SET SPI ENABLE BIT
}
//Function to Transmit data From Slave
void SPI_Slave_WRITE(unsigned char data)
{
	char buffer;
	SPDR=data;        //SERIAL DATA REGISTER
	
	while(BIT_IS_CLEAR(SPSR,SPIF));	//Wait till transmission complete
	
	buffer=SPDR;
}

*/

