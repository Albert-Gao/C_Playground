#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <getopt.h>
#include <time.h>

#include "htable.h"
#include "mylib.h"

static void print_usage(char* myprog) {

    char* options =  "\n\n"
        "Perform various operations using a hash table.  By default, words are\n"
        "read from stdin and added to the hash table, before being printed out\n"
        "alongside their frequencies to stdout.\n\n"

        " -c FILENAME  \tCheck spelling of words in FILENAME using words\n"
        "\t\tfrom stdin as dictionary.  Print unknown words to\n"
        "\t\tstdout, timing info & count to stderr (ignore -p)\n";

    char* options1 = " -d            \tUse double hashing (linear probing is the default)\n"
        " -e            \tDisplay entire contents of hash table on stderr\n"
        " -p            \tPrint stats info instead of frequencies & words\n"
        " -s SNAPSHOTS \tShow SNAPSHOTS stats snapshots (if -p is used)\n"
        " -t TABLESIZE \tUse the first prime >= TABLESIZE as htable size\n\n"

        " -h           \tDisplay this message\n";

    fprintf(stderr, "Usage: %s [OPTION]...<STDIN> %s%s\n",myprog, options, options1);

}


static void print_info(int freq, char *word){
    printf("%-4d %s\n",freq,word);
}

static int is_prime(int n){
    /* 0 is false 1 is true. */

    int i = 5;

    if (n <= 1){
        return 0;
    }
    else if (n <= 3){
        return 1;
    }
    else if (n % 2 == 0 || n % 3 == 0){
        return 0;
    }

    while (i*i <= n){
        if (n % i == 0 || n % (i + 2) == 0){
            return 0;
        }
        i += 6;
    }
    return 1;
}

static int find_prime(int n){

    if (n%2 == 0){
        n++;
    }

    while (is_prime(n) == 0){
        n +=2;
    }

    return n;
}

int main (int argc, char *argv[]){

    /* Variables used to read text file into hash table. */
    char word[256];
    const char *optstring = "c:dehps:t:";
    char option;
    htable h;

    /* Default values which are changed by command line switch statement. */
    hashing_t type = LINEAR_P;
    int size = 0;
    int snapshots = 10;

    /* Variables used for dictionary. */
    FILE *filename;
    int unknown = 0;
    clock_t fill_start,fill_end, search_start, search_end;

    /* Flags changed by command line swicth statement. */
    int pflag = 0;
    int cflag = 0;
    int eflag = 0;


    /* Switch statement to manage command line options. */
    while ((option = getopt(argc,argv,optstring)) != EOF){
        switch(option){
            case 'h':
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
                break;

            case 'd':
                type = DOUBLE_H;
                break;

            case 't':
                size = find_prime(atoi(optarg));
                break;

            case 'c':
                if (NULL == (filename = fopen(optarg, "r"))) {
                    fprintf(stderr, "%s: can’t find file %s\n", argv[0], argv[1]);
                    return EXIT_FAILURE;
                }
                cflag = 1;

                break;

            case 'e':
                eflag = 1;
                break;

            case 'p':
                pflag = 1;
                break;

            case 's':
                snapshots = atoi(optarg);
                break;

            default:
                print_usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    /* Create and fill hash table. - this becomes the dictionary. */
    h = htable_new(size, type);

    fill_start = clock();
    while (getword(word, sizeof word, stdin) != EOF){
        htable_insert(h,word);
    }
    fill_end = clock();

    /* If c was selected, file name should be set and change flag to ignore p option. */
    if (cflag == 1){
        pflag = 0; /* Ignore p option. */
        search_start = clock();
        while (getword(word, sizeof word, filename) != EOF){
            if (htable_search(h, word) == 0){
                printf("%s\n", word);
                unknown++;
            }
        }
        search_end = clock();
        fclose(filename);

        fprintf(stderr, "Fill time   : %7f\nSearch time : %7f\nUnknown words   = %d\n", \
                (fill_end-fill_start)/(double)CLOCKS_PER_SEC,   \
                (search_end-search_start)/(double)CLOCKS_PER_SEC, unknown);
    }

    /* Print tables depending on command line input. */
    if (eflag == 1){
        htable_print_entire_table(h, stderr);
    }

    if (pflag == 1){
        if (snapshots > 0){
            htable_print_stats(h, stdout, snapshots);
        }
    }

    if (pflag == 0 && cflag == 0){
        htable_print(h, print_info);
    }

    htable_free(h);
    return EXIT_SUCCESS;
}
