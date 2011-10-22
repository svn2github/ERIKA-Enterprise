#ifndef APP_H
#define APP_H

extern const int EE_APPLICATION_CDATA(App1) cvar1;
extern volatile int EE_APPLICATION_IDATA(App1) counter1;
extern int EE_APPLICATION_UDATA(App2) var2;
extern EE_UREG EE_APPLICATION_UDATA(TrustedApp) gvar;

void init_app1_timer(void);
void init_app2_timer(void);
void init_trusted_timer(void);


#endif /* APP_H */
