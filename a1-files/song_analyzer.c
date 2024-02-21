/** @file song_analyzer.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process song
 *  data and printing it in a different format.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Angadh S.
 *  @author Juan G.
 *  @author Rayyan J.
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief The maximum line length.
 *
 */

#define MAX_LINE_LEN 132

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */


// Helper functions below
FILE *fileInit(char *dataVal) {
    FILE *inputFile = fopen(dataVal, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return NULL;
    }
    return inputFile;
}

void outputFile(char *tokens[8], FILE *fp) {
	fputs(tokens[1], fp);
	fputc(',', fp);
	fputs(tokens[0], fp);
	fputc('\n', fp);
}

const char* getArtistCheck(int questionNo) {
    switch (questionNo) {
        case 1: return "Rae Spoon";
        case 2: return "Tate McRae";
        case 3: return "The Weeknd";
        case 4: return "no artist";
        case 5: return "Drake"; // here it's not only Drake, but Drake is one of the artists
        default: return NULL; // Handle unexpected cases
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s --question=<qVal> --data=<dataVal>\n", argv[0]);
        return 1;
    }

    char *qVal = NULL;
    char *dataVal = NULL;

    for (int i = 1; i < argc; i++) {
        if (strstr(argv[i], "--question=") != NULL) {
            qVal = strtok(argv[i] + 11, "=");
        } else if (strstr(argv[i], "--data") != NULL) {
            dataVal = strtok(argv[i] + 7, "=");
        }
    }

    if (qVal == NULL || dataVal == NULL) {
        printf("Invalid arguments. Both --question and --data are required.\n");
        return 1;
    }

    int intqVal = atoi(qVal);

    // Print out arguments saved to check
    printf("\narg1: %s \t arg 2: %s", qVal, dataVal);

    FILE *fp = fopen("output.csv", "w+");
    if (fp == NULL) {
        perror("Error opening output file");
        return 1;
    }

    FILE *inputFile = fileInit(dataVal);
    if (inputFile == NULL) {
        return 1;
    }

    char line[MAX_LINE_LEN];

    while (fgets(line, MAX_LINE_LEN, inputFile) != NULL) {
        char *tokens[8];
        char *token = strtok(line, ",");
        int i = 0;

        while (token != NULL && i < 8) {
            tokens[i++] = token;
            token = strtok(NULL, ",");
        }

        const char* artistName = getArtistCheck(intqVal);

        if (artistName != NULL) {
            switch (intqVal) {
                case 1:
                case 2:
                    if (strcmp(tokens[1], artistName) == 0) {
                        outputFile(tokens, fp);
                    }
                    break;

                case 3:
                    if (strcmp(tokens[1], artistName) == 0 && strstr(tokens[7], "Major") != NULL) {
                        outputFile(tokens, fp);
                    }
                    break;

                case 4:
                    if (atoi(tokens[4]) > 5000 && (strcmp(tokens[6], "A") == 0 || strcmp(tokens[6], "D") == 0)) {
                        outputFile(tokens, fp);
                    }
                    break;

                case 5:
                    if ((strcmp(tokens[3], "2021") == 0 || strcmp(tokens[3], "2022") == 0) && strstr(artistName, tokens[1]) != NULL) {
                        outputFile(tokens, fp);
                    }
                    break;

                default:
                    // Handle unexpected question numbers
                    break;
            }
        }
    }

    fclose(inputFile);
    fclose(fp);

    return 0;
}

 
