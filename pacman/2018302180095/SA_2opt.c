#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
	int x;
	int y;
} Node;
struct {
	Node posi;
	int parent;
} q[10000];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
char direct[4] = { 'N', 'E', 'S', 'W' };
Node finalpath[10000];
Node tmpath[10000];
Node tmpath1[10000];
int tmpsum = 0;
int sum = 0;
int finalsum = 10000;
int BFS(int start_x, int start_y, int goal_x, int goal_y, game_state_t state) {
	static int vis[1000][1000];
	memset(vis, 0, sizeof vis);
	int xi = start_x;
	int yi = start_y;
	int xt = goal_x;
	int yt = goal_y;
	int rear = -1;
	int front = -1;
	rear++;
	q[rear].posi.x = xi;
	q[rear].posi.y = yi;
	q[rear].parent = -1;
	vis[xi][yi] = 1;
	Node path[10000];
	int count = 0;
	while (rear != front) {
		front++;
		Node e = q[front].posi;
		if (e.x == xt && e.y == yt) {
			int k = q[front].parent;

			path[count] = q[front].posi;
			count++;
			while (k != -1) {

				path[count] = q[k].posi;//path从终点到起点
				count++;
				k = q[k].parent;
			}
			if (tmpath[0].x == 0) {
				for (int x = 0; x < count; x++) {
					tmpath[sum + count - x - 1] = path[x];//将总路径记录下来
				}
				return count;
			}
			else {
				for (int x = 1; x < count; x++) {
					tmpath[sum + count - x - 1] = path[x - 1];//将总路径记录下来
				}
				return count - 1;
			}
			//返回路径长度
		}
		xi = e.x;
		yi = e.y;
		for (int i = 0; i < 4; i++) {
			int xx = xi + dx[i];
			int yy = yi + dy[i];
			if (vis[xx][yy] == 0 && xx >= 0 && yy >= 0 &&
				state.grid[xx][yy] == 0 ) {
				vis[xx][yy] = 1;
				rear++;
				q[rear].posi.x = xx;
				q[rear].posi.y = yy;
				q[rear].parent = front;
			}
		}
	}
}
void printPath(Node path[]) {
	for (int i = 1; i < finalsum; i++) {
		if (path[i].x == path[i - 1].x) {
			if (path[i].y == path[i - 1].y - 1) {
				printf("%c", direct[3]);
			}
			else if (path[i].y == path[i - 1].y + 1) {
				printf("%c", direct[1]);
			}
		}
		if (path[i].y == path[i - 1].y) {
			if (path[i].x == path[i - 1].x - 1)
				printf("%c", direct[0]);
			if (path[i].x == path[i - 1].x + 1)
				printf("%c", direct[2]);
		}
	}
}
void swap(Node*a, Node*b) {
	Node tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

double P(int a, int b, int T) {
	//printf("%lf", exp((double)(a - b) / T));
	return (double)(a - b) / T + 1;
}
int main() {
	game_state_t state;
	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here
	Node food[1000];
	int fdcount = 0;
	for (int x = 0; x < state.n; x++) {
		for (int y = 0; y < state.m; y++) {
			if (state.food[x][y] == 1 && state.grid[x][y] == 0) {
				food[fdcount].x = x;
				food[fdcount].y = y;
				fdcount++;
			}
		}
	}
	sum = BFS(state.start_x, state.start_y, food[0].x, food[0].y, state);
	for (int x = 0; x < fdcount - 1; x++) {
		sum = sum + BFS(food[x].x, food[x].y, food[x + 1].x, food[x + 1].y, state);
	}
	finalsum = sum;
	tmpsum = sum;
	for (int x = 0; x < sum; x++) {
		finalpath[x] = tmpath[x];
		tmpath1[x] = tmpath[x];
	}//将所有的路径都初始化
	
	int kmax = 10000;
	srand((unsigned )time(NULL));
	for (int k = 1; k < kmax ; k = k * (k + 1)) {//循环次数
		double T = kmax / (double)k;
		sum = 0;//每一次循环都要初始化
		tmpath[0].x = 0;//初始化
		int target1 = rand() % fdcount;
		int target2 = rand() % fdcount;
		int targetmin = (target1 < target2) ? target1 : target2;
		int targetmax = (target1 > target2) ? target1 : target2;//将target大小排一下
		while (targetmax > targetmin) {
			swap(&food[targetmax], &food[targetmin]);
			targetmax--;
			targetmin++;
		}//交换完毕


		sum = BFS(state.start_x, state.start_y, food[0].x, food[0].y, state);
		for (int x = 0; x < fdcount - 1; x++) {
			sum = sum + BFS(food[x].x, food[x].y, food[x + 1].x, food[x + 1].y, state);
		}
		int m = rand() % 1;
		if (P(tmpsum, sum, T) >= m ){
			tmpsum = sum;
			for (int x = 0; x < sum; x++) {
				tmpath1[x] = tmpath[x];
			}
		}
	}
	if (tmpsum < finalsum) {
		finalsum = tmpsum;
		for (int x = 0; x < finalsum; x++) {
			finalpath[x] = tmpath1[x];
		}
	}
	printPath(finalpath);
	//printf("WEESSWW\n");

	// 
	destroy(&state);
	return 0;
}