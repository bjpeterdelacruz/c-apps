#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * The wrapper function will, given a string, return the
 * same string but with line breaks inserted at the right
 * places so that no line is longer than the column number.
 *
 * Parameters: string - The string to be modified.
 *             numColumns - The maximum length of a line.
 *
 * Return values: -1 on failure, 0 on success.
 */
int line_wrapper(char* string, int numColumns) {

  int counter  = 0;
  int position = 0;

  if (string == NULL) {
    printf("string is NULL.\n");
    return -1;
  }
  if (numColumns == 0) {
    printf("Number of columns not specified.\n");
	return -1;
  }

  while (string[position] != '\0') {
    if (counter == numColumns) {
	  while (string[position] != ' ') {
	    position--;
	  }
	  string[position] = '\n';
	  counter = 0;
	}
    counter++;
	position++;
  }

  return 0;
}

/*
 * This program accepts two command-line arguments: a string and
 * a column number. This program will modify the string and return
 * the same string but with line breaks inserted at the right
 * places so that no line is longer than the specified column number.
 *
 * Parameters: argv[1] - The string to modify.
 *             argv[2] - The column number, or maximum length of a line.
 *
 * Returns -1 on failure and 0 on success.
 *
 * Author: BJ Peter DeLaCruz (bjpeter@hawaii.edu)
 * Website: http://www.thetravelingcs.com
 *
 */
int main(int argc, char** argv) {

  char* string = NULL;

  if (argc != 3) {
    printf("Need two arguments: string and number of columns.\n");
	exit(1);
  }

  string = malloc(sizeof(char) * strlen(argv[1]) + 1);
  if (string == NULL) {
    printf("Unable to allocate space to store string.\n");
	exit(1);
  }

  strcpy(string, argv[1]);

  printf("\nOld String:\n\n%s\n\n", argv[1]);

  if (line_wrapper(string, atoi(argv[2])) == -1) {
    printf("Failed to modify string.\n");
	exit(1);
  }

  printf("-------------------------\n\n");
  printf("New String:\n\n%s\n\n", string);
  free(string);

  return 0;
}
