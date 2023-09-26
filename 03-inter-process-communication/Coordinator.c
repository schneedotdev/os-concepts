#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "ExecutionResult.h"

#define REQUIRED_ARGS 6

struct ProcessInfo {
  pid_t pid;
  int shm_id;
};

int main(int argc, char **argv) {

  if (argc != REQUIRED_ARGS) {
    fprintf(stderr, "Must have exactly %d amount of command line arguments and you passed %d.\n", REQUIRED_ARGS, argc);
    exit(EXIT_FAILURE);
  }

  struct ProcessInfo child_processes[argc - 2];

  // loop through all dividends
  for (int i = 2; i < argc; ++i) {
    // create shared memory address
    int shm_id = shmget(IPC_PRIVATE, sizeof(struct ExecutionResult), IPC_CREAT | 0666);

    // file descriptor
    int fd[2];
    pipe(fd);

    pid_t process_id = fork();

    if (process_id == -1) {
      printf("fork() could not be performed.\n");
      exit(EXIT_FAILURE);
    } else if (process_id == 0) {
      char buffer[8];

      // pass read end of pipe into buffer
      sprintf(buffer, "%d", fd[0]);

      char *divisor = argv[1];
      char *dividend = argv[i];

      // execute Checker.c with args: <buffer> <divisor> <dividend>
      execlp("checker", buffer, divisor, dividend, NULL);
    } else {
      printf("Coordinator: forked process with ID %d.\n", process_id);

      // communicate the shared memory address to the child process using the pipe
      close(fd[0]);
      write(fd[1], &shm_id, sizeof(shm_id));
      close(fd[1]);

      printf("Coordinator: wrote shm ID %d to pipe (%ld bytes)\n", shm_id, sizeof(shm_id));

      // store child process info for later use
      child_processes[i - 2].pid = process_id;
      child_processes[i - 2].shm_id = shm_id;
    }
  }

  for (int i = 2; i < argc; ++i) {
    struct ProcessInfo currentProcess = child_processes[i - 2];

    // wait for child process to finish execution
    int status;
    waitpid(currentProcess.pid, &status, 0);
    int result = WEXITSTATUS(status);

    printf("Coordinator: waiting on child process ID %d...\n", currentProcess.pid);

    // attach to shared memory segment
    struct ExecutionResult * shm_ptr = (struct ExecutionResult *) shmat(currentProcess.shm_id, NULL, 0);
    printf("Coordinator: result %d read from shared memory: ", shm_ptr->exit_status);

    // destroy shared memory segment
    shmctl(currentProcess.shm_id, IPC_RMID, NULL);

    char * str = (result == 1) ? "is" : "is not";

    int divisor = shm_ptr->args[0];
    int dividend = shm_ptr->args[1];

    printf("%d %s divisible by %d.\n", dividend, str, divisor);
  }

  printf("Coordinator: exiting.\n");

  return 0;
}