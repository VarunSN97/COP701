#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <semaphore.h>
#include "../include/calculate.c"

int num_threads;
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
 FILE *fp=fopen("thread_vs_performance_(fourier).txt","a");
 for(num_threads=1;num_threads<250;num_threads++)
 {
 threads=(pthread_t*)malloc(num_threads*sizeof(pthread_t));
 time =calculateTime();
 for(int i=0;i<num_threads;i++)
  pthread_create(&threads[i],NULL,parallel_calculation,(void *)i);
  
  for(int i=0;i<num_threads;i++)
   pthread_join(threads[i],NULL);
   
   time=calculateTime()-time;
   fprintf(fp,"%d %lf\n",num_threads,time);
   free(threads);
   }
   result=result-1.5;
   result=sqrt(result*8);
  // printf("%lf %lf\n",result,time);
   
   }
   
   void *parallel_calculation(void *args)
    {
    int a= ((int)args);
    int i;
    int factor = n/num_threads;
    int start = factor * a;
    int end = start + factor;
    double sum;
    for(i=start;i<end;i++)
     sum=sum+2.0/((2.0*i-1.0)*(2.0*i-1.0)*(2.0*i+1.0));
     sem_wait(&sem);
     result=result+sum;
     sem_post(&sem);
     }
   
   
  
 
