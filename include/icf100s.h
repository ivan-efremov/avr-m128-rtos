/*
 * include/icf100s.h :  Driver for IC-F100S board
 *
 * Copyright (C) 2006 Ivan Efremov
 */

#ifndef _BOARD_IC_F100S_H
#define _BOARD_IC_F100S_H

#define ICF100S_INIT_TX        0
#define ICF100S_INIT_RX        1
#define ICF100S_SWITCH_CHANNEL 2
#define ICF100S_GET_CHANNEL    3

extern int icf100s_ioctl(message* msg);

#endif /* _BOARD_IC_F100S_H */
