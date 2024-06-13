class HeapNode:
    def __init__(self, name, priority):
        self.name = name
        self.priority = priority

def add_to_heap(heap):
    n = input("Enter name:")
    p = int(input("Enter priority:")) #if user enters non-int, will crash
    node = HeapNode(n, p)
    #always add to the end of the heap
    heap.append(node)
    #up heap
    pos = len(heap) - 1;
    parent = int( (pos -1)/2 )

    while pos != 0 and heap[parent].priority < heap[pos].priority:
        heap[parent], heap[pos] = heap[pos], heap[parent] #swap 2 nodes
        pos = parent
        parent = int( (pos -1)/2 ) #casting to int is like using lower fcn

def remove_from_heap(heap):
    if len(heap) == 0:
        print("heap is empty")
        return
    #for max heap always remove root (highst priority)
    print(f"Removing from heap: {heap[0].name} {heap[0].priority}")
    #pop last item off end of heap, use it to write over 1st item in heap  
    last = heap.pop() #heap size goes down by 1
    if len(heap) == 0:
        return
    heap[0] = last #replace previous 1st patent with last patient
    #down heap
    index = 0 
    left = 1
    right = 2
    while left < len(heap) - 1:
        biggest_child = left
        if right < len(heap)-1 and heap[right].priority > heap[left].priority:
            biggest_child = right
        if heap[biggest_child].priority > heap[index].priority:
            heap[index], heap[biggest_child] = heap[biggest_child], heap[index]
        else:
            break 
        index = biggest_child 
        left = 2*index + 1
        right = 2*index + 2
    
heap = [ ]  #start with an empty heap
x=int(input("Select 1=Add to Heap, 2=Remove from Heap, 3=Exit : "))
while x==1 or x==2:
    if x==1:
        add_to_heap(heap)
    elif x==2:
        remove_from_heap(heap)
    #print heap
    print("*****Heap*****")
    for patient in heap:
        print(f"{patient.name} {patient.priority}")
        
    x=int(input("Select 1=Add to Heap, 2=Remove from Heap, 3=Exit : "))
