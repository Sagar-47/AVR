#include <avr/io.h>


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
 }

 unsigned char USART_Recieve( void )
 {
 /* Wait for empty transmit buffer */
 while ( !( UCSRA & (1<<RXC)) );
 /* Put data into buffer, sends the data */
 return UDR;
 } 


void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	DDRB = 0b01000000;
	/* Enable SPI */
	SPCR = (1<<SPE);
}
unsigned char SPI_SlaveReceive(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return Data Register */
	return SPDR;
}
int main (void)
{
	USART_Init(BAUD_PRESCALER);
	SPI_SlaveInit();
	while (1)
	{
	    unsigned char data_2 = USART_Recieve();
		SPDR = data_2;
		unsigned char data_1 = SPI_SlaveReceive();
		USART_Transmit(data_1);
		
	}
}
