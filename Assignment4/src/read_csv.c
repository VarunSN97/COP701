#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void read_csv(char* filename, int rows , double** data)
 {
 FILE *fp=fopen(filename,"r");
 if(fp==NULL)
  {
  printf("error file not found");
  exit(0);
  }
  char* line = (char*)malloc(33554432*sizeof(char));
  for(int i=0;fgets(line,33554432,fp) && i<rows;i++)
  {
  char* token =strtok(line,",");
  for(int j=0;token && *token;j++)
   {
   data[i][j]=atof(token);
   token=strtok(NULL,",\n");
   }
   }
   fclose(fp);
 }
 
