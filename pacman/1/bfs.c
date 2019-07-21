#include "util.h"
#include <stdio.h>
#include <string.h>
//bfs
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

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  int vis[100][100];
  memset(vis, 0, sizeof vis);
  int xi = state.start_x;
  int yi = state.start_y;
  int xt = state.goal_x;
  int yt = state.goal_y;
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
			  state.grid[xx][yy] == 0) {
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
 // printf("SSWSWWSW\n");
  
  // 
  destroy(&state);
  return 0;
}

