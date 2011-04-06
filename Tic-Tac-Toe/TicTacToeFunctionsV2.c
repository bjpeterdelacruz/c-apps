#include <stdio.h>
#include <stdlib.h>
#include "ApplicationConstants.h"
#include "TwoDArray.h"
#include "TicTacToeFunctionsV2.h"

///////////////////////////////////////////////////////////////////////////
// startOver                                              April 8, 2011  //
//                                                                       //
// Description: Clears the board and randomly selects who goes first.    //
//                                                                       //
// Version: 2.0                                                          //
//                                                                       //
// Input parameters: ppcTwoDArray : The actual 2D array                  //
//                   pmsSizes     : struct containing the number of rows //
//                                  and columns in the 2D array          //
//                   moveCount    : Number of moves both players made so //
//                                  far                                  //
//                   whoseTurn    : X or O                               //
//                                                                       //
// Returns: 0 if no problems were encountered printing the message       //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
int startOver(char** ppcTwoDArray, TwoDArraySizes* pmsSizes, int* moveCount, char* whoseTurn) {
  int randNum = 0;

  if ((ppcTwoDArray = clearBoard(ppcTwoDArray, pmsSizes)) < 0) {
    return -1;
  }
  *moveCount = 0;

  randNum = rand() % 10;
  *whoseTurn = (randNum < 5) ? 'X' : 'O';

  printf("%c goes first.\n\n", *whoseTurn);

  return 0;
}

///////////////////////////////////////////////////////////////////////////
// printHowToPlayMessage                                  April 8, 2011  //
//                                                                       //
// Description: Prints instructions on how to play Tic-Tac-Toe to the    //
//              screen.                                                  //
//                                                                       //
// Version: 2.0                                                          //
//                                                                       //
// Input parameters: None                                                //
//                                                                       //
// Returns: 0 if no problems were encountered printing the message       //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
int printHowToPlayMessage(void) {

  printf("\nTic-Tac-Toe\n");
  printf("----------------------\n");
  printf("How to play:\n");
  printf("   > Whoever gets all X's or all O's in a row, column, or diagonal first wins!\n");
  printf("   > If there is a tie, the board is cleared, and a new game is automatically started.\n");
  printf("     The game won't end until a winner has been determined.\n");
  printf("   > Good luck, and have fun!\n\n");

  return 0;
}

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
     * quit the game.
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
// Version: 2.0                                                          //
//                                                                       //
// Input parameters: ppcTwoDArray : The actual 2D array                  //
//                   whoseTurn    : X or O                               //
//                   didPlayerWin : TRUE or FALSE                        //
//                   pmsSizes     : struct containing the number of rows //
//                                  and columns in the 2D array          //
//                                                                       //
// Returns: -1 if function was passed a NULL pointer                     //
//          0 if no problems were encountered                            //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
int checkRowsColumnsAndDiagonals(char** ppcTwoDArray, char* whoseTurn, char* didPlayerWin, TwoDArraySizes* pmsSizes) {
  int i, j, count;

  if (!ppcTwoDArray || !whoseTurn || !didPlayerWin || !pmsSizes) {
    printf("NULL pointer passed to checkPlayerStatus function: [%p][%p][%p][%p].\n", ppcTwoDArray, whoseTurn, didPlayerWin, pmsSizes);
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
      return 0;
    }
    count = 0;
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
      return 0;
    }
    count = 0;
  }

  /* Check left-to-right diagonal */
  for (i = 0, count = 0; i < pmsSizes->num_rows; i++) {
    if (ppcTwoDArray[i][i] == *whoseTurn) {
      count++;
    }
  }

  if (count == pmsSizes->num_rows) {
    *didPlayerWin = TRUE;
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
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////
// clearBoard                                             April 8, 2011  //
//                                                                       //
// Description: Clears the Tic-Tac-Toe board by freeing the old 2D char  //
//              array and returning a pointer to a new 2D char array.    //
//                                                                       //
// Version: 2.0                                                          //
//                                                                       //
// Input parameters: ppcTwoDArray : The actual 2D array                  //
//                   pmsSizes     : struct containing the number of rows //
//                                  and columns in the 2D array          //
//                                                                       //
// Returns: NULL if function was passed one or more NULL pointers        //
//          A pointer to a 2D char array if no problems were encountered //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
char** clearBoard(char** ppcTwoDArray, TwoDArraySizes* pmsSizes) {
  if (!ppcTwoDArray || !pmsSizes) {
    printf("NULL pointer passed to clearBoard function: [%p][%p].\n", ppcTwoDArray, pmsSizes);
    return NULL;
  }

  printf("Clearing the board...\n\n");

  free2dArray(ppcTwoDArray, pmsSizes);
  return create2dArray(pmsSizes);
}
