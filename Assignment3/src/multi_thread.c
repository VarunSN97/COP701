#include "myThread.h"
#include <stdio.h>
#include <stdlib.h>
 void *demoPrinter(void *args)
  {
  int a=((int)args);
  printf("Running %d \n",a);
  }
  int main()
   {
   thread *t1,*t2,*t3;
   int a1=1,a2=2,a3=3;
   t1=(thread*)malloc(sizeof(thread));
   t2=(thread*)malloc(sizeof(thread));
   t3=(thread*)malloc(sizeof(thread));
   mythread_create(t1,NULL,demoPrinter,(void *)a1);
   mythread_create(t2,NULL,demoPrinter,(void *)a2);
   mythread_create(t3,NULL,demoPrinter,(void *)a3);
   while(1);
   }

