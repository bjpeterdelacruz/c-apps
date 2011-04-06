#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ApplicationConstants.h"
#include "TwoDArray.h"
#include "TicTacToeFunctionsV2.h"

///////////////////////////////////////////////////////////////////////////
// Tic-Tac-Toe                                             April 8, 2011 //
//                                                                       //
// Author: BJ Peter "Beej" DeLaCruz                                      //
//                                                                       //
// Description: A game of tic-tac-toe. Players take turns putting an X   //
//              or an O in a matrix. Whoever fills in all X's or O's in  //
//              a row, column, or diagonal first wins. Game ends when    //
//              someone wins. Size of matrix is defined by num_rows and  //
//              num_cols in the pmsSizes struct. Both variables must be  //
//              equal to each other. The matrix can be any size, e.g.    //
//              10 x 10, so feel free to modify num_rows and num_cols.   //
//              Enjoy, and have fun!                                     //
//                                                                       //
// Version: 2.0                                                          //
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
  char** ppcTwoDArray      = NULL;
  int moveCount            = 0;
  int randNum              = 0;
  TwoDArraySizes* pmsSizes = NULL;

  pmsSizes = (TwoDArraySizes*) malloc(sizeof(TwoDArraySizes));
  if (pmsSizes == NULL) {
    printf("Memory allocation failure for pmsSizes!\n");
    return -1;
  }

  pmsSizes->num_rows = MAX_ROW_SIZE;
  pmsSizes->num_cols = MAX_COL_SIZE;

  if ((ppcTwoDArray = create2dArray(pmsSizes)) == NULL) {
    printf("Memory allocation failure for ppcTwoDArray!\n");
    return -1;
  }

  srand(time(NULL));

  randNum = rand() % 10;
  whoseTurn = (randNum < 5) ? 'X' : 'O';

  printHowToPlayMessage();

  printf("%c goes first.\n\n", whoseTurn);

  while (!didPlayerWin) {
    if (getPlayerMove(ppcTwoDArray, &whoseTurn, pmsSizes) < 0) {
      return -1;
    }

    if (checkRowsColumnsAndDiagonals(ppcTwoDArray, &whoseTurn, &didPlayerWin, pmsSizes) < 0) {
      return -1;
    }

    if (print2dArray(ppcTwoDArray, pmsSizes) < 0) {
      return -1;
    }

    if (didPlayerWin) {
      printf("%c won!\n\n", whoseTurn);
      break;
    }

    moveCount++;
    if (moveCount == pmsSizes->num_rows * pmsSizes->num_cols) {
      if (startOver(ppcTwoDArray, pmsSizes, &moveCount, &whoseTurn) < 0) {
	return -1;
      }
    }
    else {
      whoseTurn = (whoseTurn == 'X') ? 'O' : 'X';
    }
  }

  free2dArray(ppcTwoDArray, pmsSizes);

  return 0;
}
