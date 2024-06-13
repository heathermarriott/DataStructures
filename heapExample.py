#Example from the YouTube video: 
#https://youtu.be/M3uLrB6XAAY?si=NENNrpovJk2u8Ptr
#
class HeapNode:
    def __init__(self, name, priority):
        self.name = name
        self.priority = priority
        
bobby = HeapNode("Bobby", 90)
sue = HeapNode("Sue", 75)
john = HeapNode("John", 50)
alice = HeapNode("Alice", 20)
mary = HeapNode("Mary", 60)

heap = [bobby, sue, john, alice, mary]
ben = HeapNode("Ben", 99)
heap.append(ben)
for patient in heap:
    print(f"{patient.name} {patient.priority}")
    
#up heap
ben_pos = len(heap) - 1;
parent = int( (ben_pos -1)/2 )
print(f"ben_pos={ben_pos}  parent_pos={parent}")

while ben_pos != 0 and heap[parent].priority < heap[ben_pos].priority:
    heap[parent], heap[ben_pos] = heap[ben_pos], heap[parent]
    ben_pos = parent
    parent = int( (ben_pos -1)/2 )
    
for patient in heap:
    print(f"{patient.name} {patient.priority}")
    
#Remove node and use it to replace the root
last = heap.pop()
print(f"removing {heap[0].name}")
heap[0] = last

for patient in heap:
    print(f"{patient.name} {patient.priority}")
print("*******************") 
    
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
for patient in heap:
    print(f"{patient.name} {patient.priority}")
