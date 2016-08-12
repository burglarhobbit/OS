import time,random

a = random.sample(range(1,10000000),1000000)

def mergesort(a):
	i = 0
	j = 0
	length = len(a)
	if length > 1:
		t = length/2
		left = mergesort(a[:t])
		right = mergesort(a[t:])
		for k in range(0,len(a)):
			if i<t and j<length-t:
				if left[i] > right[j]:
					a[k] = right[j]
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
	return a

length = len(a)/2
x = time.time()
ans = mergesort(a)
y = time.time()

print y-x