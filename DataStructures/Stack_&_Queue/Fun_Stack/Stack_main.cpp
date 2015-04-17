/**~*~*
 @author Elena Menyaylenko
 CIS 22C Hwk 2
  Function accepts any number of files as inputs, just change FILE_NAMES variable to accommodate.
    Each time we read 0, display the number of elements in the stack, each time we
read 1, display the element at the top of the stack, each time we read a positive number
we push it onto the stack, and each time we read a negative number, we pop and print as
many values from the stack as the absolute value of the negative number. If there are
fewer numbers in the stack, print a message and nothing else. When the end of the file is
detected, print a message and the items left in the stack.

*~**/
#include <iostream>
#include <string>
#include <fstream>
#include "Stack.h"
using namespace std;

const string FILE_NAMES[] = {"numbers1.txt", "numbers2.txt", "numbers3.txt"};
const int NUM_FILES =(sizeof(FILE_NAMES)/sizeof(*FILE_NAMES));

// Function prototypes
int menu();
bool fExists (string);
void displayFile (string);
void processFile (string, Stack<int>*);
void processDigit (int, Stack<int>*);
void conclusion(Stack<int>*);

/**~*~*
   The main function allows the user to pick a file and process it using stacks.
*~**/
int main()
{

    for (int i = 0; i < NUM_FILES; i++)
    {
        if (fExists(FILE_NAMES[i]))
        {
            cout<< "\nFile processed: " << FILE_NAMES[i]<<endl;
            Stack<int>* stack = new Stack<int>;
            displayFile (FILE_NAMES[i]);
            processFile(FILE_NAMES[i], stack);
            conclusion(stack);
            delete stack;
        }
        else
            cout << "\nERROR: File " << FILE_NAMES[i]<<" cannot be opened and will be skipped."<<endl;
    }
    cout << "\n\t*** THE END ***\n";
    return 0;
}

/**~*~*
   The processFile function opens each file, processes each inputted file digit by digit, and closes it.
   Inputs: file is file name to process, stack is pointer to stack for this file created in main
   Outputs: (by reference) it makes changes to the stack in main (though the function processDigit)
*~**/
void processFile(string file, Stack<int>* stack)
{
    fstream fileHandle;
    int temp;

    fileHandle.open(file, fstream::in);

    while (fileHandle >> temp) // maybe atoi(temp.c_str());
    {
        processDigit(temp, stack);
    }
    fileHandle.close();
}


/**~*~*
   The processDigit function does a different task as commented below depending on each integer.
   Inputs: n is integer from reading the files, stack is reference to stack in main
   Outputs: (by reference) it makes changes to the stack in main
*~**/
void processDigit (int n, Stack<int>* stack)
{
    if (n==0) // display # elements
    {
        cout<<"The stack has " << stack->getCount()<< " numbers."<<endl;
    }
    else if (n==1) //display top element of stack
    {
        cout<< "The top of the stack contains "<< stack->getTop() << endl;
    }
    else if (n>0) // push number onto stack
    {
        stack->push(n);
    }
    else //n<0 : pop as many numbers as that value from stack
    {
        n = abs(n);

        if (n > stack->getCount())
            cout << "The stack contains less than " << n << " items."<<endl;
        else
        {

            bool status;
            int toPop = 0;
            int popped [n];

            // Pop the item.
            for (int i = 0; i<n ; i++)
            {
                if (stack->pop(toPop))
                    popped[i] = toPop;
            }
            cout << "Popped " << n << " numbers: ";
            for (int i = 0; i < n; i++)
                cout << popped[i]<<" ";
            cout<< endl;

        }
    }
}

/**~*~*
   Check that the file user chose exists.
   Inputs: file name to check if its valid
   Outputs: none
*~**/
bool fExists (string fname)
{
    bool isValid = false;
    ifstream fileHandle(fname);

    if (fileHandle.good())
        isValid = true;
    return isValid;
    fileHandle.close();
}

/**~*~*
   The displayFile function displays the contents of each file by printing them out onto the screen.
   It does not store the digits.
   Inputs: file is file name of file in question.
   Outputs: no output parameters
*~**/
void displayFile (string file)
{
    ifstream fileHandle(file);
    int value =0;
    cout<<endl;
    while (fileHandle>>value)
        cout<< value << " ";
    cout<<endl;
    fileHandle.close();
}

/**~*~*
   The conclusion function draws a conclusion of what is left on the stack.
   Inputs: stack is pointer to stack created in main for that file
   Outputs: no output parameters
*~**/
void conclusion(Stack<int>* stack)
{
    cout<< "END OF FILE: ";
    if (stack->isEmpty())
        cout << "Stack is Empty! "<< endl;
    else
    {
        cout<< "Left on the stack, from the top: ";
        while (!stack->isEmpty())
        {
            int value = 0;
            stack->pop(value);
            cout <<value << " ";
        }
        cout<<endl;
    }
}

/*
OUTPUT BELOW:
File processed: numbers1.txt

10 20 30 1 40 0 50 -2 15 25 -3 60 70
The top of the stack contains 30
The stack has 4 numbers.
Popped 2 numbers: 50 40
Popped 3 numbers: 25 15 30
END OF FILE: Left on the stack, from the top: 70 60 20 10

File processed: numbers2.txt

10 20 30 -6 40 50 -5
The stack contains less than 6 items.
Popped 5 numbers: 50 40 30 20 10
END OF FILE: Stack is Empty!

File processed: numbers3.txt

15 25 35 45 0 1 0 55 65 75 0 1 0 -50 0 1 0 -5 10 40 50 60 70 80 90 0 1 0 -3 13 23 33 43 54 -5 0 1 0 17 27 37 47 57 67 77 87 97 19 29 39 49 59 69 79 89 99 0 1 -6 0 1 14 24 34 44 0 -150 54 64 0
The stack has 4 numbers.
The top of the stack contains 45
The stack has 4 numbers.
The stack has 7 numbers.
The top of the stack contains 75
The stack has 7 numbers.
The stack contains less than 50 items.
The stack has 7 numbers.
The top of the stack contains 75
The stack has 7 numbers.
Popped 5 numbers: 75 65 55 45 35
The stack has 9 numbers.
The top of the stack contains 90
The stack has 9 numbers.
Popped 3 numbers: 90 80 70
Popped 5 numbers: 54 43 33 23 13
The stack has 6 numbers.
The top of the stack contains 60
The stack has 6 numbers.
The stack has 24 numbers.
The top of the stack contains 99
Popped 6 numbers: 99 89 79 69 59 49
The stack has 18 numbers.
The top of the stack contains 39
The stack has 22 numbers.
The stack contains less than 150 items.
The stack has 24 numbers.
END OF FILE: Left on the stack, from the top: 64 54 44 34 24 14 39 29 19 97 87 77 67 57 47 37 27 17 60 50 40 10 25 15

	*** THE END ***

*/
