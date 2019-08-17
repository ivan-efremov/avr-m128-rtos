/*
 * buffer.c:This file has realizes work static FIFO buffer.
 *
 * Copyright (C) 2006 Efremov Ivan
 * email: itivan@rambler.ru
 */

#include <buffer.h>

/*
 * Initialization static FIFO buffer
 */
void buffer_init(struct buffer* pfifobuf,
	void* pbuf,
	unsigned int size)
{
   	pfifobuf->buf = (unsigned char*)pbuf;
	pfifobuf->size = size;
	buffer_clean(pfifobuf);
}
/*
 * Push byte in end buffer
 */
char buffer_push(struct buffer* pfifobuf, unsigned char byte)
{
	if(pfifobuf->length < pfifobuf->size)
	{
		pfifobuf->buf[(pfifobuf->index+
			pfifobuf->length)%pfifobuf->size] = byte;
		pfifobuf->length++;
		return 0; // Ok, data in buffer
	}
	return -1; // Buffer is full
}
/*
 * Pop byte from begin buffer
 */
unsigned char buffer_pop(struct buffer* pfifobuf)
{
#ifdef __DEBUG__
	unsigned char byte = '?';
#else
	register unsigned char byte = 0;
#endif
	if(pfifobuf->length > 0)
	{
		byte = pfifobuf->buf[pfifobuf->index];
		pfifobuf->length--;
		pfifobuf->index++;
		if(pfifobuf->index >= pfifobuf->size)
			pfifobuf->index %= pfifobuf->size;
	}
	return byte;
}

#ifdef __DEBUG__
#include <stdio.h>
/*
 * Print the buffer
 */
void buffer_print(struct buffer* pfifobuf)
{
	unsigned int i;
	for(i=0;i<pfifobuf->size;i++)
		printf("buffer[%i] = 0x%X\n", i, *(pfifobuf->buf+i));
}
#endif /* __DEBUG__ */
