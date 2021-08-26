#include <stdio.h>
#include <stdlib.h>
#include "../include/calculate.c"
double normalMul(int n ,int **A,int **B)
{
int sum=0;
double time=calculateTime();
int **C=(int **)malloc(n*(sizeof(int *)));
for(int i=0;i<n;i++)
C[i]=(int *)malloc(n*(sizeof(int)));

for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
{sum=0;
for(int k=0;k<n;k++)
 sum+=A[i][k]*B[k][j];
 C[i][j]=sum;
 }
 
 time=calculateTime()-time;
return time;
}
double blockMul(int **A,int **B,int block,int n)
{
int ib=block,kb=block;
int acc00=0,acc01=0,acc10=0,acc11=0;
int **C=(int **)malloc(n*(sizeof(int *)));
for(int i=0;i<n;i++)
C[i]=(int *)malloc(n*(sizeof(int)));
double time=calculateTime();
for(int ii=0;ii<n;ii+=ib)
{
for(int kk=0;kk<n;kk+=kb)
{
for(int j=0;j<n;j+=2)
{
for(int i=ii;i<ii+ib;i+=2)
{
if(kk==0)
acc00=acc01=acc10=acc11=0;
else
{
acc00=C[i+0][j+0];
acc01=C[i+0][j+1];
acc10=C[i+1][j+0];
acc11=C[i+1][j+1];
}
for(int k=kk;k<kk+kb;k++)
{
acc00+=B[k][j+0]*A[i+0][k];
acc01+=B[k][j+1]*A[i+0][k];
acc10+=B[k][j+0]*A[i+1][k];
acc11+=B[k][j+1]*A[i+1][k];
}
C[i+0][j+0]=acc00;
C[i+0][j+1]=acc01;
C[i+1][j+0]=acc10;
C[i+1][j+1]=acc11;
}
}
}
}
time=calculateTime()-time;
return time;
}
void check()
{
for(int k=1000;k<=1100;k+=2)
{
FILE *fp=fopen("c.txt","a");
int **A=(int **)malloc(k*(sizeof(int *)));
int **B=(int **)malloc(k*(sizeof(int *)));

for(int i=0;i<k;i++)
{
A[i]=(int *)malloc(k*sizeof(int));
B[i]=(int *)malloc(k*sizeof(int));

}
 for(int i=0;i<k;i++)
{
for(int j=0;j<k;j++)
{
A[i][j]=rand();
B[i][j]=rand();
}
}
double min=100000.0;
double time=normalMul(k,A,B);
double t1;
int b=0;
for(int l=250;l<=k/2;l++)
{
if(l%2==0 && k%l==0)
{
t1=blockMul(A,B,l,k);
if(t1<min)
{
min=t1;
b=l;
} 
}}fprintf(fp,"%d %d %f\n",k,b,time/min);
}
}

void blockMultiplication(int **A,int **B,int n,int block)
{
int ib=block,kb=block;
int acc00=0,acc01=0,acc10=0,acc11=0;
int **C=(int **)malloc(n*(sizeof(int *)));
for(int i=0;i<n;i++)
C[i]=(int *)malloc(n*(sizeof(int)));
FILE *fp=fopen("b.txt","a");
double time=calculateTime();
for(int ii=0;ii<n;ii+=ib)
{
for(int kk=0;kk<n;kk+=kb)
{
for(int j=0;j<n;j+=2)
{
for(int i=ii;i<ii+ib;i+=2)
{
if(kk==0)
acc00=acc01=acc10=acc11=0;
else
{
acc00=C[i+0][j+0];
acc01=C[i+0][j+1];
acc10=C[i+1][j+0];
acc11=C[i+1][j+1];
}
for(int k=kk;k<kk+kb;k++)
{
acc00+=B[k][j+0]*A[i+0][k];
acc01+=B[k][j+1]*A[i+0][k];
acc10+=B[k][j+0]*A[i+1][k];
acc11+=B[k][j+1]*A[i+1][k];
}
C[i+0][j+0]=acc00;
C[i+0][j+1]=acc01;
C[i+1][j+0]=acc10;
C[i+1][j+1]=acc11;
}
}
}
}
time=calculateTime()-time;
fprintf(fp,"%f \n",time);
}

void printMatrix(int n, int **A,int **B)
{
for(int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
printf("%d /t%d ",A[i][j],B[i][j]);
printf("/n");
}
}
void verify(int n)
{
}
int main(int argc, char **argv)
{
FILE *fp = fopen("a.txt","a");
int n,nreps,block,loop=0;
if(argc!=4)
{
loop=1;
nreps=5;
}
else{
n=atoi(argv[1]);
nreps=atoi(argv[2]);
block=atoi(argv[3]);}
int sum=0;
if(loop==1)
{
for(n=4;n<1025;n=n*2)
{
int **A=(int **)malloc(n*(sizeof(int *)));
int **B=(int **)malloc(n*(sizeof(int *)));
int **C=(int **)malloc(n*(sizeof(int *)));
for(int i=0;i<n;i++)
{
A[i]=(int *)malloc(n*sizeof(int));
B[i]=(int *)malloc(n*sizeof(int));
C[i]=(int *)malloc(n*sizeof(int));
}
for(int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
{
A[i][j]=rand();
B[i][j]=rand();
}
}

double time=calculateTime();
for(int r=0;r<nreps;r++)
{
for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
{sum=0;
for(int k=0;k<n;k++)
 sum+=A[i][k]*B[k][j];
 C[i][j]=sum;
 }
 
 }
 time=calculateTime()-time;
 time=time/nreps;
 fprintf(fp,"%f \n",time);
 blockMultiplication(A,B,n,n/2);
 }}
 else
 {
 int **A=(int **)malloc(n*(sizeof(int *)));
int **B=(int **)malloc(n*(sizeof(int *)));
int **C=(int **)malloc(n*(sizeof(int *)));
for(int i=0;i<n;i++)
{
A[i]=(int *)malloc(n*sizeof(int));
B[i]=(int *)malloc(n*sizeof(int));
C[i]=(int *)malloc(n*sizeof(int));
}

 for(int i=0;i<n;i++)
{
for(int j=0;j<n;j++)
{
A[i][j]=rand();
B[i][j]=rand();
}
}

double time=calculateTime();
for(int r=0;r<nreps;r++)
{
for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
{sum=0;
for(int k=0;k<n;k++)
 sum+=A[i][k]*B[k][j];
 C[i][j]=sum;} }
 time=calculateTime()-time;
 time=time/nreps;
 fprintf(fp,"%f \n",time);
 blockMultiplication(A,B,n,block);
 if(nreps>1)
 check();}
}

