#include <stdio.h>
#include <stdlib.h> // for exit func
#include <string.h>
#include <ctype.h> // for isdigit()

void strchr_ex_0(); // address of character in string
void strstr_ex_0(); // substrings in string
void strstr_ex1(); // counts # times substring occurs in string
void strspn_ex0(); // given an allowed set, how many characters to skip until it finds char in set (c is complement, opp)
void strpbrk_ex0(); // count # sentences in string : tokenize
void strchr_ex1(); // parse whats in string between 2 # characters

int main()
{
    //strchr_ex_0();
    //strstr_ex_0();
    //strstr_ex1();
    //strspn_ex0();
    //strpbrk_ex0();
    strchr_ex1();
    return 0;
}

void strchr_ex_0() // find all 'o' in string
{
    char s1[] ="I am the one, the only one.";
    char *ptr1, *ptr2;
    ptr1 = strchr(s1, 'o');
    ptr2 = strrchr(s1,'o');
    printf("The string is: %s\n", s1);
    printf("Address of beginning of s1 is: %p\n", s1);
    for(ptr1 =s1; (ptr1= strchr(ptr1,'o')) != NULL; ptr1++) // interesting condition to skip to every 'o' !!
    {
        printf("Address of current 'o' is %p \n", ptr1);
    }
}

void strstr_ex_0() // look for substrings
{
    char a[] = "cat", b[] = "cattle", c[] = "concatenate", d[] = "foobar";
    printf("Address of b = %p\n\
           Address of c = %p\n\
           Address of d = %p\n\
           Address of a in c = %p\n\
           Address of a in d = %p\n", b,c,d,strstr(c,a), strstr(d,a));
}

void strstr_ex1() // count # times substring occurs in string
{
    char string[] = "Mississippi is my sister state", substring[] = "is", *pWalk = string;
    int count = 0;
    while(pWalk = strstr(pWalk, substring))
    {
        count++;
        pWalk+= strlen(substring);
    }
    printf("'%s' appears %d times in the string '%s'\n", substring, count, string);
}

void strspn_ex0() // count where a character appears in a string from an allowed set
{
    char sentence[] = "Hello, I am John!";
    char nonsense[] = "~*%#";
    char letters[] = "ABCDEFGHIJKLMNOPQRTSUVWXYZ\
                        abcdefghijklmnopqrstuvwxyz";
    int num_not_skipped = strspn(sentence, nonsense);
    int num_skipped = strcspn(sentence, nonsense); // NOTE: c is the COMPLEMENT, OR OPPOSITE OF STRSPN
    printf("%d chars were skipped intil nonsense was found in sentence '%s'\n", num_skipped, sentence);
    printf("%d chars were NOT skipped intil nonsense was found in sentence '%s'\n", num_not_skipped, sentence);
}

void strpbrk_ex0() // count # sentences in a file
{
#define BIGLINE 1024 // define size of a long line
    int num_sentences =0;
    char* fname = "strbrk_example.dat";
    char line[BIGLINE], *pWalk;
    FILE* fp;
    if((fp = fopen(fname, "r")) ==NULL)
    {
        printf("Fail to open file\n");
        exit(1);
    }
    while(fgets(line, BIGLINE-1, fp))
    {
        for(pWalk = line; pWalk = strpbrk(pWalk, "?!."); pWalk++)
        {
            if(!isdigit(pWalk[1]))
            {
                num_sentences++;
            }
            for(; pWalk[1] =='?' || pWalk[1] == '!'; pWalk++) {}
        }
    }
    printf("File has %d sentences in it.\n", num_sentences);
}

void strchr_ex1() // extract whats in string between 2 # characters
{
    char line[80], *ptr1, *ptr2;

    while(gets(line), strcmp(line,"quit"))
    {
        ptr1 = strchr(line, '#');
       if (ptr1)
        {
            ptr1++;
            ptr2 = strchr(ptr1,'#');
        }
        if (!ptr1 || !ptr2)
        {
            printf("String needs 2 '#' characters!\n");
            continue;
        }
        printf("%.*s\n\n", ptr2-ptr1, ptr1);
    }
}
