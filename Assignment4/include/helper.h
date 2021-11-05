#ifndef HELPER_H
#define HELPER_H
#include "parameters.h"

void xavier_weight_initialization(double***,int,int*);
void he_weight_initialization(double***,int,int*);
void matrix_mul(double*,double**,double*,int,int);
void identity(double*,double*,int);
void derivative_identity(double*,int,double*);
void sigmoid(double*,double*,int);
void derivative_sigmoid(double*,int,double*);
void tan_h(double*,double*,int);
void derivative_tan_h(double*,int,double*);
void relu(double*,double*,int);
void derivative_relu(double*,int,double*);
void forward_propogation(parameter,double**,double**,int,double*,int);
void gradient_descent(parameter,double**,double**,double**,int,double);

#endif
