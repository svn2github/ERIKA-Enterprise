#include "shared.h"

/* Hack to avoid clashing with the declaration in ee_assert.h */
typedef EE_INT8 EE_TYPEASSERTVALUE;

EE_TYPEASSERTVALUE EE_SHARED_UDATA EE_assertions[asr_dim];

volatile int EE_SHARED_UDATA send_event;

int EE_SHARED_UDATA result;
