/*
 * include/m128/processor.h: 
 *    This is file includes support AVR ATMega128 processor
 *
 * Copyright (C) 2006 Ivan Efremov
 * email: itivan@rambler.ru
 */

#ifndef _AVR_PROCESSOR_H_
#define _AVR_PROCESSOR_H_

/* Defines CPU frequency */

#ifndef F_CPU
#define F_CPU     16000000L   /* 16.00 MHz processor */
//#define F_CPU      7372800L   /* 7.37MHz processor   */
#endif

#include <avr/io.h>        /* IO device */
#include <avr/interrupt.h> /* Global manipulation of the interrupt flag */
#include <stdint.h>        /* ISO/IEC 9899:1999 7.18 Integer types */

#define TIMER_TICK	    1                   /* Timer tick in milliseconds */
#define TIMER_COUNTER   (0x10000-((F_CPU/(1000/TIMER_TICK))/1024))
#define BOTTOM_STACK    ((uint16_t)RAMEND)  /* Address stack */
#define BR_DEFAULT      9600                /* UART baud rate default */
#define BR_DIV          ((uint16_t)((F_CPU+(BR_DEFAULT*16L))/(baud*16L)-1))

struct processor {
	unsigned char sreg;         // +0
	unsigned char r0;           // +1
	unsigned char r1;           // +2
	unsigned char r2;           // +3
	unsigned char r3;           // +4
	unsigned char r4;           // +5
  	unsigned char r5;           // +6
	unsigned char r6;           // +7
	unsigned char r7;           // +8
	unsigned char r8;           // +9
	unsigned char r9;           // +10
	unsigned char r10;          // +11
	unsigned char r11;          // +12
	unsigned char r12;          // +13
	unsigned char r13;          // +14
	unsigned char r14;          // +15
	unsigned char r15;          // +16
	unsigned char r16;          // +17
	unsigned char r17;          // +18
	unsigned char r18;          // +19
	unsigned char r19;          // +20
	unsigned char r20;          // +21
  	unsigned char r21;          // +22
	unsigned char r22;          // +23
	unsigned char r23;          // +24
	unsigned char r24;          // +25
	unsigned char r25;          // +26
	unsigned char r26;          // +27
	unsigned char r27;          // +28
	unsigned char r28;          // +29
	unsigned char r29;          // +30
	unsigned char r30;          // +31
	unsigned char r31;          // +32
	unsigned int pc;            // PCL = +33, PCH = +34
	unsigned int sp;            // SPL = +35, SPH = +36
};

#define cpu_int_disable() { \
	__asm__ __volatile__("cli"::); \
}

#define cpu_int_enable() { \
	__asm__ __volatile__("sei"::); \
}

#define cpu_hlt() { \
	for(;;); \
}

#define timer_init() { \
	TCCR1A = 0; \
	TCCR1B = 5; \
	TCNT1 = TIMER_COUNTER; \
	TIMSK = 1 << TOIE1; \
	TIFR = 0; \
}

#define set_timer_counter() { \
	TCNT1 = TIMER_COUNTER; \
}

#define SAVE_CONTEXT() \
	asm volatile("push		r31 \n\t" \
				 "push		r30 \n\t" \
				 "push		r29 \n\t" \
				 "push		r28 \n\t" \
				 "push		r27 \n\t" \
				 "push		r26 \n\t" \
				 "push		r25 \n\t" \
				 "push		r24 \n\t" \
				 "push		r23 \n\t" \
				 "push		r22 \n\t" \
				 "push		r21 \n\t" \
				 "push		r20 \n\t" \
				 "push		r19 \n\t" \
				 "push		r18 \n\t" \
				 "push		r17 \n\t" \
				 "push		r16 \n\t" \
				 "push		r15 \n\t" \
				 "push		r14 \n\t" \
				 "push		r13 \n\t" \
				 "push		r12 \n\t" \
				 "push		r11 \n\t" \
				 "push		r10 \n\t" \
				 "push		r9  \n\t" \
				 "push		r8  \n\t" \
				 "push		r7  \n\t" \
				 "push		r6  \n\t" \
				 "push		r5  \n\t" \
				 "push		r4  \n\t" \
				 "push		r3  \n\t" \
				 "push		r2  \n\t" \
				 "push		r1  \n\t" \
				 "push		r0  \n\t" \
				 "in		r16, __SREG__ \n\t" \
				 "push		r16 \n\t" \
				 "\n\t" \
				 "in		r28, __SP_L__ \n\t" \
				 "in		r29, __SP_H__ \n\t" \
				 "adiw		r28, 1 \n\t" \
				 "ldi		r20, 33 \n\t" \
				 "ldi		r21, 0x00 \n\t" \
				 "mov		r22, r28 \n\t" \
				 "mov		r23, r29 \n\t" \
 				 "lds		r24, current \n\t" \
				 "lds		r25, current+1 \n\t" \
				 "call		memcpy  \n\t" \
				 "\n\t" \
 				 "in		r28, __SP_L__ \n\t" \
				 "in		r29, __SP_H__ \n\t" \
				 "lds		r30, current \n\t" \
				 "lds		r31, current+1 \n\t" \
				 "ldd		r24, Y+34 \n\t" \
				 "ldd		r25, Y+35 \n\t" \
				 "adiw		r28, 33 \n\t" \
				 "std		Z+33, r25 \n\t" \
				 "std		Z+34, r24 \n\t" \
				 "std		Z+35, r28 \n\t" \
				 "std		Z+36, r29 \n\t" \
 				 "out		__SP_L__, r28 \n\t" \
				 "out		__SP_H__, r29"::)

#define RESTORE_CONTEXT() \
	asm volatile("lds		r30, current \n\t" \
				 "lds		r31, current+1 \n\t" \
				 "ldd		r26, Z+33 \n\t" \
				 "ldd		r27, Z+34 \n\t" \
				 "ldd		r28, Z+35 \n\t" \
				 "ldd		r29, Z+36 \n\t" \
				 "out		__SP_L__, r28 \n\t" \
				 "out		__SP_H__, r29 \n\t" \
				 "std		Y+1, r27 \n\t" \
				 "std		Y+2, r26 \n\t" \
				 "ldd		r16, Z+0 \n\t" \
				 "out		__SREG__, r16 \n\t" \
				 "ldd		r0, Z+1 \n\t" \
				 "ldd		r1, Z+2 \n\t" \
				 "ldd		r2, Z+3 \n\t" \
				 "ldd		r3, Z+4 \n\t" \
				 "ldd		r4, Z+5 \n\t" \
				 "ldd		r5, Z+6 \n\t" \
				 "ldd		r6, Z+7 \n\t" \
				 "ldd		r7, Z+8 \n\t" \
				 "ldd		r8, Z+9 \n\t" \
				 "ldd		r9, Z+10 \n\t" \
				 "ldd		r10, Z+11 \n\t" \
				 "ldd		r11, Z+12 \n\t" \
				 "ldd		r12, Z+13 \n\t" \
				 "ldd		r13, Z+14 \n\t" \
				 "ldd		r14, Z+15 \n\t" \
				 "ldd		r15, Z+16 \n\t" \
				 "ldd		r16, Z+17 \n\t" \
				 "ldd		r17, Z+18 \n\t" \
				 "ldd		r18, Z+19 \n\t" \
				 "ldd		r19, Z+20 \n\t" \
				 "ldd		r20, Z+21 \n\t" \
				 "ldd		r21, Z+22 \n\t" \
				 "ldd		r22, Z+23 \n\t" \
				 "ldd		r23, Z+24 \n\t" \
				 "ldd		r24, Z+25 \n\t" \
				 "ldd		r25, Z+26 \n\t" \
				 "ldd		r26, Z+27 \n\t" \
				 "ldd		r27, Z+28 \n\t" \
				 "ldd		r28, Z+29 \n\t" \
				 "ldd		r29, Z+30 \n\t" \
				 "ldd		r30, Z+31 \n\t" \
				 "ldd		r31, Z+32 \n\t" \
				 "reti"::)

#define cpu_init() { \
	cpu_int_disable(); \
	XDIV  = 0x00; \
	XMCRA = 0x00; \
	PORTA = 0xFF; \
	DDRA  = 0x00; \
	PORTB = 0xFF; \
	DDRB  = 0x00; \
	PORTC = 0xFF; \
	DDRC  = 0x00; \
	PORTD = 0xFF; \
	DDRD  = 0x00; \
	PORTE = 0xFF; \
	DDRE  = 0x00; \
	PORTF = 0xFF; \
	DDRF  = 0x00; \
	PORTG = 0x1F; \
	DDRG  = 0x00; \
	MCUCR = 0x00; \
	EICRA = 0x00; \
	EICRB = 0x00; \
	EIMSK = 0x00; \
	TIMSK = 0x00; \
	ETIMSK = 0x00; \
	UBRR0L = (uint8_t)(BR_DIV & 0x00FF); \
	UBRR0H = (uint8_t)(BR_DIV >> 8); \
	UCSR0B = (1<<RXEN)|(1<<TXEN); \
}

#endif /* _AVR_PROCESSOR_H_ */
