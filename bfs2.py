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

def bfs(graph, root, dest):
    visited = [root]
    queue = [root]
    parent = {root: None}   

    while queue:
        x = queue.pop(0)

        if x == dest:       
            break

        for child in graph[x]:
            if child not in visited:
                visited.append(child)
                parent[child] = x   
                queue.append(child)

    # reconstruct BFS path
    path = []
    curr = dest
    while curr is not None:
        path.append(curr)
        curr = parent[curr]

    path.reverse()
    print("Path:", path)

print("starting point is 1")
dest = int(input("Enter destination: "))
bfs(graph, 1, dest)


