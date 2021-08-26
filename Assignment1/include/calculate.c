#include <sys/time.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double micro=1.0e-6;
double calculateTime()
{
struct timeval TV;
struct timezone TZ;
int RC=gettimeofday(&TV,&TZ);
if(RC==1)
{
printf("BAD call to gettimeofday\n");
return (-1);
}
return (((double)TV.tv_sec)+micro*((double)TV.tv_usec));
}
