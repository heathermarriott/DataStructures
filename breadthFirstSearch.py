# Video walkthrough:
# https://youtu.be/mDYEhcKpiz0
#
graph = {
    1 : [2, 12],
    2 : [1, 3, 13],
    3 : [2, 4, 9],
    4 : [3, 5],
    5 : [4, 5],
    6 : [5, 9, 15],
    7 : [8, 9],
    8 : [7, 10, 11, 14, 15],
    9 : [3, 6, 7],
    10: [8],
    11: [8,12, 13],
    12: [1, 11, 14],
    13: [2, 11],
    14: [8, 12],
    15: [6, 8]
}

def bfs(graph, root):
    visited=[root]
    queue = [root]

    while queue:
        x = queue.pop(0) #by popping element in position 0, this behaves like a Queue
    
        for child in graph[x]:
            if child not in visited:
                visited.append(child)
                queue.append(child)
    print(visited)
           
bfs(graph, 1)
