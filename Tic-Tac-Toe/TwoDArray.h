#define MAX_ROW_SIZE 3
#define MAX_COL_SIZE 3

typedef struct {
  int num_rows;
  int num_cols;
} TwoDArraySizes;

char** create2dArray(TwoDArraySizes* pmsSizes);
int print2dArray(char** ppcTwoDArray, TwoDArraySizes* pmsSizes);
int free2dArray(char** ppcTwoDArray, TwoDArraySizes* pmsSizes);
