#include <stdio.h>
#include <stdlib.h>
#include "ApplicationConstants.h"
#include "TwoDArray.h"

///////////////////////////////////////////////////////////////////////////
// create2dArray                                           April 4, 2011 //
//                                                                       //
// Description: Dynamically allocates a 2-dimensional array to store     //
//              characters.                                              //
//                                                                       //
// Version: 1.1                                                          //
//                                                                       //
// Input parameters: pmsSizes : struct containing the number of rows and //
//                              columns in the 2D array                  //
//                                                                       //
// Returns: NULL if memory allocation for 2D array is unsuccessful       //
//          Pointer to 2D array if no problems were encountered          //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
char** create2dArray(TwoDArraySizes* pmsSizes) {
  int i, j;
  char** ppcTwoDArray = NULL;

  if (pmsSizes == NULL) {
    printf("NULL pointer passed to create2dArray function [%p].\n", pmsSizes);
    return NULL;
  }

  ppcTwoDArray = (char**) malloc(sizeof(char*) * pmsSizes->num_rows);

  if (ppcTwoDArray == NULL) {
    printf("Memory allocation failure for ppcTwoDArray!\n");
    return NULL;
  }

  for (i = 0; i < pmsSizes->num_cols; i++) {
    ppcTwoDArray[i] = (char*) malloc(sizeof(char) * pmsSizes->num_cols);
    if (ppcTwoDArray[i] == NULL) {
      printf("Memory allocation failure for ppcTwoDArray[%d]!\n", i);
      return NULL;
    }
  }

  for (i = 0; i < pmsSizes->num_rows; i++) {
    for (j = 0;j < pmsSizes->num_cols; j++) {
      ppcTwoDArray[i][j] = ' ';
    }
  }

  return ppcTwoDArray;
}

///////////////////////////////////////////////////////////////////////////
// print2dArray                                           April 4, 2011  //
//                                                                       //
// Description: Prints the contents of a 2-dimensional array to the      //
//              screen.                                                  //
//                                                                       //
// Version: 1.1                                                          //
//                                                                       //
// Input parameters: ppcTwoDArray : The actual 2D array                  //
//                   pmsSizes     : struct containing the number of rows //
//                                  and columns in the 2D array          //
//                                                                       //
// Returns: -1 if function was passed a NULL pointer                     //
//          0 if no problems were encountered                            //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
int print2dArray(char** ppcTwoDArray, TwoDArraySizes* pmsSizes) {
  int i, j;

  if (ppcTwoDArray == NULL || pmsSizes == NULL) {
    printf("NULL pointer passed to print2dArray function: [%p][%p].\n", ppcTwoDArray, pmsSizes);
    return -1;
  }

  printf("\n");
  for (i = 0; i < pmsSizes->num_rows - 1; i++) {
    for (j = 0; j < pmsSizes->num_cols - 1; j++) {
      printf(" %c |", ppcTwoDArray[i][j]);
    }
    printf(" %c\n", ppcTwoDArray[i][j]);
    printf("-----------\n");
  }
  for (j = 0; j < pmsSizes->num_cols - 1; j++) {
    printf(" %c |", ppcTwoDArray[i][j]);
  }
  printf(" %c\n\n", ppcTwoDArray[i][j]);

  return 0;
}

///////////////////////////////////////////////////////////////////////////
// free2dArray                                            April 4, 2011  //
//                                                                       //
// Description: Frees the 2D array when the game is over.                //
//                                                                       //
// Version: 1.1                                                          //
//                                                                       //
// Input parameters: ppcTwoDArray : The actual 2D array                  //
//                   pmsSizes     : struct containing the number of rows //
//                                  and columns in the 2D array          //
//                                                                       //
// Returns: 0 if no problems were encountered                            //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
int free2dArray(char** ppcTwoDArray, TwoDArraySizes* pmsSizes) {
  int i;
  if (ppcTwoDArray == NULL || pmsSizes == NULL) {
    printf("NULL pointer passed to free2dArray function: [%p][%p].\n", ppcTwoDArray, pmsSizes);
    return -1;
  }

  for (i = 0; i < pmsSizes->num_rows; i++) {
    free(ppcTwoDArray[i]);
  }
  free(ppcTwoDArray);

  return 0;
}
