/** @file song_analyzer.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process song
 *  data and printing it in a different format.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Angadh S.
 *  @author Juan G.
 *  @author Fintan Coyle
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

typedef struct{
    char* track_name;
    char* artist_name;
    char* artist_count;
    char* released_year;
    char* in_spotify_playlist;
    char* streams;
    char* key;
    char* mode;
} sheet_struct;

//sheet_struct arrayx[5000]; //create an array of all the song structs


void writeToSheet(sheet_struct temp_struct, FILE *resultFile){

  // helper function that writes the artist name and song to a file
  fputs(temp_struct.artist_name, resultFile);
  fputs(",", resultFile);
  fputs(temp_struct.track_name, resultFile);
  fputs("\n", resultFile);
}


void q1(sheet_struct temp_struct, FILE *resultFile) {

  // helper function to answer the first question
  const char* artist_to_find = "Rae Spoon";
  
  const char* artist_in_loop = temp_struct.artist_name; // create constant share of the struct
    
  //puts(arrayx[i].artist_name);
  if (strcmp(artist_to_find, artist_in_loop) == 0) { // compare if both constant chars are the same name
      
    writeToSheet(temp_struct, resultFile); // writes artsist name to sheet if true


    }
      
    
  }


void q2(sheet_struct temp_struct, FILE *resultFile) {

  // helper function to answer the first question 

  const char* artist_to_find = "Tate McRae";
  

  const char* artist_in_loop = temp_struct.artist_name;
    

  if (strcmp(artist_to_find, artist_in_loop) == 0) {
      
    writeToSheet(temp_struct, resultFile);

  }
      
    
}

void q3(sheet_struct temp_struct, FILE *resultFile){
  const char* artist_to_find = "The Weeknd";

  const char* artist_in_loop = temp_struct.artist_name;
  
  
    //puts(arrayx[i].artist_name);
  if (strcmp(artist_to_find, artist_in_loop) == 0 && strstr(temp_struct.mode, "Major")) { // compares artist name and checks to see if the song is Major
    
    writeToSheet(temp_struct, resultFile); // writes artist name to result sheet if true
  }



}


void q4(sheet_struct temp_struct, FILE *resultFile) {

  char nonConstCopy[100];
  strcpy(nonConstCopy, temp_struct.in_spotify_playlist);
  int intSpotifyPlaylists = atoi(nonConstCopy);

  int threshold = 5000;

  if (intSpotifyPlaylists > threshold && (strstr(temp_struct.key, "A") || strstr(temp_struct.key, "D"))) { // checks to see if over 5000 spotify and in key of A or D
    writeToSheet(temp_struct, resultFile);
  }
}


void q5(sheet_struct temp_struct, FILE *resultFile) {

  char nonConstCopy[100];
  strcpy(nonConstCopy, temp_struct.released_year);
  int intReleasedYear = atoi(nonConstCopy);

  if (((intReleasedYear == 2021) || intReleasedYear == 2022) && strstr(temp_struct.artist_name, "Drake")) { // checks to see the year of the song and if Drake is an artist
    writeToSheet(temp_struct, resultFile);
  }


}
  

  





int main(int argc, char *argv[])
{
    // TODO: your code.

    
    FILE *resultFile = fopen("output.csv", "w"); // create an open a file making it writeable

    fputs("Artist(s)", resultFile); // setting up result file in format
    fputs(",", resultFile);
    fputs("Song", resultFile);
    fputs("\n", resultFile);


  
    char *questNum = NULL;
    char *spreadSheet = NULL;
    for (int i = 1; i < argc; i++) {
      if ((strstr(argv[i], "--question")) != NULL){
        questNum = strtok(argv[i] + 11, "="); // finding the question number from the argument
      }
      else if ((strstr(argv[i], "--data")) != NULL){
        spreadSheet = strtok(argv[i] + 7, "="); // finding the spreasheet that must be opened
      }
        
    }

    char nonConstCopy[10000];
    strcpy(nonConstCopy, questNum);
    int intNumber = atoi(nonConstCopy); // creating an integer version of the char questNum
   
    char list_of_row[MAX_LINE_LEN];
    char result[MAX_LINE_LEN];
    FILE *data;
    
  
    


    data = fopen(spreadSheet, "r"); // opening the spreasheet in write mode
    if (data == NULL) { // Basic error handling
      perror("Error opening file");
      return (-1);
    }
    fgets(list_of_row, MAX_LINE_LEN, data); // open the first line of the spreasheet


    int i = 0;
    
    while (fgets(list_of_row, MAX_LINE_LEN, data)!= NULL) { // while loop that loops through each line of the file

      char* tokens[8]; // seperate each column into tokens
      char* token = strtok(list_of_row, ",");
      int z = 0;
      while (z<8 && token != NULL){
        tokens[z] = token;
        token = strtok(NULL, ",");
        z++;
      }

      sheet_struct temp_struct = {tokens[0],tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6], tokens[7]}; // compile tokens into a tempoary struct


      // based on the quest num, the temp_struct is put through the needed question and processed

      if (intNumber == 1){
  
        q1(temp_struct, resultFile);
      }
      if (intNumber == 2) {

        q2(temp_struct, resultFile);
      }

      if (intNumber == 3) {
      
        q3(temp_struct, resultFile);


      }

      if (intNumber == 4) {
        
        q4(temp_struct, resultFile);

      }
      if (intNumber == 5) {
        q5(temp_struct, resultFile);
      }
      



      
      i++; // loop through to the next line


    }

  

   
    fclose(data);// close data file
 
    

    fclose(resultFile); // Close the result file

    exit(0);
}


