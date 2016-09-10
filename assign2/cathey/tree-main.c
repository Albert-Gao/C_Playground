#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <getopt.h>
#include <time.h>

#include "tree.h"
#include "mylib.h"

static void print_usage(char* myprog) {
    char* options = "\n\n"
    "Perform various operations using a binary tree.  By default, words\n"
    "are read from stdin and added to the tree, before being printed out\n"
    "alongside their frequencies to stdout.\n\n"
    " -c FILENAME \tCheck spelling of words in FILENAME using words\n"
    "\t\tread from stdin as the dictionary.  Print timing\n"
    "\t\tinfo & unknown words to stderr (ignore -d & -o)\n";

char* options1 = "-d\t\t Only print the tree depth (ignore -o)\n"
    "-f FILENAME \tWrite DOT output to FILENAME (if -o given)\n"
    "-o\t\tOutput the tree in DOT form to file 'tree-view.dot'\n"
    "-r\t\tMake the tree an RBT (the default is a BST)\n\n"

    "-h\t\t Print this message\n";


    fprintf(stderr, "Usage: %s [OPTION]... <STDIN> %s%s\n",myprog, options, options1);

}


static void print_info(int freq, char *word){
    printf("%-4d %s\n",freq,word);
}

int main (int argc, char *argv[]){

    /* Variables used to read text file into hash table. */
    char word[256];
    const char *optstring = "c:df:orh";
    char option;
    tree h;

    /* Default values which are changed by command line switch statement. */
    tree_t tree_type = BST;
    FILE *outfile;
    char* out = NULL;

    /* Variables used for dictionary. */
    FILE *filename;
    int unknown = 0;
    clock_t fill_start,fill_end, search_start, search_end;

    /* Flags changed by command line swicth statement. */
    int cflag = 0;
    int dflag = 0;
    int oflag = 0;

    /* Switch statement to manage command line options. */
    while ((option = getopt(argc,argv,optstring)) != EOF){
        switch(option){
            case'f':
                out = optarg;
                break;

            case 'o':
                oflag = 1;
                break;

            case 'r':
                tree_type = RBT;
                break;

            case 'd':
                dflag = 1;
                break;

            case 'c':
                if (NULL == (filename = fopen(optarg, "r"))) {
                    fprintf(stderr, "%s: can’t find file %s\n", argv[0], argv[1]);
                    return EXIT_FAILURE;
                }
                cflag = 1;
                break;

            case 'h':
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
                break;

            default:
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (out == NULL){
        out = "tree-view.dot";
    }

    h = tree_new(tree_type);

    fill_start = clock();
    while (getword(word, sizeof word, stdin) != EOF){
        h = tree_insert(h,word);
    }
    fill_end = clock();

    if (oflag == 1){
        outfile = fopen(out, "w");
        tree_output_dot(h, outfile);
        fprintf(stderr,"Creating dot file '%s'\n",out );
        fclose(outfile);
    }

    if (cflag == 1){
        dflag = 0;
        oflag = 0;
        search_start = clock();
        while (getword(word, sizeof word, filename) != EOF){
            if (tree_search(h, word) == 0){
                printf("  %s\n", word);
                unknown++;
            }
        }

        search_end = clock();
        fclose(filename);

        fprintf(stderr, "Fill time    : %7f\nSearch time  : %7f\nUnknown words  = %d\n", \
                (fill_end-fill_start)/(double)CLOCKS_PER_SEC,           \
                (search_end-search_start)/(double)CLOCKS_PER_SEC, unknown);
    }

    if (dflag == 1){
        printf("%d\n",tree_depth(h));
    }else if (dflag == 0 && cflag == 0 && oflag == 0){
        tree_preorder(h, print_info);
    }

    tree_free(h);
    return EXIT_SUCCESS;
}


