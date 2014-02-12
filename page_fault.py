#!/bin/python
import resource, sys

def page_fault():
	if len(sys.argv) != 2:
		print "Usage: python",sys.argv[0],"<number of desired page faults>"
		return

	N = int(sys.argv[1])

	print "Page size:", resource.getpagesize()
	print "Size of integer:", sys.getsizeof(N)

	ints_per_page = resource.getpagesize() / sys.getsizeof(N) # 
	arr = [0] * ints_per_page * N
	
	i = 0
	while i < len(arr):
		# print "arr[" + str(i) + "]: " + str( arr[i] ) # Slow version
		i += ints_per_page # skipping over an entire page, thus causing a minor page fault
	
if __name__ == "__main__":
	page_fault()