#ifndef SHARED_H
#define SHARED_H

#include <ee.h>

enum assertions {
	asr_init = 1,
	asr_startz0,
	asr_startz6,
	asr_taskz0main,
	asr_taskz0bkg,
	asr_setevent1,
	asr_gotevent1,
	asr_ackevent1,
	asr_setevent2,
	asr_gotevent2,
	asr_ackevent2,
	asr_setevent2b,
	asr_gotevent2b,
	asr_ackevent2b,
	asr_dim
};

/* Used for acknowledging events */
extern volatile int EE_SHARED_UDATA send_event;

/* Final result */
extern int EE_SHARED_UDATA result;

#endif /* SHARED_H */
