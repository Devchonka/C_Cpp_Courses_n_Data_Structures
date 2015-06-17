/*********************************************************************************
** CIS 26B                                                            Spring, 2015
** Advanced C
******************
**
** Homework 5: Binary Search Trees and Queues
**********************************************************************************
**  Written By: Menyaylenko, Elena
**
**  Date:               06/16/2015
**  IDE (compiler):     GNU GCC Compiler, Unix OS
**


    To compile code:
        gcc -std=c99  *.h *.c -o c_hwk5
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
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "BST.h"
#include "queue.h"

void get_fnames(char*, char*, int, char**);
void read_file(char*, bstNODE**);
void tokenize_line(char*, bstNODE**); // insert to BST here
char* lowercase(char*);
void delete_trailingJunk(char[]);

const int LINE_SIZE = 1024; // characters per line
const int PAGE_SIZE = 60; // lines per page

/**
    Function main takes in command line arguments and prints out the results.
    It puts a time stamp. At the end of execution, it frees dynamically allocated memory.
*/
int main(int argc, char** argv)
{
    struct tm *timeptr;
    time_t timeval;
    char buffer[80];
    time(&timeval);
    timeptr = localtime(&timeval);
    strftime(buffer, 80, "%c\n", timeptr);
    printf("-------------------------\n %s\n", buffer);
    char fname_in[256]="";
    char fname_out[256]="";
    get_fnames(fname_in, fname_out, argc, argv);
    bstNODE* root = NULL;
    read_file(fname_in, &root);
    printTreeInorder(root);
    root = freeTree(root);
    return 0;
}

/**
    Function get_fnames returns by reference the input and output file names,
    depending on user preference from command line.
	Pre:  fname_in, fname_out, argc, argv
	Post: n/a
*/
void get_fnames(char* fname_in, char* fname_out, int argc, char** argv)
{
    char default_fname_in[] = "le_petit_prince.txt";
    char default_fname_out[] = "out.txt";
    switch(argc)
    {
    case 1:
    {
        strcpy(fname_in, default_fname_in);
        strcpy(fname_out, default_fname_out);
        break;
    }
    case 2:
    {
        strcpy(fname_in, argv[1]);
        strcpy(fname_out, default_fname_out);
        break;
    }
    case 3:
    {
        strcpy(fname_in, argv[1]);
        strcpy(fname_out, argv[2]);
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
    the line, in order to fill out the tree.
*/
void read_file(char* fname_in, bstNODE** root)
{
    char line[LINE_SIZE];
    FILE* ifp;
    ifp = fopen(fname_in, "r");
    if(!ifp)
    {
        printf("Error: Cannot open file.\n");
    }
    while(fgets(line, sizeof(line), ifp))
    {
        if(line[0] != '\n') // single newline will go through
        {
            line[strlen(line)-1] = '\0'; // get rid of newline
        }
        tokenize_line(line, root);
    }
    fclose(ifp);
}

/**
    Function tokenize_line will break a line into words, in order to pass them to a tree building function for the BST.
*/
void tokenize_line(char line[], bstNODE** root) // also insert tokens to bst/queue
{
    static int line_num =0;
    static int page_num =0;
    char* word = strtok(line,"\040\t\n,");
    if(word) // first word in the line
    {
        delete_trailingJunk(word);
        char* new_word = lowercase(word);
        insert_bstNode(root, new_word, line_num, page_num);
    }
    while(word) // remaining words in the line
    {
        word = strtok(NULL,"\040\t\n,");
        if(word)
        {
            delete_trailingJunk(word);
            char* new_word = lowercase(word);
            insert_bstNode(root, new_word, line_num, page_num);
        }
    }
    line_num++;
    page_num = line_num / LINE_SIZE;
}

/**
    Function lowercase lowers all the letters in a string passed to it, and returns a pointer to a dynamically
    allocated array of characters for the minimum length of a string.
*/
char* lowercase(char str[]) // also dynamically allocates memory for new string
{
    char* lowered_string ="";
    if(str)
    {
        int length = strlen(str);
        lowered_string  = (char*) malloc((1+length) * sizeof(char));
        if(!lowered_string)
        {
            printf("Error: Fatal error in string malloc.\n");
            return NULL;
        }
        int i=0;
        for(; i<length; i++)
        {
            lowered_string[i] = tolower(str[i]);
        }
        lowered_string[length] = '\0';
    }
    return lowered_string;
}

/**
    Function to get rid of trailing unneeded chars. Currently implemented for dot.
*/

void delete_trailingJunk(char word[])
{
    while(word[strlen(word)-1] == '.' || word[strlen(word)-1] == '?' || word[strlen(word)-1] == '"')
    {
        word[strlen(word)-1] = '\0';
    }
}


/**
OUTPUT:

-------------------------
 Tue Jun 16 22:32:29 2015

...

...
 4 seuls
 67 si
 1 sibérie
 1 sienne
 2 signifie
 3 signifie"apprivoiser
 1 signifie"créer
 1 signifie"oui
 1 signifie"qui
 3 signifie"éphémère
 10 silence
 3 simple
 3 simplement
 2 simples
 1 simplicité
 1 simplifié
 2 sinon
 2 sire
 13 six
 1 sixième
 1 siégeait
 1 soi
 2 soi-même
 3 soient
 8 soif
 1 soigner
 2 soigneusement
 1 soin
 9 soir
 1 sois
 1 soit
 1 soixante-deux
 1 soixante-douze
 1 soi£
 1 sol
 22 soleil
 1 solliciter
 2 sommes
 46 son
 1 songeant
 1 songé
 43 sont
 1 sont-elles
 1 sortant
 1 sorte
 1 sortes
 2 sorti
 1 sortir
 1 sortirait
 2 sortis
 1 sot
 1 sotte
 2 soucieux
 2 soudain
 1 souffla
 1 souffrir
 1 souhaitais
 1 soulevai
 2 soulevant
 2 soupir
 1 soupira
 1 source
 1 sourire
 1 sourires
 2 sourit
 10 sous
 1 souvenais
 5 souvenir
 4 souvenirs
 1 souviens
 1 souvint
 1 soyez
 1 splendide
 3 stupéfait
 1 stylographe
 4 su
 2 sud
 1 suffira
 1 suffirait
 1 suffisait
 5 suffit
 41 suis
 1 suis-je
 1 suivante
 2 sujet
 1 sujets
 1 supportais
 1 supporte
 66 sur
 1 sur"les
 1 surprendre
 5 surpris
 1 surprise
 2 surtout
 1 surveille
 1 surveillé
 1 sèche
 1 sérieuse
 4 sérieuses
 15 sérieux
 22 sûr
 1 sûr"et
 1 sûrement
 1 t'admire
 2 t'ai
 1 t'aider
 1 t'aime
 1 t'apprivoise
 2 t'asseoir
 1 t'assoiras
 1 t'attends
 1 t'aurai
 1 t'avais
 1 t'emporter
 1 t'en
 1 t'entendre
 1 t'intéresser
 4 t'ordonne
 18 ta
 1 table
 1 tabouret."d'une
 1 tailla
 1 taille
 1 taire
 4 taisais
 1 taisent
 1 tandis
 6 tant
 6 tantôt
 5 tard
 4 tas
 30 te
 1 tel
 16 tellement
 1 tempes
 14 temps
 2 tenaient
 1 tenait
 1 tendresse
 2 tenir
 1 tentatives
 1 terminé
 22 terre
 1 terrible
 2 terribles
 1 terrier
 6 tes
 1 tien
 1 tienne
 1 tiennes
 2 tiens
 4 tigres
 2 timidement
 1 tirant
 3 tirer
 1 tiroir
 1 tiré
 24 toi
 2 toi-même
 3 toilette
 1 toit..."elles
 1 tolère
 1 tolérait
 2 tomba
 2 tombe
 5 tombé
 1 tombée
 7 ton
 2 tonnerre
 3 tort
 1 toucha
 1 touche
 22 toujours
 1 toujours)
 8 tour
 1 tourmenta
 1 tourmenté
 1 tournent
 1 tourné
 11 tous
 1 toussa
 1 tousserait
 1 toussé
 55 tout
 14 toute
 23 toutes
 1 toux
 1 trace
 1 tracer
 1 tragédie
 1 trains
 1 traiteront
 2 tranquille
 6 travail
 1 travaillaient
 1 travailler
 2 travaillé
 1 travaux
 2 travers
 1 traversa
 1 traîne
 1 tremblaient
 1 tremblait
 2 trembler
 6 trente
 1 trie
 8 triste
 15 trois
 3 troisième
 1 trompaient
 1 trompe
 1 tromperai
 1 trompé
 28 trop
 3 troupeau
 1 trous
 2 trouva
 1 trouvais
 1 trouvait
 3 trouve
 3 trouvent
 1 trouver
 1 trouvera
 2 trouves
 2 trouvé
 49 très
 3 trésor
 1 trône
 136 tu
 2 turc
 2 turent
 1 tus
 2 tut
 1 tué
 2 tâche
 1 tâtonne
 2 télescope
 6 tête
 233 un
 123 une
 6 unique
 1 universel
 2 uns
 5 utile
 6 va
 2 va-t'en
 1 vacances
 4 vais
 1 valait
 1 valu
 12 vaniteux
 1 vanité
 1 vanter
 3 vas
 1 vaste
 1 venais
 6 venait
 1 vends-tu
 2 venin
 2 venir
 7 vent
 1 venue
 2 verras
 2 verre
 1 verrez
 16 vers
 1 verseront
 1 verte
 1 verticalement
 6 veut
 10 veux
 5 veux-tu
 1 vexé
 1 vexée
 1 vide
 2 vides
 12 vie
 2 vieille
 1 vieilles
 1 vieillir
 1 viendrait
 10 viens
 5 viens-tu
 1 vierge
 1 vierges
 1 vies
 9 vieux
 1 vigne
 1 vilain
 3 village
 3 villes
 3 vingt
 5 vingt-deux
 1 vingt-huit
 1 vingt-quatre
 1 vingt-six
 1 vint
 1 vis
 1 visage
 4 visite
 2 visiter
 1 vit
 5 vite
 1 vitres
 1 vivant
 1 vive
 4 voici
 1 voie
 2 voient
 7 voilà
 8 voir
 3 vois
 6 voit
 4 voix
 1 volais
 4 volcan
 1 volcaniques
 12 volcans
 1 vole
 1 voler
 1 volonté
 1 volé
 1 vont
 4 votre
 1 voudrais
 3 voudras
 3 voulais
 4 voulait
 1 vouloir
 1 voulu
 2 voulut
 49 vous
 7 voyage
 2 voyagent
 1 voyager
 2 voyageurs
 1 voyagé
 3 voyais
 2 voyait
 1 voyons!"comme
 8 vrai
 5 vraiment
 12 vu
 1 vues
 2 vécu
 1 vécues
 1 vénus
 3 véritable
 1 véritablement
 1 vérité
 1 vît
 27 y
 10 yeux
 6 À
 23 Ça
 1 États-unis
 1 Évidemment
 172 à
 2 âge
 2 ç'a
 63 ça
 1 ça:
 1 ébauchaient
 1 ébauches
 1 échange
 1 échapper
 1 éclair
 1 éclairées
 2 éclat
 1 éclata
 1 éclater
 1 économie
 2 écorce
 1 écorces
 2 écouter
 1 écouté
 1 écoutée
 1 écrasent
 1 écrivait
 1 écrivons
 1 également
 2 égaré
 1 églises
 1 éloignée
 1 élèvent
 1 élégant
 3 éléphant
 1 émerveilla
 1 émouvante
 1 ému
 1 énigmes
 1 énorme
 1 énormément
 1 épargne
 2 épaules
 1 éphémère
 1 éphémères
 12 épines
 1 époque
 1 épouvantable
 2 éruptions
 5 étaient
 2 étais
 45 était
 2 éteignit
 1 éteindre
 7 éteint
 1 éteinte
 2 éteints
 1 éternel
 1 éternelles
 1 étions
 7 étoile
 34 étoiles
 1 étoiles-là
 1 étonnés
 1 étrange
 1 étranges
 1 étudié
 13 été
 1 évadé
 1 évasion
 1 éveillés
 1 évidence
 5 êtes
 5 êtes-vous
 11 être
 1 île
 1 îlot
*/
