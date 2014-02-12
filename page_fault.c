/*
 * Michael Recachinas
 * CS 4414: Operating Systems
 * Produce N Page Faults - Challenge
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char ** argv) {
    printf("Page size on Mike's Macbook Air running OS X 10.9.1: %d\n",getpagesize());
    printf("Int size on Mike's Macbook Air running OS X 10.9.1: %lu\n", sizeof(int));
    if (argc < 2){
        printf("Usage: ./page_fault <number of page faults>\n");
        return -1;
    }
    int i,j,N, page_size,int_size; /* Declare variables */
    N = atoi(argv[1]); /* Grab approximate number of desired page faults */
    int_size = sizeof(int); /* Get machine's size of representing signed integers */
    page_size = (int)getpagesize()/int_size; /* Entries per page for signed integers */
    int a[N][page_size]; /* 2D Array where the ROWS are the number of desired faults and the COLS have the size of a page */
    int x = 0;

    for (i = 0; i < page_size; i++) {
        for (j=0; j<N; j++) {
            // printf("a[%d][%d]: %d\n", j, i, a[j][i]);
             x += a[j][i];
        }
    }
    return 1;
}

