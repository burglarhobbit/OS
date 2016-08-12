#Count no. of inversions
import time

array = []
with open('IntegerArray.txt') as f:
	array = [int(line) for line in f]

#print array
#array = [111,1,15,3,20,5,7,9,67,2,4,6,8,12,56,23,112]

def mergesort(a,inv):
	i = 0
	j = 0
	length = len(a)
#	inv = inversions
	if length > 1:
		t = length/2
		left,inv = mergesort(a[:t],inv)
		right,inv = mergesort(a[t:],inv)

		for k in range(0,len(a)):
			if i<t and j<length-t:
				if left[i] > right[j]:
					a[k] = right[j]
					inv = inv + len(left) - i
					j += 1
				elif left[i] < right[j]:
					a[k] = left[i]
					i += 1
			else:
				if i>=t:
					a[k] = right[j]
					j += 1
				else:
					a[k] = left[i]
					i += 1
	return a,inv

# length = len(a)/2
x = time.time()
ans,inversions = mergesort(array,0)
y = time.time()
print inversions
print y-x