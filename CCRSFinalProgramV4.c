#include <stdio.h>
#include <string.h>						// strlen() and strcmp() functions
#include <stdbool.h>					// bool data type
#include <ctype.h>						// tolower() and isalpha() functions
#include "CCRSFinalProgramHeader.h"

/*
***************************************************************
 Program Name: CCFinalProgram.c
 This program reads and scan contents of text file into separate 2-dimensional arrays.  The program changes the case of array to lowercase, and, if applicable, parses and sorts the array.  The program then checks to see if each word on a separate list, Reserved Word List, is on our initial block of text via a binary search.  The code will output any word in the block of text that's not in the reserved word on a new line.
 Variables:  
	Characters:
	  words - Contents in text files will be initially assigned to this 2-dimensional array.
	  wordsP - A 2-dimensional array that contains the block of text.
	  wordsR - Reserved words list. This is also a 2-dimensional array.
	  wordsM - Missing block of text words not in the reserved words list. This is also a 2-dimensional array.
	  tempW  - Temporary holding spot for rock sort.
	Integers (unless indicated otherwise, default values are 0):
	  count    - Iteration  counter.
	  countW   - Word count for default array, words.
	  countPW  - Parsed word count.  Used in binary search as iteration counter.
	  countRW  - Reserved/target word count. Used in binary search as iteration counter.
	  countM   - Count for missing words in reserved word list, but not in parsed text array.  Used as iteration counter.
	  outer    - For loop iteration counter
	  inner    - For loop iteration counter
	  top      - Binary search parameter.
	  bottom   - Binary search parameter.  Default value is parsed word count less 1.  Reduce by 1 to adjust index to 0 from 1.
	  middle   - Binary search parameter.  Default value is average of top and bottom.
	Debug:
	  debugCycle - Used for debugging.  Counts number of iterations in for loop.  Default value is 0.
	  debug 	 - Used to turn debug prints on and off.  Boolean data type.  Value of true will turn debug on.  Value of zero will turn them off.
	File Pointer:
	  fptr - Open external files.
	Functions included in "CCRSFinalProgramHeader.h"
	  textFileToArray - Assigns contents of *.txt files to 2-dimensional array.  Call on function in main.  Pass by address the fptr and words variables.
	  singleCaseArray - Changes characters in array to single case (lower). Call on function in main.  Pass by address the words variable.
	  parseWords      - Removes punctuation from array. Call on function in main.  Pass by address the words variable.							
	  resetWordsArray - Words array is default array *.txt files are saved into.  Reset after each use. Call on function in main.  Pass by address the words variable.				
	  rockSort        - Sort array contents in ascending order. Call on function in main.  Pass by address the words variable.
	  binarySearch    - Search for targeted words via binary search method. Call on function in main.  Pass by address the wordsP and wordsR variables.
	  

 	Written by Cory Caddell  
 	8/7/22
 	Modifications: CC altered code to make use of functions on 8/9/22.
				   CC altered code to move functions to header file on 8/10/22
				   RS altered code to include notification if files didn't open properly on 8/10/22
***************************************************************
*/

/* Global variable included in "CCRSFinalProgramHeader.h"
	int outer, inner 
	int count, countW, countPW, countRW, countM 
	int top, bottom, middle
	int debugCycle						
	bool debug
*/ 

int main()									
{
	// Declare Local Variables
	FILE *fptr;
	char words[500][20];						// Default array that will contain contents of text files
	char wordsP[500][20];						// Block of text words
	char wordsR[500][20];						// Reserved words list
	char wordsM[500][20];						// Block of text words missing from reserve word list
	char tempW[20];								// Temporary holding spot for rock sort.


	/*********************************** Prepare block of text for binary search **********************************************/

	fptr = fopen("FinalExamFileToParseSearch.txt", "r");			// Make sure this matches external file.
	textFileToArray(fptr, words);					// Order matters.  This function needs to be placed directly after fptr assignment.
	singleCaseArray(words);							// Change to single case, so we're comparing apples to apples in binary search.
	parseWords(words);								// Remove all punctuation, except for apostrophes and hyphens (just in case)

	count = 0;										
	while(words[count][0] > 0)						
	{
		strcpy(wordsP[count], words[count]);		// Copy to block of text array.
		count++;
	}
	countPW = count;								// Block of text word count.  Used in binary search.
	resetWordsArray(words);							// Having a default array allows us to use same function without updating it for different variables.


	if (debug)
	{
		printf("\n<<<<<<<<<<<<< Begin Debug - Block of Text >>>>>>>>>>>>>>>>>>>>>>>>>\n");
		
		count = 0;
		while(wordsP[count][0] > 0)
		{
			printf(" %s", wordsP[count]);
			count++;
		}
		printf(" \n\nWord count = %i\n\n", count);

		printf("<<<<<<<<<<<<< End Debug - Block of Text >>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
	}
	
	
	/*********************************** Prepare reserved word list for binary search **********************************************/
	
	fptr = fopen("FinalExamReserveWordList.txt", "r");		// Make sure this matches external file.
	textFileToArray(fptr, words);					// Order matters.  This function needs to be placed directly after fptr assignment.
	singleCaseArray(words);							// Change to single case, so we're comparing apples to apples in binary search.					
	rockSort(words, tempW);							// Words will be sorted in alphabetical order.  Enables us to use binary search later in program.
	
	count = 0;
	while(words[count][0] > 0)
	{
		strcpy(wordsR[count], words[count]);		// Copy to reserve list array.
		count++;
	}
	countRW = count;								// Reserve list word count.  Used in binary search.

	if (debug)
	{
		printf("\n<<<<<<<<<<<<< Begin Debug - Reserved Words >>>>>>>>>>>>>>>>>>>>>>>>>\n");
		
		count = 0;
		while(words[count][0] > 0)
		{
			printf(" %s\n", wordsR[count]);
			count++;
		}
		printf(" Word count = %i\n\n", count);

		printf("<<<<<<<<<<<<< End Debug - Reserved Words >>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
	}
	

	/*************************** Search block of text for words in reserved list via binary search ********************************/

	binarySearch(wordsP, wordsR, wordsM);

	/******************* Output word(s) if block of text is not in Reserved Word List **********************************************/

	if (countM > 0)
	{
		printf("The following words are not included in reserved word List:\n");
		for(outer = 0; outer < countM; outer++)
		{
			printf("  %s\n", wordsM[outer]);
		}
	}
	else																// Inform the user that all words in block of text were in reserved word list.
	{
		printf("All of the words in the block of text were on the reserved word list.\n\n");
	}

	return(0);
}																		// End of main


