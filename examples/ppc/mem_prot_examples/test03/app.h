#ifndef APP_H
#define APP_H

void discard(EE_UREG x);

EE_INT32 CallMyTaskTrustedService(EE_INT32 arg);
EE_INT32 CallMyIsrTrustedService(EE_INT32 arg);

#define CallMyQuickTrustedService(x) ((EE_INT32)EE_SysCall1((EE_UREG)(x), \
	EE_ID_TRUSTED_MyQuickTrustedService))

#endif /* APP_H */
