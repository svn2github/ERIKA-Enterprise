#ifndef _INCLUDES_DEBUG_ARM_32_H_
#define _INCLUDES_DEBUG_ARM_32_H_

#define MAX_MSGLEN	1024

extern void HYPERVISOR_console_io(int what, int len, char *msg);

int strln(const char *s)
{
    int i = 0;
    while (s[i] != '\n' && i < MAX_MSGLEN) i++;
    return ++i;
}

#define printk(s)	HYPERVISOR_console_io(CONSOLEIO_write, strln(s), s);

#endif /* _INCLUDES_DEBUG_ARM_32_H_ */
