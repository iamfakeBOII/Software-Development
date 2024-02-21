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

typedef struct {
	FILE *fp;
	FILE *inputFile;
}Files;

Files returnFiles(char* dataVal) {
	Files files;
	files.fp = fopen("output.csv", "w+");
	fprintf(files.fp, "Artist(s), Song\n");
	
	files.inputFile = fopen(dataVal, "r");

	return files;
}

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

void outputFile(char *tokens[8], FILE *fp) {
	fputs(tokens[1], fp);
	fputc(',', fp);
	fputs(tokens[0], fp);
	fputc('\n', fp);
}

const char* getArtistCheck(int questionNo) {
	if(questionNo == 1) {
		return "Rae Spoon";	
	}
	else if (questionNo == 2) {
		return "Tate McRae";
	}
	else if (questionNo == 3) {
		return "The Weeknd";
	}
	else if (questionNo == 4) {
		return "no artist";
	}
	else if (questionNo == 5) {
		return "Drake"; // here its not only drake but drake is one of the artists
						
	}
}

int main(int argc, char *argv[])
{
    // TODO: your code.
	
	if (argc < 3) { // Three arguments technically since the program name is in the execution line
		printf("Need more! %s \n", argv[0]);
		return 1;
	}
	
	// Some definitions for stored arguments
	
	char *qVal = NULL;
	char *dataVal = NULL;

	for (int i = 1; i < argc; i++) {
		if(strstr(argv[i], "--question=") != NULL) {
			qVal = strtok(argv[i] + 11, "=");
		}
		
		else if (strstr(argv[i], "--data") != NULL) {
			dataVal = strtok(argv[i] + 7, "=");
		}
	}
	
	char storedInt[256];
	strcpy(storedInt, qVal);
	int intqVal = atoi(storedInt);
	// printf("%d\n", intqVal);

	// Print out arguments saved to check //
	printf("\narg1: %s \t arg 2: %s", qVal, dataVal);
	Files file = returnFiles(dataVal);
	FILE *fp = file.fp;
	FILE *inputFile = file.inputFile;

	char line[MAX_LINE_LEN]; // parse each line in the loop
	
	// final array storing all values satisfying question 1 mc rae //
	char *conditionMet[1000];
	while(fgets(line, MAX_LINE_LEN, inputFile) != NULL) {
			char tempLine[MAX_LINE_LEN];
			strcpy(tempLine, line);

			char *tokens[8];
			char *token = strtok(line, ",");
			int i = 0;
			while (token != NULL && i < 8) {
				tokens[i++] = token;
				token = strtok(NULL, ",");
			}
			// printf("%s\n", tokens[1]);
			
			// Call function and get the artist name for relevant question
			const char* artistName = getArtistCheck(intqVal);
			// printf("%s", artistName);
			// printf("Key:%s\n", tokens[7]);
			
			// Messy if statement block ;;
	
			if((intqVal == 1 || intqVal == 2) && strcmp(tokens[1], artistName) == 0) {
				outputFile(tokens, fp);
			}

			else if (intqVal == 3 && strcmp(tokens[1], artistName) == 0 && strstr(tokens[7], "Major") != NULL) {
				outputFile(tokens, fp);
			}

			else if (intqVal == 4 && atoi(tokens[4]) > 5000 && (strcmp(tokens[6], "A") == 0 || strcmp(tokens[6], "D") == 0)) {
				outputFile(tokens, fp);
			}

			else if (intqVal == 5 && (strcmp(tokens[3], "2021") == 0 || strcmp(tokens[3], "2022") == 0) && strstr(artistName, tokens[1]) != NULL) {
				outputFile(tokens, fp);
			}

		}
		
			// continue;

	fclose(inputFile);

	fclose(fp); // close ouput file

    exit(0);
}

 
