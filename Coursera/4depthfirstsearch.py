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

stack = list()
traversal = []


def DepthFirstSearch(Dict,v,destination):
	global traversal
		
	traversal.append(v)	
	if v == destination:
		return True
	for edge in Dict[v]:
		if edge not in traversal:
			if edge == destination:
				return True
			else:
				return	DepthFirstSearch(Dict,edge,destination)

print DepthFirstSearch(graph,10,7)
