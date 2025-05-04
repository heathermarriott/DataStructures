#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAXROW 15
#define MAXCOL 15

typedef enum status {DEAD, ALIVE} Status;  //DEAD=0 ALIVE=1
typedef Status Grid[MAXROW][MAXCOL];

void copy_grid(Grid grid, Grid clone){
    int r, c;
    for (r=0; r< MAXROW; r++){
        for (c=0; c< MAXCOL; c++){
            clone[r][c]=grid[r][c];
        }
    }

}
void init(Grid grid){
    int r, c;
    for (r=0; r< MAXROW; r++){
        for (c=0; c< MAXCOL; c++){
            if (rand()%2 ==0){
                grid[r][c] = DEAD;
            }
            else {
                grid[r][c] = ALIVE;
            }
        }
    }
}

int neighbor_count(int row, int col, Grid grid){
    int neighbors=0;
    int c, r;
    int lowest_row=row, highest_row=row;
    int lowest_col=col, highest_col=col;
    //count neighbors above unless you are on row 0
    if (row >0){
        lowest_row= row-1;
    }
    //count neighbors below unless you are on last row
    if (row < (MAXROW-1)){
        highest_row= row+1;
    }
    //count neighbors to left unless you are at column 0
    if (col >0){
        lowest_col= col-1;
    }
    //count neighbors to right unless you are at last column
    if (col < (MAXCOL-1)){
        highest_col= col+1;
    }
    for (r=lowest_row; r<= highest_row; r++){
        for (c=lowest_col; c<= highest_col; c++){
            if ((r==row)&&(c==col)){
                continue; //don't count yourself 
            }
            neighbors+= grid[r][c];
        }
    }

    return neighbors;
}

void print_grid(Grid grid){
    int row, col, alive=0;
    static int day=0;
    day++;
    
    printf("\n\n");
    for (row=0; row< MAXROW; row++){
        for (col=0; col< MAXCOL; col++){
            if (grid[row][col] == ALIVE){
                printf("*");
                alive++;
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Day: %d\n", day);
    printf("Alive: %d\n", alive);
}

int someone_alive(Grid grid){
    int row, col;
    for (row=0; row< MAXROW; row++){
        for (col=0; col< MAXCOL; col++){
            if (grid[row][col] == ALIVE){
                return 1;
            }
        }
    }
    return 0;
}

void clear_screen(){
    printf("\033[2J\033[H");
}

int main() {
    Grid grid;
    Grid next_day;
    int next=1, neighbors;
    int row, col;
    
    srand(time(NULL));
    init(grid);
    clear_screen();
    print_grid(grid);
    
    while(someone_alive(grid) && next){
        for (row=0; row< MAXROW; row++){
            for (col=0; col< MAXCOL; col++){
                neighbors=neighbor_count(row, col, grid);
                switch (neighbors){
                    case 0:
                    case 1: //underpopulation
                        next_day[row][col] = DEAD;
                        break;
                    case 2: //stay alive or stay dead
                        next_day[row][col] = grid[row][col];
                        break;
                    case 3: 
                        next_day[row][col] = ALIVE;
                        break;
                    default: //4 or more neighbors, overcrowding
                        next_day[row][col] = DEAD;
                        break;
                } //end switch
            } //end for
        } //end for
        
        copy_grid(next_day, grid);
        sleep(1);
        clear_screen();
        print_grid(grid);
    }
    return 0;
}
