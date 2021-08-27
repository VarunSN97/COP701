#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <semaphore.h>
#include "../include/calculate.c"

#define num_threads 500

int n;
double result;
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
   result=result-1.5;
   result=sqrt(result*8);
   printf("%lf %lf\n",result,time);
   }
   
   void *parallel_calculation(void *args)
    {
    int a= ((int)args);
    int factor = n/num_threads;
    int start = factor * a;
    int end = start + factor;
    double sum;
    for(double i=start;i<end;i++)
     sum=sum+2/((2*i-1)*(2*i-1)*(2*i+1));
     sem_wait(&sem);
     result=result+sum;
     sem_post(&sem);
     }
   
   
  
 
