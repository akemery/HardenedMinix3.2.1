#include <lib.h>
#include <unistd.h>

int h_read_tsc(u32_t *hi, u32_t *lo){
  message m;
  //m.HTASK_TYPE = HTASK_READTSC;
  m.HTASK_PNAME = NULL;
  m.HTASK_P_ENDPT      = 0;
  _syscall(PM_PROC_NR,PM_HARDENING,&m);
  //*hi = m.HTASK_HI;
  //*lo = m.HTASK_LO;
  return(0);
}

