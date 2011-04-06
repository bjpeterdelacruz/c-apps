#include <stdio.h>
#include <stdlib.h>
#include "ApplicationConstants.h"
#include "TwoDArray.h"
#include "TicTacToeFunctions.h"

///////////////////////////////////////////////////////////////////////////
// getPlayerMove                                          April 4, 2011  //
//                                                                       //
// Description: Asks the player to enter coordinates in the matrix at    //
//              which to put an X or an O. A coordinate is valid if the  //
//              row and column numbers are between 0 and MAX_ROW_SIZE-1, //
//              and 0 and MAX_COL_SIZE-1, respectively, inclusively, and //
//              the space is unoccupied by either an X or an O, i.e. it  //
//              is occupied by a ' ' (space).                            //
//                                                                       //
// Version: 1.1                                                          //
//                                                                       //
// Input parameters: ppcTwoDArray : The actual 2D array                  //
//                   whoseTurn    : X or O                               //
//                   pmsSizes     : struct containing the number of rows //
//                                  and columns in the 2D array          //
//                                                                       //
// Returns: -1 if function was passed a NULL pointer                     //
//          -2 if a keyboard input error occurred                        //
//          0 if no problems were encountered                            //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
int getPlayerMove(char** ppcTwoDArray, char* whoseTurn, TwoDArraySizes* pmsSizes) {
  int row, col, errorCount = 0;

  if (!ppcTwoDArray || !whoseTurn || !pmsSizes) {
    printf("NULL pointer passed to getCoordinates function: [%p][%p][%p].\n", ppcTwoDArray, whoseTurn, pmsSizes);
    return -1;
  }

  while (TRUE) {
    row = 0;
    col = 0;

    printf("Please enter row number: ");
    scanf("%d", &row);
    printf("Please enter column number: ");
    scanf("%d", &col);

    if (row >= pmsSizes->num_rows || col >= pmsSizes->num_cols || row < 0 || col < 0) {
      printf("\nInvalid coordinates [%d][%d].\n", row, col);
      printf("Row number must be between 0 and %d, inclusive.\n", pmsSizes->num_rows);
      printf("Column number must be between 0 and %d, inclusive.\n", pmsSizes->num_cols);
      printf("Please try again.\n\n");
    }
    else if (ppcTwoDArray[row][col] != ' ') {
      printf("\nSpace already occupied by an %c.\n", ppcTwoDArray[row][col]);
      printf("Please try again.\n\n");
      errorCount++;
    }
    else {
      break;
    }

    /*
     * If the player pressed the Up key on a Unix system and then pressed the Enter key,
     * the program will loop infinitely, so if the error count reaches 10, prematurely
     * quit the game. (A hack, yes.)
     */
    if (errorCount == 10) {
      printf("Detected input error. Aborting program...\n");
      return -2;
    }
  }

  ppcTwoDArray[row][col] = *whoseTurn;

  return 0;
}

///////////////////////////////////////////////////////////////////////////
// checkRowsColumnsAndDiagonals                           April 4, 2011  //
//                                                                       //
// Description: Checks if there is a tie or a player won. If there is a  //
//              tie, isTie is set to TRUE, and didPlayerWin is set to    //
//              FALSE. If a player won (either X or O), isTie is set to  //
//              FALSE, and didPlayerWin is set to TRUE.                  //
//                                                                       //
// Version: 1.1                                                          //
//                                                                       //
// Input parameters: ppcTwoDArray : The actual 2D array                  //
//                   whoseTurn    : X or O                               //
//                   didPlayerWin : TRUE or FALSE                        //
//                   isTie        : TRUE or FALSE                        //
//                   pmsSizes     : struct containing the number of rows //
//                                  and columns in the 2D array          //
//                                                                       //
// Returns: -1 if function was passed a NULL pointer                     //
//          0 if no problems were encountered                            //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
int checkRowsColumnsAndDiagonals(char** ppcTwoDArray, char* whoseTurn, char* didPlayerWin, char* isTie, TwoDArraySizes* pmsSizes) {
  int i, j, count;

  if (!ppcTwoDArray || !whoseTurn || !didPlayerWin || !isTie || !pmsSizes) {
    printf("NULL pointer passed to checkPlayerStatus function: [%p][%p][%p][%p][%p].\n", ppcTwoDArray, whoseTurn, didPlayerWin, isTie, pmsSizes);
    return -1;
  }

  /* Check if there is a tie first */
  for (i = 0; i < pmsSizes->num_rows; i++) {
    for (j = 0; j < pmsSizes->num_cols; j++) {
      if (ppcTwoDArray[i][j] != ' ') {
        count++;
      }
    }
  }

  if (count == pmsSizes->num_cols * pmsSizes->num_cols) {
    *isTie = TRUE;
    *didPlayerWin = FALSE;
    return 0;
  }

  /* Check rows */
  for (i = 0, count = 0; i < pmsSizes->num_rows; i++) {
    for (j = 0; j < pmsSizes->num_cols; j++) {
      if (ppcTwoDArray[i][j] == *whoseTurn) {
	count++;
      }
    }
    if (count == pmsSizes->num_cols) {
      *didPlayerWin = TRUE;
      *isTie = FALSE;
      return 0;
    }
  }

  /* Check columns */
  for (i = 0, count = 0; i < pmsSizes->num_cols; i++) {
    for (j = 0; j < pmsSizes->num_rows; j++) {
      if (ppcTwoDArray[i][j] == *whoseTurn) {
        count++;
      }
    }
    if (count == pmsSizes->num_rows) {
      *didPlayerWin = TRUE;
      *isTie = FALSE;
      return 0;
    }
  }

  /* Check left-to-right diagonal */
  for (i = 0, count = 0; i < pmsSizes->num_rows; i++) {
    if (ppcTwoDArray[i][i] == *whoseTurn) {
      count++;
    }
  }

  if (count == pmsSizes->num_rows) {
    *didPlayerWin = TRUE;
    *isTie = FALSE;
    return 0;
  }

  /* Check right-to-left diagonal */
  for (i = 0, j = pmsSizes->num_rows - 1, count = 0; i < pmsSizes->num_rows; i++, j--) {
    if (ppcTwoDArray[i][j] == *whoseTurn) {
      count++;
    }
  }

  if (count == pmsSizes->num_rows) {
    *didPlayerWin = TRUE;
    *isTie = FALSE;
  }

  return 0;
}
