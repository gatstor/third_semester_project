#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define eds 2.71828
typedef struct {
	int x;
	int y;
} Node;
struct {
	Node posi;
	int parent;
} q[100000];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
char direct[4] = {'N', 'E', 'S', 'W'};
typedef struct {
	int x, y;
} Food_posi;
int BFS(int **grid, int xi, int yi, int xt, int yt, int d/*, int food_num, Food_posi food_posi[]*/) {
	int vis[200][200];
  	memset(vis, 0, sizeof vis);
	int rear = -1;
    int front = -1;
    rear++;
    q[rear].posi.x = xi;
    q[rear].posi.y = yi;
    q[rear].parent = -1;
    vis[xi][yi] = 1;
    Node path[10000];
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
				grid[xx][yy] == 0) {
			  	vis[xx][yy] = 1;
			  	rear++;
			    q[rear].posi.x = xx;
			    q[rear].posi.y = yy;
			    q[rear].parent = front;
		  	}
	  	}
 	 }
    for (int i = count; i >= 1; i--) {
	  	  if (path[i].x == path[i - 1].x) {
				if (path[i].y == path[i - 1].y - 1) {
					//printf("%c", direct[1]);
					d++;
				} else if (path[i].y == path[i - 1].y +1) {
					d++;
					//printf("%c", direct[3]);
				}
			}
		    if (path[i].y == path[i - 1].y) {
				if (path[i].x == path[i - 1].x - 1)
					d++;
				    //printf("%c", direct[2]);
				if (path[i].x == path[i - 1].x + 1)
					d++;
					//printf("%c", direct[0]);
			}
			/*for (int j = 0; j < food_num; j++) {
				if(food_posi[j].x == path[i - 1].x &&
				   food_posi[j].y == path[i - 1].y) {
					tag[j] = 1;
				}
			}*/
  	}
	return d;
}
int tag1[1000];
void BFS1(int **grid, int xi, int yi, int xt, int yt, int food_num, Food_posi food_posi[]) {
	for (int i = 0; i < 1000; i++) {
		tag1[i] = 0;
	}
	int vis[200][200];
  	memset(vis, 0, sizeof vis);
	int rear = -1;
    int front = -1;
    rear++;
    q[rear].posi.x = xi;
    q[rear].posi.y = yi;
    q[rear].parent = -1;
    vis[xi][yi] = 1;
    Node path[5000];
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
				grid[xx][yy] == 0) {
			  	vis[xx][yy] = 1;
			  	rear++;
			    q[rear].posi.x = xx;
			    q[rear].posi.y = yy;
			    q[rear].parent = front;
		  	}
	  	}
 	 }
    for (int i = count; i >= 1; i--) {
	  	  if (path[i].x == path[i - 1].x) {
				if (path[i].y == path[i - 1].y - 1) {
					printf("%c", direct[1]);
				} else if (path[i].y == path[i - 1].y + 1) {
					printf("%c", direct[3]);
				}
			}
		    if (path[i].y == path[i - 1].y) {
				if (path[i].x == path[i - 1].x - 1)
					printf("%c", direct[2]);
				if (path[i].x == path[i - 1].x + 1)
					printf("%c", direct[0]);
			}	
            for (int j = 0; j <= food_num; j++) {
				if(food_posi[j].x == path[i - 1].x &&
				   food_posi[j].y == path[i - 1].y ||
				   food_posi[j].x == path[i].x &&
				   food_posi[j].y == path[i].y) {
					tag1[j] = 1;
				}
  			}
		}
}


/*typedef struct {
	int x, y;
} Food_posi;*/

void swap(Food_posi *a, Food_posi *b) {
	Food_posi tmp = *a;
	*a = *b;
	*b = tmp;
}

int H_dist(int xi, int yi, int xt, int yt) {
	//return abs(xt - xi) + abs(yt - yi);
	int x = xt - xi;
	int y = yt - yi;
	if (x < 0) {
		x = -x;
	}
	if (y < 0) {
		y = -y;
	}
	return x + y;
}

typedef struct {
	int x, y;
	int length;
} Food;
int getgreedy(game_state_t state, Food_posi food_posi[]) {
	int cntnum = 0;
	Food food_posi_len[10000];//food position and distance from start to food every time
    int food_num = 0;
    int n = state.n;
    int m = state.m;	
    for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (state.food[i][j] == 1) {
				food_posi_len[food_num].x = i;
				food_posi_len[food_num].y = j;
				food_posi_len[food_num].length = H_dist(state.start_x, state.start_y, i, j);
				food_num++;
			}
		}
	}
	//printf("food_num = %d\n", food_num);
	int tag[10000];
	memset(tag, 0, 10000);
	int min = 0x3f3f3f3f;
	int tmp;//store the minimum length of food's posi in array 
	for (int i = 0; i < food_num; i++) {
		if(food_posi_len[i].length < min) {
			min = food_posi_len[i].length;
			tmp = i;
		}
	}
	//printf("tmp = %d\n", tmp);
	tag[tmp] = 1;
	int xi = state.start_x;
	int yi = state.start_y;
	while(1) {
		int vis[1000][1000];
  		//memset(vis, 0, sizeof vis);
	//	printf("xi = %d yi = %d\n", xi, yi);
		for (int i = 0; i < 1000; i++) {
			for (int j = 0; j < 1000; j++) {
				vis[i][j] = 0;
			}
		}
  		//int xi = state.start_x;
  		//int yi = state.start_y;
  		int xt = food_posi_len[tmp].x;
  		int yt = food_posi_len[tmp].y;
		food_posi[cntnum].x = xt;
		food_posi[cntnum].y = yt;
		cntnum++;
		//printf("x = %d y = %d cnt = %d\n", food_posi[cntnum - 1].x, food_posi[cntnum - 1].y, cntnum - 1);
		//printf("xt = %d yt = %d\n", xt, yt);
   		int rear = -1;
        int front = -1;
        rear++;
        q[rear].posi.x = xi;
  		q[rear].posi.y = yi;
  		q[rear].parent = -1;
  		vis[xi][yi] = 1;
  		Node path[10000];
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
		//for (int i = 0; i < food_num; i++) {
		//	printf("tag[%d] = %d\n", i, tag[i]);
		//}
		for (int i = count; i>=1; i--) {//print one path
			for (int j = 0; j < food_num; j++) {
				if (path[i - 1].x == food_posi_len[j].x &&
					path[i - 1].y == food_posi_len[j].y) {
					tag[j] = 1;
				}
				if (path[i].x == food_posi_len[j].x &&
					path[i].y == food_posi_len[j].y) {
					tag[j] = 1;
				}
			}
		/*	if (path[i].x == path[i - 1].x) {
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
			}*/
  		}
		//for (int i = 0; i < food_num; i++) {
		//	printf("\ntag[%d] = %d\n", i, tag[i]);
		//}
		int check = 1;
		for (int i = 0; i < food_num; i++){
			if (tag[i] == 0) {
				check = 0;
			}
		}
		//printf("check = %d\n", check);	
		if (check == 1) {
			/*printf("cntnum = %d\n", cntnum);
			for (int i = 0; i <)*/
			return cntnum;
		}
		check = 1;
		xi = xt;
		yi = yt;
		for (int i = 0; i < food_num; i++) {
			if (tag[i] == 0 ) {
				food_posi_len[i].length = H_dist(xi, yi, food_posi_len[i].x, food_posi_len[i].y);
			}
		}
		min = 0x3f3f3f3f;
		for (int i = 0; i < food_num; i++) {
			if (min > food_posi_len[i].length && tag[i] == 0) {
				min = food_posi_len[i].length;
				tmp = i;
			}
		}

	}	
	//printf("cntnum = %d\n", cntnum);
	//return cntnum; 
}
int main() {
    game_state_t state;
    memset(&state, 0, sizeof(state));
    init(&state);
    // write your code here
	int n = state.n;
    int m = state.m;
	Food_posi food_posi[1000];
	int count = getgreedy(state, food_posi);//include start
	food_posi[count].x = state.start_x;
    food_posi[count].y = state.start_y;
	for (int i = 0; i <= (count -1) / 2; i++) {
		swap(&food_posi[i], &food_posi[count -1 -i]);
	}
	//printf("%d\n", count);
	//for (int i = 0; i <= count; i++) {
	//	printf("x = %d y = %d\n", food_posi[i].x, food_posi[i].y);
	//}
   /*int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (state.food[i][j] == 1) {
				 food_posi[count].x = i;
				 food_posi[count].y = j;
				 count++;
			}
		}
	}	//store food position
	food_posi[count].x = state.start_x;
	food_posi[count].y = state.start_y;*/
    // printf("WEESSWW\n");
    int intial_sum = 0;
    for (int i = count; i > 0; i--) {
	    intial_sum += BFS(state.grid, food_posi[i].x, food_posi[i].y, food_posi[i - 1].x, food_posi[i - 1].y, -1);
    }
    //printf("%d\n", intial_sum);
    srand(time(NULL));
	int out_count = 0;
	int out_time = count;
	int swap_sum;
	while (out_count < out_time) {
		swap_sum = 0;
        double T = (out_time) / (out_count + 1) * 0.01;
		int swap1 = rand() % count;
		int swap2 = rand() % count;
		swap(&food_posi[swap1], &food_posi[swap2]);
		for (int i = count; i > 0; i--) {
			swap_sum += BFS(state.grid, food_posi[i].x, food_posi[i].y, food_posi[i - 1].x, food_posi[i - 1].y, -1);
		}
                double exp = (swap_sum - intial_sum) / T;
		if ( pow(eds, exp) >= (double)(rand() % 2)) {
			intial_sum = swap_sum;
		} else {
			swap(&food_posi[swap1], &food_posi[swap2]);
		}
		out_count++;
	}
	for (int i = count; i > 0;) {
		if (tag1[i - 1] == 0) {
			//printf("i = %d\n", i);
			//printf("i - 1 = %d\n", i - 1);
			BFS1(state.grid, food_posi[i].x, food_posi[i].y, food_posi[i - 1].x, food_posi[i - 1].y, count, food_posi);
			i--;	
	    } else if (tag1[i - 1] == 1) {
			int j = i - 1;
			while(tag1[j] == 1 && j > 0) {
				j--;
			}
			//printf("j = %d\n", j);
			BFS1(state.grid, food_posi[i].x, food_posi[i].y, food_posi[j].x, food_posi[j].y, count, food_posi);
			i = j;
			//printf("i = %d\n", i);
		}
	}
	/*for (int i = 0; i <= count; i++) {
		printf("tag[%d] = %d\n", i, tag[i]);
	}*/
    destroy(&state);
    return 0;
   
}
