/*
 * GccApplication5.c
 *
 * Created: 6/20/2017 7:04:38 PM
 * Author : Zeus
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
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
	
	UCSRB = (1<<RXEN)|(1<<TXEN); // Enabling Receiving and Transmitting Flags
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0); // URSEL - chooses one of UCSRC(1) and UBRRH(0)
	// USBS - Stop bit 1 (0) or 2 (1)
	// UCSZ0 - sets no. of data bits Ex. 8 (1)
	UCSRB |= (1 << RXCIE); // Sets Receive Interrupt Flag 
	
	}
int main(void)
{
    /* Replace with your application code */
   USART_Init( BAUD_PRESCALER);
    sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
    while(1)
	{	
	}
}
ISR(USART_RXC_vect)
{
	
char a;
 a = UDR; // transfer of data to a character empties receive buffer
UDR = a; // Copied data is sent back to be transmitter
}
