# Compute Strongly Connected Components of a given graph

import time

fin = open("GraphSampleDirected.txt","r")
graph = {}
inverse_graph = {}
vertex = [] # All the vertexes are stored in this list
for line in fin:
	node = int(line.split()[0])
	vertex.append(node)
	edges = []
	
	for edge in line.split()[1:]:
		edges.append(int(edge))
		graph[node] = edges
		
		append_present_vertex = inverse_graph.get(int(edge),[])
		append_present_vertex.append(node)		
		inverse_graph[int(edge)] = append_present_vertex
fin.close()

n = len(vertex) # no. of elements
traversal = []

time_count = 0
timewise_visited_vertex = [0]*n # (Index = time, value = vertex)
strongly_conn_comps = [] # Leaders list
leader = None # Current Leader while Recursively traversing through the graph

# For computing time taken over each vertex for Inverse Graph
def DepthFirstSearchInverse(Graph,v):
	global traversal,time_count,timewise_visited_vertex
	
	traversal.append(v)
	s = Graph.get(v,None)
	if s is not None:
		for edge in s:
			if edge not in traversal:
				print edge
				DepthFirstSearchInverse(Graph,edge)
				timewise_visited_vertex[time_count] = edge
				time_count += 1

def DFSLoopInverse(Graph,vertexlist):
	global traversal,time_count,timewise_visited_vertex
	for v in vertexlist:
		if v not in traversal:
			timewise_visited_vertex[time_count] = v
			time_count += 1
			DepthFirstSearchInverse(Graph,v)

# For computing strongly connected components
def DepthFirstSearch(Graph,v):
	global traversal,strongly_conn_comps,leader

	strongly_conn_comps.append((v,leader))
	traversal.append(v)

	s = Graph.get(v,None)
	if s is not None:
		for edge in s:
			if edge not in traversal:
				DepthFirstSearch(Graph,edge)

def DFSLoop(Graph,vertexlist):
	global traversal,strongly_conn_comps,leader
	for v in vertexlist:
		if v not in traversal:
			leader = v
			DepthFirstSearch(Graph,v)
			# strongly_conn_comps.append(v) 

DFSLoopInverse(inverse_graph,vertex)
print timewise_visited_vertex
traversal = []
DFSLoop(graph, reversed(timewise_visited_vertex))
print strongly_conn_comps

