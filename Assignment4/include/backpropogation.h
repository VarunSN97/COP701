#ifndef BACK_PROPOGATION_H
#define BACK_PROPOGATION_H
#include "parameters.h"

void weight_correction(parameter,int,double**, double**, double***,int*);
void update_weight(int,double***,parameter,int*);
#endif
