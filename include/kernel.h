/*
 * include/kernel.h: This is the master header for the kernel.
 *     It includes other files and defines api functions.
 *
 * Copyright (C) 2006 Ivan Efremov
 * email: itivan@rambler.ru
 */

#ifndef _KERNEL_H_
#define _KERNEL_H_

/* Define architecture */

#ifdef atmega128
	#include <m128/processor.h> /* ATMEGA128 CPU core */
#elif defined at90can128
	#include <c128/processor.h> /* AT90CAN128 CPU core */
#elif
	#error "Architecture not defined"
#endif

#include "../etc/system.conf"

/*
#if DRIVERS
	#include <driver.h>
#endif
*/

#include <stdint.h>

/*******************************************************************************
 *
 *                                 TCB
 *
 *******************************************************************************/

#if(NR_TASKS > 32)
	#error "NR_TASKS:Number tasks can't be more 32"
#endif

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef ERR
#define ERR (-1)  /* General error flag */
#endif

#ifndef OK
#define OK 0      /* General OK flag */
#endif

#define TASK(name) void name(void) /* Entry pointer to task */

#define FIRST_TASK      task[0]              /* IDLE task */
#define LAST_TASK       task[NR_TASKS-1]     /* Last task */

#define TASK_RUNNING    0    /* Task is executed */
#define TASK_STOPPED    1    /* Task is stopped */
#define TASK_ZOMBIE     2    /* Task is zombie */

typedef struct task_TCB {  /* Structure of the Task Control Block */
	struct processor regs; /* Process registers, don't touch */
	uint8_t id;            /* Task ID */
	uint8_t state;         /* Current state task */
	uint8_t counter;       /* Counter ticks */
	uint8_t priority;      /* Priority, must be > 0 and <= 255 */
} TCB;

/*******************************************************************************
 *
 *                                KERNEL API
 *
 *******************************************************************************/

#ifdef __KERNEL__

extern volatile TCB *current;

extern int8_t putk(char ch); /* Put kernel */
extern int8_t printk(const char *str, ...); /* Print kernel */
extern void panic(const char *str);  /* Kernel panic messages */

#endif __KERNEL__

extern TASK(idle);
extern int8_t setup(void);
extern int8_t create_task(TCB* pTCB, void (*fntask)(void),
	uint8_t priority, uint16_t stack);

#endif /* _KERNEL_H_ */
