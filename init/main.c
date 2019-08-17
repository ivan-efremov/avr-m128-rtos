/*
 * init/main.c: Startup code
 *
 * Copyright (C) 2006 Ivan Efremov
 * email: itivan@rambler.ru
 */

#include <kernel.h>

/*******************************************************************
 *                     MY TASKS DECLARE                            *
 *******************************************************************/

static TCB tcb1, tcb2;

extern TASK(main1); /* Task 1 */
extern TASK(main2); /* Task 2 */

/*******************************************************************
 *                      ENTRY POINTER                              *
 *******************************************************************/

void main(void)
{
	/* 1. Initialization kernel */

	if(setup() == ERR)
		panic("kernel can't starting");

	/* 3. Initialization all tasks */

	if(create_task(&tcb1, main1, 10, 128) == ERR)
		panic("Can't create task 1");
	if(create_task(&tcb2, main2, 10, 128) == ERR)
		panic("Can't create task 2");

	/* 4. Starting idle task */

	idle();
}
