#include <lib.h>
#include <unistd.h>

#define MAXLEN  20

int hardening(int type, pid_t pid, 
  char *name, int namelen){
  message m;
  switch(type){
     case HTASK_EN_HARDENING_ALL_F:
          m.HTASK_TYPE = HTASK_EN_HARDENING_ALL_F;
          m.HTASK_P_ENDPT      = pid;
          break;
     
     case HTASK_DIS_HARDENING_ALL_F:
          m.HTASK_TYPE = HTASK_DIS_HARDENING_ALL_F;
          m.HTASK_P_ENDPT      = pid;
          break;
     case HTASK_EN_HARDENING_PID:
          m.HTASK_TYPE = HTASK_EN_HARDENING_PID;
          m.HTASK_P_ENDPT      = pid;
          break;
     case HTASK_DIS_HARDENING_PID:
          m.HTASK_TYPE = HTASK_DIS_HARDENING_PID;
          m.HTASK_P_ENDPT      = pid;
          break;
     case HTASK_DISPLAY_HARDENIG:
          m.HTASK_TYPE = HTASK_DISPLAY_HARDENIG;
          m.HTASK_P_ENDPT   = pid; 
          break; 
     case HTASK_EN_INJECT:
          m.HTASK_TYPE = HTASK_EN_INJECT;
          m.HTASK_P_ENDPT      = pid;
          break;
     case HTASK_DIS_INJECT:
          m.HTASK_TYPE = HTASK_DIS_INJECT;
          m.HTASK_P_ENDPT      = pid;
          break;
     default:
          return(-1);
  }
  return(_syscall(PM_PROC_NR,PM_HARDENING,&m));
}
