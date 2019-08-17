/*
 * tasks/tasks.c: All my tasks.
 *
 * Copyright (C) 2006 Ivan Efremov
 * email: itivan@rambler.ru
 */

#include <kernel.h>

/*********************************************************************
 *                          TASK 1
 *********************************************************************/

TASK(main1)
{
	/*
	 * To do, initialization of task
	 */
	unsigned int a = 0;
	DDRD = 0xFF;
	for(;;)
	{
		/*
		 * Task body
		 */
		PORTD = 0x80;
		a++;
	}
}

/*********************************************************************
 *                          TASK 2
 *********************************************************************/

TASK(main2)
{
	unsigned int a = 0;
	DDRD = 0xFF;
	for(;;)
	{
		a++;
		PORTD = 0x40;
	}
}
