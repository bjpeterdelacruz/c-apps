int startOver(char** ppcTwoDArray, TwoDArraySizes* pmsSizes, int* moveCount, char* whoseTurn);
int printHowToPlayMessage(void);
int getPlayerMove(char** ppcTwoDArray, char* whoseTurn, TwoDArraySizes* pmsSizes);
int checkRowsColumnsAndDiagonals(char** ppcTwoDArray, char* whoseTurn, char* didPlayerWin, TwoDArraySizes* pmsSizes);
char** clearBoard(char** ppcTwoDArray, TwoDArraySizes* pmsSizes);
