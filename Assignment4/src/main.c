#include "../include/parameters.h"
#include "../include/trainer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/read_csv.h"
#include "../include/classifier.h"
#include "../include/regression.h"
void min_feature(parameter param)
{double temp;
//printf("min feature");
int x = param.training_rows * 8 /10;
for(int i=0;i<param.n_features;i++)
 {temp=1000.0;
 for(int j=0;j<x;j++)
  {
  if(param.data_training[j][i]<temp)
  {
  temp=param.data_training[j][i];
  }
  }
  param.min_n[i]=temp;
 // printf("%f \n",temp);
 }
 
}
void max_feature(parameter param)
{
double temp;
int x = param.training_rows * 8 /10;
for(int i=0;i<param.n_features;i++)
 { temp=0.0;
 for(int j=0;j<x;j++)
  {
  if(param.data_training[j][i]>temp)
  {
  temp=param.data_training[j][i];
  }
  }
  param.max_n[i]=temp;
  printf("%f \n",temp);
 }
 }
void mean(parameter param)
 {
 int x =param.training_rows * 8 / 10;
 for(int i=0;i<param.n_features;i++)
  {
  for(int j=0;j<x;j++)
   param.mean[i]+=param.data_training[j][i];
   param.mean[i]=param.mean[i]/x;
 
 }
 }
 void sd(parameter param)
  {
  int x = param.training_rows * 8 /10;
  for(int i=0;i<param.n_features;i++)
   {
   for(int j=0;j<x;j++)
   param.sd[i]+=pow(param.data_training[j][i]-param.mean[i] , 2);
   param.sd[i]=sqrt(param.sd[i]/x);
   
   }
  }

int main(int argc, char** argv)
 {
 parameter param;
 param.n_layers = atoi(argv[1]);
 param.learning_rate=atof(argv[2]);
 param.n_features=atoi(argv[3]);
 param.training_rows=atoi(argv[4]);
 param.epochs=atoi(argv[5]);
 param.batch_size=atoi(argv[6]);
 param.n_nodes_layer=(int*)malloc(param.n_layers*sizeof(int));
 param.activation_function=(int*)malloc(param.n_layers*sizeof(int));
 param.n_nodes_layer=(int*)malloc(param.n_layers*sizeof(int));
 param.mean=(double*)malloc(param.n_features*sizeof(double));
 param.sd=(double*)malloc(param.n_features*sizeof(double));
 param.min_n=(double*)malloc(param.n_features*sizeof(double));
 param.max_n=(double*)malloc(param.n_features*sizeof(double));
 if(strcmp(argv[7],"classification")==0)
  param.method=1;
  else
  param.method=2;
  if(strcmp(argv[8],"cross_entropy")==0)
  param.cost_function=1;
  else
  param.cost_function=2;
  
 for(int i=0;i<param.n_layers;i++)
 {
 if(strcmp(argv[9+i],"sigmoid")==0)
 param.activation_function[i]=1;
 else if(strcmp(argv[9+i],"tan_h")==0)
 param.activation_function[i]=2;
 else if(strcmp(argv[9+i],"relu")==0)
 param.activation_function[i]=3;
 
 }
 for(int i=0;i<param.n_layers;i++)
  {
  param.n_nodes_layer[i]=atoi(argv[9+param.n_layers+i]);
  }
  
  int layers_present= param.n_layers+2;
    int* total_nodes_layer=(int*)malloc((param.n_layers+2)*sizeof(int));
  for(int i=0;i<layers_present;i++)
   {
   if(i==0)
   total_nodes_layer[i]=param.n_features+1;
   else if (i==layers_present-1)
    total_nodes_layer[i]=1;
    else
    total_nodes_layer[i]=param.n_nodes_layer[i-1];
    }
  
   param.weight=(double***)calloc((param.n_layers+1),sizeof(double**));
   for(int i=0;i<param.n_layers+1;i++)
    {
    param.weight[i]=(double**)calloc(total_nodes_layer[i] , sizeof(double*));
    for(int j=0;j<total_nodes_layer[i];j++)
    param.weight[i][j]=(double*)calloc(total_nodes_layer[i+1],sizeof(double));
    }
   // free(total_nodes_layer);
   if(param.method==1){
    param.data_training=(double**)malloc(455*sizeof(double*));
    for(int i=0;i<455;i++)
     param.data_training[i]=(double*)malloc((param.n_features+1)*sizeof(double));
    read_csv("src/data.csv",455,param.data_training);
 
    param.data_test=(double**)malloc(114*sizeof(double*));
    for(int i=0;i<114;i++)
     param.data_test[i]=(double*)malloc((param.n_features+1)*sizeof(double));
    read_csv("src/test.csv",114,param.data_test);
 
    double* total_error=(double*)malloc(param.epochs*sizeof(double));
    mean(param);
    sd(param);
    for(int i=0;i<param.training_rows;i++)
     for(int j=0;j<param.n_features;j++)
      param.data_training[i][j]=((param.data_training[i][j]-param.mean[j])/(param.sd[j]));
    
    for(int i=0;i<114;i++)
     for(int j=0;j<param.n_features;j++)
      param.data_test[i][j]=((param.data_test[i][j]-param.mean[j])/(param.sd[j]));
    
   double*** weight_update=(double***)calloc((param.n_layers+1),sizeof(double**));
   for(int i=0;i<param.n_layers+1;i++)
    {
    weight_update[i]=(double**)calloc(total_nodes_layer[i] , sizeof(double*));
    for(int j=0;j<total_nodes_layer[i];j++)
    weight_update[i][j]=(double*)calloc(total_nodes_layer[i+1],sizeof(double));
    }
 printf("Starting Training \n");  
    trainer(param,total_error,total_nodes_layer,weight_update);
    
    FILE *fp1=fopen("error_c.txt","a");
    for(int i=0;i<param.epochs;i++)
     fprintf(fp1,"%d %f \n",i,(total_error[i]/param.training_rows));
    free(total_error);
   
 double** input=(double**)malloc(layers_present*sizeof(double*));
 for(int i=0;i<layers_present;i++)
  {
  if(i==0)
   input[i]=(double*)malloc((param.n_features)*sizeof(double));
  else if(i==layers_present-1)
  input[i]=(double*)malloc(sizeof(double));
  else
  input[i]=(double*)malloc(param.n_nodes_layer[i-1]*sizeof(double));
  }
  double** output=(double**)malloc(layers_present*sizeof(double*));
 for(int i=0;i<layers_present;i++)
  {
  if(i==0)
   output[i]=(double*)malloc((param.n_features+1)*sizeof(double));
  else if(i==layers_present-1)
  output[i]=(double*)malloc(sizeof(double));
  else
  output[i]=(double*)malloc(param.n_nodes_layer[i-1]*sizeof(double));
  }
    
    
    double counter=0;
    for(int i=0;i<114;i++)
     counter+=classifier(param,input,output,i);
     double accuracy= counter/114.0*100;
     printf("%f \n",accuracy);
 }
 else{
 param.data_training=(double**)malloc(405*sizeof(double*));
    for(int i=0;i<405;i++)
     param.data_training[i]=(double*)malloc((param.n_features+1)*sizeof(double));
    read_csv("src/Boston.csv",405,param.data_training);
       param.data_test=(double**)malloc(101*sizeof(double*));
    for(int i=0;i<101;i++)
     param.data_test[i]=(double*)malloc((param.n_features+1)*sizeof(double));
    read_csv("src/regression_test.csv",101,param.data_test);
   
    double* total_error=(double*)malloc(param.epochs*sizeof(double));
    max_feature(param);
    min_feature(param);
    for(int i=0;i<param.training_rows;i++)
     for(int j=0;j<param.n_features;j++)
      param.data_training[i][j]=((param.data_training[i][j]-param.min_n[j])/(param.max_n[j]-param.min_n[j]));
      
      for(int i=0;i<101;i++)
     for(int j=0;j<param.n_features;j++)
      param.data_test[i][j]=((param.data_test[i][j]-param.min_n[j])/(param.max_n[j]-param.min_n[j]));
      
   double*** weight_update=(double***)calloc((param.n_layers+1),sizeof(double**));
   for(int i=0;i<param.n_layers+1;i++)
    {
    weight_update[i]=(double**)calloc(total_nodes_layer[i] , sizeof(double*));
    for(int j=0;j<total_nodes_layer[i];j++)
    weight_update[i][j]=(double*)calloc(total_nodes_layer[i+1],sizeof(double));
    }
   printf("Starting Training \n");
    trainer(param,total_error,total_nodes_layer,weight_update);
    
    FILE *fp1=fopen("error_R.txt","a");
    for(int i=0;i<param.epochs;i++){
    printf("Running Epoch %d \n",i);
     fprintf(fp1,"%d %f \n",i,(total_error[i]/param.training_rows));}
    free(total_error);
   
 double** input=(double**)malloc(layers_present*sizeof(double*));
 for(int i=0;i<layers_present;i++)
  {
  if(i==0)
   input[i]=(double*)malloc((param.n_features)*sizeof(double));
  else if(i==layers_present-1)
  input[i]=(double*)malloc(sizeof(double));
  else
  input[i]=(double*)malloc(param.n_nodes_layer[i-1]*sizeof(double));
  }
  double** output=(double**)malloc(layers_present*sizeof(double*));
 for(int i=0;i<layers_present;i++)
  {
  if(i==0)
   output[i]=(double*)malloc((param.n_features+1)*sizeof(double));
  else if(i==layers_present-1)
  output[i]=(double*)malloc(sizeof(double));
  else
  output[i]=(double*)malloc(param.n_nodes_layer[i-1]*sizeof(double));
  }
  
    printf("Done \n");
    
    double counter=0;
    for(int i=0;i<101;i++)
     counter+=regression(param,input,output,i);
     double accuracy= counter/101.0;
     printf("%f \n",accuracy);}    
     
 
 }
 
