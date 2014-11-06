#ifndef _INCLUDES_DEBUG_ARM_32_H_
#define _INCLUDES_DEBUG_ARM_32_H_

#define MAX_MSGLEN	1024
#define STRERR		"EE: console error\n"
#define STRERR_LEN	18

extern void HYPERVISOR_console_io(int what, int len, char *msg);

int strln(char *s)
{
    int i = 0;

    if (s == NULL)
	return -1;
    /* Safety: last character is always a \n */
    s[MAX_MSGLEN-1] = '\n';
    while (s[i] != '\n' && i < MAX_MSGLEN) i++;
    return ++i;
}

#define printk(s)	HYPERVISOR_console_io(CONSOLEIO_write, strln(s), s)
#define panic_printk()	HYPERVISOR_console_io(CONSOLEIO_write, STRERR_LEN, STRERR)

#endif /* _INCLUDES_DEBUG_ARM_32_H_ */
