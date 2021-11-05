#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../include/parameters.h"

void xavier_weight_initialization(double*** weight, int n_layers, int* n_nodes_layer)
 {
 srand(time(0));
 double* temp= (double*)malloc(n_layers*sizeof(double));
 for(int i=0;i<n_layers-1;i++)
  {
  temp[i]= (sqrt(6.0)/(sqrt(n_nodes_layer[i]+n_nodes_layer[i+1])));
  }
 for (int i=1;i<n_layers;i++)
  {
  for (int j=0;j<n_nodes_layer[i-1];j++)
   {
   for (int k=0;k<n_nodes_layer[i];k++)
    {
    weight[i-1][j][k]=-temp[i-1]+(double)rand()*(2*temp[i-1]);
    }
    }
    }
    free(temp);
   
 }
 
void he_weight_initialization(double*** weight, int n_layers, int* n_nodes_layer)
 {
 srand(time(0));
 double* temp =(double*)malloc(n_layers*sizeof(double));
 for(int i=0;i<n_layers-1;i++)
  {
  temp[i]=sqrt(2.0/n_nodes_layer[i]);
  }
 for(int i=0;i<n_layers-1;i++)
  {
  for(int j=0;j<n_nodes_layer[i];j++)
   {
   for(int k=0;k<n_nodes_layer[i+1];k++)
    {
    weight[i][j][k]=(double)rand()*temp[i];
    }
    }
    }
    free(temp);
 }
 
 void matrix_mul(double* arr, double** mat, double* result, int n ,int p)
  {
  for(int i=0;i<n;i++)
   {
    result[i]=0.0;
   for(int j=0;j<p;j++)
    result[i]+=arr[j]*mat[j][i];
    }
    }

void identity(double* input, double* output, int size)
{
 for(int i=0;i<size;i++)
 output[i]=input[i];
}

void derivative_identity(double* output, int size, double* derivative)
{
for(int i=0;i<size;i++)
derivative[i]=1;
}

    
void sigmoid(double* input, double* output, int size)
     {
     for(int i=0;i<size;i++)
      {
      output[i]=1/(1+exp(-input[i]));
      }
      }
      

void derivative_sigmoid(double* output, int size, double* derivative)
 {
 for(int i=0;i<size;i++)
  derivative[i]=output[i]*(1.0-output[i]);
 } 

void tan_h(double* input, double* output, int size)
 {
 for(int i=0;i<size;i++)
  output[i]=tanh(input[i]);
  }
  
void derivative_tan_h(double* output, int size, double* derivative)
 {
 for(int i=0;i<size;i++)
  derivative[i]= 1.0 - output[i]*output[i];
 }
  
void relu(double* input, double* output, int size)
 {
 for(int i=0;i<size;i++)
  {
  if (input[i]>0)
   output[i]=input[i];
   else
   output[i]=0;
   }
   }
   
void derivative_relu(double* output, int size, double* derivative)
 {
 for(int i=0;i<size;i++)
  {
  if(output[i]<=0)
   derivative[i]=0;
   else if(output[i]>0)
   derivative[i]=1;
  }
 }
   
void forward_propogation(parameter param,double** input,double** output,int train_record, double* total_error,int iteration)
 {
 double correct_value = param.data_training[train_record][param.n_features];
 int p=param.n_features+1;
// printf("0 \n");
 for(int i=0;i<param.n_features;i++)
  {
  output[0][0]=1;
 // printf("%d \n",train_record);
  output[0][i+1]=input[0][i]=(param.data_training[train_record][i]);
  
  
  }//printf("1 \n");
  for(int i=1;i<param.n_layers+1;i++)
   {
   matrix_mul(output[i-1],param.weight[i-1],input[i],param.n_nodes_layer[i-1],p);
   p=param.n_nodes_layer[i-1];
   
   switch(param.activation_function[i-1])
    {
    case 1:
    sigmoid(input[i],output[i],p);
    break;
    case 2:
    tan_h(input[i],output[i],p);
    break;
    case 3:
    relu(input[i],output[i],p);
    break;
    }
    }
    matrix_mul(output[param.n_layers],param.weight[param.n_layers],input[param.n_layers+1],1,param.n_nodes_layer[param.n_layers-1]);
   if(param.method==1) 
   sigmoid(input[param.n_layers+1],output[param.n_layers+1],1/*param.n_nodes_layer[param.n_layers-1]*/);
   else{   
   identity(input[param.n_layers+1],output[param.n_layers+1],1);
   //printf("run \n");
   }
   if(param.cost_function==1)
    {total_error[iteration]+=-(correct_value * log(output[param.n_layers+1][0]) + (1.0-correct_value)* log(fabs(.99-output[param.n_layers+1][0])));
    }
   else
    total_error[iteration]+=fabs(correct_value - output[param.n_layers+1][0]);
  //  printf("%f \n",output[param.n_layers+1][0]);}
    }
    

void gradient_descent(parameter param, double** input, double** output, double** gd,int layer_no,double correct_output)
 {
 double error=0.0;
 double** derivative=(double**)malloc((param.n_layers+2)*sizeof(double*));
 for(int i=0;i<param.n_layers+2;i++)
  {
  if(i==0)
   derivative[i]=(double*)malloc((param.n_features+1)*sizeof(double));
  else if(i==param.n_layers+1)
   derivative[i]=(double*)malloc(1*sizeof(double));
   else
   derivative[i]=(double*)malloc(param.n_nodes_layer[i+1] * sizeof(double));
   }
   if(layer_no==param.n_layers + 1)
    {
    error=correct_output - output[layer_no][0];
    if(param.method==1)
    derivative_sigmoid(output[layer_no],1,derivative[layer_no]);
    else
    derivative_identity(output[layer_no],1,derivative[layer_no]);
    gd[layer_no][0]=error*derivative[layer_no][0];
    }
    else
     {
     switch(param.activation_function[layer_no-1]){
     case 1:
      derivative_sigmoid(output[layer_no],param.n_nodes_layer[layer_no-1],derivative[layer_no]);
      if(layer_no==param.n_layers)
       {
       for(int i=0;i<param.n_nodes_layer[layer_no-1];i++)
        {
        error=gd[layer_no][0]*param.weight[layer_no-1][i][0];
        gd[layer_no][i]=error*derivative[layer_no][i];
        }
       }
       else{
      for(int i=0;i<param.n_nodes_layer[layer_no-1];i++)
       {
       error = 0.0;
       for(int j=0;j<param.n_nodes_layer[layer_no];j++)
        error+=gd[layer_no][j]*param.weight[layer_no-1][i][j];
        
        gd[layer_no][i]=error*derivative[layer_no][i];
        }}
        break;
     case 2:
      derivative_tan_h(output[layer_no],param.n_nodes_layer[layer_no-1],derivative[layer_no]);
      if(layer_no==param.n_layers)
       {
       for(int i=0;i<param.n_nodes_layer[layer_no-1];i++)
        {
        error=gd[layer_no][0]*param.weight[layer_no-1][i][0];
        gd[layer_no][i]=error*derivative[layer_no][i];
        }
       }
       else{
      for(int i=0;i<param.n_nodes_layer[layer_no-1];i++)
       {
       error = 0.0;
       for(int j=0;j<param.n_nodes_layer[layer_no];j++)
        error+=gd[layer_no][j]*param.weight[layer_no-1][i][j];
        
        gd[layer_no][i]=error*derivative[layer_no][i];
        }}
        break;
        case 3:
      derivative_relu(output[layer_no],param.n_nodes_layer[layer_no-1],derivative[layer_no]);
      if(layer_no==param.n_layers)
       {
       for(int i=0;i<param.n_nodes_layer[layer_no-1];i++)
        {
        error=gd[layer_no][0]*param.weight[layer_no-1][i][0];
        gd[layer_no][i]=error*derivative[layer_no][i];
        }
       }
       else{
      for(int i=0;i<param.n_nodes_layer[layer_no-1];i++)
       {
       error = 0.0;
       for(int j=0;j<param.n_nodes_layer[layer_no];j++)
        error+=gd[layer_no][j]*param.weight[layer_no-1][i][j];
        
        gd[layer_no][i]=error*derivative[layer_no][i];
        }}
        break;
        }
   
   }
  for(int i=0;i<param.n_layers+2;i++)
   free(derivative[i]);
   free(derivative); 
 }
 
 
 
    
    
 
 
   
   
      
      
     
    
  
  
