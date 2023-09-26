#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define REQUIRED_ARGS 3

int is_divisible(int dividend, int divisor);

int main(int argc, char **argv) {

  if (argc != REQUIRED_ARGS) {
    fprintf(stderr, "Must have exactly %d amount of command line arguments and you passed %d.\n", REQUIRED_ARGS,argc);
    exit(EXIT_FAILURE);
  }

  pid_t process_id = atoi(argv[0]);

  printf("Checker process [%d]: Starting.\n", process_id);

  int divisor = atoi(argv[1]);
  int dividend = atoi(argv[2]);

  if (is_divisible(dividend, divisor)) {
    printf("Checker process [%d]: %d *IS* divisible by %d.\n", process_id, dividend, divisor);
    printf("Checker process [%d]: Returning 1.\n", process_id);
    return 1;
  } 

  printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", process_id, dividend, divisor);
  printf("Checker process [%d]: Returning 0.\n", process_id);

  return 0;
}

int is_divisible(int dividend, int divisor) {
  return dividend % divisor == 0;
}