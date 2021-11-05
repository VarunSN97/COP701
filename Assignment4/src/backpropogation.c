#include <stdio.h>
#include <stdlib.h>
#include "../include/helper.h" 
#include "../include/trainer.h"
void weight_correction(parameter param, int example_no, double** input, double** output,double*** weight_update,int* total_nodes)
{

double correct_output = param.data_training[example_no][param.n_features];
double** gradient= (double**)malloc((param.n_layers+2)*sizeof(double*));
for(int i=0;i<param.n_layers+2;i++)
 {
 if(i==0)
  gradient[i]=(double*)malloc(param.n_features*sizeof(double));
  else if(i==param.n_layers+1)
   gradient[i]=(double*)malloc(sizeof(double));
   else
   gradient[i]=(double*)malloc(param.n_nodes_layer[i-1]*sizeof(double));
 }
free(gradient[0]); 
 
 gradient_descent(param,input,output,gradient,param.n_layers+1,correct_output);
 //printf("check1 \n");
 for(int i=0;i<param.n_nodes_layer[param.n_layers-1];i++)
 { weight_update[param.n_layers][i][0]+= param.learning_rate * gradient[param.n_layers+1][0] * output[param.n_layers][i];
  
  //printf("check2 \n");
  }
  for(int i= param.n_layers-1;i>=0;i--)
  {//printf("%d %d\n",total_nodes[0],total_nodes[1]);
  gradient_descent(param,input,output,gradient,i+1,correct_output);
//printf("%d %d\n",total_nodes[0],total_nodes[1]);
  
  for(int j=0;j<total_nodes[i];j++)
  for(int k=0;k<total_nodes[i+1];k++)
  { weight_update[i][j][k]+=param.learning_rate * gradient[i+1][k] * output[i][j];}
   }
  //printf("correcting weight \n");
/*for(int i=1;i<param.n_layers+2;i++)
free(gradient[i]);
free(gradient);
*/
}
void update_weight(int batch, double*** weight_update,parameter param, int* total_nodes)
{
//printf("try1 \n");printf("%d %d \n",total_nodes[0],total_nodes[1]);
 for(int i=0;i<param.n_layers+1;i++){
  for (int j=0;j<total_nodes[i];j++){
   for(int k=0;k<total_nodes[i+1];k++)
    {//printf ("%d %d %d \n",i,j,k);
    param.weight[i][j][k]+=weight_update[i][j][k]/((double)batch);}}}
 //printf("try \n");
 for(int i=0;i<param.n_layers+1;i++)
  for (int j=0;j<total_nodes[i];j++)
   for(int k=0;k<total_nodes[i+1];k++)
    weight_update[i][j][k]=0;
    
  //  printf("updating weight \n");
}
