/**
 * Manages the command line options.
 * Uses htable: definitions of htable data structure.
 * Uses mylib: memory allocation and getword functions.
 * @Author foxre274 gaoha773 scrca599
 * @Date 10/Sep/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <getopt.h>
#include <time.h>

#include "htable.h"
#include "mylib.h"

/**
 * Displays help option if h or unknown key is typed on the command line.
 * Called from switch statement. 
 * @param myprog name of the program read from the command line which is
 * displayed in the usage statement. 
 *
 */
static void print_usage(char* myprog) {

    char* options =  "\n\n"
        "Perform various operations using a hash table.  By default, words are\n"
        "read from stdin and added to the hash table, before being printed out\n"
        "alongside their frequencies to stdout.\n\n"

        " -c FILENAME  Check spelling of words in FILENAME using words\n"
        "\t      from stdin as dictionary.  Print unknown words to\n"
        "\t      stdout, timing info & count to stderr (ignore -p)\n";

   char* options1 = " -d           Use double hashing (linear probing is the default)\n"
                    " -e           Display entire contents of hash table on stderr\n"
                    " -p           Print stats info instead of frequencies & words\n"
                    " -s SNAPSHOTS Show SNAPSHOTS stats snapshots (if -p is used)\n"
                    " -t TABLESIZE Use the first prime >= TABLESIZE as htable size\n\n"

                    " -h           Display this message\n";

   fprintf(stderr, "Usage: %s [OPTION]... <STDIN> %s%s\n",myprog, options, options1);
}

/**
 * Prints a single line of the table. 
 *
 * @param freq number of occurences of words in the table.
 * @param word word to be printed to the screen. 
 */

static void print_info(int freq, char *word){
    printf("%-4d %s\n",freq,word);
}

/**
 * Checks to see if a number is a prime number.
 *
 * @param n number to check if is a prime.
 *
 * @return 1 if prime, 0 if not.
 */
static int is_prime(int n){

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

/**
 * Finds the next prime equal to or greater than the given number.
 * Uses is_prime.
 *
 * @param n the number to find next prime from.
 *
 * @return next prime number. 
 */
static int find_prime(int n){

    if (n%2 == 0){
        n++;
    }

    while (is_prime(n) == 0){
        n += 2;
    }

    return n;
}

/**
 * Gathers input from the command line and responds to the given
 * arguments.
 * Refer to help menu (-h) for more information.
 *
 * @param argc number of arguments on the command line. 
 * @param argv[] array of arguments.
 *
 * @return exit success or exit failure. 
 */
int main (int argc, char *argv[]){

    char word[256];
    const char *optstring = "c:dehps:t:";
    char option;
    htable h;

    hashing_t type = LINEAR_P;
    int size = 0;
    int snapshots = 10;

    FILE *filename;
    int unknown = 0;
    clock_t fill_start,fill_end, search_start, search_end;

    int pflag = 0;
    int cflag = 0;
    int eflag = 0;

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
                    fprintf(stderr, "%s: can't find file %s\n", argv[0], argv[1]);
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

    h = htable_new(size, type);

    fill_start = clock();
    while (getword(word, sizeof word, stdin) != EOF){
        htable_insert(h,word);
    }
    fill_end = clock();

    if (cflag == 1){
        pflag = 0; 
        search_start = clock();
        while (getword(word, sizeof word, filename) != EOF){
            if (htable_search(h, word) == 0){
                printf("%s\n", word);
                unknown++;
            }
        }
        search_end = clock();
        fclose(filename);

        fprintf(stderr, "Fill time     : %7f\nSearch time   : %7f\nUnknown words = %d\n",\
                (fill_end-fill_start)/(double)CLOCKS_PER_SEC,\
                (search_end-search_start)/(double)CLOCKS_PER_SEC, unknown);
    }

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
