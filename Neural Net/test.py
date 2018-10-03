import random
import time
#!/bin/python3

import math
import os
import random
import re
import sys

def quickSort(arr):
	partition(arr, 0, len(arr))
	return arr

def partition(arr, low, hi):
	if(hi - low) <= 1:
		return 1
	ci = low
	pi = low
	pv = arr[low]
	for i in range(low + 1, hi):
		if pv > arr[i]:
			temp = arr[i]
			arr[i] = arr[pi]
			arr[pi] = temp
			pi += 1
			ci = i
	arr[ci] = arr[pi]
	arr[pi] = pv
	partition(arr, low, pi)
	partition(arr, pi + 1, hi)

def bigSorting(unsorted):
    i = [int(x) for x in unsorted]
    quickSort(i)
    return i

print("this program start...")
fptr = open("input.txt")
print("The file is open...")
n = int(fptr.readline())
unsorted = []
print(n)
for _ in range(n):
    unsorted_item = fptr.readline()
    unsorted.append(unsorted_item)
print("Starting bigSorting")
result = bigSorting(unsorted)

print(result)

fptr.close()


def generateInts(num=100):
	nums = []
	for i in range(num):
		nums.append(int((random.random()*1000)//1))
	return nums

def test(n):
	arr = generateInts(n)
	start = time.clock()
	quickSort(arr)
	run_time = time.clock() - start
	return run_time

#fptr = open("test.txt", "w")

#for i in range(100, 100000, 100):
#	print(i)
#	fptr.write("{}, {}\n".format(i,test(i)*1000000))

#fptr.close()
