#ifndef PARAMETERS_H
#define PARAMETERS_H

typedef struct input
 {
 double*** weight;
 int n_layers;
 int* n_nodes_layer;
 int* activation_function;
 double learning_rate;
 int n_features;
 int training_rows;
 int epochs;
 int batch_size;
 double** data_training;
 double** data_test;
 int method;//regression or classification
 int cost_function;//mse or cel
 double* mean;
 double* sd;
 double* min_n;
 double* max_n;
 }parameter;
 
 #endif
