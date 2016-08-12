import time,random

a = random.sample(range(1,1000000),100000)

def mergesort(array1,array2):
	length1 = len(array1)
	length2 = len(array2)
	C = []
	A = []
	B = []
	i = 0
	j = 0
	if length1 > 1:
		t = length1/2
		A = mergesort(array1[:t],array1[t:])
	else:
		A = array1
	if length2 > 1:
		t = length2/2
		B = mergesort(array2[:t],array2[t:])
	else:
		B = array2
	for k in range(0,length1+length2):
		if i<length1 and j<length2:
			if A[i] > B[j]:
				C.append(B[j])
				j = j + 1
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
	return C[:]

length = len(a)/2
x = time.time()
ans = mergesort(a[:length],a[length:])
y = time.time()

print y-x