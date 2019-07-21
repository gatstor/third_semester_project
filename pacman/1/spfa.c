#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#define MAX 20000
#define MAXV 20000
#define INF 32000
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
int visit[MAXV];

int *SPFA(AdjGraph *G, int s, int v) {
	int ans[MAXV];
	int * eans = (int *)malloc(MAX * sizeof(int));
	ArcNode *p;
	int tmp;
	double dist[MAXV];
      int  path[MAXV];
	for (int i = 0; i < G->n; i++) {
		dist[i] =9999999;
		path[i] = -1;
	}
	dist[s] = 0;
	int queuemy[MAXV];
	int front = -1, rear = -1;
	rear++;
	queuemy[rear] = s;
	visit[s] = 1;
	while (front != rear) {
		front++;
		tmp = queuemy[front];
		visit[tmp] = 0;
		p = G->adjlist[tmp].firstarc;
		while (p != NULL) {
			if (dist[tmp] + p->weight < dist[p->adjvex]) {
				dist[p->adjvex] = dist[tmp] + p->weight;
				path[p->adjvex] = tmp;
				visit[p->adjvex] = 1;
				rear++;
				queuemy[rear] = p->adjvex;
			}
			p = p->nextarc;
		}
	}
	int k = 0;
	while (path[v] != -1) {
		ans[k] = v;
		v = path[v];
		k++;
	}
	eans[0] = s;
	for (int i = 1; i <= k; i++) {
		eans[i] = ans[k - i];
	}
	int * temp1 = eans;
	return eans;
}
void Create_list(game_state_t state,AdjGraph **G)
{
	int x;
	int y;
	ArcNode *p;
	int e=0;
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
				if (state.grid[x][y+1]==0)//右边有路径
				{
					p = (ArcNode*)malloc(sizeof(ArcNode));
					p->adjvex = i + 1;
					p->weight = state.cost[x][y + 1];
					p->nextarc = (*G)->adjlist[i].firstarc;
					(*G)->adjlist[i].firstarc = p;
					e++;
				}
			}
			if (j == 1)//向左寻找
			{
				if (state.grid[x][y-1] == 0)//左边有路径
				{
					p = (ArcNode*)malloc(sizeof(ArcNode));
					p->adjvex = i - 1;
					p->weight = state.cost[x][y - 1];
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
					p->weight = state.cost[x - 1][y];
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
					p->weight = state.cost[x + 1][y];
					p->nextarc = (*G)->adjlist[i].firstarc;
					(*G)->adjlist[i].firstarc = p;
					e++;
				}
			}
		}
	}
	(*G)->n=state.m*state.n;
	(*G)->e=e;
}

void printDir(int *path, int m){
    char dir[MAXV];
    int i = 0;
    for(i = 0; path[1]!= m*100;i++){
        if(path[i+1]-path[i]==1){
            dir[i] = 'E';
        }else if(path[i+1]==path[i]-1){
            dir[i] = 'W';
        }else if(path[i+1]==path[i]+m){
            dir[i] = 'S';
        }else if(path[i+1]==path[i]-m){
            dir[i] = 'N';
        }
    }
    dir[i] = '\0';
    printf("%s",dir);
}
int main(){
    game_state_t state;
    memset(&state, 0, sizeof(state));
    init(&state);
    // write your code here
    AdjGraph *G;
    G = (AdjGraph *)malloc(sizeof(AdjGraph));
    // 
    Create_list(state, &G);
    int u = state.start_x*state.m + state.start_y;
    int v = state.goal_x*state.m + state.goal_y;
    int* path;
    path = (int *)malloc(sizeof(int)*20000);
    path = SPFA(G,u,v);
    int m = state.m;
    printDir(path,m);
    destroy(&state);
    
    return 0;
}
