#include <stdio.h>
#include <stdlib.h>
#include "ApplicationConstants.h"
#include "TwoDArray.h"
#include "TicTacToeFunctions.h"

///////////////////////////////////////////////////////////////////////////
// Tic-Tac-Toe                                             April 4, 2011 //
//                                                                       //
// Author: BJ Peter "Beej" DeLaCruz                                      //
//                                                                       //
// Description: A game of tic-tac-toe. Players take turns putting an X   //
//              or an O in a matrix. Whoever fills in all X's or O's in  //
//              a row, column, or diagonal first wins. Game ends when    //
//              there is a tie. Size of matrix is defined by ROW and COL //
//              in the constants.h header file. ROW and COL must be      //
//              equal to each other. The matrix can be any size, e.g.    //
//              10 x 10, so feel free to modify the ROW and COL          //
//              constants. Enjoy, and have fun!                          //
//                                                                       //
// Version: 1.1                                                          //
//                                                                       //
// Input parameters: None                                                //
//                                                                       //
// Returns: -1 if problems were encountered                              //
//           0 on success                                                //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
int main(void) {
  char whoseTurn           = 'X';
  char didPlayerWin        = FALSE;
  char isTie               = FALSE;
  char** ppcTwoDArray      = NULL;
  TwoDArraySizes* pmsSizes = NULL;

  pmsSizes = (TwoDArraySizes*) malloc(sizeof(TwoDArraySizes));
  if (pmsSizes == NULL) {
    printf("Memory allocation failure for pmsSizes!\n");
    return -1;
  }

  pmsSizes->num_rows = MAX_ROW_SIZE;
  pmsSizes->num_cols = MAX_COL_SIZE;

  ppcTwoDArray = create2dArray(pmsSizes);
  if (ppcTwoDArray == NULL) {
    printf("Memory allocation failure for ppcTwoDArray!\n");
    return -1;
  }

  printf("\nTic-Tac-Toe\n");
  printf("----------------------\n");
  printf("How to play:\n");
  printf("   > Whoever gets all X's or all O's in a row, column, or diagonal first wins!\n\n");
  printf("%c goes first.\n\n", whoseTurn);

  while (!didPlayerWin && !isTie) {
    if (getPlayerMove(ppcTwoDArray, &whoseTurn, pmsSizes) < 0) {
      return -1;
    }

    if (checkRowsColumnsAndDiagonals(ppcTwoDArray, &whoseTurn, &didPlayerWin, &isTie, pmsSizes) < 0) {
      return -1;
    }

    if (print2dArray(ppcTwoDArray, pmsSizes) < 0) {
      return -1;
    }

    if (isTie || didPlayerWin) {
      break;
    }

    whoseTurn = (whoseTurn == 'X') ? 'O' : 'X';
  }

  if (didPlayerWin) {
    printf("%c won!\n\n", whoseTurn);
  }
  else {
    printf("The game is tie.\n\n");
  }

  free2dArray(ppcTwoDArray, pmsSizes);

  return 0;
}
