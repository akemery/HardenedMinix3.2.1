#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hardening.h"
int main(int argc, char *argv[]){
   if(argc<2)
     printf("USAGE %s type pid name\n", argv[0]);
   int type = atoi(argv[1]);
   switch(type){
       case HTASK_EN_HARDENING_ALL_F:
          hardening(HTASK_EN_HARDENING_ALL_F, -10, NULL, 0);
          break;
     
     case HTASK_DIS_HARDENING_ALL_F:
          hardening(HTASK_DIS_HARDENING_ALL_F, -10, NULL, 0);
          break;
     case HTASK_EN_HARDENING_PNAME:
          hardening(HTASK_EN_HARDENING_PNAME, -10, argv[2], strlen(argv[2]));
          break;
   }
   return(0);
}
