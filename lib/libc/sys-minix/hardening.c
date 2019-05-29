#include <lib.h>
#include <unistd.h>

#define MAXLEN  20

int hardening(int type, pid_t pid, char *name, int namelen){
  message m;
  switch(type){
     case HTASK_EN_HARDENING_ALL_F:
          m.HTASK_TYPE = HTASK_EN_HARDENING_ALL_F;
          m.HTASK_PNAME = NULL;
          m.HTASK_P_ENDPT      = pid;
          break;
     
     case HTASK_DIS_HARDENING_ALL_F:
          m.HTASK_TYPE = HTASK_DIS_HARDENING_ALL_F;
          m.HTASK_PNAME = NULL;
          m.HTASK_P_ENDPT      = pid;
          break;
     case HTASK_EN_HARDENING_PID:
          m.HTASK_TYPE = HTASK_EN_HARDENING_PID;
          break;
     case HTASK_EN_HARDENING_PNAME:
          m.HTASK_TYPE = HTASK_EN_HARDENING_PNAME;
          int len = (namelen > MAXLEN) ? MAXLEN : namelen;
          m.HTASK_PNAME = (vir_bytes)name;
          m.HTASK_PNAME_LEN = len;
          m.HTASK_P_ENDPT      = pid;
          break;
     case HTASK_DIS_HARDENING_PNAME:
          break;
     default:
          return(-1);
  }
  return(_syscall(PM_PROC_NR,PM_HARDENING,&m));
}

