/**
 A simple message table for errors.
*/

#ifndef VALIDATION_H
#define VALIDATION_H

/**
 Enum class for set of errors that could be encountered from user input.
*/
enum class Error
{
    BAD_IFILE, BAD_OFILE, BAD_INPUT, BAD_SEARCH, ERROR_COUNT
};

/**
 Prints out the Error selected.
*/
const char* const ErrorTable[ static_cast<int>(Error::ERROR_COUNT) ]  =
{
    "\n  Error: Please enter a valid input file.\n",
    "\n  Error: Please enter a valid output file.\n",
    "\n  Error: Bad input, press 'M' for menu.\n",
    "\n  Error: No year from searched movie is found.\n"
} ;

void printErrorMsg(Error);

#endif // VALIDATION_H
