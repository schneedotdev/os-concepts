# Working With Memory Allocations and Deallocations

This package includes the following files.

1. `Driver.c`
- This is the driver program which will be used to invoke the MemoryManager.
2. `MemoryManager.c`
- MemoryManager is implemented here. Allocations must happen on heap.
3. `MemoryManager.h`
- Header file declaring the function exposed from MemoryManager

# Requirements
1. The Driver program takes a single command-line argument, which serves as the seed for the pseudo-random number generator. The seed determines the sequence of seemingly random numbers generated. Using different seeds helps validate the correctness of the implementation.
   
2. The memory bounds for the process are pre-defined in the provided code and should not be altered.

3. The Driver program calls the memory-manager function, which has already been implemented in Driver.c. It retrieves the running count of certain values.

4. The memory-manager utilizes the random number generator to compute the number of iterations needed to allocate and deallocate arrays. This count falls between 100,000 (inclusive) and 120,000 (exclusive). A utility method, get_iteration_count, is available in the MemoryManager.c file to map a random integer into this range.

5. Steps 5 to 9 are repeated within a loop, and the number of iterations is determined by the random number obtained.

6. The memory-manager uses the random number generator to determine the size of the array to be allocated. The size should range between 1000 (inclusive) and 1500 (exclusive). The array must be allocated on the heap; failure to do so results in a penalty.

7. After the array is allocated, the memory-manager populates each element using the random number generator.

8. The array is then sorted in ascending order.

9.  The median element of the array is obtained. For simplicity, the ⌊𝑎𝑟𝑟𝑎𝑦_𝑠𝑖𝑧𝑒/2⌋ formula is used to calculate the index of the median, regardless of the number of elements.

10. The program checks if the median element is divisible by 13. If it is, the running count of such values is incremented by 1.

11. Once the loop variable initialized in Step 4 reaches its limit, the loop is exited, and the total number of median elements divisible by 13 is reported.

## To compile
```
make build
```

## To run
```
./Driver.out <seed>
```

## Example Output

```
[Driver] With seed: 1234
[MemoryManager] Number of Iterations: 102414
[Driver] Running Count: 7850

[Driver] With seed: 7979
[MemoryManager] Number of Iterations: 100505
[Driver] Running Count: 7832
```

*Results may vary based on your OS. The above results are within a Linux Environment*