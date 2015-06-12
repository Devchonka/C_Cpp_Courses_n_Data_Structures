/**
CIS 26B -  Advanced C Programming

This file contains functions practicing the variable number of arguments as an input to functions.
The parameters either specify the number of arguments to follow, or just the arguments themselves.
In the first case, an int must be passed - in the second case, you use a sentinel value.
The first input parameter must be passed regardless.

Write a function named findMax that finds the maximum of any number of integer arguments.

Write a function named findAvg that finds the average of the integer arguments.
It also displays the parameters greater than or equal to the average.

Write a function named findMax_2 that finds the maximum of any number of integer arguments.
Use as a sentinel value 0 to stop. The first parameter is to represent one of the numbers.

Write a function named display that takes any number of arguments.
The first argument must be an integer.
The remaining arguments will be strings.
The first argument specifies the number of strings.

   To compile code:
        gcc -std=c99  main.c -o c_xtraCred_1
    To check memory leaks with Valgrind: (no dynamic allocation here)
        valgrind --tool=memcheck --leak-check=yes ./c_xtraCred_1
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int findMax(int,...);
double findAvg(int,...);
int findMax_2(int,...);
void display(int,...);

int main()
{
    printf("Testing findMax:\n");
    printf("The largest is: %d\n", findMax(3, 20, 90, 10));
    printf("The largest is: %d\n", findMax(4, 20, 10, 50, 30));
    printf("The largest is: %d\n", findMax(2, 20, 10));
    printf("The largest is: %d\n", findMax(1, 13));
    printf("The largest is: %d\n", findMax(5, -20, 10, -50, -30, -90));
    printf("\nTesting findAvg:\n");
    printf("The average is: %.1f\n", findAvg(3, 20, 90, 10));
    printf("The average is: %.1f\n", findAvg(4, 20, 10, 50, 31));
    printf("The average is: %.1f\n", findAvg(2, 22, 13));
    printf("The average is: %.1f\n", findAvg(1, 13));
    printf("The average is: %.1f\n", findAvg(5, -20, 11, -53, -30, -90));
    printf("\nTesting findMax_2:\n");
    printf("The largest is: %d\n", findMax_2(99, 20, 90, 10, 0));
    printf("The largest is: %d\n", findMax_2(40, 20, 10, 50, 30, 0));
    printf("The largest is: %d\n", findMax_2(25, 20, 10, 0));
    printf("The largest is: %d\n", findMax_2(10, 13, 0));
    printf("The largest is: %d\n", findMax_2(5, -20, 2, -50, -30, -90, 0));
    printf("\nTesting display:\n");
    display(5, "one", "two", "three", "four", "five");
    display(2, "dog", "cat");
    display(4, "dog", "cat", "mouse", "bird");
    display(3, "cat", "mouse", "bird");
    return 0;
}

/**
Function returns max int inside any set of integers in any number of input parameters.
*/
int findMax(int n_param,...)
{
    va_list args;
    int max = 0, temp = 0, count =0;
    va_start(args, n_param);  // initialize all params after n_param
    for(; count<n_param; ++count)
    {
        temp = va_arg(args, int);
        if(temp>max)
        {
            max = temp;
        }
    }
    va_end(args); // clean up list
    return max;
}

/**
Function finds the average of any number of int input parameters and prints all inputs greater than average.
*/
double findAvg(int n_param, ...)
{
    va_list args;
    int count =0, temp =0;
    double sum = 0.0, avg =0.0;
    va_start(args, n_param);  // initialize all params after n_param
    for(; count<n_param; ++count)
    {
        sum+=va_arg(args, int);
    }
    avg = sum / n_param;
    va_start(args, n_param);
    printf("Elements bigger than average: ");
    for(count =0; count<n_param; ++count)
    {
        temp=va_arg(args, int);
        if(temp>avg)
        {
            printf("%d ", temp);
        }
    }
    putchar('\n');
    va_end(args); // clean up list
    return avg;
}

int findMax_2(int first,...)
{
    int temp =first, max = first;
    va_list args;
    va_start(args,first);

    while (temp)
    {
        if(temp>max)
        {
            max = temp;
        }
        temp = va_arg(args, int);
    }
    va_end(args);
    return max;
}

void display(int n_strings,...)
{
    va_list args;
    int count =0;
    char temp[64];
    va_start(args, n_strings);
    for(; count<n_strings; ++count)
    {
        printf("%s ", va_arg(args, char*));
    }
    putchar('\n');
    va_end(args); // clean up list
}
