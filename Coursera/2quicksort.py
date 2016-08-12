
arr = [11,1,15,3,20,5,7,9,67,2,4,6,8,12,56,23,112]

def quicksort(array):
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
	
		temp = array[i-1]
		array[i-1] = array[0]
		array[0] = temp
		
		leftPart = quicksort(array[:i-1])
		rightPart = quicksort(array[i:])
		return leftPart + [pivot] + rightPart
	return array

array = quicksort(arr)
print array