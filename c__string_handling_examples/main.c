#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strchr_ex_0(); // address of character in string
void strstr_ex_0(); // substrings in string
void strstr_ex1(); // counts # times substring occurs in string
void strspn_ex0(); // given an allowed set, how many characters to skip until it finds char in set (c is complement, opp)
void strbrk_ex0();

int main()
{
    //strchr_ex_0();
    //strstr_ex_0();
    //strstr_ex1();
    //strspn_ex0();
    strbrk_ex0();
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

void strbrk_ex0()
{



}
