#include "../include/helper.h"
#include "../include/parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double regression(parameter param,double** input,double** output,int train_record)
 {
 int p=param.n_features+1;
 double correct_value=param.data_test[train_record][param.n_features];
 for(int i=0;i<param.n_features;i++)
  {
  output[0][0]=1;
  output[0][i+1]=input[0][i]=param.data_test[train_record][i];
  }
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
   identity(input[param.n_layers+1],output[param.n_layers+1],1);
  // printf("%f \n ",output[param.n_layers+1][0]);
   double a=((output[param.n_layers+1][0]- correct_value)*(output[param.n_layers+1][0]- correct_value));
      
   
 return a;

    }

