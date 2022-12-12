#include <stdio.h>
#include <string.h>						
#include <stdbool.h>					
#include <ctype.h>	
#include <stdlib.h>

// Declare global variables.  Variables are defined in global.c

extern int outer;                          // Iteration counters
extern int inner;                          // Iteration counters
extern int count;                          // Iteration counters		
extern int countW;						   // Word counters					
extern int countPW;						   // Word counters
extern int countRW;						   // Word counters
extern int countM;						   // Word counters					
extern int top;                            // Search parameters for binary search
extern int bottom;                         // Search parameters for binary search
extern int middle;                         // Search parameters for binary search								
extern int debugCycle;                     // Used for debugging. Counts number times rock sort loop iterates.												
extern bool debug;                         // Turn debug on and off	

// Define Function Prototypes
#ifndef CCFinalProgramHeader_h

#define CCFinalProgramHeader_h								
void textFileToArray(FILE *, char words[500][20]);          // Assigns contents of *.txt files to 2-dimensional array.  Call on function in main.  Pass by address the fptr and words variables.
void singleCaseArray(char words[500][20]);                  // Changes characters in array to single case (lower). Call on function in main.  Pass by address the words variable.
void parseWords(char words[500][20]);	                    // Removes punctuation from array. Call on function in main.  Pass by address the words variable.							
void resetWordsArray(char words[500][20]);	                // Words array is default array *.txt files are saved into.  Reset after each use. Call on function in main.  Pass by address the words variable.				
void rockSort(char words[500][20], char tempW[20]);// Sort array contents in ascending order. Call on function in main.  Pass by address the words variable.
void binarySearch(char wordsP[500][20], char wordsR[500][20], char wordsM[500][20]);        // Search for targeted words via binary search method. Call on function in main.  Pass by address the wordsP and wordsR variables.
#endif