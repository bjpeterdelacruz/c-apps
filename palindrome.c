#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE  100
#define TRUE  1
#define FALSE 0

/*
 * This function finds all substrings of at least length N that are palindromes.
 *
 * Example:
 *   - If N = 3 and string = "abbbbxyzbjjbjpppj", then "bbb", "bbb", "bjjb", "jbj", "jpppj", "ppp".
 * Parameters:
 *   - string: String inputted by user.
 *   - sublen: Minimum length of palindrome.
 * Returns:
 *   - 0 on success, -1 if string is NULL.
 */
int findAllPalindromes(char* string, int sublen) {

  int start, end, left, right, length;
  char isPalindrome = TRUE;

  if (string == NULL) {
    printf("string is NULL.\n");
    return -1;
  }

  length = strlen(string);
  for (start = 0; start < length - (sublen - 1); start++) {
    for (end = start + sublen - 1; (string[start] != string[end] || string[start] == string[end + 1]) && string[end] != '\0'; end++);

    left = start;
    right = end;

    while (left < right && isPalindrome) {
      if (string[left] != string[right]) {
        isPalindrome = FALSE;
      }
      left++;
      right--;
    }

    if (isPalindrome) {
      for (left = start; left < end + 1; left++) {
        printf("%c", string[left]);
      }
      printf("\n");
    }
    else {
      isPalindrome = TRUE;
    }
  }

  return 0;
}

/*
 * This program asks the user to input a string and then finds all substrings of at least length N
 * that are palindromes. Finally, the results are outputted to the screen.
 *
 * Parameters: None.
 * Returns:    0 on success, 1 if one or more parameters are supplied or string is NULL.
 */
int main(char** argv, int argc) {

  char* string = NULL;

  if (argc > 1) {
    printf("This program takes no arguments.\n");
    exit(1);
  }

  string = (char*) malloc(sizeof(char) * SIZE);
  if (string == NULL) {
    printf("string is NULL.\n");
    exit(1);
  }

  printf("Enter a string: ");
  scanf("%s", string);

  findAllPalindromes(string, 3); /* N = 3 */

  free(string);

  return 0;
}
