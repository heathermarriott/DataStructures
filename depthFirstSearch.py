#Create a Depth First Search
graph = {
    1 : [2, 12],
    2 : [3, 13],
    3 : [4, 9],
    4 : [5],
    5 : [ ],
    6 : [ ],
    7 : [ ],
    8 : [7, 10, 15],
    9 : [6],
    10: [],
    11: [8],
    12: [11, 14],
    13: [],
    14: [8],
    15: [6]
}
def dfs(graph, root):
    visited=[]
    stack=[root]
    
    while stack:
        x = stack.pop()
        if x not in visited:
            visited.append(x)
            #add children of x in reverse order
            for child in graph[x][::-1]:
                stack.append(child)
    print(visited)

dfs(graph, 1)
