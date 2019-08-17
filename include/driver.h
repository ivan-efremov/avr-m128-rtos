/*
 * driver.h:
 *
 * Copyright (C) 2006 Ivan Efremov
 */

#ifndef _DRIVER_H_
#define _DRIVER_H_

/* Gets major, minor number */

#define MAJOR(dev)	(((unsigned char)(dev))>>4)
#define MINOR(dev)	((unsigned char)(dev)&0x0F)

/* Operations on device */

#define DEV_IOCTL    0        /* Control device */
#define DEV_OPEN     1        /* Open device */
#define DEV_CLOSE    2        /* Close device */
#define DEV_READ     3        /* Read device */
#define DEV_WRITE    4        /* Write device */

/* Info about and entry points into the device dependent code */

struct driver {
	int (*dr_ioctl)();    /* DEV_IOCTL message handler */
	int (*dr_open )();    /* DEV_OPEN  message handler */
	int (*dr_close)();    /* DEV_CLOSE message handler */
	int (*dr_read )();    /* DEV_READ  message handler */
	int (*dr_write)();    /* DEV_WRITE message handler */
};

extern struct driver drvmap[NR_DEVICES];
extern struct driver* get_driver(unsigned char number);
extern int do_nop();

/* Major-Minor device list */

#define DEV_UART0    0x00     /* USART0 */
#define DEV_UART1    0x01     /* USART1 */
#define DEV_ICF100S  0x10     /* ICF100S */

/*******************************************************************************
 *
 *                                   UART
 *
 *******************************************************************************/

#if DRV_UART

#include <uart.h>

#endif /* DRV_UART */

/*******************************************************************************
 *
 *                                  ICF100S
 *
 *******************************************************************************/

#if DRV_ICF100S

#include <icf100s.h>

#endif /* DRV_ICF100S */

#endif
