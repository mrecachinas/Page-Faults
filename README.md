# Page Faults

This was a challenge for Spring 2014's CS 4414: Operating Systems class at the University of Virginia taught by Professor David Evans.

## Preliminary Questions

- When does a page fault occur?
	- A page fault occurs
- **Question: Is there a way to exploit this to write a program that generates approximately *N* page faults?**
	- Yes!

## Breakdown of the Code

1. By using `getpagesize()` or something similar, we grab the machine's given page size. 
	- By default, on an x86 machine, this should be 4 KB = 4096 bytes.

2. Next, by using `sizeof(int)`, we can grab the language's `signed integer` size.
	- For C, this should default to 4 bytes.
	- For Rust, this defaults to 8 bytes.
	- For Python, this defaults to 24 bytes.

3. Then, we can find the number of `int`s per page.
	- For C, 4096/4 = 1024.
	- For Rust, 4096/8 = 512.
	- For Python, 4096/24 = 170.67 ~ 171.

4. By using a 2D int array `int arr[N][ints_per_page]`, where `N` = number of desired page faults and `ints_per_page` = page sized normalized to an int, we loop in column major order, which skips over an entire page. Therefore, each iteration of the inner loop results in a minor page fault. Having N rows means we ultimately perform this N times, which yields approximately N page faults.

## Running the Code

### What you'll need:
- C Compiler: `gcc`, `clang`, or `llvm` compiler
	- My 2011 13" Macbook Air Mac OS X 10.9.1 runs `Apple LLVM version 5.0 (clang-500.2.79) (based on LLVM 3.3svn)`
- Rust Compiler: `rustc 0.9`
- Python Interpreter: (Anything really) 2.7.5 or higher
	- Mac OS X comes preinstalled with a Python interpreter
	
### How to Run Automated Test Script:
- First, ensure all print statements within page_fault.c, page_fault.rs, and page_fault.py are commented out.
- I have provided a Python test script which will run page_fault.c, page_fault.rs, and page_fault.py 500 times with varying inputs.
	- To run: `python run_script.py`
	- This will output several new files of the form `c_0.txt` denoting the language (C) and the number of desired page faults (0).
- Then, using `cat <textfile.txt> | grep "[0-9]*  page reclaims" | sed "s/[a-z]//g"> <output.out>` you can grab the specific number of minor page faults and pipe the result to a new file.
- Finally, to average each file, just run `python average.py < <output.out>`.

### How to Run without Test Script:
- For C: `gcc -o c_page_fault page_fault.c && /usr/bin/time -l ./c_page_fault <number of desired page faults>`.
	- Note: if you're using `clang`, just replace `gcc` with `clang` in previous command.
- For Rust: `rustc page_fault.rs && /usr/bin/time -l ./page_fault <number of desired page faults>`
- For Python: `/usr/bin/time -l python page_fault.py <number of desired page faults>`

**Note**: Also, if you run `top` and view the `FAULTS` column, this will list the approximate number of page faults for any given process. If you would like to see this program in `top`, just include the print statements so the programs execute for a longer duration.

**Note**: use `/usr/bin/time -l` because `time -l` is not a valid flag for that command.

**Note**: you will most likely see `page faults: 0`, this is OK! `page faults` indicates number of *major* page faults (to be discussed later...). What we're interested in is `page reclaims`, which are *minor* page faults.

## Results
From my test script, I found the following results:

#### For 0 desired page faults and 500 runs:
- **C**: 145.41
- **Rust**: 434.89
- **Python**: 1501.182

#### For 500 desired page faults and 500 runs:
- **C**: 641.648
- **Rust**: 937.048
- **Python**: 1664.762

## Difference between major and minor (and invalid!) page faults

### Major Page Faults
The page is still in memory, but the MMU doesn’t know about it.

### Minor Page Faults
The page is only on disk and must be retrieved with the disk penalty. 

### Invalid Page Faults
When MMU/TLB goes to disk address, null pointer or permission denial -> program terminates via segmentation fault and core is dumped.

### Can we write a program to generate *N* **major** page faults?
Maybe. The reason why major page faults are more difficult to program is because the OS will try to predict which pages you may want to access.

## The elephant, or *python*, in the room

### Why does Python generate 1000+ minor page faults every time the program runs?
If you're interested, the following article offers a great explanation as to the internal workings of Python. From this, you may be able to see where these page faults might be generated.

[Why Your Python Runs Slow Pt. 1, - Data Structures](http://lukauskas.co.uk/articles/2014/02/13/why-your-python-runs-slow-part-1-data-structures/)
## Sources
- CS 4414
- The Internet
