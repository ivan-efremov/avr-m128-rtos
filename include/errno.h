/*
 * errno.h
 */

#ifndef _ERRNO_H_
#define _ERRNO_H_

extern int errno; /* Place where the error numbers go */

#ifndef ERR
#define ERR (-1)  /* General error flag */
#endif

#ifndef OK
#define OK 0      /* General OK flag */
#endif

/* Here are the numerical values of the error numbers. */

#define _NERROR       90     /* Number of errors */

#define EPERM         (-1)   /* Operation not permitted */
#define ENOENT        (-2)   /* No such file or directory */
#define ESRCH         (-3)   /* No such process */
#define EINTR         (-4)   /* Interrupted function call */
#define EIO           (-5)   /* Input/output error */
#define ENXIO         (-6)   /* No such device or address */
#define E2BIG         (-7)   /* Arg list too long */
#define ENOEXEC       (-8)   /* Exec format error */
#define EBADF         (-9)   /* Bad file descriptor */
#define ECHILD        (-10)  /* No child process */
#define EAGAIN        (-11)  /* Resource temporarily unavailable */
#define ENOMEM        (-12)  /* Not enough space */
#define EACCES        (-13)  /* Permission denied */
#define EFAULT        (-14)  /* Bad address */
#define ENOTBLK       (-15)  /* Extension: not a block special file */
#define EBUSY         (-16)  /* Resource busy */
#define EEXIST        (-17)  /* File exists */
#define EXDEV         (-18)  /* Improper link */
#define ENODEV        (-19)  /* No such device */
#define ENOTDIR       (-20)  /* Not a directory */
#define EISDIR        (-21)  /* Is a directory */
#define EINVAL        (-22)  /* Invalid argument */
#define ENFILE        (-23)  /* Too many open files in system */
#define EMFILE        (-24)  /* Too many open files */
#define ENOTTY        (-25)  /* Inappropriate I/O control operation */
#define ETXTBSY       (-26)  /* No longer used */
#define EFBIG         (-27)  /* File too large */
#define ENOSPC        (-28)  /* No space left on device */
#define ESPIPE        (-29)  /* Invalid seek */
#define EROFS         (-30)  /* Read-only file system */
#define EMLINK        (-31)  /* too many links */
#define EPIPE         (-32)  /* broken pipe */
#define EDOM          (-33)  /* Domain error    	(from ANSI C std) */
#define ERANGE        (-34)  /* Result too large	(from ANSI C std) */
#define EDEADLK       (-35)  /* Resource deadlock avoided */
#define ENAMETOOLONG  (-36)  /* File name too long */
#define ENOLCK        (-37)  /* No locks available */
#define ENOSYS        (-38)  /* Function not implemented */
#define ENOTEMPTY     (-39)  /* Directory not empty */
#define EGENERIC      (-40)  /* Generic error */

/* The following errors relate to networking. */

#define EPACKSIZE     (-50)  /* invalid packet size for some protocol */
#define EOUTOFBUFS    (-51)  /* not enough buffers left */
#define EBADIOCTL     (-52)  /* illegal ioctl for device */
#define EBADMODE      (-53)  /* badmode in ioctl */
#define EWOULDBLOCK   (-54)
#define EBADDEST      (-55)  /* not a valid destination address */
#define EDSTNOTRCH    (-56)  /* destination not reachable */
#define EISCONN	    (-57)  /* all ready connected */
#define EADDRINUSE    (-58)  /* address in use */
#define ECONNREFUSED  (-59)  /* connection refused */
#define ECONNRESET    (-60)  /* connection reset */
#define ETIMEDOUT     (-61)  /* connection timed out */
#define EURG	    (-62)  /* urgent data present */
#define ENOURG	    (-63)  /* no urgent data present */
#define ENOTCONN      (-64)  /* no connection (yet or anymore) */
#define ESHUTDOWN     (-65)  /* a write call to a shutdown connection */
#define ENOCONN       (-66)  /* no such connection */

/* The following are not POSIX errors, but they can still happen. */

#define ELOCKED       (-70)  /* can't send message */
#define EBADCALL      (-71)  /* error on send/receive */

/* The following error codes are generated by the kernel itself. */

#define E_BAD_DEST    (-80)  /* destination address illegal */
#define E_BAD_SRC     (-81)  /* source address illegal */
#define E_TRY_AGAIN   (-82)  /* can't send - tables full */
#define E_OVERRUN     (-83)  /* interrupt for task that is not waiting */
#define E_BAD_BUF     (-84)  /* message buf outside caller's addr space */
#define E_TASK        (-85)  /* can't send to task */
#define E_NO_MESSAGE  (-86)  /* RECEIVE failed: no message present */
#define E_NO_PERM     (-87)  /* ordinary users can't send to tasks */
#define E_BAD_FCN     (-88)  /* only valid fcns are SEND, RECEIVE, BOTH */
#define E_BAD_ADDR    (-89)  /* bad address given to utility routine */
#define E_BAD_PROC    (-90)  /* bad proc number given to utility */

#endif /* _ERRNO_H */