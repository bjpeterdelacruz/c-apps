#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * This function will find the n-th ugly number iteratively.
 *
 * Parameters: nth : the n-th ugly number to find, e.g. 1500.
 *
 * Returns: -1 if memory cannot be allocated or a positive number, which represents
 *          the ugly number.
 */
long findNthUglyNumber(int nth) {
  long number = 1;
  int position = 0;

  long* lArray = (long*) malloc(sizeof(long) * nth);
  if (lArray == NULL) {
    printf("Unable to allocate memory to store numbers.\n");
    return -1;
  }

  while (1) {
    long iTemp = number;
    while (iTemp % 5 == 0) { iTemp /= 5; }
    while (iTemp % 3 == 0) { iTemp /= 3; }
    while (iTemp % 2 == 0) { iTemp /= 2; }
    if (iTemp == 1) {
      lArray[position] = number;
      if (position % 100 == 0 && position > 0) {
        printf("Found the %dth ugly number: %ld\n", position, number);
      }
      position++;
    }
    if (position >= nth) {
      break;
    }
    number++;
  }

  /* Sanity check */
  printf("\nHere are the first ten ugly numbers:\n");
  for (position = 0; position < 11; position++) {
    printf("[%2d]: %ld\n", position, lArray[position]);
  }
  printf("\n");

  return lArray[position - 1];
}

/**
 * This program finds the n-th ugly number, where n is a number inputted by the user.
 * An ugly number is a number whose prime factors are only 2, 3, or 5.
 */
int main() {
  long result;
  int nth;
  time_t start, end;

  printf("Please enter a number: ");
  scanf("%d", &nth);

  start = time(NULL);
  result = findNthUglyNumber(nth);
  end = time(NULL);

  if (result > 0) {
    printf("The %dth ugly number is %ld.\n", nth, result);
    printf("Time elapsed: %.1f seconds\n", difftime(end, start));
  }

  return 0;
}
