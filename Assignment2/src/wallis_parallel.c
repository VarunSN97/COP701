#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <semaphore.h>
#include "../include/calculate.c"

#define num_threads 80

int n;
double result=1;
sem_t sem;
void *parallel_calculation(void *);

int main(int argc, char** argv)
 {
 pthread_t *threads;
 n=atoi(argv[1]);
 sem_init(&sem,0,1);
 double time;
 threads=(pthread_t*)malloc(num_threads*sizeof(pthread_t));
 time =calculateTime();
 for(int i=0;i<num_threads;i++)
  pthread_create(&threads[i],NULL,parallel_calculation,(void *)i);
  
  for(int i=0;i<num_threads;i++)
   pthread_join(threads[i],NULL);
   
   time=calculateTime()-time;
   result=result*2;
   printf("%lf %lf\n",result,time);
   }
   
   void *parallel_calculation(void *args)
    {
    int a= ((int)args);
    int factor = n/num_threads;
    int start = factor * a;
    int end = start + factor;
    double product=1.0;
    for(double i=start;i<end;i++)
     product=product*((2*(i+1))/(2*(i+1)-1))*((2*(i+1))/(2*(i+1)+1));
     sem_wait(&sem);
     result=result*product;
     sem_post(&sem);
     }
   
   
  
 
