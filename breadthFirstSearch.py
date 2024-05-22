# Video walkthrough:
# https://youtu.be/LwuHtD2EquM?si=vzNgfhkQZfbiACJh
#
graph = {
    1 : [2, 12],
    2 : [3, 13],
    3 : [4, 9],
    4 : [5],
    5 :[3],
    6 : [5],
    7 : [9],
    8 : [7, 10, 15],
    9 : [6, 12],
    10: [14],
    11: [8,13],
    12: [11, 14],
    13: [],
    14: [8],
    15: [6]
}

def bfs(graph, root):
    visited=[root]
    queue = [root]

    while queue:
        x = queue.pop(0)
    
        for child in graph[x]:
            if child not in visited:
                visited.append(child)
                queue.append(child)
    print(visited)
           
bfs(graph, 1)
