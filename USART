/*
 * GccApplication5.c
 *
 * Created: 6/20/2017 7:04:38 PM
 * Author : zeus
 */ 


#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>
#define BAUDRATE 9600
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


int main(void)
{
    /* Replace with your application code */
   USART_Init( 95/*BAUD_PRESCALER*/);
    while(1)
	{
		unsigned char data = USART_Recieve(); // Receiving data in a separate bit is important 
		USART_Transmit(data);
	}
}

