#include <stdio.h>
#include "gcd.h"

void main ()
{
int n1, n2, lcm;

    printf("Enter two integers: ");
    scanf("%d %d", &n1, &n2);
    lcm=n1*n2/gcd(n1,n2);
    printf("LCM of %d and %d is %d", n1, n2, gcd);
    }
