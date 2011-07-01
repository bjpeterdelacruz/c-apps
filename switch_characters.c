#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This function reverses all words in a string. Punctuation marks are ignored.
 * For example, "Hello, World!" becomes "olleH, dlroW!"
 *
 * Parameters: string - String to reverse.
 * Return:     -1 if string is NULL, 0 on success.
 */
int switch_characters(char* string) {

  int  length  = 0;
  int  posX    = 0;
  int  posY    = 0;
  int  tempPos = 0;
  char temp    = 0;

  if (string == NULL) {
    printf("string is NULL.\n");
    return -1;
  }

  length = strlen(string);

  for (posX = 0; posX < length; posX++) {
    for (posY = posX; string[posY] != ' ' &&
                      string[posY] != '\0' &&
                      ((string[posY] > 47 && string[posY] < 58) ||
                       (string[posY] > 64 && string[posY] < 91) ||
                       (string[posY] > 96 && string[posY] < 123)); posY++);
    tempPos = posY;
    posY--;
    while (posY > posX) {
      temp = string[posY];
      string[posY] = string[posX];
      string[posX] = temp;
      posY--;
      posX++;
    }
    posX = tempPos;
    if (string[tempPos] != ' ' && string[tempPos] != '\0') {
      posX++;
    }
  }

  return 0;
}

/*
 * The main method tests the switch_characters function above by passing
 * a pointer to a string stored in dynamically allocated memory.
 *
 * Parameters: None.
 * Return:     -1 on failure, 0 on success.
 */
int main() {

  char* string = (char*) malloc(sizeof(char) * 100);
  if (string == NULL) {
    printf("Failed to allocate memory.\n");
    exit(1);
  }

  strcpy(string, "Hello World! My cat, Wiggles, likes to sleep.");

  printf("%s\n", string);

  if (switch_characters(string) == -1) {
    exit(1);
  }

  printf("%s\n", string);

}
