#Breadth First Search


import random

fin = open("GraphSample.txt","r")
graph = {}
for line in fin:
	node = int(line.split()[0])
	edges = []
	for edge in line.split()[1:]:
		edges.append(int(edge))
		graph[node] = edges
fin.close()
'''for key,value in graph.iteritems():
    print key,value
'''
class Queue: #Use Stack, if we want to use depth first search
	def __init__(self):
		self.items = []
	
	def isEmpty(self):
		return self.items == []

	def enqueue(self, item):
		self.items.insert(0,item)

	def dequeue(self):
		return self.items.pop()

	def size(self):
		return len(self.items)

def BreadthFirstSearch(Dict,ver,dest):
	traversal = []
	traversal.append(ver)
	q1 = Queue()
	q1.enqueue((ver,0)) # 0 = distance
	minPath = None
	if dest == ver:
		minPath = 0

	while q1.isEmpty() == False:
		v,distance =  q1.dequeue()
		#path += 1
		for edge in Dict[v]:
			if edge not in traversal:
				traversal.append(edge)
				if edge == dest:
					return distance + 1,traversal
				else:
					q1.enqueue((edge,distance+1))
	return 0

print BreadthFirstSearch(graph,10,7)

