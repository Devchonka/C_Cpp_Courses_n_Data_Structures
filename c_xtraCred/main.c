/**
**  Written By: Menyaylenko, Elena
**
**  Date:               06/03/2015
**  IDE (compiler):     GNU GCC Compiler, Unix OS

    Sieve of Eratosthenes based of bit manipulation.

    It finds all the prime numbers less than a given number (Euler Project Problem 10).

    There are 2 loops in the algorithm. The outer loop goes from 2 until the square root of a given number,
    checking if that number is not yet checked off in the bit array. If not yet checked off and is prime,
    the inner loop starts to cross off all its multiples.

    To compile code:
        gcc -std=c99  main.c -o c_xtraCred NUMBER

        - where NUMBER is any number of your choice (ie. 35)

    To check memory leaks with Valgrind:
        valgrind --tool=memcheck --leak-check=yes ./c_xtraCred

*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void sieve_of_Erathosthenes(bool*, unsigned);
unsigned bit_square(unsigned);
void print_primes(bool*, unsigned);
void print_largest_prime(bool*, unsigned);

/**
    Function main gets the input from the user from the command line.
    In the case that the user provides many inputs, the program selects a safe number (1000).
*/
int main(int argc, char* argv[])
{
    unsigned num = argc > 1 ? abs(atoi(argv[1])) : 1000;
    printf("Number Provided for Sieve of Eratosthenes: %d\n", num);
    bool* primes = malloc(num); // the array where elements with '0' left are primes
    memset(primes, 0, num); // set all bits to zero
    sieve_of_Erathosthenes(primes, num);
    //print_primes(primes, num);
    print_largest_prime(primes, num-1);
    free(primes);
    return 0;
}
/**
    This function is the algorithm for the sieve.

Create a list of consecutive integers from 2 through n: (2, 3, 4, ..., n).
Initially, let p equal 2, the first prime number.
Starting from p, enumerate its multiples by counting to n in increments of p, and mark them in the list (these will be 2p, 3p, 4p, ... ; the p itself should not be marked).
Find the first number greater than p in the list that is not marked. If there was no such number, stop. Otherwise, let p now equal this new number (which is the next prime), and repeat from step 3.

*/
void sieve_of_Erathosthenes(bool* primes, unsigned num)
{
    long sqrt_num = 1 + sqrt(num);
    unsigned inner_bound, outer_bound=2;
    bool *pMultiples, *pSieve = primes + outer_bound;
    // algorithm sieve itself
    while(outer_bound <sqrt_num)
    {
        if(!*pSieve++)
        {
            inner_bound= bit_square(outer_bound);
            pMultiples = primes + inner_bound;
            while(inner_bound<num)
            {
                *pMultiples |= 1; // set the bit
                pMultiples+=outer_bound;
                inner_bound+=outer_bound;
            }
        }
        outer_bound++;
    }
}

/**
    Function prints the largest prime number less than a certain given number by checking
    which entries are still '0' (unmarked).
*/
void print_largest_prime(bool* primes, unsigned last_elem)
{
    printf("\nLargest prime number less than %d is ..", last_elem+1);
    while(last_elem)
    {
        if(!primes[last_elem])
        {
            printf("%d\n", last_elem);
            break;
        }
        last_elem--;
    }
}

/**
    Function that prints all numbers in a row which are prime numbers making up a user defined number.
    They do so by checking which entries in the primes array are still '0'.
*/
void print_primes(bool* primes, unsigned num)
{
    printf("\nPrime numbers less than %d are..\n", num);
    int i=2;
    for(; i < num; ++i)
        if(primes[i] == 0)
        {
            printf("%d ", i);
        }
    putchar('\n');
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
