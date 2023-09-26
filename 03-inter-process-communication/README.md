# Inter-Process Communication (IPC) using Pipes and Shared Memory

This package includes the following files.

1. `Coordinator.c`
- Parent process forks children that run Checker.c programs. The parent process communicates via a pipe, passing a shared memory addresses to store the result of the Checker program execution.
2. `Checker.c`
- This is the program that will run after the exec call and will check whether the divisor and dividend args passed to the program are divisible by eachother. The result of the execution is then passed through a shared memory segment.
1. `ExecutionResult.h` 
- Contains a tuple holding the program args and the exit status to be passed through shared memory.

## Requirements
1. The Checker must accept three arguments, and the Coordinator must accept five
command line arguments.
2. The Coordinator creates a pipe using the `pipe()` command for each child process. The read
end of the pipe will be passed to the Checker, and the write end of the pipe will be used
by the Coordinator to provide the shared memory segment ID.
3. The Coordinator should spawn 4 processes using the `fork()` command and print their
process IDs as they are created.
4. Child-specific processing immediately following the `fork()` command loads the Checker
program into the newly created process using the `exec()` command. This ensures that the
forked process is no longer a copy of the Checker. This `exec()` command should also pass
3 arguments to the Checker program: the divisor, dividend, and the FD of the read end of the pipe created in (2).
5. The Coordinator sets up the shared memory using `shmget()` and writes its ID to the pipe.
6. The Checker starts executing, prints out its process ID, and retrieves the shared memory
segment ID from the pipe.
7. The Checker determines whether or not argTwo is divisible by argOne and prints this
information.
8. If divisible, Checker should write 1 (true) to the shared memory segment, or 0 (false)
otherwise.
9. Parent-specific processing in the Coordinator should ensure that the Coordinator will `wait()` for each instance of the child-specific processing to complete. This is done AFTER all the processes have been started. The results retrieved from shared memory should be printed and match up with what was printed in (7).
10. Both the Coordinator and Checker should clean up: FDs should be closed and shared
memory marked to be destroyed (use the `shmctl()` command).

## To compile
```
make all
```

## To run
```
./coordinator <divisor> <dividend1> <dividend2> <dividend3> <dividend4>
```

## For example
```
./coorindator 3 10 12 14 120
```

## Example Output
```
> ./coordinator 3 3 20 49 102
Coordinator: forked process with ID 25496.
Coordinator: wrote shm ID 4063308 to pipe (4 bytes)
Coordinator: forked process with ID 25497.
Coordinator: wrote shm ID 4096077 to pipe (4 bytes)
Coordinator: forked process with ID 25498.
Coordinator: wrote shm ID 4128846 to pipe (4 bytes)
Coordinator: forked process with ID 25499.
Coordinator: wrote shm ID 4161615 to pipe (4 bytes)
Coordinator: waiting on child process ID 25496...
Checker process [25498]: starting.
Checker process [25498]: read 4 bytes containing shm ID 4128846
Checker process [25498]: 49 *IS NOT* divisible by 3.
Checker process [25498]: wrote result (0) to shared memory.
Checker process [25497]: starting.
Checker process [25497]: read 4 bytes containing shm ID 4096077
Checker process [25497]: 20 *IS NOT* divisible by 3.
Checker process [25497]: wrote result (0) to shared memory.
Checker process [25499]: starting.
Checker process [25499]: read 4 bytes containing shm ID 4161615
Checker process [25499]: 102 *IS* divisible by 3.
Checker process [25499]: wrote result (1) to shared memory.
Checker process [25496]: starting.
Checker process [25496]: read 4 bytes containing shm ID 4063308
Checker process [25496]: 3 *IS* divisible by 3.
Checker process [25496]: wrote result (1) to shared memory.
Coordinator: result 1 read from shared memory: 3 is divisible by 3.
Coordinator: waiting on child process ID 25497...
Coordinator: result 0 read from shared memory: 20 is not divisible by 3.
Coordinator: waiting on child process ID 25498...
Coordinator: result 0 read from shared memory: 49 is not divisible by 3.
Coordinator: waiting on child process ID 25499...
Coordinator: result 1 read from shared memory: 102 is divisible by 3.
Coordinator: exiting.

> ./coordinator 7 32 49 846 22344
Coordinator: forked process with ID 25504.
Coordinator: wrote shm ID 4194380 to pipe (4 bytes)
Coordinator: forked process with ID 25505.
Coordinator: wrote shm ID 4227149 to pipe (4 bytes)
Coordinator: forked process with ID 25506.
Coordinator: wrote shm ID 4259918 to pipe (4 bytes)
Coordinator: forked process with ID 25507.
Coordinator: wrote shm ID 4292687 to pipe (4 bytes)
Coordinator: waiting on child process ID 25504...
Checker process [25504]: starting.
Checker process [25504]: read 4 bytes containing shm ID 4194380
Checker process [25504]: 32 *IS NOT* divisible by 7.
Checker process [25504]: wrote result (0) to shared memory.
Coordinator: result 0 read from shared memory: 32 is not divisible by 7.
Coordinator: waiting on child process ID 25505...
Checker process [25506]: starting.
Checker process [25506]: read 4 bytes containing shm ID 4259918
Checker process [25506]: 846 *IS NOT* divisible by 7.
Checker process [25506]: wrote result (0) to shared memory.
Checker process [25507]: starting.
Checker process [25505]: starting.
Checker process [25507]: read 4 bytes containing shm ID 4292687
Checker process [25505]: read 4 bytes containing shm ID 4227149
Checker process [25507]: 22344 *IS* divisible by 7.
Checker process [25507]: wrote result (1) to shared memory.
Checker process [25505]: 49 *IS* divisible by 7.
Checker process [25505]: wrote result (1) to shared memory.
Coordinator: result 1 read from shared memory: 49 is divisible by 7.
Coordinator: waiting on child process ID 25506...
Coordinator: result 0 read from shared memory: 846 is not divisible by 7.
Coordinator: waiting on child process ID 25507...
Coordinator: result 1 read from shared memory: 22344 is divisible by 7.
Coordinator: exiting.
```