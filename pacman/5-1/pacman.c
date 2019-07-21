#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAXV 10000
#define INF 10000

char direct[4] = { 'N', 'E', 'S', 'W' };

typedef struct ANode {
	int adjvex;
	struct ANode *nextarc;
	double weight;
}ArcNode;

typedef struct Vnode {
	int info;
	ArcNode *firstarc;
}VNode;

typedef struct {
	VNode adjlist[MAXV];
	int n, e;
}AdjGraph;

void giveWeigh(AdjGraph*G, game_state_t state) {//对怪物赋权函数
	//下面是仅仅以怪物为中心的9个格子进行赋权值，
	for (int x = 0; x < state.num_ghosts; x++) {
		int m = state.ghost_x[x] * state.m + state.ghost_y[x];
		ArcNode*p = G->adjlist[m].firstarc;//从中心指向四周
		while (p != NULL) {
			//p->weight = 1000;
			ArcNode*p1 = G->adjlist[p->adjvex].firstarc;//直接指向四周
			while (p1 != NULL) {
				if (p1->adjvex == m) {
					p1->weight = 90; //怪物的权值
				}
				else {
					//p1->weight = 100;
					ArcNode*p2 = G->adjlist[p1->adjvex].firstarc;
					while (p2 != NULL) {
						if (p2->adjvex == p->adjvex) {
							p2->weight = 20;//怪物四周的权值
						}
						else {
							ArcNode*p3 = G->adjlist[p2->adjvex].firstarc;
							while (p3 != NULL) {
								if (p3->adjvex == p1->adjvex) {
									//p3->weight = 10;//怪物对角格子的权值
								}
								p3 = p3->nextarc;
							}
						}
						p2 = p2->nextarc;
					}
				}
				p1 = p1->nextarc;
			}
			p = p->nextarc;
		}
	}
	
	//下面是以两个怪物为中心，进行全图赋权值，可以修改权值与曼哈顿距离的函数来控制权值
	/*for (int x = 0; x < state.n; x++) {
		for (int y = 0; y < state.m; y++) {
			int linknum = x * state.m + y;
			if (G->adjlist[linknum].firstarc != NULL) { //说明该点不是墙
				int manha = 0;//曼哈顿距离
				double weigh = 0;
				for (int ghn = 0; ghn < state.num_ghosts; ghn++) {//权值与曼哈顿距离的函数
					manha = fabs(x - state.ghost_x[ghn]) + fabs(y - state.ghost_y[ghn]);
					weigh = weigh + 100 / (double)(manha * manha);
				}
				//double weigh = 100000 /(double)( manha * manha * manha);
				ArcNode*p1 = G->adjlist[linknum].firstarc;//p1从原点指向周围的结点
				while (p1 != NULL) {
					ArcNode* p2 = G->adjlist[p1->adjvex].firstarc;//p2直接指向周围的点
					while (p2 != NULL) {
						if (p2->adjvex == linknum) {
							p2->weight = weigh;
							break;
						}
						p2 = p2->nextarc;
					}
					p1 = p1->nextarc;
				}
			}
		}
	}*/
}
void giveWeigh2(AdjGraph*G, game_state_t state, int foodn, int*foodnum) {//对豆豆赋权函数
	//下面是仅仅以豆豆为中心的9个格子进行赋权值，
	/*for (int x = 0; x < state.num_ghosts; x++) {
		int m = state.ghost_x[x] * state.m + state.ghost_y[x];
		ArcNode*p = G->adjlist[m].firstarc;//从中心指向四周
		while (p != NULL) {
			//p->weight = 1000;
			ArcNode*p1 = G->adjlist[p->adjvex].firstarc;//直接指向四周
			while (p1 != NULL) {
				if (p1->adjvex == m) {
					p1->weight = 1000; //怪物的权值
				}
				else {
					//p1->weight = 100;
					ArcNode*p2 = G->adjlist[p1->adjvex].firstarc;
					while (p2 != NULL) {
						if (p2->adjvex == p->adjvex) {
							p2->weight = 100;//怪物四周的权值
						}
						else {
							ArcNode*p3 = G->adjlist[p2->adjvex].firstarc;
							while (p3 != NULL) {
								if (p3->adjvex == p1->adjvex) {
									//p3->weight = 10;//怪物对角格子的权值
								}
								p3 = p3->nextarc;
							}
						}
						p2 = p2->nextarc;
					}
				}
				p1 = p1->nextarc;
			}
			p = p->nextarc;
		}
	}
	*/
	//下面是以每一个豆豆为中心，进行全图赋权值，可以修改权值与曼哈顿距离的函数来控制权值
	for (int x = 0; x < state.n; x++) {
		for (int y = 0; y < state.m; y++) {
			int linknum = x * state.m + y;
			if (G->adjlist[linknum].firstarc != NULL) { //说明该点不是墙
				double manha = 0;//曼哈顿距离
				double weigh = 0;
				for (int ghn = 0; ghn < foodn; ghn++) {//权值与曼哈顿距离的函数
					int fx = foodnum[ghn] / state.m;
					int fy = foodnum[ghn] % state.m;
					manha = fabs(x - fx) + fabs(y - fy);
					weigh = weigh + manha * manha  / 1000;
					//manha = fabs(x - state.ghost_x[ghn]) + fabs(y - state.ghost_y[ghn]);
					//weigh = weigh + 100 / (double)(manha * manha);
				}
				//double weigh = 100000 /(double)( manha * manha * manha);
				//weigh = manha * manha / 1000;
				ArcNode*p1 = G->adjlist[linknum].firstarc;//p1从原点指向周围的结点
				while (p1 != NULL) {
					ArcNode* p2 = G->adjlist[p1->adjvex].firstarc;//p2直接指向周围的点
					while (p2 != NULL) {
						if (p2->adjvex == linknum) {
							p2->weight = p2->weight + weigh;
							break;
						}
						p2 = p2->nextarc;
					}
					p1 = p1->nextarc;
				}
			}
		}
	}
}

int *Dijkstra(AdjGraph *G, int u, int*foodnum) {//以u为起点，返回一条到权值最小的豆豆的路径，foodnum为豆豆的邻接表编号数组
	int tmp[MAXV];
	int *temp;
	temp = (int*)malloc(sizeof(int)*MAXV);
	for (int i = 0; i < MAXV; i++)
	{
		temp[i] = -2;
	}
	ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
	double dist[MAXV];
	int 	path[MAXV];
	int S[MAXV];
	double  MINdis;
	int 	i = 0, j = 0, v = 0;
	for (int i = 0; i < G->n; i++) {
		S[i] = 0;
		if (u != i) {
			dist[i] = INF;
		}
		else {
			dist[i] = -1;
		}
		path[i] = -1;
	}
	p = G->adjlist[u].firstarc;
	while (p != NULL) {
		dist[p->adjvex] = p->weight;
		path[p->adjvex] = u;
		p = p->nextarc;
	}
	S[u] = 1;
	path[u] = -1;
	for (i = 0; i < G->n - 1; i++) {
		MINdis = INF;
		for (j = 0; j < G->n; j++) {
			if (S[j] == 0 && dist[j] < MINdis) {
				v = j;
				MINdis = dist[j];
			}
		}
		S[v] = 1;
		p = G->adjlist[v].firstarc;
		while (p != NULL) {
			if (dist[p->adjvex] > p->weight + dist[v]) {
				dist[p->adjvex] = p->weight + dist[v];
				path[p->adjvex] = v;
			}
			p = p->nextarc;
		}
	}
	double min = INF;
	int minnum = 100;
	for (int x = 0; foodnum[x] != -1; x++) {
		if (foodnum[x] >= 0 && dist[foodnum[x]] < min) {
			minnum = foodnum[x];
			min = dist[foodnum[x]];
		}
	}
	int k = 0;
	while (path[minnum] != -1) {
		tmp[k] = minnum;
		minnum = path[minnum];
		k++;
	}
	temp[0] = u;
	for (int i = 1; i <= k; i++) {
		temp[i] = tmp[k - i];
	}
	if (k < 1)
		return NULL;
	return temp;
	
}


void Create_list(game_state_t state, AdjGraph **G)
{
	int x;
	int y;
	ArcNode *p;
	int e = 0;
	for (int i = 0; i < state.m*state.n; i++)
	{
		(*G)->adjlist[i].firstarc = NULL;
	}
	for (int i = 0; i < state.m*state.n; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			x = i / state.m;
			y = i % state.m;
			if (state.grid[x][y] == 1)
				break;//当前位置是墙，不做路径考虑
			if (j == 0)//向右寻找
			{
				if (state.grid[x][y + 1] == 0)//右边有路径
				{
					p = (ArcNode*)malloc(sizeof(ArcNode));
					p->adjvex = i + 1;
					p->weight = 0;
					p->nextarc = (*G)->adjlist[i].firstarc;
					(*G)->adjlist[i].firstarc = p;
					e++;
				}
			}
			if (j == 1)//向左寻找
			{
				if (state.grid[x][y - 1] == 0)//左边有路径
				{
					p = (ArcNode*)malloc(sizeof(ArcNode));
					p->adjvex = i - 1;
					p->weight = 0;
					p->nextarc = (*G)->adjlist[i].firstarc;
					(*G)->adjlist[i].firstarc = p;
					e++;
				}
			}
			if (j == 2)//向上寻找
			{
				if (state.grid[x - 1][y] == 0)//上边有路径
				{
					p = (ArcNode*)malloc(sizeof(ArcNode));
					p->adjvex = i - state.m;
					p->weight = 0;
					p->nextarc = (*G)->adjlist[i].firstarc;
					(*G)->adjlist[i].firstarc = p;
					e++;
				}
			}
			if (j == 3)//向下寻找
			{
				if (state.grid[x + 1][y] == 0)//下边有路径
				{
					p = (ArcNode*)malloc(sizeof(ArcNode));
					p->adjvex = i + state.m;
					p->weight = 0;
					p->nextarc = (*G)->adjlist[i].firstarc;
					(*G)->adjlist[i].firstarc = p;
					e++;
				}
			}
		}
	}
	(*G)->n = state.m*state.n;
	(*G)->e = e;
}

void printPath(int path[], game_state_t state) {
	if (path[1] >= 0 && path[0] >= 0) {
	int m = path[0];
	int n = path[1];
	int x1 = m / state.m;
	int y1 = m % state.m;
	int x2 = n / state.m;
	int y2 = n % state.m;
	if (x1 == x2) {
		if (y1 == y2 - 1) {
			printf("%c", direct[1]);
		}
		else if (y1 == y2 + 1) {
			printf("%c", direct[3]);
		}
	}
	if (y1 == y2) {
		if (x1 == x2 - 1)
			printf("%c", direct[2]);
		if (x1 == x2 + 1)
			printf("%c", direct[0]);
	}
}
}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  AdjGraph*G = (AdjGraph*)malloc(sizeof(AdjGraph));
	Create_list(state, &G);
	giveWeigh(G, state);
	int foodnum[MAXV];
	memset(foodnum, -1, sizeof(foodnum));

	int count = 0;
	for (int x = 0; x < state.n; x++) {//食物点的标记，并且转换为邻接表下标
		for (int y = 0; y < state.m; y++) {
			if (state.food[x][y] == 1 && state.grid[x][y] == 0) {
				foodnum[count] = x * state.m + y;
				count++;
			}
		}
	}

	giveWeigh2(G, state, count, foodnum);

	int start = state.red_x * state.m + state.red_y;
	int *path = Dijkstra(G, start, foodnum);
	if (path == NULL) {
		for (int x = 0; foodnum[x] != -1; x++) {
			if (foodnum[x] == start) {
				foodnum[x] = -2;
				break;
			}
		}
		path = Dijkstra(G, start, foodnum);
	}
	if (path != NULL) {
          printPath(path, state); 
	}
  //
  destroy(&state);
  return 0;
}