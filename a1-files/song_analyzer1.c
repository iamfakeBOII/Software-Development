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

typedef struct {
	char *song_name;
	char *artist_name;
	char *year;
	char *playlist_count;
	char *streams;
	char *key;
	char *mode;
}csvStruct;

FILE *fileInit(char *dataVal) {
	FILE *inputFile;
	inputFile = fopen(dataVal, "r");
	// Function call to q1, q2, ....
	if (inputFile == NULL) {
		return NULL;
	}
	return inputFile;
}

void outputFile(csvStruct struct_holder, FILE *fp) {
	fputs(struct_holder.artist_name, fp);
	fputc(',', fp);
	fputs(struct_holder.song_name, fp);
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

	//Output file
	FILE *fp;	
	fp = fopen("output.csv", "w+");
	//fprintf(fp, "Artist(s), Song");
	fputs("Artist(s)", fp); // setting up result file in format
    fputs(",", fp);
    fputs("Song", fp);
    fputs("\n", fp);
	
	//Input file
	FILE *inputFile;
	inputFile = fopen(dataVal, "r");
	// Function call to q1, q2, ....
	if (inputFile == NULL) {
		return 1;
	}

	//FILE *inputFile = fileInit(dataVal);
	char line[MAX_LINE_LEN]; // parse each line in the loop
							 //
	fgets(line, MAX_LINE_LEN, inputFile); // Skips frst line	
	// final array storing all values satisfying question 1 mc rae //
	while(fgets(line, MAX_LINE_LEN, inputFile) != NULL) {

			char *tokens[8];
			char *token = strtok(line, ",");
			int i = 0;
			while (token != NULL && i < 8) {
				tokens[i++] = token;
				token = strtok(NULL, ",");
			}
			
			const char* artistName = getArtistCheck(intqVal);

			csvStruct struct_holder = {tokens[0], tokens[1], tokens[3], tokens[4], tokens[5], tokens[6], tokens[7]};

			if (intqVal == 1) {
				if (strcmp(artistName, struct_holder.artist_name) == 0) {
					outputFile(struct_holder, fp);
				}
			}
			else if (intqVal == 2) {
				if (strcmp(artistName, struct_holder.artist_name) == 0) {
					outputFile(struct_holder, fp);
				}
			}
			else if (intqVal == 3) {
				// printf("we ballin\n");
				if (strcmp(artistName, struct_holder.artist_name) == 0 && strstr(struct_holder.mode, "Major")) {
					outputFile(struct_holder, fp);
				}
			}
			else if (intqVal == 4) {
				int checkPlaylist = 5000;

				char playCount[100];
				strcpy(playCount, struct_holder.playlist_count);
				int playCountInt = atoi(playCount);

				if (playCountInt > checkPlaylist && (strstr(struct_holder.key, "D") || strstr(struct_holder.key, "A"))) {
					outputFile(struct_holder, fp);
				}
			}
			else if (intqVal == 5) {
				// printf("we here\n");
				int intYear = atoi(struct_holder.year);
				if ((intYear == 2021 || intYear == 2022) && strstr(struct_holder.artist_name, artistName)) {
					outputFile(struct_holder, fp);
				}
			}

		}
		
			// continue;

	fclose(inputFile);

	fclose(fp); // close ouput file

    exit(0);
}

 
