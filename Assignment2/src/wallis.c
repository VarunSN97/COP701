#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include "../include/calculate.c"

#define PI 3.14159265358979323846


double pi_value(int);

int main(int argc, char **argv)
 {
 double time,result,accuracy;
 int n;
 FILE *fp1=fopen("time_serial.txt","a");
 FILE *fp2=fopen("accuracy.txt","a");
 n=atoi(argv[1]);
 time=calculateTime();
 result=pi_value(n);
 time =calculateTime()-time;
 fprintf(fp1,"%f \n",time);
 fclose(fp1);
 printf("%.30lf %lf\n",result,time);
 accuracy= 100-(fabs(result-PI)/PI*100);
 fprintf(fp2,"%f \n",accuracy);
 fclose(fp2);
 
 }
 
 double pi_value(int n)
  {
  double result=1.0;
  for(double i=1;i<=n;i++)
   result=result*((2*i)/(2*i-1))*((2*i)/(2*i+1));

   return result*2;
   }
   
  
   
 
 
 
