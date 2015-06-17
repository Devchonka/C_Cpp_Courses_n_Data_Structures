/**
 This is ch 5 of the Advanced C book.
 Topic: Advanced Input and Output, hashing to disk,non-decimal i/o, assignment suppression on input,
 output field justification, string output, scan sets, escape sequences.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fileHandle_ex0();
void hash_ex0();

int main()
{
    //fileHandle_ex0();
    hash_ex0();

    return 0;
}

void fileHandle_ex0()
{
    char fname[] = "output.dat";
    FILE* fp;
    int i[] = {1,2,3,4,5}, j[5], k, *pWalk_j;
    long pos;

    if ((fp = fopen(fname, "w+b")) == NULL)
    {
        printf("Could not open %s.\n", fname);
        exit(1);
    }
    fwrite(i, sizeof(int), 5, fp); // write from i into the file
    rewind(fp); // back to first byte
    fread(j, sizeof(int), 5, fp); // read into j from file
    for (pWalk_j = j, k=0; k<5; k++, pWalk_j++)
    {
        printf("j[%d] = %d\n", k, *pWalk_j);
    }
    fseek(fp, 2*sizeof(int), SEEK_SET); // point at 3rd element (3)
    k=6;

    fwrite(&k, sizeof(int), 1, fp); // overwrite 3 with 6
    fseek(fp, -1*sizeof(int), SEEK_CUR); // is 6 there?
    k = 0;
    fread(&k, sizeof(int), 1, fp);
    printf(" Overwrote: %d\n", k);
    k = 13;
    fseek(fp,-1*sizeof(int), SEEK_END);
    fwrite(&k, sizeof(int), 1, fp);
    fseek(fp,-1*sizeof(int), SEEK_END);
    fread(&k, sizeof(int), 1, fp);
    printf(" Overwrote: %d\n", k);

    pos = ftell(fp); // byte offset from file start

    printf("We are %ld bytes from file start, and # elements: %d.\n", pos, pos/sizeof(int));
}

void hash_ex0()
{
    struct record
    {
        char key[50];
    };

    FILE* fp;
    char* fname = "file.dat";
    struct record hashtable[100] = {""};
    struct record temprec;
    long hash =0;
    char line[100], *pWalk;

    fp = fopen(fname, "w+b"); // write, read binary file

    while (printf("Enter Key: "), fgets(line, sizeof(line), stdin), strcmp(line, "quit\n")!=0)
    {
        hash =0;
        for (pWalk = line; *pWalk != '\0'; pWalk++)
        {
            hash = hash + (*pWalk) * (*pWalk) * (*pWalk);
        }
        hash = hash % 100;
        strcpy(hashtable[hash].key, line);
        printf("Hash value on output is: %ld \n", hash);
    }

    fwrite(hashtable, sizeof(struct record),sizeof(hashtable), fp);
    printf("\nEnd of writing to file.. \n Starting to read file.. \n\n");

    while(printf("Enter Key: "), fgets(line, sizeof(line), stdin), strcmp(line, "quit\n") !=0)
    {
        hash =0;
        for (pWalk = line; *pWalk != '\0'; pWalk++)
        {
            hash = hash + (*pWalk) * (*pWalk) * (*pWalk);
        }
        hash = hash % 100;
        fseek (fp, hash * sizeof(struct record), SEEK_SET);
        fread (&temprec, sizeof(struct record), 1, fp); // if 1st byte is zero, then record isnt there
        if (memcmp(&temprec, "", 1) ==0)
        {
            printf("Record not found!\n");
        }
        printf("Hash value on input is: %ld Key is: %s \n", hash, temprec.key);
    }
}
