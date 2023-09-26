# Working With Memory Allocations and Deallocations


This package includes the following files.

1. Driver.c
   - This is the driver program which will be used to invoke the MemoryManager.
2. MemoryManager.c
   - MemoryManager is implemented here. Allocations must happen on heap.
3. MemoryManager.h
   - Header file declaring the function exposed from MemoryManager

## To compile:
```
make build
```

## To run:
```
./Driver.out <seed>
```

## Example Output with Seed 1234:

```
[Driver] With seed: 1234
[MemoryManager] Number of Iterations: 102414
[Driver] Running Count: 7850

[Driver] With seed: 7979
[MemoryManager] Number of Iterations: 100505
[Driver] Running Count: 7832
```

*Results may vary based on your OS. The above results are within a Linux Environment*