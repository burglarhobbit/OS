import time,random
from math import sqrt

def mergesort(a,sortBy):
	i = 0
	j = 0
	length = len(a)
	check = False
	if length > 1:
		t = length/2
		left = mergesort(a[:t],sortBy)
		right = mergesort(a[t:],sortBy)
		for k in range(0,length):
			if check:
				check = False
				continue
			if i<t and j<length-t:
				if left[i][sortBy] > right[j][sortBy]:
					a[k] = right[j]
					j += 1
				elif left[i][sortBy] < right[j][sortBy]:
					a[k] = left[i]
					i += 1
				else:
					a[k] = left[i]
					a[k+1] = right[j]
					i += 1
					j += 1
					check = True
			else:
				try:
					if i>=t:
						a[k] = right[j]
						j += 1
					elif j>=t:
						a[k] = left[i]
						i += 1
				except:
					pass
	return a[:]


def ClosestPair(PX,PY):
	l = len(PX)

	if l == 2:
		if PX[0] != PY [-1]:
			return PX[0],PY[-1]
		else:
			return PX[0],PY[0]	
	elif l > 2:
		d1 = None
		d2 = None
		delta = None
		p1 = None
		q1 = None
		p2 = None
		q2 = None
		if l/2 > 1:
			# Left Half
			QX = PX[0:l/2]
			QY = PY[0:l/2]
			#print "QX: %s" %str(QX)
			#print "QY: %s" %str(QY)
			p1,q1 = ClosestPair(QX[:],QY[:])
			#print "P1Q1: %s%s" %(str(p1),str(q1))
			d1 = sqrt((p1[0] - q1[0])**2 + (p1[1] - q1[1])**2)

		if l - (l/2) > 1:
			# Right Half
			RX = PX[l/2:]
			RY = PY[l/2:]
			#print "RX: %s" %str(RX)
			#print "RY: %s" %str(RY)
			
			p2,q2 = ClosestPair(RX[:],RY[:])
			#print "P2Q2: %s%s" %(str(p2),str(q2))			
			d2 = sqrt((p2[0] - q2[0])**2 + (p2[1] - q2[1])**2)

		if d1 is None:
			delta = d2
		elif d2 is None:
			delta = d1
		else:
			delta = min(d1,d2)

		p3,q3,d3 = ClosestSplitPair(PX[:],PY[:],delta)

		d = min(delta,d3)
		
		if d == d1:
			#print p1,q1
			return p1,q1
		elif d == d2:
			#print p2,q2
			return p2,q2
		elif d == d3:
			#print p3,q3
			return p3,q3
#	return PX[0],PY[0]
def ClosestSplitPair(PX,PY,delta):

	l = len(PX)

	xbar = PX[0:l/2][-1][0]
	SY = []
	for i in PY:
		if i[0] > xbar - delta and i[0] < xbar + delta:
			SY.append(i)

	best = delta
	bestPairP = None
	bestPairQ = None
	length_SY = len(SY)
	
	if length_SY > 1:
		#print "SY: %s" %str(SY)
		for i in range(0,min(length_SY,6)):
			for j in range(i+1,min(length_SY,7)):
				p = SY[i]
				q = SY[j]
				d = sqrt((p[0] - q[0])**2 + (p[1] - q[1])**2)
				if d < best:
					bestPairP = p
					bestPairQ = q
					best = d
	return bestPairP,bestPairQ,best

if __name__ == "__main__":
	#P = random.sample(range(1,100000000),10000000)
	#Q = random.sample(range(1,100),10)
	A = [ [ random.randint(1,100000000) for j in range(2) ] for i in range(10000000) ]

	#print A[:]
	print "Done!"
	AX = mergesort(A[:],0) # 0 = sort by X
	AY = mergesort(A[:],1) # 1 = sort by Y
	print "Sorting over!"
#	print AX	
#	print AY
	x = time.time()
	SplitPair = ClosestPair(AX[:],AY[:])
	print SplitPair

	# length = len(a)/2
	
	# ans = mergesort(a)
	y = time.time()

	print y-x	