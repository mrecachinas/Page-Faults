/*
 * Michael Recachinas
 * CS 4414: Operating Systems
 * Produce N Page Faults - Challenge
 * Rust Implementation (within ~500)
 */

/*
 * Execute: /usr/bin/time -l ./a.out <number of desired page faults>
 * Alternatively, uncomment printf within nested for-loop to use 'top'.
 * Interesting note: above 2047, it defaults to 144 page faults (same as 0)
 */

use std::{os,mem};

fn main() {
	let args: ~[~str] = os::args();
    if args.len() != 2 { /* Command-line argument error handling */
        println!("Usage: {} <number of desired page faults>", args[0])
    } else {
    	let n = from_str::<uint>(args[1]).unwrap();

    	let page_size = os::page_size();
        println!("Page size: {}", page_size);
    	
        let int_size = mem::size_of_val(&1);
        println!("Signed Integer size: {}", int_size);

    	let ints_per_page = page_size/int_size;
        println!("How many signed ints fit on a page? {}", ints_per_page);

    	let mut arr: ~[int] = std::vec::from_elem(n*ints_per_page, 0);
    	
        let mut i = 0;
    	while i < (ints_per_page * n) { // Instead of a 2D array, we're simulating a 2D array using a 1D array
    		// println!("a[{}]: {}",i, arr[i]); // Long Version for 'top'
            arr[i] = 1;
    		i += ints_per_page;
    	}
    }
}
