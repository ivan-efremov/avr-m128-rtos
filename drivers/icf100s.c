/*
 * icf100s.c: Driver for IC-F100S board (ICOM Inc.)
 */

#include <kernel.h>  /* Kernel core */
#include <icf100s.h> /* Board IC-F100S */

#if DRV_UART==0
	#error "Depends on DRV_UART"
#endif

int icf100s_ioctl(message* msg)
{
	
	switch(id)
	{
	case ICF100S_INIT_TX:
		// Configure port F
		DDRF = _BV(PINF1)|_BV(PINF3); // Port F1,F3 config to write
		PORTF = 0x00; // Fx = 00000000
		// Configure port E
		DDRE = _BV(PINE2)|_BV(PINE3)|_BV(PINE5); // Port E2, E3, E5 config to write
		PORTE = 0x64; // Ex = 01100100
		break;
	case ICF100S_INIT_RX:
		PORTE = 0x00;
		DDRE = 0x00;
		break;
	case ICF100S_SWITCH_CHANNEL:
		{
			unsigned char channel[13] = {
				0xFE, 0xFE, 0xEE, 0xEF, 0xE8, 0x26, 0x01, 0x00,
				0x00, 0x00,	0x30,   ch, 0xFD
			};
			unsigned char i, j;
			int fd;
			if((fd=open("uart1", O_WRONLY))==-1)
				fprintf(stderr, "Error:channel_switch() can't open uart1\n");
			for(j=0; j<2; j++)
				for(i=0; i<13; i++)
					if(write(fd, &channel[i], 1)==-1)
						fprintf(stderr, "Error:channel_switch() can't write to uart1\n");
			close(fd);
		}
		break;
	case ICF100S_GET_CHANNEL:
		{
			char msg[24] = {
				0x01, 0x30, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
				0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
				0xEE, 0xEF, 0xE0, 0x26, 0x01, 0x00, 0x00, 0xFD
			};
			int fd, i;
			unsigned char data;
	
			fd = open("uart1", O_RDWR);
			// 1) Step 1
			write(fd, msg, 24);
			for(i=0;i<62;i++)
				read(fd, &data, 1);
			// 2) Step 2
			msg[18] = 0xE2;
			write(fd, msg, 24);
			// 3) Step 3
			for(i=0;i<807;i++)
				read(fd, &data, 1);
			close(fd);
			return ++data;
		}
		break;
	default:
	#if DEBUG
		printk("icf100s_ioctl():bad message\n");
	#endif
		return ERR;
	}
	return OK;
}
