/* test 98: malloc, free */

/* created by Emery Assogba */
/* assogba.emery@gmail.com         26-Juin-2019  12:45:04 */

/* Copyright (C) 2019 by Emery Assogba. All rights reserved. */
/* Used by permission. */

#include <stdlib.h>
#include <string.h>

#define BUFFSIZE    4096
#define ITERATIONS    10

#define MAX_ERROR 2
#include "common.c"

int main(int argc, char **argv);
void quit(void);

int main(int argc, char **argv)
{
  start(98);
  char *buff;
  void *ptr;
  int i;
  
  if(argc != 3){
    printf ("USAGE test101 <#iterations> <#buff_size>\n");
    quit();
    return(0);
  }
  int iter = atoi(argv[1]);
  int buff_size = atoi(argv[2]);
  buff = (char*)malloc(buff_size*sizeof(char)*iter);
  if(!buff){
     printf("No Memory\n"); 
     quit();
  }
  ptr = memset(buff, 'a', buff_size*iter);
  for(i = 0; i < buff_size*iter; i++)
     if(*(buff+i)!='a'){
        printf("Memory error\n");
        quit();
     }
  free(buff);
 
  //}
  quit();
  return(0);
}
