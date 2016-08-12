#Breadth First Search


import random

fin = open("GraphSampleDirected.txt","r")
graph = {}
vertex = []
for line in fin:
	node = int(line.split()[0])
	vertex.append(node)
	edges = []
	for edge in line.split()[1:]:
		edges.append(int(edge))
		graph[node] = edges
fin.close()
'''for key,value in graph.iteritems():
    print key,value
'''
n = len(vertex) # no. of elements
f = [0]*n

traversal = []
current_label = n

def DepthFirstSearch(Dict,v):
	global traversal,current_label,f
		
	traversal.append(v)
	s = Dict.get(v,None)
	if s is not None:
		for edge in s:
			if edge not in traversal:
				DepthFirstSearch(Dict,edge)
	f[v-1] = current_label
	current_label -= 1

def DFSLoop(Graph):
	global traversal,vertex
	for v in vertex:
		if v not in traversal:
			DepthFirstSearch(Graph,v)

DFSLoop(graph)
print zip(vertex,f) #(VertexIndex,TopologicalOrder)
