

/*
 * I2C.c
 *
 * Created: 7/6/2017 3:47:58 PM
 * Author : zeus
 */ 

#include <avr/io.h> 
#define  F_CPU 14745600UL
#include <util/delay.h>
#define  BAUDRATE 9600
#define BAUD_PRESCALER ((F_CPU/16*(BAUDRATE))-1)
//Baud rate is 2400


void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

unsigned char USART_Recieve( void )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<RXC)) );
	/* Put data into buffer, sends the data */
	return UDR;
}

void TWI_Init()
{
	
	TWBR=0b00100000;//set Baud rate ton 100kHZ
	TWSR=(0<<TWPS1)|(0<<TWPS0);//set prescalar to 1
}
 
void TWI_START()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	/* setting TWINT, Declaring Master and transmitting Start condition if Bus is available, activating TWI mode*/
	 while (!(TWCR &(1<<TWINT)));/* Wait for START BIT to be transmitted. TWINT is set - START condition has been transmitted.*/
	 while((TWSR & 0xF8) != 0x08);/*Acknowledgement received. Start bit successfully transmitted. Confirming control over Bus lines*/
}
void TWI_Address(unsigned int a)
{
	unsigned int a = 0x20;
	TWDR = 0x20; /*Loading address*/
	TWCR = (1<<TWINT) |(1<<TWEN);/*clearing TWINT, setting TWI transmission active*/
	while (!(TWCR &(1<<TWINT)));/* Waiting for Action Completion */
	while((TWSR & 0xF8) != 0x18/*MT_SLA_ACK*/);/*Check Completion of Address transmission and receiving Address Acknowledgement*/
}

void SLA_Transmit(unsigned char data)
{
	
	
	TWDR = data; /* Load Data to be sent*/
	TWCR = (1<<TWINT) | (1<<TWEN); /*Transmitiing Data*/
	while (!(TWCR & (1<<TWINT))); /* Waiting for Action Completion */
	while((TWSR & 0xF8) != 0x28/*MT_SLA_ACK*/);/*Completed transmission of transmission of Data, and receiving acknowledgement for the same*/
	USART_Transmit(TWSR & 0xF8);/*Check what is recieved as acknowledgement*/
}

void TWI_Stop()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); /* Transmit stop condition*/
	while(!(TWCR & (1<<TWSTO))); /*Waiting for stop condition to be transmitted*/
}

void ERROR()
{
	USART_Transmit('E');
}

int main(void)
{
	USART_Init(95);
	while (1) 
    {
		TWI_Init();
		TWI_START();
		TWI_Address();
		SLA_Transmit('a');
		TWI_Stop();
		_delay_ms(100);
    }
}

