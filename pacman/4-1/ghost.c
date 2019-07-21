#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
	int x;
	int y;
} Node;
struct {
	Node posi;
	int parent;
} q[1000];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
char direct[4] = {'N', 'E', 'S', 'W'};
void BFS(game_state_t state, int xi, int yi, int xt, int yt) {
	int vis[100][100];
  	memset(vis, 0, sizeof vis);
	int rear = -1;
    int front = -1;
    rear++;
    q[rear].posi.x = xi;
    q[rear].posi.y = yi;
    q[rear].parent = -1;
    vis[xi][yi] = 1;
    Node path[1000];
    int count = 0;
    while(rear != front) {
	    front++;
  	  	Node e = q[front].posi;
	  	if (e.x == xt && e.y == yt) {
			    int k = q[front].parent;
				count++;
				path[count] = q[front].posi;
				while (k != -1) {
					count++;
					path[count] = q[k].posi;
					k = q[k].parent;
				}
				break;
	  	}
	 	xi = e.x;
	 	yi = e.y;
	 	for (int i = 0; i < 4; i++) {
		 	 int xx = xi + dx[i];
		  	 int yy = yi + dy[i];
		  	if (vis[xx][yy] == 0 &&
				state.grid[xx][yy] != 1 /*&&
				xx != state.ghost_x[0] &&
				yy != state.ghost_y[0]*/) {
			  	vis[xx][yy] = 1;
			  	rear++;
			    q[rear].posi.x = xx;
			    q[rear].posi.y = yy;
			    q[rear].parent = front;
		  	}
	  	}
 	 }
    for (int i = count; i>=1; i--) {
	  	  if (path[i].x == path[i - 1].x) {
				if (path[i].y == path[i - 1].y - 1) {
					printf("%c", direct[1]);
				} else if (path[i].y == path[i - 1].y +1) {
					printf("%c", direct[3]);
				}
			}
		    if (path[i].y == path[i - 1].y) {
				if (path[i].x == path[i - 1].x - 1)
					printf("%c", direct[2]);
				if (path[i].x == path[i - 1].x + 1)
					printf("%c", direct[0]);
			}
  	}
}

int main() {
    game_state_t state;
    memset(&state, 0, sizeof(state));
    init(&state);
  // write your code here
 
 
 
    srand(time(0));
    int dx[] = {-1, 0, 0, 1};
    int dy[] = {0, -1, 1, 0};
    char d_name[] = {NORTH, WEST, EAST, SOUTH};
  //state.grid[state.ghost_x[0]][state.ghost_y[0]] = 1;
  //state.grid[state.ghost_x[1]][state.ghost_y[1]] = 1;
 
    if (state.index == 0) {
        int i = 0;
        while (1) {
	        while(1) {
                int flag = 0;
	            int d1 = rand() % 4;
                int idx1 = 0;
                int tx1 = state.ghost_x[idx1] + dx[d1];
                int ty1 = state.ghost_y[idx1] + dy[d1];
	            if (i == 4
					 && tx1 >= 2 
					 && tx1 < state.n - 2 
					 && ty1 >= 2 
					 && ty1 <state.m  - 2
					 && !state.grid[tx1][ty1]) {
                    putchar(d_name[d1]);
	                flag = 1;
                    break;
                }
	            if (flag == 1 || i != 4){
	        	   break;
	            }
	        }
	        if (i == 4){
		        break;
	        }
            int d = i % 4;
            int idx = 0;
            int tx = state.ghost_x[idx] + dx[d];
            int ty = state.ghost_y[idx] + dy[d];
	        int len = abs (tx - state.start_x)
			        + abs (ty - state.start_y)
			        - abs (state.ghost_x[idx] - state.start_x)
			        - abs (state.ghost_y[idx] - state.start_y);
            if (tx >= 2 && tx < state.n - 2
				 && ty >= 2 && ty < state.m  - 2 
				 && !state.grid[tx][ty] && len < 0) {
                putchar(d_name[d]);
                break;
            }
	        i++;
      }
   }
   if (state.index == 1) {
  	   BFS(state, state.ghost_x[1], state.ghost_y[1],
			   state.start_x, state.start_y);
	
   } 
  //
    destroy(&state);
    return 0;
}


