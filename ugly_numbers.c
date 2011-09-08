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

  return lArray[nth - 1];
}

/**
 * Given a number, this function returns the appropriate suffix. For example:
 * 11th, 12th, 13th, 21st, 22nd, 23rd, 24th, 25th...
 *
 * Parameters: nth : the number for which to get the suffix.
 *
 * Returns: "st", "nd", "rd", or "th" based on the number.
 */
const char* convert(int nth) {
  int n = (nth < 0) ? -nth : nth; /* Always use positive integers. */

  /* 11, 12, and 13 */
  if (10 < (n % 100) && (n % 100) < 14) {
    return "th";
  }
 
  switch (n % 10) {
    case 1:
      return "st";
    case 2:
      return "nd";
    case 3:
      return "rd";
    default:
      return "th";
  }
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
    printf("The %d%s ugly number is %ld.\n", nth, convert(nth), result);
    printf("Time elapsed: %.1f seconds\n", difftime(end, start));
  }

  return 0;
}
