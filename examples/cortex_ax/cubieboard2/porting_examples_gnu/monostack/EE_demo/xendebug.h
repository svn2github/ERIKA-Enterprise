#ifndef _INCLUDES_DEBUG_ARM_32_H_
#define _INCLUDES_DEBUG_ARM_32_H_

#define MAX_MSGLEN	1024
#define STRERR		"EE: console error\n"
#define STRERR_LEN	18

extern void HYPERVISOR_console_io(int what, int len, char *msg);

char *itoa(int i, char *b)
{
	char const digit[] = "0123456789";
	char *p = b;
	int shifter;
	if (i < 0) {
		*p++ = '-';
		i *= -1;
	}
	shifter = i;
	do {
		++p;
		shifter = shifter / 10;
	} while(shifter);
	*p = '\0';
	do {
		*--p = digit[i%10];
		i = i / 10;
	} while(i);
	return b;
}

int strln(char *s)
{
    int i = 0;

    if (s == NULL)
	return -1;
    /* Safety: last character is always a \n */
    s[MAX_MSGLEN-1] = '\n';
    while (s[i] != '\n' && s[i] != '\0' && i < MAX_MSGLEN) i++;
    if (s[i] == '\0')
        s[i] = '\n';
    return ++i;
}

#define printk(s)	HYPERVISOR_console_io(0, strln(s), s)
#define panic_printk()	HYPERVISOR_console_io(0, STRERR_LEN, STRERR)

void print_number(int n)
{
	char buf[20];

	itoa(n, buf);
	printk(buf);
}

#endif /* _INCLUDES_DEBUG_ARM_32_H_ */
