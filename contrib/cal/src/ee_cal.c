#include <ee.h>
#include "ee_cal.h"

int main_cal(int argc, char *argv[]);

TASK(calTask)
{
  char *argv[] = { "",
#ifdef CAL_STATISTICS
  "--statistics"
#else
  ""
#endif
  };
  int argc = sizeof(argv)/sizeof(argv[0]);
  main_cal(argc, argv);
}

void EE_cal_init() {}

void EE_cal_start() {
  ActivateTask(calTask);
}
