/**
 This is a set of functions in use for the line text editor program.
*/

#include <iostream>
#include <exception>
#include <string>
#include <cctype>
#include <iomanip>
#include <fstream>
#include "cvalidation.h"
#include "CircDoublyList.h"
using namespace std;

const string FILENAME = "input.txt";

/**
 Prints out error message from cvalidation.h
*/
void printErrorMsg(Error msg)
{
    cout << ErrorTable[static_cast<int>(msg)] << endl;
}

/**
 Returns True if index provided in (string form) is a valid integer value within the list, False otherwise.
*/
bool validIndex(string ind, CircDoublyList<string>* doubly)
{
    bool isDigits = false; // check that whole string is numeric
    unsigned int i=0;
    for (i = 0; i < ind.size(); i++)
    {
        if (!isdigit(ind[i]))
        {
            break;
        }
    }
    if (i==ind.size()) // if reached the end, whole string numeric
        isDigits = true;

    return (isDigits && (stoi(ind)>0) && (stoi(ind) <= doubly->getCount())); // check also that valid index
}

/**
 Takes in part of a string, and extracts the characters until the first whitespace, then converts to integers.
 Changes the pos by reference, if exception is not thrown.
*/
bool nextPos(string input, int& pos) // trying to put together functions
{
    try
    {
        pos = stoi(input.substr(0, input.find_first_of(" "))); // make it catch if not digits
    }
    catch (exception& e)
    {
    }
    return (pos); // whether position was set
}

/**
 Validates whether the first letter user input is valid.
 Returns true if the first letter is a simple(TFBHAQ) command, then the second is ENTER.
 Returns true if the first letter if a complex (ILDS) command and the second is SPACE.
 Otherwise returns false.
*/
bool validLetter(char c1, char c2)
{
    bool validChoice = false;
    string ezChar = "TFBHAQ", oChar = "ILDSW";
    if ((ezChar.find(toupper(c1)) != std::string::npos) && c2 =='\0') // if easy letter, ENTER
        validChoice = true;
    else if ((oChar.find(toupper(c1)) != std::string::npos) && c2 ==' ') // if other letter, SPACE
        validChoice = true;
    else
        printErrorMsg(Error::BAD_INPUT);
    return validChoice;
}

/**
 Parses the user input into bits - position integers and the text.
 Calls functions to validate integer positions.
 It then sets the text or line positions by reference, if the command was complex (TFBHAQ).
*/
bool parseInput(CircDoublyList<string>* doubly, string input, int& pos1, int& pos2, string& text)
{
    bool isValid = false;

    if (validLetter(input[0], input[1]))
    {
        switch (toupper(input[0]))
        {
        case 'T':
        case 'F':
        case 'B':
        case 'H':
        case 'A':
        case 'Q':
        {
            isValid = true;
            break;
        }
        case 'I': // sets text of line to insert to list
        {
            if(nextPos(input.substr(2), pos1) && validIndex(to_string(pos1), doubly))
                text = input.substr(2).substr(input.substr(2).find_first_of(" ")+1); // +3 for first char, 1st space, and 1 after 2nd space
            isValid = true;
            break;
        }
        case 'S': // sets text of output file name
        {
            text = input.substr(2);
            isValid = true;
            break;
        }
        case 'L': // set pos1, pos2
        case 'D':
        case 'W':
        {
            if(nextPos(input.substr(2), pos1) && nextPos(input.substr(3+input.substr(2).find_first_of(" ")), pos2))
            {
                if (validIndex(to_string(pos1), doubly) && validIndex(to_string(pos2), doubly))
                {
                    isValid = true;
                }
                else
                    printErrorMsg(Error::BAD_INPUT);
            }
            break;
        }
        }
    }
    return isValid;
}

/**
 Prints the available commands out on the screen.
*/
void help()
{
    int w1 = 30, w2 = 10;
    cout<< endl;
    cout << setw(w1) << left << "T: " << setw(w2) << left << "Display the total number of lines in the text" << endl;
    cout << setw(w1) << left << "F: " <<  setw(w2) << left << "Print all lines from first to last "<< endl;
    cout << setw(w1) << left << "B: " <<  setw(w2) << left << "Print all lines from last to first"<< endl;
    cout << setw(w1) << left << "I <line #> <text>: " <<  setw(w2) << left << "Insert text at given line number in the list"<< endl;
    cout << setw(w1) << left << "L <line #1> <line #2>: " <<  setw(w2) << left << "List lines, inclusive, from line #1 to line #2"<< endl;
    cout << setw(w1) << left << "W <line #1> <line #2>: " <<  setw(w2) << left << "Swap line #1 and line #2"<< endl;
    cout << setw(w1) << left << "D <line #1> <line #2>: " <<  setw(w2) << left << "Delete lines, inclusive, from line #1 to line #2"<< endl;
    cout << setw(w1) << left << "S <output file name>: " <<  setw(w2) << left << "Save updated text to an output file"<< endl;
    cout << setw(w1) << left << "H: " <<  setw(w2) << left << "(Help) Display available command instructions"<< endl;
    cout << setw(w1) << left << "A: " <<  setw(w2) << left << "(About) Display information about the developer"<< endl;
    cout << setw(w1) << left << "Q: " <<  setw(w2) << left << "Quit editing the file (don’t forget to save it)"<<endl;
}

/**
 Populates linked list with entries by inserting nodes line by line from input text file.
*/
bool populateList(CircDoublyList<string>* doubly)
{
    ifstream fileHandle;
    fileHandle.open(FILENAME);

    bool ableToPopulate = fileHandle.good();
    if (ableToPopulate)
    {
        string line = "";
        int pos = 1;
        while (getline (fileHandle, line))
        {
            doubly->insertNode(line, pos++);
        }
        fileHandle.close();
    }
    else
        printErrorMsg(Error::BAD_IFILE);
    return ableToPopulate;
}

/**
 Saves contents of linked list into an output file name fname.
*/
bool saveOutput(CircDoublyList<string>* doubly, string fname)
{
    fstream fileHandle;
    fileHandle.open(fname, fstream::out);
    bool ableToSave = fileHandle.good();

    if (ableToSave)
    {
        doublyNode<string>* currPtr = doubly->getHead()->_fwd; // save output function needs access to node ptr
        int nodesLeft = doubly->getCount();
        while (nodesLeft)
        {
            fileHandle << currPtr->_line <<"\n";
            currPtr = currPtr->_fwd;
            nodesLeft--;
        }
        cout << "Output Saved!" << endl;
    }
    else
        printErrorMsg(Error::BAD_OFILE);
    fileHandle.close();
    return ableToSave;
}

/**
 Prints out information about the developer.
*/
void about()
{
    cout << endl;
    cout << "Developer information: " << endl;
    cout << "Elena Menyaylenko\n"<< "CIS 22C\n" << "Fall 2015\n" << "De Anza College" << endl;
}

/**
 Loop to continue getting commands while user input not valid.
*/
char command(int& pos1, int& pos2, string& text, CircDoublyList<string>* doubly)
{
    string input;
    do
    {
        cout<<" >> ";
        getline(cin,input);
    }
    while (!parseInput(doubly, input, pos1, pos2, text));
    return toupper(input[0]); // return it as char
}

/**
 Loop to process validated user input.
 Function calls various linked list functions to implement what user asks for.
*/
void processCommand(CircDoublyList<string>* doubly)
{
    bool inProgress = true;
    while (inProgress)
    {
        int pos1 = 0, pos2 = 0;
        string text ="";
        char user = command(pos1, pos2, text, doubly);

        switch (user)
        {
        case 'T':
        {
            cout<< "Text contains " << doubly->getCount() << " lines."<<endl;
            break;
        }
        case 'F':
        {
            doubly->displayList(1, doubly->getCount());
            break;
        }
        case 'B':
        {
            doubly->displayList(doubly->getCount(),1);
            break;
        }
        case 'I':
        {
            if (!text.empty())
            {
                if (doubly->insertNode(text, pos1))
                    cout << "Inserted "<<text<<" at line "<<pos1<<endl;
            }
            else
                printErrorMsg(Error::BAD_INPUT);

            break;
        }
        case 'L':
        {
            doubly->displayList (pos1, pos2);
            break;
        }
        case 'D':
        {
            if (pos1 && pos2)
            {
                if (pos1<=pos2)
                {
                    for (int i = pos1; i<=pos2; i++)
                        doubly->deleteNode(i);
                    cout << "Deleted node "<<pos1<<" to "<<pos2<<endl;
                }
                else
                {
                    for (int i = pos1; i>=pos2; i--)
                        doubly->deleteNode(i);
                    cout << "Deleted node "<<pos1<<" to "<<pos2<<endl;
                }
                break;
            }
        }
        case 'S':
        {
            saveOutput(doubly, text);
            break;
        }
        case 'H':
        {
            help();
            break;
        }
        case 'A':
        {
            about();
            break;
        }
        case 'W':
            {
                doubly->swapNode(pos1,pos2);
                break;
            }
        case 'Q':
            inProgress = false;
        }

    }
}
