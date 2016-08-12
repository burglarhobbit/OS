#Count the number of steps for comparison using first element as pivot

import time

arr = []
count = 0
with open('QuickSort.txt') as f:
	arr = [int(line) for line in f]

def quicksort(array,count):
	length = len(array)
	i = 1
	if length > 1:
		pivot = array[0]
		
		for j in range(1,length):
			if pivot > array[j]:
				temp = array[i]
				array[i] = array[j]
				array[j] = temp
				i += 1
		count += length - 1
		temp = array[i-1]
		array[i-1] = array[0]
		array[0] = temp
		
		leftPart,count = quicksort(array[:i-1],count)
		rightPart,count = quicksort(array[i:],count)
		return leftPart + [pivot] + rightPart,count
	return array,count

array,count = quicksort(arr,count)
#print array
print count	