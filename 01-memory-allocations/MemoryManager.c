#include <stdio.h>
#include <stdlib.h>

int compare (const void * a, const void * b) {
   return (*(int*)a - *(int*)b);
}

int return_median(int *arr, int size) {
   qsort(arr, size, sizeof(int), compare);
   return arr[size/2];
}

int get_iteration_count(int rand) {
    return (rand % 20000) + 100000;     
}

int get_arr_size(int rand) {
    return (rand % 500) + 1000;
}


/**
 * This is the method that you need to implement.
 * Implement the following steps in the given order.
 *
 *  1. Generate the number of iterations
 *      - Generate a random number. Map it to the range [100000 - 120000) using the 
 *      utility function 'get_iteration_count'.
 * 
 * 2. For each iteration:
 *      2.a Generate an array size - Generate a random number and map it to the range [1000 - 1500) using
 *          the utility function 'get_arr_size'.
 * 
 *      2.b Allocate memory for the array in the heap.
 *
 *      2.c Populate the array with random numbers.
 *
 *      2.d Get the median of the array using the function 'return_median'.
 *
 *      2.e Check if the median is divisible by 13.
 *
 *      2.f Return the number of medians that were divisible by 13.
 *
 */
int get_running_count()
{
    int num_divisible_by_13 = 0;

    // 1. generate a random number of iterations
    int num_of_iterations = get_iteration_count(rand());
    printf("[MemoryManager] Number of Iterations: %d\n", num_of_iterations);

    for (int i = 0; i < num_of_iterations; ++i) {
        // 2a. generate a random array size to be allocated on the heap
        int size = get_arr_size(rand());
        // 2b. allocate memory for an int array on the heap
        int * arr = (int *) malloc(size * sizeof(int));

        // if allocation failed, print to stderr and exit the program.
        if (arr == NULL) {
            fprintf(stderr, "[MemoryManager] Failed to allocate memory during iteration %d\n", i + 1);
            exit(EXIT_FAILURE);
        }

        // 2c. assign random integer values for each element of array
        for (int j = 0; j < size; ++j) {
            arr[j] = rand();
        }

        // 2d. find the median element of the array 
        int median_of_array = return_median(arr, size);

        // 2e. increment if the median is divisible by 13
        if (median_of_array % 13 == 0) {
            num_divisible_by_13++;
        }

        // deallocate the memory
        free(arr);
    }
    
    // 2f. return the total number of medians divisible by 13
    return num_divisible_by_13;
}
