/*********************************************************************************
** CIS 26B                                                            Spring, 2015
** Advanced C
******************
**
** Homework 5: Binary Search Trees and Queues
    Make a concordance of a file by breaking up the words as tokens and counting
    the number of their appearances, while documenting the page and line number
    of their existance.
**********************************************************************************
**  Written By: Menyaylenko, Elena
**
**  Date:               06/16/2015
**  IDE (compiler):     GNU GCC Compiler, Unix OS
**

    To compile code:
        gcc -std=c99  *.h *.c -o c_hwk5
    To run with arguments:
    ./c_hwk5 le_petit_prince.txt

    To check memory leaks with Valgrind: - no dynamic allocations in this code
        valgrind --tool=memcheck --leak-check=yes ./c_hwk5

    To use gdb debugger:
        cc -g *.c *.h -o c_hwk5
        gdb c_hwk5
        break line_number OR break [file_name]:line_number OR break [file_name]:func_name
        run [args] // if program requires command line args
        print variable_name
        c //continue
        s // step
************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "BST.h"
#include "queue.h"

void get_fnames(char**, char**, int, char**);
void read_file(char*, bstNODE**, FILE_INFO*);
void write_file(char*, bstNODE*, FILE_INFO*);
void tokenize_line(char*, bstNODE**, FILE_INFO*); // insert to BST here
char* get_timeStamp();
void lowercase_string(char**);
char* allocateString(char*, bool);

const int LINE_SIZE = 1024; // characters per line
const int PAGE_SIZE = 40; // lines per page

/**
    Function main takes in command line arguments and prints out the results.
    It puts a time stamp. At the end of execution, it frees dynamically allocated memory.
*/
int main(int argc, char** argv)
{
    // Get file names from user
    char* fname_in = NULL;
    char* fname_out = NULL;
    get_fnames(&fname_in, &fname_out, argc, argv);
    // Build the BST with leafs containing queues
    bstNODE* root = NULL;
    FILE_INFO fileInf = {0,0,0,0};
    read_file(fname_in, &root, &fileInf);
    //printTreeInorder(root);
    write_file(fname_out, root, &fileInf);
    root = freeTree(root);
    free(fname_in);
    free(fname_out);
    return 0;
}

/**
    Function get_timeStamp modifies the value of the char buffer
*/
char* get_timeStamp()
{
    struct tm *timeptr;
    time_t timeval;
    char time_buffer[80];
    time(&timeval);
    timeptr = localtime(&timeval);
    strftime(time_buffer, 80, "%c\n", timeptr);
    char* return_string = allocateString(time_buffer, false);
    return return_string;
}


/** Create a dynamically allocated string
	Pre:  tempString, int (bool really) toLower- because for the text we want words lowered
	Post: string - dynamically allocated
*/
char* allocateString(char tempString[], bool toLower)
{
    // convert to lowercase if needed
    if(toLower)
    {
        int i=0, len = strlen(tempString);
        for(; i<len; i++)
        {
            tempString[i] = tolower(tempString[i]);
        }
        tempString[len] = '\0';
    }
    // delete  junk before and after string
    char invalid_characters[] = ".?!\",'():-";
    while(tempString[0] != '\0' && strchr(invalid_characters, tempString[0]))  // first letter is found in invalid list..
    {
        strcpy(tempString, tempString+1);
    }
    while(tempString[0] != '\0' && strchr(invalid_characters, tempString[strlen(tempString)-1]))  // first letter is found in invalid list..
    {
        tempString[strlen(tempString)-1] = '\0';
    }
    //allocate string
    char* string;
    int   stringSize;
    stringSize = strlen(tempString) + 1;
    string = calloc(stringSize, sizeof(char));
    if(string == NULL)
    {
        printf("Error: not enough memory for string allocation of state/city.\a\n");
        exit(1);
    }
    strcpy(string, tempString);
    return string;
}

/**
    Function get_fnames returns by reference the input and output file names,
    depending on user preference from command line.
	Pre:  fname_in, fname_out, argc, argv
	Post: n/a
*/
void get_fnames(char** fname_in, char** fname_out, int argc, char** argv)
{
    char default_fname_in[] = "le_petit_prince.txt";
    char default_fname_out[] = "out.txt";
    switch(argc)
    {
    case 1: // no args provided: use defaults
    {
        *fname_in = allocateString(default_fname_in, false);
        *fname_out = allocateString(default_fname_out, false);
        break;
    }
    case 2: // only input file provided, so output is default file name
    {
        *fname_in = allocateString(argv[1], false);
        *fname_out = allocateString(default_fname_out, false);
        break;
    }
    case 3: // both input and output file names provided
    {
        *fname_in = allocateString(argv[1], false);
        *fname_out = allocateString(argv[2], false);
        break;
    }
    default:
    {
        fprintf(stderr, "Usage: %s [input_file.txt] [output_file.txt]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    }
}

/**
    Function read_file reads an input file, and passes the line into a function which will tokenize
    the line, in order to fill out the tree. It fills out the file information too into fileInf.
*/
void read_file(char* fname_in, bstNODE** root, FILE_INFO* fileInf)
{
    char line[LINE_SIZE];
    FILE* ifp;
    ifp = fopen(fname_in, "r");
    if(!ifp)
    {
        printf("Error: Cannot open input file %s.\n", fname_in);
        exit(1);
    }
    while(fgets(line, sizeof(line), ifp))
    {
        if(line[0] != '\n') // single newline will go through
        {
            line[strlen(line)-1] = '\0'; // get rid of newline
        }
        tokenize_line(line, root, fileInf);
    }
    fclose(ifp);
}

/**
    Function used to write the lexically parsed file to a new file named by the user (or default).
*/
void write_file(char* fname_out, bstNODE* root, FILE_INFO* fileInf)
{
    FILE* ofp;
    ofp = fopen(fname_out, "w+a");
    if(!ofp)
    {
        printf("Error: Cannot open output file %s.\n", fname_out);
        exit(1);
    }
    char* time = get_timeStamp();
    fprintf(ofp, "\nReport made at: %s\n", time);
    fprintf(ofp, "There are %d distinct tokens, %d pages, %d lines per page.\n", fileInf->num_distinct_words, \
            fileInf->num_pages, PAGE_SIZE);
    fprintf(ofp, "The longest token in this text has %d characters.\n", fileInf->length_longest_word);
    printTreeInorder(root, ofp);
    fclose(ofp);
    free(time);
}

/**
    Function tokenize_line will break a line into words, in order to pass them to a tree building function for the BST.
*/
void tokenize_line(char line[], bstNODE** root, FILE_INFO* fileInf) // also insert tokens to bst/queues
{
    static int total_lines_read =0;
    static int line_num =0;
    static int page_num =0;
    line_num++;
    total_lines_read++;
    if(total_lines_read / PAGE_SIZE - page_num)
    {
        line_num =0;
    }
    page_num = total_lines_read / PAGE_SIZE;
    fileInf->num_lines = total_lines_read;
    fileInf->num_pages = page_num;
    char* word = strtok(line,"\040\t\n,");
    if(word) // first word in the line
    {
        char* new_word = allocateString(word, true);
        insert_bstNode(root, new_word, line_num, fileInf);
        if(strlen(new_word)>fileInf->length_longest_word)
        {
            fileInf->length_longest_word = strlen(new_word);
        }
    }
    while(word) // remaining words in the line
    {
        word = strtok(NULL,"\040\t\n,?!");
        if(word)
        {
            char* new_word = allocateString(word, true);
            insert_bstNode(root, new_word, line_num, fileInf);
            if(strlen(new_word)>fileInf->length_longest_word)
            {
                fileInf->length_longest_word = strlen(new_word);
            }
        }
    }
}

/**
OUTPUT (part of the output as an example):


Report made at: Fri Jun 26 08:24:54 2015

There are 2657 distinct tokens, 38 pages, 40 lines per page.
The longest token in this text has 25 characters.

 538  0.7 0.10 0.28 0.30 0.32 0.36 0.38 1.0 1.2 1.4 1.6 1.8 1.10 1.16 1.18 1.20 1.22 1.24 1.26 1.28 1.32 1.34 1.36 1.38 2.2 2.4 2.6 2.10 2.19 2.21 2.23 2.27 2.29 2.31 2.33 2.35 2.37 2.39 3.1 3.3 3.7 3.9 3.11 3.13 3.15 3.19 3.21 3.24 3.25 3.27 3.29 3.33 4.3 4.7 4.19 4.21 4.23 4.25 4.27 4.29 4.35 4.37 4.39 5.1 5.12 5.17 5.21 5.23 5.25 5.27 5.29 5.33 5.39 6.6 6.8 6.10 6.12 6.14 6.16 6.20 6.22 6.24 6.26 6.28 6.30 6.32 6.34 6.36 7.0 7.4 7.8 7.10 7.12 7.14 7.16 7.20 7.22 7.24 7.34 7.36 8.0 8.2 8.6 8.16 8.18 8.20 8.24 8.28 8.30 8.38 9.9 9.13 9.21 9.23 9.25 9.27 9.29 9.31 9.33 10.4 10.8 10.12 10.16 10.18 10.20 10.22 10.24 10.32 10.34 10.38 11.0 11.2 11.4 11.6 11.10 11.12 11.16 11.18 11.20 11.22 11.24 11.26 11.28 11.30 11.32 11.34 11.36 11.38 12.0 12.2 12.4 12.6 12.8 12.10 12.14 12.16 12.18 12.20 12.22 12.24 12.26 12.30 13.1 13.5 13.7 13.9 13.11 13.25 13.27 13.29 13.31 13.33 14.2 14.4 14.6 14.8 14.10 14.12 14.14 14.16 14.18 14.29 14.31 14.33 14.35 14.36 15.0 15.2 15.4 15.6 15.8 15.10 15.12 15.14 15.16 15.18 15.20 15.22 15.24 15.26 15.28 15.30 15.32 15.34 15.36 15.38 16.0 16.2 16.4 16.6 16.10 16.12 16.14 16.16 16.18 16.20 16.22 16.24 16.26 16.30 16.32 16.34 16.36 16.38 17.0 17.6 17.15 17.19 17.21 17.23 17.25 17.27 17.29 17.31 17.33 17.35 18.1 18.3 18.5 18.7 18.9 18.11 18.13 18.15 18.21 18.23 18.25 18.29 18.31 18.33 18.35 18.37 19.16 19.20 19.22 19.24 19.26 19.28 19.30 19.32 19.34 19.36 19.38 20.0 20.2 20.4 20.6 20.8 20.10 20.12 20.14 20.16 20.18 20.20 20.22 20.26 20.30 20.32 20.34 20.36 20.38 21.0 21.2 21.4 21.6 21.8 21.10 21.12 21.14 21.16 21.18 21.20 21.22 22.1 22.8 22.12 22.14 22.16 22.18 22.20 22.22 22.24 22.26 22.28 22.30 22.32 22.36 22.38 23.0 23.2 23.4 23.8 23.10 23.12 23.14 23.18 23.20 23.22 23.31 23.33 23.35 23.39 24.1 24.3 24.10 24.12 24.14 24.16 24.18 24.20 24.22 24.29 24.33 24.37 24.39 25.1 25.12 25.14 25.16 25.18 25.20 25.22 25.24 25.26 25.28 25.30 25.32 25.34 25.36 25.38 26.0 26.2 26.4 26.6 26.8 26.10 26.13 26.15 26.17 26.19 26.21 26.23 26.25 26.27 26.29 26.31 26.33 26.35 26.37 26.39 27.1 27.5 27.7 27.9 27.11 27.13 27.15 27.19 27.21 27.23 27.25 27.27 27.29 27.33 27.37 28.1 28.3 28.5 28.7 28.9 28.11 28.13 28.20 28.22 28.24 28.28 28.30 28.34 28.36 28.38 29.0 29.2 29.4 29.6 29.8 29.15 29.19 29.21 29.23 29.25 29.34 29.36 29.38 30.0 30.2 30.4 30.6 30.12 30.14 30.18 30.20 30.22 30.26 30.28 30.32 30.36 31.0 31.2 31.6 31.15 31.17 31.21 31.25 31.29 31.33 31.39 32.1 32.3 32.5 32.7 32.9 32.13 32.15 32.17 32.19 32.21 32.23 32.27 32.31 32.34 32.36 32.38 33.2 33.6 33.10 33.12 33.16 33.18 33.22 33.24 33.26 33.33 33.35 33.37 33.39 34.1 34.3 34.9 34.13 34.17 34.19 34.21 34.23 34.29 34.31 34.33 34.39 35.3 35.5 35.9 35.13 35.15 35.17 35.19 35.23 35.25 35.27 35.29 35.31 35.33 35.35 35.39 36.1 36.3 36.5 36.7 36.9 36.13 36.17 36.21 36.23 36.25 36.27 36.31 36.33 36.37 36.39 37.1 37.5 37.9 37.13 37.17 37.19 37.23 37.27 37.31 37.33 37.35 37.37 38.15 38.19
 1 /home/john/statusreport 38.27
 1 06/29/15 38.23
 6 1 0.1 1.10 2.31 2.35 5.12 29.38
 1 1"c'est 5.12
 1 10 9.38
 1 11 12.37
 1 12 14.0
 1 13 14.25
 1 14 17.13
 1 15 19.12
 1 16 21.31
 1 17 22.4
 1 18 23.27
 1 19 24.6
 1 1909 3.37
 1 1920 4.1
 3 2 0.12 0.14 0.24
 1 20 24.25
 1 21 25.10
 1 22 28.16
 1 23 29.11
 1 24 29.30
 1 25 31.11
 1 26 33.31
 1 27 38.4
 1 3 2.15
 1 325 10.0
 1 3251 3.35
 1 326 10.0
 1 327 10.0
 1 328 10.0
 1 329 10.0
 1 330 10.0
 1 4 3.31
 1 5 4.15
 1 6 5.15
 4 612 3.37 4.1 4.3 4.5
 1 7 6.4
 1 8 7.29
 1 9 9.3
 42 a 0.26 1.22 3.35 4.5 4.11 5.5 5.8 7.12 7.20 8.14 11.20 12.8 12.12 12.18 15.0 17.35 18.3 18.5 19.7 19.32 20.14 21.26 22.20 22.22 23.39 26.6 26.17 27.9 27.33 31.23 33.12 36.5 37.33 38.10 38.15 38.17 38.21
 5 a-t-il 4.3 5.12 17.17 38.19
 1 abandonné 0.14
 2 abandonnée 11.20 37.13
 1 abeilles 15.12
 1 aborda 17.19
 1 abritée 27.37
 2 absolu 10.28 11.14
 1 absolument 20.6
 4 absurde 1.4 17.17 30.14
 1 abîme 34.35
 1 acheter 16.6
 1 acheté 4.11
 1 acheva 14.18
 1 achevé 12.24
 1 achètent 26.37
 1 actes 9.0
 3 activité 9.5 20.32
 1 addition 15.0
 2 additions 7.12 7.20
 7 adieu 9.9 9.13 24.1 24.3 27.29 28.1 28.3
 1 admirateur 13.1
 1 admirateurs 13.3
 1 admiration 7.38
 1 admire-moi 13.31
 2 admirer 13.25 13.27
 1 adorent 22.8
 6 afin 0.12 4.11 22.26 28.5 28.9 28.13
 1 afrique 22.18
 1 agacé 8.36
 1 agaçant 9.33
 19 ah 2.31 4.25 5.17 7.36 10.4 13.1 13.9 15.16 19.36 22.20 22.32 25.1 25.26 27.13 29.34 33.22 35.39 37.1
 8 ai 0.9 0.18 4.3 15.0 16.18 23.39 27.33
 1 aider 18.21
 1 aies 34.21
 1 aiguilles 24.8
 1 aiguisées 24.8
 1 aille 3.24
 1 aima 18.21
 2 aime 5.37 7.24
 1 aiment 4.3
 1 aimeras 35.35
 2 aimes 7.26 35.27
 1 aimez 38.17
 4 aimé 4.7 7.12 30.34
 15 ainsi 0.14 0.18 0.26 2.12 2.19 3.33 4.5 4.17 8.10 8.34 12.18 27.11 31.8 31.37
 2 air 12.32 14.6
 1 aisément 22.6
 1 ait 20.28
 10 ajouta 2.33 3.28 4.27 7.6 9.31 25.28 27.27 31.15 32.7 34.27
 1 ajouta-t-il 30.32
 1 ajoutais 5.35
 1 ajouter 38.10
 1 ajouté 8.6
 1 ajustait 7.31
 1 aliment 31.37
 1 allaient 21.39
 1 allait 18.21
 2 aller 3.29 5.31
 2 allons 5.19 10.20
 1 allume 17.17
 3 allumeur 17.15 18.21
 5 allumeurs 21.37 21.39 22.6
 1 allumé 21.39
 1 allé 4.11
 43 alors 0.7 0.12 0.28 1.0 1.4 1.12 1.30 2.25 2.35 3.26 3.39 4.3 4.5 4.11 5.5 6.16 6.18 7.38 8.32 9.0 10.20 10.24 11.30 16.18 18.7 18.9 20.14 20.30 21.39 24.22 25.12 26.29 27.9 27.23 31.13 33.12 34.13 35.35 36.9 36.13 38.10
 1 ambassadeur 12.30
 15 ami 1.20 3.23 4.3 4.11 4.12 18.21 19.5 26.37 27.33 29.36 30.6 36.13
 1 ami..."pour 4.9
 1 amies 35.35
 5 amis 5.12 24.18 25.38 26.35 36.13
 1 amour 8.34
 3 amusant 13.15 17.2 37.23
 1 amélioré 0.18
 2 an 22.1 35.17
 1 ancienne 30.38
 1 animé 5.12
 1 anneau 22.10
 1 annoncer 34.25
 1 année 18.5
 2 années 10.20 23.39
 10 ans 0.3 0.14 0.26 0.34 4.11 15.0 38.6
 1 anéantir 7.20
 1 apaisent 29.17
 1 apercevais 30.16
 1 apercevoir 3.35
 1 aperçu 3.37
 1 aperçus 23.39
 5 aperçut 2.19 10.4 13.3 19.16 32.19
 1 apparaissaient 7.31
 1 apparaître 7.32
 2 apparition 0.36 7.31
 1 apportée 7.31
 1 apprendre 2.25
 4 appris 0.16 0.34 3.33 5.17
 1 apprivoisa 27.11
 1 apprivoise 26.37
 2 apprivoise-moi 26.33 26.37
 1 apprivoiser 33.28
 5 apprivoisé 25.24 26.6 26.29 27.33 28.11
 1 apprivoisées 27.33
 1 approche-toi 10.12
 7 après 3.11 6.28 13.17 25.28 30.26 33.4 34.7
 1 arbre 38.1
 1 arbres 4.31
 5 arbustes 4.21 4.27 4.31 5.10 6.8
 1 armure 7.26
 2 armée 21.37 21.39
 1 arracha 9.7
 2 arracher 5.5 5.8
 1 arriva 24.27
 1 arrivaient 24.8
 1 arrive 22.6
 1 arrosa 9.7
 1 arrosoir 8.8
 1 arrosée 27.37
 15 as 5.27 9.21 9.33 16.22 26.29 27.15 28.7 28.11 30.18 32.38 34.9 35.5
 3 assez 17.2 17.15 18.31
 2 assis 32.13 33.33
 1 assistait 7.31
 2 assister 5.31 11.20
 2 astronome 3.35 3.37
 2 astéroïde 3.37 5.12
 1 astéroïdes 10.0
 1 atteint 31.19
 1 attend 20.28
 4 attendre 5.21 5.23 5.25 34.3
 1 attention 5.12
 1 attentivement 1.14
 51 au 0.14 0.18 0.28 0.36 1.4 2.33 3.35 3.37 4.11 4.17 4.19 4.31 5.17 5.31 6.6 7.10 7.20 8.10 8.34 9.5 11.22 12.0 13.15 13.23 14.4 17.17 18.31 20.28 21.10 24.8 25.5 25.7 26.4 27.29 27.33 29.32 29.34 30.14 30.38 31.0 31.4 31.8 31.21 32.11 34.13 34.15 36.17 38.8 38.10
 2 au-dessus 22.26 35.17
 1 aucun 31.19
 2 aucune 9.21
 1 aujourd'hui 34.29
 2 auprès 30.26 32.13
 2 aurait 4.9 11.20
 5 auras 36.5 36.9 36.13 37.5 37.23
 1 auriez 8.6
 1 aurons 26.4
 33 aussi 0.20 1.4 2.35 3.15 4.11 4.29 5.12 6.8 8.26 9.5 9.7 9.21 17.6 18.31 19.30 20.10 20.36 21.39 22.38 25.5 25.36 27.9 29.34 30.12 30.18 30.22 32.11 34.29 36.31 37.19 37.25 38.17
 3 aussitôt 2.37 5.5 11.18
 1 autorité 10.28
 3 autour 16.30 23.12
 6 autre 0.16 2.39 26.13 31.37
 2 autrefois 18.1 18.21
 13 autres 3.7 4.35 7.31 8.26 11.8 13.3 19.1 21.10 26.29 27.9 27.33
 1 autrui 12.14
 10 aux 0.9 4.3 5.12 5.31 9.29 17.6 31.19 33.20
 1 auxquelles 3.35
 1 auxquels 5.8
 1 avais 34.19
 34 avait 3.39 4.9 5.5 5.10 7.26 7.31 7.32 7.34 8.6 8.8 8.10 8.14 8.16 8.22 8.26 8.32 8.34 12.32 17.4 17.15 19.18 22.10 23.37 25.3 31.19 31.35 33.33 34.37 35.7 37.29
 1 avalait 0.3
 1 avale 29.17
 1 avalent 0.5
 1 avancera 27.5
 3 avant 4.39 12.26 16.22
 35 avec 0.7 0.18 0.26 0.36 1.4 1.20 3.13 3.28 4.3 4.5 4.11 4.31 4.37 6.6 6.28 6.30 7.31 7.34 8.12 9.7 11.4 12.28 17.39 22.30 25.22 25.24 27.9 31.2 32.9 34.13 34.17 35.1 36.13 37.19
 1 aventures 0.7
 1 avertir 5.12
 1 aveugles 32.9
 2 avez 13.5 22.8
 6 avion 2.19 2.23 3.1 29.34
 2 avions 0.16 31.19
 1 avis 4.1
 1 avoir 11.20
 1 avoua 14.14
 6 ayant 8.8 12.24 20.28 21.39 24.27 30.16
 4 b 3.37 4.1 4.3 4.5
 1 baissant 14.14
 1 balivernes 14.35
 1 ballet 21.39
 1 banque 16.32
 3 baobab 4.31 5.5 7.31
 17 baobabs 4.17 4.29 4.31 4.39 5.1 5.5 5.6 5.8 5.10 5.12 9.7 22.8 32.21 32.25
 1 battre 34.19
 4 beau 5.10 9.29 13.27 30.32
 18 beaucoup 0.7 0.16 0.18 0.34 2.0 2.19 2.33 3.35 4.9 5.8 9.5 13.23 22.8 23.39 26.35
 2 beauté 7.32 31.0
 5 belle 4.3 7.31 8.0 19.32 22.28
 2 belles 27.37 30.28
 1 berçai 7.26
 8 besoin 0.12 1.10 4.9 12.16 26.4 29.17
 97 bien 0.20 0.28 0.34 1.22 1.36 3.3 3.13 3.15 3.29 3.35 4.7 4.11 4.21 5.10 5.12 5.19 5.31 7.26 7.31 8.4 8.10 8.22 9.5 9.25 9.29 10.36 11.18 11.36 12.14 12.18 12.20 12.34 13.33 13.37 15.18 16.22 17.17 18.5 19.30 19.32 21.18 21.35 22.8 22.10 23.8 23.20 24.8 25.5 25.7 25.18 25.36 26.4 26.35 27.17 27.21 27.37 28.3 28.28 29.4 29.34 30.6 30.24 30.38 31.6 31.31 31.37 32.5 32.11 33.39 34.3 34.33 34.35 35.7 35.9 35.25 35.29 35.33 36.13 38.6 38.8 38.10 38.12 38.15 38.17
 1 bientôt 8.6
 1 bizarre 33.10
 2 bizarres 13.37 14.22
 6 blé 26.29 27.25
 8 boa 0.3 0.12 1.8 1.10 4.11
 7 boas 0.5 0.14 0.20 0.34 32.32
 1 boirait 20.10
 9 boire 0.26 6.18 29.17 29.34 31.33 34.19 35.31 37.19
 1 bois 14.6
 1 bois-tu 14.8
 2 bon 10.28 34.9
 1 bond 34.13
 1 bonheur 27.5
 13 bonhomme 0.34 0.36 1.4 1.8 3.9 29.38 32.31 34.15 35.5 35.13 35.19 35.39
 21 bonjour 13.5 14.29 14.31 17.21 17.23 17.35 18.37 23.31 23.33 24.10 24.12 24.29 24.33 25.12 25.14 28.18 28.20 29.13 29.15
 8 bonne 8.34 20.18 21.26 22.12 22.14 30.22 31.37 35.31
 3 bonnes 5.5
 2 bonsoir 17.27 18.17
 1 bonté 8.6
 1 bouche 17.8
 2 bouger 0.5 37.39
 4 boulon 6.18 6.22 6.32 7.26
 1 bout 4.31
 2 bouteilles 14.4
 1 bouton 7.31
 1 boîte 4.11
 1 bracelet 23.12
 6 bras 7.26 31.4 31.37 34.15 34.19 34.35
 1 bredouillait 10.26
 1 breveter 16.22
 1 bridge 0.20
 1 brillent 15.10
 3 brindille 5.5 7.31
 1 brindilles 7.31
 1 briques 4.3
 8 bruit 15.0 26.29 34.13 36.39 38.1 38.15
 4 brusquement 2.37 4.19 7.24 7.26
 1 brusquerie 6.6
 1 brûlent 9.5
 1 bu 32.11
 1 bureau 20.6
 10 businessman 14.27 14.38 15.4 16.14 16.26 17.8 17.17 19.1 21.35 36.5
 1 but 31.37
 1 buvant 29.32
 8 buveur 14.2 14.4 14.6 14.10 14.14 14.18 17.17 19.1
 2 bâilla 10.14 11.38
 1 bâillant 7.34
 1 bâille 10.20
 1 bâillements 10.20
 1 bâillent 29.4
 4 bâiller 10.16 10.20 10.24
 1 bélier 1.22
 1 bénie 19.9
 1 bête 23.2
 2 bêtes 9.27 9.29
 1 c'eft 26.0
 1 c'en 33.2
 130 c'est 0.14 0.16 1.10 1.22 1.34 1.38 2.4 2.12 2.19 2.21 2.23 2.31 3.3 3.13 3.27 3.33 4.3 4.5 4.11 4.17 4.21 4.23 5.1 5.8 5.10 6.24 7.12 7.24 7.26 8.6 8.24 9.5 9.29 9.33 10.20 12.14 13.7 13.15 15.18 15.38 16.24 16.26 16.38 17.2 17.6 17.17 17.23 17.27 17.31 17.35 18.5 18.11 18.33 19.1 19.9 19.28 19.30 20.6 20.18 20.22 20.32 21.0 21.10 22.8 22.22 25.12 25.36 26.8 26.21 26.29 27.9 27.15 27.37 28.7 28.9 28.36 29.21 30.6 30.36 31.6 31.21 31.29 33.39 34.33 35.19 35.27 35.31 35.35 36.25 36.31 36.37 37.9 37.27 37.37 38.6 38.8 38.17
 2 c'est-à-dire 21.35 38.8
 1 c'e§t 0.20
 1 c'étaient 5.5
 14 c'était 0.26 9.5 9.35 10.28 11.14 17.15 18.1 21.39 24.31 29.17 30.34 31.37 35.11
 1 c:\home\john\statusreport 38.26
 1 cabine 28.26
 1 cachait 30.38
 1 cache 30.36
 1 cache-nez 34.19
 5 cadeau 27.29 31.37 35.35 36.1
 3 caisse 1.34 3.13 34.39

 VALGRIND OUTPUT:
elena@elena-e5250 ~/CodeBlocksProjects/c_hwk5 $ gcc -std=c99  *.h *.c -o c_hwk5
elena@elena-e5250 ~/CodeBlocksProjects/c_hwk5 $ valgrind --tool=memcheck --leak-check=full ./c_hwk5
==6089== Memcheck, a memory error detector
==6089== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==6089== Using Valgrind-3.10.0.SVN and LibVEX; rerun with -h for copyright info
==6089== Command: ./c_hwk5
==6089==
==6089== Invalid read of size 1
==6089==    at 0x4C2E0E2: strlen (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==6089==    by 0x401669: tokenize_line (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4013F3: read_file (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x400F1F: main (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==  Address 0x51fce10 is 0 bytes inside a block of size 4 free'd
==6089==    at 0x4C2BDEC: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==6089==    by 0x400C6D: insert_bstNode (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x40165D: tokenize_line (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4013F3: read_file (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x400F1F: main (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==
==6089== Invalid read of size 1
==6089==    at 0x4C2E0F4: strlen (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==6089==    by 0x401669: tokenize_line (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4013F3: read_file (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x400F1F: main (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==  Address 0x51fce11 is 1 bytes inside a block of size 4 free'd
==6089==    at 0x4C2BDEC: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==6089==    by 0x400C6D: insert_bstNode (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x40165D: tokenize_line (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4013F3: read_file (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x400F1F: main (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==
==6089== Source and destination overlap in strcpy(0xffefffbf8, 0xffefffbf9)
==6089==    at 0x4C2E272: strcpy (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==6089==    by 0x40109A: allocateString (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x40163F: tokenize_line (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4013F3: read_file (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x400F1F: main (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==
==6089== Invalid read of size 1
==6089==    at 0x4C2E0E2: strlen (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==6089==    by 0x4015EC: tokenize_line (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4013F3: read_file (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x400F1F: main (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==  Address 0x5200510 is 0 bytes inside a block of size 5 free'd
==6089==    at 0x4C2BDEC: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==6089==    by 0x400C6D: insert_bstNode (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4015E0: tokenize_line (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4013F3: read_file (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x400F1F: main (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==
==6089== Invalid read of size 1
==6089==    at 0x4C2E0F4: strlen (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==6089==    by 0x4015EC: tokenize_line (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4013F3: read_file (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x400F1F: main (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==  Address 0x5200511 is 1 bytes inside a block of size 5 free'd
==6089==    at 0x4C2BDEC: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==6089==    by 0x400C6D: insert_bstNode (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4015E0: tokenize_line (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4013F3: read_file (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x400F1F: main (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==
==6089== Source and destination overlap in strcpy(0xffefffbe0, 0xffefffbe1)
==6089==    at 0x4C2E272: strcpy (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==6089==    by 0x40109A: allocateString (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4015C2: tokenize_line (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x4013F3: read_file (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==    by 0x400F1F: main (in /home/elena/CodeBlocksProjects/c_hwk5/c_hwk5)
==6089==
==6089==
==6089== HEAP SUMMARY:
==6089==     in use at exit: 0 bytes in 0 blocks
==6089==   total heap usage: 29,497 allocs, 29,497 frees, 408,267 bytes allocated
==6089==
==6089== All heap blocks were freed -- no leaks are possible
==6089==
==6089== For counts of detected and suppressed errors, rerun with: -v
==6089== ERROR SUMMARY: 58060 errors from 6 contexts (suppressed: 0 from 0)
elena@elena-e5250 ~/CodeBlocksProjects/c_hwk5 $
*/
