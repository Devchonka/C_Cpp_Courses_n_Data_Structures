#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

unsigned bit_square(unsigned);

int main(int argc, char* argv[])
{
    unsigned num = argc > 1 ? abs(atoi(argv[1])) : 1000;
    unsigned i, j;
    long sqrt_num = 1 + sqrt(num);
    printf("Number Provided for Sieve of Eratosthenes: %d\n", num);

    bool* primes = malloc(num);
    memset(primes, 0, num); // set all bits to zero

bool* ptr; unsigned array_bound;
// algorithm sieve itself
    for(i = 2; i < sqrt_num; i++)
    {

        if(primes[i] == 0)
        {
            array_bound= bit_square(i);
            ptr = primes + array_bound;

            while(array_bound<num)
            {
                *ptr |= 1; // set the bit
                ptr+=i; array_bound+=i;
            }
        }
    }
    printf("PRINTING SOLUTION\n");
// print primes
    for(i = 2; i < num; ++i)
        if(primes[i] == 0)
        {
            printf("prime number: %d\n", i);
        }
    free(primes);
    return 0;
}


/**
    Recursive Algorithm:
    square(num) = 0 if n == 0
  if num is even
     square(num) = 4*square(num/2)
  if n is odd
     square(num) = 4*square(floor(num/2)) + 4*floor(num/2) + 1
*/
unsigned bit_square(unsigned num)
{
    if(num==0)
    {
        return 0;
    }
    unsigned x = num>>1; // floor (n/2)
    if(num&1)  // num odd
    {
        return ((bit_square(x)<<2) + (x<<2) + 1);
    }
    else // num even
    {
        return (bit_square(x)<<2);
    }
}
