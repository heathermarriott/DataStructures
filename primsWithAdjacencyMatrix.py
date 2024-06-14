class Edge:
    def __init__(self, x, y, weight):
        self.x = x
        self.y = y
        self.weight = weight
    def __str__(self):
        return f"{chr(self.x+65)}->{chr(self.y+65)} weight:{self.weight}"

def down_heap(heap, index):
    left = 2*index + 1
    right = 2*index + 2
    while left < len(heap) - 1:
        biggest_child = left
        if right < len(heap)-1 and heap[right].weight < heap[left].weight:
            biggest_child = right
        if heap[biggest_child].weight < heap[index].weight:
            heap[index], heap[biggest_child] = heap[biggest_child], heap[index]
        else:
            break 
        index = biggest_child 
        left = 2*index + 1
        right = 2*index + 2

def remove_from_heap(heap):
    edge = heap[0]
    heap[0]=heap[len(heap)-1]
    heap.pop()
    down_heap(heap, 0)
    return edge

def up_heap(heap, pos):
    parent = int( (pos -1)/2 )
    
    while pos != 0 and heap[parent].weight > heap[pos].weight:
        heap[parent], heap[pos] = heap[pos], heap[parent]
        pos = parent
        parent = int( (pos -1)/2 )
    
def add_to_heap(heap, edge):
    heap.append(edge)
    up_heap(heap, len(heap)-1)
    
def prims(g, starting_node):
    """ Find the minimum spanning tree
        g - a graph in adjacency matrix format
        starting_node - 0=A 1=B, ....
    """
    mst=[]
    visited= [False] * len(g[0])
    heap=[] #priority queue with edges 
    cost=0
    visited[starting_node] = True
    
    #add all edges from starting_node not min_heap
    for x in range(0, len(g[0])):
        if g[starting_node][x] == 0: #starting_node == x:
            continue
        else:
            add_to_heap(heap, Edge(starting_node, x, g[starting_node][x]))
    print([str(e) for e in heap])
    
    while len(heap) > 0 and len(mst) < len(g[0])-1:
        smallest=remove_from_heap(heap)
        if not visited[smallest.y] :
            visited[smallest.y] = True
            mst.append(smallest)
            #add all edges from smallest to heap if unvisited
            for x in range(0, len(g[0])):
                if g[smallest.y][x] == 0:
                    continue
                else:
                    add_to_heap(heap, Edge(smallest.y, x, g[smallest.y][x]))
            print([str(e) for e in heap])
  
    print("MST: ")
    for e in mst:
        print(e)
    
#         A  B  C  D       
graph = [ [0, 4, 2, 6], 
          [4, 0, 1, 4],
          [2, 1, 0, 3],
          [6, 4, 3, 0]]
#    'A' : [('B', 4),('C', 2), ('D', 6)],
#    'B' : [('A', 4), ('C', 1), ('D', 4)],
#    'C' : [('A', 2), ('B', 1), ('D', 3)],
#    'D' : [('A', 6), ('B', 4), ('C', 3)]
#    }
    
#pick starting vertex
prims(graph, 0)   #'A') A=0 B=1 C=2 D=3
