#
#  A----6--------B
#  |             | \1
#  |1           2|  / C 
#  D_____1_______E/ 2
class TableEntry:
    def __init__(self, node, shortest_distance_to_start, prev=""):
        self.node = node
        self.dist = shortest_distance_to_start
        self.prev = prev
        self.visited = False
        self.pos_in_heap = -1
    def __str__(self):
        return f"{self.node} dist:{self.dist:4} prev:{self.prev:4} visited: {self.visited}"


class Heap:
    def __init__(self):
        self.heap = []
        
    def __str__(self):
        s="Heap:"
        for e in self.heap:
            s=s+"\n"+str(e)
        return s

    def down_heap(self, index):
        heap=self.heap
        left = 2*index + 1
        right = 2*index + 2
        while left < len(heap) - 1:
            biggest_child = left
            if right < len(heap)-1 and heap[right].dist < heap[left].dist:
                biggest_child = right
            if heap[biggest_child].dist < heap[index].dist:
                heap[index].pos_in_heap = biggest_child
                heap[biggest_child].pos_in_heap = index
                heap[index], heap[biggest_child] = heap[biggest_child], heap[index]
                
            else:
                break 
            index = biggest_child 
            left = 2*index + 1
            right = 2*index + 2

    def remove_from_heap(self):  #update edge to vertex
        heap=self.heap
        edge = heap[0]
        heap[0]=heap[len(heap)-1]
        heap[0].pos_in_heap = 0
        heap.pop()
        self.down_heap(0)
        return edge

    def up_heap(self, pos):
        heap=self.heap
        parent = int( (pos -1)/2 )
        
        while pos != 0 and heap[parent].dist > heap[pos].dist:
            heap[parent].pos_in_heap = pos
            heap[pos].pos_in_heap =parent
            heap[parent], heap[pos] = heap[pos], heap[parent]
            pos = parent
            parent = int( (pos -1)/2 )
        
    def add_to_heap(self, edge): #update edge to vertex
        heap=self.heap
        heap.append(edge)
        edge.pos_in_heap = len(heap)-1
        self.up_heap(len(heap)-1)

    

graph = {
    'A' : [('B', 6), ('D', 1)],
    'B' : [('A', 6), ('C', 1), ('E', 2) ],
    'C' : [('B', 1), ('E', 2)],
    'D' : [('A', 1),  ('E', 1)],
    'E' : [('B', 2), ('C', 2), ('D', 1)]
}

def print_table(table):
    #table is dictionary of node names (ex. A)
    #and TableEntry values 
    print("********table******")
    for k in table.keys():
        print(str(table[k]))
        
def update_table(g, node, table, heap):
    #find distance from start to node
    distance=table[node].dist
  
    #for all edgest connected to node, look at distance 
    for neighbor in g[node]:
        if table[neighbor[0]].dist > (neighbor[1] + distance):
            table[neighbor[0]].dist = neighbor[1] + distance
            table[neighbor[0]].prev = node
            heap.up_heap( table[neighbor[0]].pos_in_heap)
        
def find_smallest(table):
    small=999
    small_entry=None
    cnt=0
    for k in table.keys():
        if table[k].dist < small and table[k].visited == False:
            small=table[k].dist
            small_entry = k
        cnt=cnt+1
    
    if small_entry == None:
        return small_entry
    
    table[small_entry].visited = True
    return table[small_entry]

def dijkstras_shortest_path(g, start, end):
    table = { }
    unvisited = Heap() #heap keep track of smallest distances from unvisited nodes
    
    #populate table with start node distance 0 all others
    #999 (or a number to indicate infinity)
    for key in g.keys():
        if key == start:
            table[key] = TableEntry(key, 0)
        else:
            table[key]= TableEntry(key, 999)
        unvisited.add_to_heap(table[key])  #our heap is referencing the same items as table, not clone
        
    print("unvisited", unvisited)
    print_table(table)
    
    while len(unvisited.heap) > 0:
        #find the item in table with smallest shortest_distance_to_start
        min = unvisited.remove_from_heap()
        print("Smallest unvisited node: ",min.node, min.dist, min.prev)
        if min.dist == 999:
            break
        
        update_table(g, min.node, table, unvisited)
        
        print_table(table)
        print(unvisited)
            
    if len(unvisited.heap) > 0:
        print("some nodes in graph are unreachable")
        print("unvisited", unvisited)
        print("visited", visited)
        
    else:
        print("*********shortest path**************")
        path = [end ]
        entry=table[end]
        print("distance is:", entry.dist)
        while entry.prev != '':
            path.insert(0, entry.prev)
            entry=table[entry.prev]
        print(path)
        
dijkstras_shortest_path(graph, 'A', 'C')
