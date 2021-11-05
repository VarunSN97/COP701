#include "myThread.h"
#include <stdio.h>
#include <stdlib.h>
lock *l;
int counter;
static void *demoprinter(void *args)
{
set_lock(l);
unsigned long i=0;
counter +=1;
printf("counter %d \n",counter);
for(i=0;i<0xFFFFFFFF;i++);
printf("running %d \n",counter);
release_lock(l);
}
int main()
 {
 l=(lock*)malloc(sizeof(lock));
 int a=1;
 int b=2;
 int c =3,d=4;
 thread *t1,*t2,*t3,*t4;
 t1=(thread *)malloc(sizeof(thread));
 t2=(thread *)malloc(sizeof(thread));
 t3=(thread *)malloc(sizeof(thread));
 t4=(thread *)malloc(sizeof(thread));
 
 int al= mythread_create(t1,NULL,demoprinter,(void *)a);
 
 int bl= mythread_create(t2,NULL,demoprinter,(void *)b);
  
 
 while(1);
 return 0;
 }
 
