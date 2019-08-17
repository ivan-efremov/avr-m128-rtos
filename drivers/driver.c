/*
 * driver.c: This file contains device driver interface.
 *
 * Copyright (C) 2006 Efremov Ivan
 * email: itivan@rambler.ru
 */

#include <kernel.h>
#include <driver.h>
#include <errno.h>

/*******************************************************************************
 *
 *                               DRIVERS TABLE
 *
 *******************************************************************************/

#if DRIVERS

struct driver drvmap[NR_DEVICES] = {
/*+====================================================================+
  |  DEV_IOCTL  |  DEV_OPEN  |  DEV_CLOSE  |  DEV_READ  |  DEV_WRITE   |
  +====================================================================+*/
#ifdef DRV_UART
  { uart_ioctl  , uart_open  , uart_close  , uart_read  , uart_write   },
#else
  { do_nop      , do_nop     , do_nop      , do_nop     , do_nop       },
#endif
#if DRV_ICF100S
  { icf100s_ioctl, do_nop    , do_nop      , do_nop     , do_nop       },
#else
  { do_nop      , do_nop     , do_nop      , do_nop     , do_nop       },
#endif
/*+====================================================================+*/
};

/*
 * Getting driver struct
 */
struct driver* get_driver(unsigned char number)
{
	return &drvmap[MAJOR(number)];
}

/*
 * Do nothing
 */
int do_nop()
{
	return ERR;
}

#endif /* DRIVERS */
