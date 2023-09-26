#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>

#define REQUIRED_ARGS 6

int main(int argc, char **argv) {

  if (argc != REQUIRED_ARGS) {
    fprintf(stderr, "Must have exactly %d amount of command line arguments and you passed %d.\n", REQUIRED_ARGS, argc);
    exit(EXIT_FAILURE);
  }

  // loop through all dividends
  for (int i = 2; i < argc; ++i) {
    pid_t process_id = fork();

    if (process_id == -1) {
      printf("fork() could not be performed.\n");
      exit(EXIT_FAILURE);
    } else if (process_id == 0) {
      // convert pid to string for passing as an arg to exec
      int pid = getpid();
      char pid_array[6];
      sprintf(pid_array, "%d", pid);

      char *divisor = argv[1];
      char *dividend = argv[i];

      // execute Checker.c with args: <pid> <divisor> <dividend>
      execlp("checker", pid_array, divisor, dividend, NULL);
    } else {
      printf("Coordinator: forked process with ID %d.\n", process_id);
      printf("Coordinator: waiting for process [%d].\n", process_id);

      int status;
      wait(&status);
      int result = WEXITSTATUS(status);

      printf("Coordinator: child process %d returned %d.\n", process_id, result);
    }
  }

  printf("Coordinator: exiting.\n");

  return 0;
}