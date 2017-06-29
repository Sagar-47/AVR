/*
 * SPI.c
 *
 * Created: 6/27/2017 5:32:53 PM
 * Author : zeus
 */ 

#include <avr/io.h>
#define F_CPU 14745600UL
#include <util/delay.h>
#define BAUDRATE 9600
#define BAUD_PRESCALER 95


void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRRH = (unsigned char)(95>>8);
	UBRRL = (unsigned char)95;
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
}unsigned char USART_Recieve( void )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<RXC)) );
	/* Put data into buffer, sends the data */
	return UDR;
}

void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<PINB5)|(1<<PINB7);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_MasterTransreceiver(unsigned char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

int main(void)
{
	USART_Init(BAUD_PRESCALER);
    SPI_MasterInit();
    while(1) 
    {
		unsigned char data_1 = USART_Recieve();
		SPI_MasterTransreceiver(data_1);
		USART_Transmit(SPDR);
    }
}

