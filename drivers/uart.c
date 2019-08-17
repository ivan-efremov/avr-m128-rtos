/*
 * uart.c: UART driver
 */

#include <kernel.h>
#include <uart.h>
#include <errno.h>

static int uart_baudrate(unsigned char minordev, unsigned long int baud)
{
	unsigned char brDiv =
		(unsigned char)((F_CPU+(baud*8L))/(baud*16L)-1);
	switch(minordev)
	{
	case UART0:
		UBRR0L = brDiv;
		break;
	case UART1:
		UBRR1L = brDiv;
		break;
	default:
	#if DEBUG
		printk("Warning:UART%i device not found\n", minordev);
	#endif
		return ENODEV;
	}
	return OK;
}

int uart_ioctl()
{
	return ERR;
}

int uart_open(unsigned char minordev, unsigned long int baud, unsigned char flags)
{
	unsigned char f_ucsrb = 0;
	if(flags & F_RX) // !!! check flags
		f_ucsrb = 1 << RXEN;
	if(flags & F_TX)
		f_ucsrb |= 1 << TXEN;
	switch(minordev)
	{
	case UART0:
		UCSR0B = f_ucsrb;
		break;
	case UART1:
		UCSR1B = f_ucsrb;
		break;
	default:
	#if DEBUG
		printk("Warning:UART%i device not found\n", minordev);
	#endif
		return ENODEV;
	}
	(void)uart_baudrate(minordev, baud); // set baud rate
	return OK;
}

int uart_close(unsigned char minordev)
{
	switch(minordev)
	{
	case UART0: // UART0
		while(!(UCSR0A & (1<<UDRE)));
		while(!(UCSR0A & (1<<TXC)));
		UCSR0B = 0;
		break;
	case UART1: // UART1
		while(!(UCSR1A & (1<<UDRE)));
		while(!(UCSR1A & (1<<TXC)));
		UCSR1B = 0;
		break;
	default:
	#if DEBUG
		printk("Warning:UART%i device not found\n", minordev);
	#endif
		return ENODEV;
	}
	delay(10);
	return OK;
}

int uart_read(unsigned char minordev)
{
//	unsigned char status;
	int byte = 0;
	switch(minordev)
	{
	case UART0: // UART0
		while(!(UCSR0A & (1<<RXC))); // wait fulling receiver buffer
//		status = UCSR0A;
		byte = (int)UDR0;
		break;
	case UART1: // UART1
		while(!(UCSR1A & (1<<RXC)));
//		status = UCSR1A;
		byte = (int)UDR1;
		break;
	default:
	#if DEBUG
		printk("Warning:UART%i device not found\n", minordev);
	#endif
		return ENODEV;
	}
/*
	if(status & (1<<DOR))
	{
		uart[minordev].errors |= ERR_HW_BUF_OVERFLOW;
		return ERR;
	}
*/
	return byte;
}

int uart_write(unsigned char minordev, unsigned char byte)
{
	switch(minordev)
	{
	case UART0: // UART0
		while(!(UCSR0A & (1<<UDRE))); // wait cleaning transmit buffer
		UDR0 = byte; // load byte of data and starting transmit
		break;
	case UART1: // UART1
		while(!(UCSR1A & (1<<UDRE)));
		UDR1 = byte;
		break;
	default:
	#if DEBUG
		printk("Warning:UART%i device not found\n", minordev);
	#endif
		return ENODEV;
	}
	return OK;
}
