

begin_puzzle=[[2,5,3],[1,9,6],[4,7,8]]


def print_board(board):
    print("-"*15)
    for r in board:
        for x in r:
            if x!= 9:
                print(f"| {x} |",end='')
            else:
                print("|   |",end='')
        print("")
        print("-"*15)

#take current board, return all possible other boards
#when legal move taken
def deep_copy(board):
    #makes a deep copy of board
    new_array=[[j for j in i ] for i in board]
    #print(new_array)
    return new_array

def next_moves(board):
    nine_row=0
    nine_col=0
    #figure out where blank space is (9 pos)
    for i in range(len(board)):
        for j in range(len(board[0])):
            if board[i][j]==9:
                nine_row=i
                nine_col=j
    pos=[] #possible next boards
    if nine_row>0: #could swap up
        up_board=deep_copy(board)
        up_board[nine_row -1][nine_col]=board[nine_row][nine_col]
        up_board[nine_row][nine_col]=board[nine_row-1][nine_col]
        pos.append(up_board)
    if nine_row<2: #could swap down
        down_board=deep_copy(board)
        down_board[nine_row +1][nine_col]=board[nine_row][nine_col]
        down_board[nine_row][nine_col]=board[nine_row+1][nine_col]
        pos.append(down_board)
    if nine_col>0: #could swap left
        left_board=deep_copy(board)
        left_board[nine_row][nine_col-1]=board[nine_row][nine_col]
        left_board[nine_row][nine_col]=board[nine_row][nine_col-1]
        pos.append(left_board)
    if nine_col<2: #could swap right
        right_board=deep_copy(board)
        right_board[nine_row][nine_col+1]=board[nine_row][nine_col]
        right_board[nine_row][nine_col]=board[nine_row][nine_col+1]
        pos.append(right_board)
    return pos

def BFS(start_node):
    queue = []
    start_index=0
    queue.append(start_node)

    # we want an end board like this 9=blank space
    end_puzzle=[[1,2,3],[4,5,6],[7,8,9]]
    visited = {}
    visited[str(start_node)]=None

    while queue[start_index] != end_puzzle :
        x=queue[start_index]
        start_index+=1 
           
        for b in next_moves(x): 
            if str(b) not in visited:
                visited[str(b)]=x
                queue.append(b)
    #construct BFS path by reversing order
    path =[]
    curr=end_puzzle
    while curr is not None:
        path.append(curr)
        curr=visited[str(curr)]
    path.reverse()
    for p in path:
        print_board(p)
        
print("begin_puzzle", begin_puzzle)
print("******beginning board****")
print_board(begin_puzzle)
print("************************")
BFS(begin_puzzle)
