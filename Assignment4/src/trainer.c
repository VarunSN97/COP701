#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/helper.h"
#include "../include/backpropogation.h"
void shuffle(int* a ,int n)
     {
     int i,j;
     srand(time(NULL));
     for(int i=n-1;i>=0;i--)
      {
      j=rand()%(i+1);
      int temp=a[i];
      a[i]=a[i+1];
      a[i+1]=temp;
      }
      }
void trainer(parameter param,  double* total_error,int* total_nodes_layer,double*** weight_update)
 {
 int layers_present= param.n_layers+2;
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
 /* int* total_nodes_layer=(int*)malloc(layers_present*sizeof(int));
  for(int i=0;i<layers_present;i++)
   {
   if(i==0)
   total_nodes_layer[i]=param.n_features+1;
   else if (i==layers_present-1)
    total_nodes_layer[i]=1;
    else
    total_nodes_layer[i]=param.n_nodes_layer[i-1];
    }*/
   /*double*** weight_update=(double***)calloc((param.n_layers+1),sizeof(double**));
   for(int i=0;i<param.n_layers+1;i++)
    {
    weight_update[i]=(double**)calloc(total_nodes_layer[i] , sizeof(double*));
    for(int j=0;j<total_nodes_layer[i];j++)
    weight_update[i][j]=(double*)calloc(total_nodes_layer[i+1],sizeof(double));
    }
    */
   int* train = (int*)malloc(param.training_rows*sizeof(int));
   for(int i=0;i<param.training_rows;i++)
    train[i]=i;
   if(param.activation_function[0]==1 || param.activation_function[0]==2)
    xavier_weight_initialization(param.weight,layers_present,total_nodes_layer);
    else
    he_weight_initialization(param.weight,layers_present,total_nodes_layer);
    int c=1;
    //printf("%d %d \n",total_nodes_layer[0],total_nodes_layer[1]);
    for(int i=0;i<param.epochs;i++){
    shuffle(train,param.training_rows);
    
     for(int j=0;j<param.training_rows;j++)
      {
    //  printf("%d %d \n",total_nodes_layer[0],total_nodes_layer[1]);
      forward_propogation(param,input,output,train[j],total_error,i);
      //printf("%d %d %f %f \n",param.n_nodes_layer[0],total_nodes_layer[1],param.weight[0][0][0],param.weight[1][0][0]);
      //printf("A \n");
      //printf("%f  \n",weight_update[0][0][0]);
      weight_correction(param,train[j],input,output,weight_update, total_nodes_layer);
      //  printf("%d %d \n",total_nodes_layer[0],total_nodes_layer[1]);
       if(c==param.batch_size)
        {
      //  printf("complete \n");
        update_weight(c,weight_update,param,total_nodes_layer);
        c=1;
        }
        else
         c++;
        // printf("3 \n");
      }
      }
            
      free(train);
      free(total_nodes_layer);
      
      for(int i=0;i<layers_present;i++)
       {
       free(input[i]);
       free(output[i]);
       }
       free(input);
       free(output);
      
     }

 

