/*
 * arch/arch.c: This is module for ATmega128 only !
 *
 * Copyright (C) 2006 Ivan Efremov
 * email: itivan@rambler.ru
 */

#include <m128/processor.h>

extern void do_timer(void);

int8_t putk(char ch)
{
	if(ch!=0) {
		if(ch=='\n') putk('\r');
		while(!(UCSR0A & (1<<UDRE0))); // Waiting...
		UDR0 = ch;
		return 1;
	}
	return 0;
}
/*
 * ISR, Timer interrupt
 */
ISR(TIMER1_OVF_vect) __attribute__ ((naked));
ISR(TIMER1_OVF_vect)
{
	/* Save current task */
	SAVE_CONTEXT();
	/* Set timer counter */
	set_timer_counter();
	/* Call kernel timer */
	do_timer();
	/* Restore task */
	RESTORE_CONTEXT();
}


