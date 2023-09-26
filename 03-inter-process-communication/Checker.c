#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "ExecutionResult.h"

#define REQUIRED_ARGS 3

int is_divisible(int dividend, int divisor);

int main(int argc, char **argv) {

  if (argc != REQUIRED_ARGS) {
    fprintf(stderr, "Must have exactly %d amount of command line arguments and you passed %d.\n", REQUIRED_ARGS,argc);
    exit(EXIT_FAILURE);
  }

  pid_t process_id = getpid();
  printf("Checker process [%d]: Starting.\n", process_id);

  // file descriptor
  int fd = atoi(argv[0]);
  int shm_id = atoi(argv[0]);

  // read shared memory address from fd into shm_id
  read(fd, &shm_id, sizeof(shm_id));
  printf("Checker process [%d]: read %ld bytes containing shm ID %d\n", process_id, sizeof(shm_id), shm_id);

  // create a pointer to the shared memory segment
  struct ExecutionResult * shm_ptr = (struct ExecutionResult *) shmat(shm_id, NULL, 0);

  int divisor = atoi(argv[1]);
  int dividend = atoi(argv[2]);

  if (is_divisible(dividend, divisor)) {
    printf("Checker process [%d]: %d *IS* divisible by %d.\n", process_id, dividend, divisor);
    shm_ptr->exit_status = 1;
  } else {
    printf("Checker process [%d]: %d *IS NOT* divisible by %d.\n", process_id, dividend, divisor);
    shm_ptr->exit_status = 0;
  }

  printf("Checker process [%d]: wrote result (%d) to shared memory.\n", process_id, shm_ptr->exit_status);

  // store program arg values in shared memory
  shm_ptr->args[0] = divisor;
  shm_ptr->args[1] = dividend;

  int exit_status = shm_ptr->exit_status;

  // detach from shared memory
  shmdt(shm_ptr);

  return exit_status;
}

int is_divisible(int dividend, int divisor) {
  return dividend % divisor == 0;
}