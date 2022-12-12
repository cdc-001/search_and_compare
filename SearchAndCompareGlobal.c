#include <stdbool.h>
#include "SearchAndCompare.h"

/****************** Define Global Variables **************************/

int outer = 0;                          // Iteration counters
int inner = 0;                          // Iteration counters
int count = 0;	                        // Iteration counters
int countW = 0;						    // Word counters
int countPW = 0;                        // Word counters
int countRW = 0;                        // Word counters
int countM = 0;					        // Word counters
int top = 0;                            // Search parameters for binary search
int bottom = 0;                         // Search parameters for binary search
int middle = 0;							// Search parameters for binary search	
int debugCycle = 0;					    // Used for debugging. Counts number times rock sort loop iterates.						
//bool debug = 1;	                        // Turn on debug
bool debug = 0;                      // Turn off debug