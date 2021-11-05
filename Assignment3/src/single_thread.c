#include "myThread.h"
#include <stdio.h>
#include <stdlib.h>
 void *demoPrinter(void *args)
  {
  int a=((int)args);
  printf("Running ");
  }
  int main()
   {
   thread *t1;
   
   t1=(thread*)malloc(sizeof(thread));
   
   mythread_create(t1,NULL,demoPrinter,NULL);
   
   while(1);
   }

