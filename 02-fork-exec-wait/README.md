# Working with fork(), exec(), and wait() System Calls

This package includes the following files.

1. `Coordinator.c`
   - This is the program that will fork child processes and exec the Checker.c program within those child processes. The program in execution will compute if dividends passed as command line arguments are divisible by a divisor passed as an argument.
2. `Checker.c`
   - This is the program that will run after the exec call and will check whether the divisor and dividend args passed to the program are divisible by eachother.

## Requirements

1. The Checker must accept two arguments, and the Coordinator must accept five command line
arguments.
2. The Coordinator should spawn 4 processes using the `fork()` command and must ensure that it
completes one full cycle of `fork()`, `exec()` and `wait()` for a given process before it moves on to
spawning a new process.
3. Once it has used the `fork()` command, the Coordinator will print out the process ID of the process that
it created. This can be retrieved by checking the return value of the `fork()` command.
4. Child-specific processing immediately following the `fork()` command then loads the Checker program
into the newly created process using the `exec()` command. This ensures that the forked process is no
longer a copy of the Coordinator. This `exec()` command should also pass 2 arguments to the Checker
program. For this assignment, it is recommended that you use the `execlp()` command. The man
page for exec (man 2 exec) will give details on the usage of the `exec()` family of functions.
5. When the Checker is executing it prints out its process ID; this should match the one returned by the
`fork()` command in step 3.
6. The Checker then determines whether or not argTwo is divisible by argOne and prints this information.
7. If divisible, Checker should return a nonzero exit code. If not divisible, Checker should return 0. These
correspond to the standard UNIX ‘success’ and ‘failure’ exit codes. Each exit code received by the
Coordinator should be printed. You can use the `WEXITSTATUS()` macro to determine the exit status
code (see `man 2 wait`).
8. Parent-specific processing in the Coordinator should ensure that the Coordinator will `wait()` for
each instance of the child-specific processing to complete.

## To compile
    make all

## To run
```
./coordinator <divisor> <dividend1> <dividend2> <dividend3> <dividend4>
```

## For example
```
./coorindator 3 10 12 14 120
```

# Example Output
```
./coordinator 3 3 20 49 102
Coordinator: forked process with ID 23339.
Coordinator: waiting for process [23339].
Checker process [23339]: Starting.
Checker process [23339]: 3 *IS* divisible by 3.
Checker process [23339]: Returning 1.
Coordinator: child process 23339 returned 1.
Coordinator: forked process with ID 23340.
Coordinator: waiting for process [23340].
Checker process [23340]: Starting.
Checker process [23340]: 20 *IS NOT* divisible by 3.
Checker process [23340]: Returning 0.
Coordinator: child process 23340 returned 0.
Coordinator: forked process with ID 23341.
Coordinator: waiting for process [23341].
Checker process [23341]: Starting.
Checker process [23341]: 49 *IS NOT* divisible by 3.
Checker process [23341]: Returning 0.
Coordinator: child process 23341 returned 0.
Coordinator: forked process with ID 23342.
Coordinator: waiting for process [23342].
Checker process [23342]: Starting.
Checker process [23342]: 102 *IS* divisible by 3.
Checker process [23342]: Returning 1.
Coordinator: child process 23342 returned 1.
Coordinator: exiting.

> ./coordinator 7 32 49 846 22344
Coordinator: forked process with ID 23981.
Coordinator: waiting for process [23981].
Checker process [23981]: Starting.
Checker process [23981]: 32 *IS NOT* divisible by 7.
Checker process [23981]: Returning 0.
Coordinator: child process 23981 returned 0.
Coordinator: forked process with ID 23982.
Coordinator: waiting for process [23982].
Checker process [23982]: Starting.
Checker process [23982]: 49 *IS* divisible by 7.
Checker process [23982]: Returning 1.
Coordinator: child process 23982 returned 1.
Coordinator: forked process with ID 23983.
Coordinator: waiting for process [23983].
Checker process [23983]: Starting.
Checker process [23983]: 846 *IS NOT* divisible by 7.
Checker process [23983]: Returning 0.
Coordinator: child process 23983 returned 0.
Coordinator: forked process with ID 23984.
Coordinator: waiting for process [23984].
Checker process [23984]: Starting.
Checker process [23984]: 22344 *IS* divisible by 7.
Checker process [23984]: Returning 1.
Coordinator: child process 23984 returned 1.
```