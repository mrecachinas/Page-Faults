#!bin/python
import sys
file_input = map(int, map(str.rstrip, sys.__stdin__.readlines()))
print reduce(lambda x, y: x+y, file_input) / float(len(file_input))