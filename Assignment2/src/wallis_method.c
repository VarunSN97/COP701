#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include "../include/calculate.c"

#define PI 3.14159265358979323846

int n_iterations,num_threads;
double result_p=1;
sem_t sem;

double pi_value(int);

void *parallel_calculation(void *);

int main(int argc, char **argv)
 {
 double time1,time2,result_s,accuracy;
 pthread_t *threads;
 sem_init(&sem,0,1);
 FILE *fp1=fopen("time_serial_wallis.txt","a");
 FILE *fp2=fopen("accuracy_wallis.txt","a");
 FILE *fp3=fopen("time_parallel_wallis.txt","a");
 FILE *fp4=fopen("speed_up_wallis.txt","a");
 FILE *fp5=fopen("exact_bits_wallis.txt","a");
 num_threads=atoi(argv[1]);
 n_iterations=atoi(argv[2]);
 time1=calculateTime();
 result_s=pi_value(n_iterations);
 time1 =calculateTime()-time1;
 fprintf(fp1,"%f \n",time1);
 fclose(fp1);
 
 threads=(pthread_t*)malloc(num_threads*sizeof(pthread_t));
 time2 =calculateTime();
 for(int i=0;i<num_threads;i++)
  pthread_create(&threads[i],NULL,parallel_calculation,(void *)i);
  
  for(int i=0;i<num_threads;i++)
   pthread_join(threads[i],NULL);
   
   time2=calculateTime()-time2;
   result_p=result_p*2;
   fprintf(fp3,"%f \n",time2);
   fclose(fp3);
    accuracy= 100-(fabs(result_s-PI)/PI*100);
    if(result_s==result_p || accuracy >99.0)
     {
     fprintf(fp2,"%f \n",accuracy);
     fclose(fp2);
     }
   fprintf(fp4,"%f \n",time1/time2);
 fclose(fp4);
 
 double a=PI-3.0;
 double b=result_s-3.0;
 int count=0;
 for(int i=1;i<=15;i++)
  {
  a=a*10;
  b=b*10;
  if((int)floor(a) == (int)floor(b))
   count++;
   else 
    break;
    a=a-floor(a);
    b=b-floor(b);
  }
  fprintf(fp5,"%d \n",count);
  fclose(fp5);
 
 }
 
 double pi_value(int n)
  {
  double result_s=1.0;
  for(double i=1;i<=n;i++)
   result_s=result_s*((2*i)/(2*i-1))*((2*i)/(2*i+1));

   return result_s*2;
   }
      
   void *parallel_calculation(void *args)
    {
    int a= ((int)args);
    int factor = n_iterations/num_threads;
    int start = factor * a;
    int end = start + factor;
    double product=1.0;
    for(double i=start;i<end;i++)
     product=product*((2*(i+1))/(2*(i+1)-1))*((2*(i+1))/(2*(i+1)+1));
     sem_wait(&sem);
     result_p=result_p*product;
     sem_post(&sem);
     }
   
  
   
 
 
 
