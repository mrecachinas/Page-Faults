/*
 * Michael Recachinas
 * CS 4414: Operating Systems
 * Produce N Page Faults - Challenge
 * C Implementation (within ~144)
 */

/*
 * Execute: /usr/bin/time -l ./a.out <number of desired page faults>
 * Alternatively, uncomment printf within nested for-loop to use 'top'.
 * Interesting note: above 2047, it defaults to 144 page faults (same as 0)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char ** argv) {
    if (argc < 2){ /* Command-line argument error handling */
        // printf("Usage: %s <number of desired page faults>\n", argv[0]);
        return -1;
    }
    int i, j, N, page_size, int_size, ints_per_page;

    N = atoi(argv[1]); /* Grab approximate number of desired page faults */
    
    page_size = getpagesize(); /* Machine-dependent page size (unsigned int) */
    printf("Page size: %d\n", page_size );
    
    int_size = sizeof(int); /* Get machine's size of representing signed integers */
    printf("Signed Integer size: %lu\n", sizeof(int) );
    
    ints_per_page = (int)page_size/int_size; /* Entries per page for signed integers */
    printf("How many signed ints fit on a page? %d\n", ints_per_page );

    int a[N][ints_per_page]; /* 2D Array: N - ROWS, ints_per_page - COLS */
    int x=0;
    /* Note: this nested loop is running in COLUMN MAJOR order. */
    for (i = 0; i < page_size; i++) {
        for (j=0; j<N; j++) {
             // printf("a[%d][%d]: %d\n", j, i, a[j][i]); /* Slow version (for 'top') */
            x += a[j][i];
        }
    }
    return 1;
}

