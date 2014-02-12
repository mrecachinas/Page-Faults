#!bin/python
import os

os.system("rm *.txt")
os.system("clang -o page_fault_c *.c")
os.system("touch c_0.txt")
os.system("touch c_500.txt")

os.system("touch py_0.txt")
os.system("touch py_500.txt")

os.system("rustc page_fault.rs")
os.system("touch rs_0.txt")
os.system("touch rs_500.txt")
for i in xrange(0, 500):
	os.system("(/usr/bin/time -l ./page_fault_c 0) 2>> c_0.txt")
	os.system("(/usr/bin/time -l ./page_fault_c 500) 2>> c_500.txt")
	os.system("(/usr/bin/time -l ./page_fault 0) 2>> rs_0.txt")
	os.system("(/usr/bin/time -l ./page_fault 500) 2>> rs_500.txt")
	os.system("(/usr/bin/time -l python page_fault.py 0) 2>> py_0.txt")
	os.system("(/usr/bin/time -l python page_fault.py 500) 2>> py_500.txt")