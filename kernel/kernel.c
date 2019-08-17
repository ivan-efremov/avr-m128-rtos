/*
 * kernel/kernel.c: Initializes the system and defines api functions.
 *
 * Copyright (C) 2006 Ivan Efremov
 * email: itivan@rambler.ru
 */

#define __KERNEL__

#include <kernel.h>
#include <stdio.h>

/*******************************************************************************
 *
 *                                   DATA
 *
 *******************************************************************************/

static TCB Idle = { /* Idle task */
	{},             /* CPU regs      */
	0,              /* Task ID       */
	TASK_RUNNING,   /* State RUNNING */
	1,              /* Tick counter  */
	1,              /* Task priority */
};

static TCB* task[NR_TASKS] = { /* Table tasks */
	&Idle                      /* Idle task */
};

volatile TCB *current = &Idle;             /* Current running task */
//volatile uint32_t millisec = (uint32_t)0L; /* Timer ticks */
volatile uint32_t jiffies = (uint32_t)0L;  /* Timer ticks */
static uint16_t start_stack = BOTTOM_STACK - KERNEL_STACK; /* Start stack */
static char buf[PRINTK_BUF];               /* Buffer for printk() */

/*******************************************************************************
 *
 *                                SCHEDULER
 *
 *******************************************************************************/

/*
 * Init. scheduler
 */
#define sched_init() \
{ \
	uint8_t i; \
	for(i=1;i<NR_TASKS;i++) \
		task[i] = NULL; \
}
/*
 * This is the scheduler proper
 */
static void schedule(void)
{
	uint8_t i, next;
	int16_t c;
	TCB** p;
	for(;;) {
		c = -1;
		next = 0;
		i = NR_TASKS;
		p = &task[NR_TASKS];
		while(--i) {
			if(!*--p)
				continue;
			if((*p)->state == TASK_RUNNING && ((int16_t)(*p)->counter) > c)
				c = (int16_t)(*p)->counter, next = i;
		}
		if(c) break;
		for(p=&LAST_TASK;p>&FIRST_TASK;--p)
			if(*p)
				(*p)->counter = ((*p)->counter >> 1) + (int16_t)(*p)->priority;
	}
	current = task[next];
}

/*******************************************************************************
 *
 *                                 KERNEL
 *
 *******************************************************************************/

/*
 * Setup kernel
 */
int8_t setup(void)
{
	cpu_init();    /* Initialization CPU core */
	sched_init();  /* Scheduler Init. */
	return OK;
}
/*
 * Idle task
 */
TASK(idle)
{
	/* Setup timer */
	timer_init();
	cpu_int_enable();
	/* Wait starting scheduler */
	for(;;);
//		printk("%i", sizeof(TCB));
}
/*
 * Create task TCB
 */
int8_t create_task(TCB* pTCB,
				   void (*fntask)(void),
				   uint8_t priority,
				   uint16_t stack)
{
	uint8_t i;
	for(i=1;i<NR_TASKS;i++) {
		if(task[i]==NULL) {
			memset(pTCB, 0, sizeof(TCB));
			pTCB->regs.pc = (uint16_t)fntask;
			pTCB->regs.sp = start_stack;
			pTCB->state = TASK_RUNNING;
			pTCB->counter = pTCB->priority = priority;
			pTCB->id = i;
			start_stack -= stack;
			task[i] = pTCB;
			return OK;
		}
	}
	return ERR;
}
/*
 * Print kernel
 */
int8_t printk(const char *fmt, ...)
{
	int8_t i = 0;
	va_list args;
	va_start(args, fmt);
	(void)vsprintf(buf, fmt, args);
	va_end(args);
	while(buf[i]!='\0' && i < PRINTK_BUF)
		putk(buf[i++]);
	return i;
}
/*
 * Painic kernel
 */
void panic(const char *str)
{
	cpu_int_disable();
	(void)printk("Kernel panic:%s\n", str);
	cpu_hlt();
}
/*
 * Kernel timer
 */
void do_timer(void)
{
	/* Find next task */
	if((--current->counter)==0)
		schedule();
}
