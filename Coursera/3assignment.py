#Karger Minimum Cut for graphs

import csv

arr = list()
count = 0
with open('kargerMinCut.txt') as f:
	reader = csv.reader(f, dialect='excel', delimiter='\t')
	for i,line in enumerate(reader):
		for j,value in enumerate(line):
			if value!= '':
				if j==0:
					arr.append([int(value)])
				else:
					arr[i].append(int(value))

