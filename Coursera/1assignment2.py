#Count no. of inversions
import time

array = []
with open('IntegerArray.txt') as f:
	array = [int(line) for line in f]

#print array
#array = [111,1,15,3,20,5,7,9,67,2,4,6,8,12,56,23,112]
#inv = 0
def mergesort(array1,array2,inversion):
	length1 = len(array1)
	length2 = len(array2)
	C = []
	A = []
	B = []
	i = 0
	j = 0
	inv = inversion
	if length1 > 1:
		t = length1/2
		A,inv = mergesort(array1[:t],array1[t:],inv)
		#inv += inv1
	else:
		A = array1
	if length2 > 1:
		t = length2/2
		B,inv = mergesort(array2[:t],array2[t:],inv)
		#inv += inv2
	else:
		B = array2
	for k in range(0,length1+length2):
		if i<length1 and j<length2:
			if A[i] > B[j]:
				C.append(B[j])
				j = j + 1
				inv = inv + len(A) - i
			elif A[i] < B[j]:
				C.append(A[i])
				i = i + 1
		else:
			if i>=length1:
				C.append(B[j])
				j += 1
			else:
				C.append(A[i])
				i += 1
	return C[:],inv

length = len(array)/2
x = time.time()
ans,inv = mergesort(array[:length],array[length:],0)
y = time.time()
print inv
print y-x