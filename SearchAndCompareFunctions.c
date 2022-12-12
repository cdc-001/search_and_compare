#include "SearchAndCompare.h"								// Need to include for use of global variables

/************** All functions declared in CCFinalProgramHead.h are defined here *******/
/**************** CCFinalProgramHead.h header file function definitions ***************/

void textFileToArray(FILE *fptr, char words[500][20])
{
	if (fptr == 0)												// Inform user file could not be found.
	{
		printf("error: file not found\n");
		exit (1);												// Exit program
	}
	
	count = 0;
	while (!feof(fptr))											// Using while statement allows us to use same code for any file.
	{

		
		fscanf(fptr, " %s", words[count]);			
		count++;


	}
	fclose(fptr);												// Always close your file			
}																// End of Text File to Array Function

/***************************************************************************************************************************************/

void singleCaseArray(char words[500][20])
{
	count = 0;
	while(words[count][0] > 0)									// Cycle through each word in the array.
	{
			for (inner = 0; inner < strlen(words[count]); inner++)
			{
				words[count][inner] = tolower(words[count][inner]);
			}
			
			count++;
	}
}																// End of case change function.

/***************************************************************************************************************************************/

void parseWords(char words[500][20])									// Remove most punctuation from array.
{
	count = 0;														
	while(words[count][0] > 0)											// Cycle through each word in array					
	{
			for (inner = 0; inner < strlen(words[count]); inner++)		// Cycle through each character in array
			{	
					if (isalpha(words[count][inner]) || words[count][inner] == 45 || words[count][inner] == 39)		// Per ASCII table, values for hyphen and apostrophes are 45 and 39, respectively.							
					{
						words[count][inner] = words[count][inner];		// Only keep letters, hyphens, and apostrophes in array.														
					}	
					else
					{
						words[count][inner] = '\0'; 					// Remove any punctuation, except for apostrophe and hyphen.
						break;											// Break out of loop to next word in array.
					}	
			}
			
			count++;
	}


	if (debug)
	{
		printf("\n<<<<<<<<<<<<< Begin Debug - Parsed Words >>>>>>>>>>>>>>>>>>>>>>>>>\n");

		for (outer = 0; outer < count; outer++)
		{
			printf("wordsP[%i]: %s\n", outer, words[outer]);		// Output vertically to make sure there's no weird spacing
		}

		printf("<<<<<<<<<<<<< End Debug - Parsed Words >>>>>>>>>>>>>>>>>>>>>>>>>\n\n");

	}


}																	// End of word parsing

/***************************************************************************************************************************************/

void resetWordsArray(char words[500][20])					// Want to make sure there's no left over values once we use this array again for Reserved Word list.
{
	count = 0;
	while(words[count][0] > 0)
	{
			for (inner = 0; inner < strlen(words[count]); inner++)
			{
				words[count][inner] = '\0';
			}
			count++;
	}
}															// End of array reset

/***************************************************************************************************************************************/

void rockSort(char words[500][20], char tempW[20])				// Sorting target words in ascendig order enables the use of binary search below.
{
	count = 0;												
	while(words[count][0] > 0)								// Count amount of words in target list.  Will degregate count for efficiency purposes.
	{
		count++;											
	}
	countW = count - 1;										// Change index to 0, currently index is at 1.

	
	debugCycle = 0;										
	for (outer = 0; outer < countW; outer++)				// Cycle through each target word.
	{

			if (debug)
			{
				printf("<<<Debug - Rock Sort >>> Cycle: [%i]; Word Compare: [%s] vs [%s] = [%i]\n", debugCycle, words[outer], words[outer + 1], strcmp(words[outer], words[outer + 1]));
			}

			debugCycle++;
			
			
			if (strcmp(words[outer], words[outer + 1]) > 0)			// If true, larger words needs to be moved down the list
			{
				strcpy(tempW, words[outer]);						// Store larger word in temp variable.  Otherwise, it'll be overwritten in next line of code
				strcpy(words[outer], words[outer + 1]);				// Move smaller word up the list
				strcpy(words[outer + 1], tempW);					// Move larger word down the list
			}

			
			if (outer == (countW -1))								// Reset the loop.  Largest word has been moved to bottom of list.							
			{
				outer = -1;											// Reset loop counter							
				countW--;											// Reduce next iteration by one, since largest word doesn't need to re-evaluated					
				debugCycle = 0;
			}

	}																	

}																// End of Rock Sort

/***************************************************************************************************************************************/

void binarySearch(char wordsP[500][20], char wordsR[500][20], char wordsM[500][20])
{

	countM = 0;															// Missing word counter.
	for (outer = 0; outer < countPW; outer++)							// Cycle through each word in the block of text.
	{
			top = 0; 														// Defining parameters in first loop will ensure they're reset when program cycle to next word.
			bottom = countRW - 1;											// Reduce countRW index to 0.  Currently indexed at 1.
			middle = (bottom + top) / 2;									// Median word
					
			for (inner = 0; inner < countRW; inner++)						// Cycle through each target word.
			{	
					if(debug)
					{
						printf("<<<<Debug>>>> Target Word: %s; Top[%i] = %s; Middle[%i] = %s; Bottom[%i] = %s\n", wordsP[outer], top, wordsR[top], middle, wordsR[middle], bottom, wordsR[bottom]);
					}
					
					
					if (strcmp(wordsP[outer], wordsR[top]) == 0 || strcmp(wordsP[outer], wordsR[middle]) == 0 || strcmp(wordsP[outer], wordsR[bottom]) == 0 )						// Current word in block of text is on the reserved word list.
					{
						if(debug)
						{
							printf("<<<Debug>>>Found it >>>> %s\n", wordsP[outer]);
						}
						break;															// Break to outer loop/next word in block of text.
					}
					else if (strcmp(wordsP[outer], wordsR[middle]) < 0)					// Target word is towards the top of list, if in list.
					{
						if (bottom == middle)											// If bottom still equals middle after adjusting middle below in last cycle, then word is not in list.
						{
							strcpy(wordsM[countM], wordsP[outer]);						// Store block of text words NOT in reserved word list in new array. 
							countM++;													// Count amount of block of text words NOT in reserved list.
							break;														// Break to outer loop/next word in block of text.
						}
						
						bottom = middle;												// Narrow down parameters
						middle = (bottom + top) / 2;									// Adjust median word 
					}
					else																// Target word is towards the bottom of the list, if in list.
					{
						if (top == middle)												// If top still equals middle after adjusting middle below in last cycle, then word is not in list.
						{
							strcpy(wordsM[countM], wordsP[outer]);						// Store block of text words NOT in reserved word list in new array.  
							countM++;													// Count amount of block of text words NOT in reserved list.
							break;														// Break to outer loop/next word in block of text.
						}
						
						top = middle;													// Narrow down parameters
						
						if (((float)(bottom + top) / 2) - ((bottom + top) / 2) > 0)		// Need to round up if average is not an integer.
						{
							middle = (bottom + top) / 2 + 1;							// Adjust parameter, but round up if average is not an integer.  Otherwise, middle will never equal bottom in some scenarios. 
						}
						else
						{
							middle = (bottom + top) / 2 ;								// Adjust parameters. 
						}
					}

					
					if (top == bottom)													// Once these two equal, word is not in list.
					{
						strcpy(wordsM[countM], wordsP[outer]);							// Store block of text words NOT in reserved word list in new array.  
						countM++;														// Count amount of block of text words NOT in reserved list.
						break;															// Break to outer loop/next word in block of text.
					}		
			}
		}																				
}																						// End of binary search