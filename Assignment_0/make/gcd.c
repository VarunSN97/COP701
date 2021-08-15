#include <stdio.h>
int gcd(int n1, int n2)
{int i, gcd;

    

    for(i=1; i <= n1 && i <= n2; ++i)
    {
        // Checks if i is factor of both integers
        if(n1%i==0 && n2%i==0)
            gcd = i;
    }

    return gcd;
    }
