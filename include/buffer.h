/*
 * buffer.h:This file has realizes work static FIFO buffer.
 *
 * Copyright (C) 2006 Efremov Ivan
 * email: itivan@rambler.ru
 */

#ifndef _BUFFER_FIFO_H_
#define _BUFFER_FIFO_H_

/************************** FIFO BUFFER ****************************/

struct buffer {
	unsigned char *buf;    /* Pointer to fifo buffer */
	unsigned int length;   /* Length of the data */
	unsigned int index;    /* Index into the buffer */
	unsigned int size;     /* Size of buffer in bytes */
};

/*
 * Clean buffer
 */

#define buffer_clean(pfifobuf) \
{ \
	(pfifobuf)->index = (pfifobuf)->length = 0; \
}

/*
 * Length buffer
 */

#define buffer_length(pfifobuf)  ((pfifobuf)->length)

/*
 * Buffer is empty ?
 */

#define buffer_empty(pfifobuf)   ((unsigned char)((pfifobuf)->length == 0))

/*
 * Buffer is full ?
 */
#define buffer_full(pfifobuf)    ((unsigned char)((pfifobuf)->length==(pfifobuf)->size))

/*
 * Initialization static FIFO buffer
 */

extern void buffer_init(struct buffer* pfifobuf,
	void* pbuf, unsigned int size);

/*
 * Push byte in end buffer
 */

extern char buffer_push(struct buffer* pfifobuf,
	unsigned char byte);

/*
 * Pop byte from begin buffer
 */

extern unsigned char buffer_pop(struct buffer* pfifobuf);

#ifdef __DEBUG__
extern void buffer_print(struct buffer* pfifobuf);
#endif /* __DEBUG__ */

#endif /* _BUFFER_FIFO_H_ */
