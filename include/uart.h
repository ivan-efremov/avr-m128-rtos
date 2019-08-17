/*
 * uart.h: Uart driver version 0.01
 *         29/06/06
 */

#ifndef _UART_H_
#define _UART_H_

/***************************** CONST *******************************/

#define NR_UART     2           /* Number minor devices */

#define UART0   	0x00		/* UART0, do not change! */
#define UART1   	0x01 		/* UART1, do not change! */

/**************************** BUFFERS ******************************/

#define UART0_TX_BUFFER_SIZE 32 /* Number of bytes for UART0 transmit buffer */
#define UART1_TX_BUFFER_SIZE 32 /* Number of bytes for UART1 transmit buffer */

#define UART0_RX_BUFFER_SIZE 32 /* Number of bytes for UART0 receive buffer */
#define UART1_RX_BUFFER_SIZE 32 /* Number of bytes for UART1 receive buffer */

/***************************** BAUD ********************************/

#define BR_110	110L     	/* 110   baud rate */
#define BR_300	300L     	/* 300   baud rate */
#define BR_1200	1200L     	/* 1200  baud rate */
#define BR_2400	2400L     	/* 2400  baud rate */
#define BR_4800	4800L     	/* 4800  baud rate */
#define BR_9600	9600L     	/* 9600  baud rate */
#define BR_14400	14400L     	/* 14400 baud rate */
#define BR_19200	19200L     	/* 19200 baud rate */
#define BR_28800	28800L     	/* 28800 baud rate */
#define BR_38400	38400L     	/* 38400 baud rate */
#define BR_57600	57600L     	/* 57600 baud rate */
#define BR_115200	115200L     /* 115200 baud rate */

/***************************** FLAGS *******************************/

#define F_ASIN      0x01
#define F_SIN       0x02
#define F_RX        0x04
#define F_TX        0x08

/***************************** ERRORS ******************************/

#define ERR_NONE              0x00 // No errors
#define ERR_FIRST_STOPBIT     0x01 // Bad first stop bit
#define ERR_HW_BUF_OVERFLOW   0x02 // Hardware buffer overflow
#define ERR_PARITY_CONTROL    0x04 // Parity error

/************************* I/O FUNCTIONS ***************************/

extern int uart_ioctl();
extern int uart_open(unsigned char minordev,
	unsigned long int baud, unsigned char flags);
extern int uart_close(unsigned char minordev);
extern int uart_read(unsigned char minordev);
extern int uart_write(unsigned char minordev, unsigned char byte);

#endif /* _UART_H_ */
