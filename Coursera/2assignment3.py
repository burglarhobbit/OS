#Count the number of steps for comparison using last element as pivot

import time

arr = []
count = 0
with open('QuickSort.txt') as f:
	arr = [int(line) for line in f]

def quicksort(array,count):
	length = len(array)
	i = 1
	if length > 1:
		middle = 0
		pivot = array[0]
		pivotPos = 0

		if length%2 == 0:
			middle = (length/2) - 1
		else:
			middle = length/2
		mid = array[middle]
		if (mid > array[0] and mid < array[-1]) or (mid < array[0] and mid > array[-1]):
			pivot = mid
			pivotPos = middle

		elif (array[0] > array[-1] and array[0] < mid) or (array[0] < array[-1] and array[0] > mid):
			pivot = array[0]
			pivotPos = 0

		elif (array[-1] > mid and array[-1] < array[0]) or (array[-1] < mid and array[-1] > array[0]):
			pivot = array[-1]
			pivotPos = -1
		if pivotPos != 0:
			temp = array[0]
			array[0] = array[pivotPos]
			array[pivotPos] = temp
		for j in range(1,length):
			if pivot > array[j]:
				temp = array[i]
				array[i] = array[j]
				array[j] = temp
				i += 1
		count += length - 1
		temp = array[i - 1]
		array[i - 1] = array[0]
		array[0] = temp
		
		leftPart,count = quicksort(array[:i-1],count)
		rightPart,count = quicksort(array[i:],count)
		return leftPart + [pivot] + rightPart,count
	return array,count

array,count = quicksort(arr,count)
#print array
print count
j = 0	
for i in range(0,9999):
	for z in range(i+1,10000):
		if array[i] > array[z]:
			#print "False"
			j +=1
print j