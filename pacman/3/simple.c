#include "util.h"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#define MAXV 2000
#define MAX 10000
#define INF 9999
typedef struct l {
	long long 	int x;
	long long 	int y;
	char path[800];
	long long 	int length;
}box;

int visited[1000][1000];
box queue[10000];
int exist[1000][1000];
int hav_eat[1000][1000];


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


int Is_Ghost_Near(game_state_t state, int x, int y)//x,y is the position now,to judge 5*5
{
	int pos_now = x * state.m + y;
	int ghost_now[100];
	int m = state.m;
	for (int i = 0; i < state.num_ghosts; i++)
	{
		ghost_now[i] = state.m*state.ghost_x[i] + state.ghost_y[i];
		if (pos_now - ghost_now[i] == 1 || pos_now - ghost_now[i] == -1 || pos_now - ghost_now[i] == m || pos_now - ghost_now[i] == -m || pos_now - ghost_now[i] == 0)
			return 1;
		/*	else if(pos_now-ghost_now[i]==2||pos_now-ghost_now[i]==-2||pos_now-ghost_now[i]==2*m||pos_now-ghost_now[i]==-2*m||pos_now-ghost_now[i]==m+1||pos_now-ghost_now[i]==m-1||pos_now-ghost_now[i]==-m+1||pos_now-ghost_now[i]==-m-1)
				return 1;*/
				/*	if(pos_now-ghost_now[i]<3&&pos_now-ghost_now[i]>-3)
				return 1;
			else if(pos_now-ghost_now[i]<m+3&&pos_now-ghost_now[i]>m-3)
				return 1;
			else if(pos_now-ghost_now[i]<2*m+3&&pos_now-ghost_now[i]>2*m-3)
				return 1;
			else if (pos_now-ghost_now[i]<-m+3&&pos_now-ghost_now[i]>-m-3)
				return 1;
			else if(pos_now-ghost_now[i]<-2*m+3&&pos_now-ghost_now[i]>-2*m-3)
				return 1;
			else if(pos_now-ghost_now[i]<-3*m+3&&pos_now-ghost_now[i]>-3*m-3)
				return 1;
			else if(pos_now-ghost_now[i]<3*m+3&&pos_now-ghost_now[i]>3*m-3)
				return 1;
			else if(pos_now-ghost_now[i]<4*m+4&&pos_now-ghost_now[i]>4*m-4)
				return 1;
			else if(pos_now-ghost_now[i]<-4*m+4&&pos_now-ghost_now[i]>-4*m-4)
				return 1;*/
	}
	return 0;

}

int* BFS(game_state_t state, game_state_t u, game_state_t *v)
{
	int *pa;
	pa = (int*)malloc(sizeof(int) * 1000);
	int top = 0;
	int p[1000];
	for (int i = 0; i < 1000; i++)
	{
		p[i] = -2;
	}
	pa = p;
	p[top] = state.start_x*state.m + state.start_y;
	top++;
	long long int rear = 0;
	long long int maxsize = 10000;
	long long int front = 0;
	box temp1;
	box temp2;
	temp1.x = u.start_x;
	temp1.y = u.start_y;
	temp1.length = 0;
	temp1.path[temp1.length] = '\0';
	exist[temp1.x][temp1.y] = 1;
	queue[front] = temp1;
	front++;
	front = front % maxsize;
	while (rear != front)
	{
		temp1 = queue[rear];
		rear++;
		rear = rear % maxsize;
		visited[temp1.x][temp1.y] = 1;
		exist[temp1.x][temp1.y] = 0;
		if (state.food[temp1.x][temp1.y] == 1 && hav_eat[temp1.x][temp1.y] == 0)
		{
			hav_eat[temp1.x][temp1.y] = 1;
			for (int i = 0; i < temp1.length; i++)
			{
				if (temp1.path[i] == 'N')
					p[top] = p[top - 1] - state.m;
				else if (temp1.path[i] == 'S')
					p[top] = p[top - 1] + state.m;
				else if (temp1.path[i] == 'W')
					p[top] = p[top - 1] - 1;
				else if (temp1.path[i] == 'E')
					p[top] = p[top - 1] + 1;
				top++;
			}
			(*v).start_x = temp1.x;
			(*v).start_y = temp1.y;
			pa = p;
			return pa;
		}
		for (int i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				temp2.x = temp1.x + 1;
				temp2.y = temp1.y;
				temp2.length = temp1.length + 1;
				strcpy(temp2.path, temp1.path);
				temp2.path[temp2.length - 1] = 'S';
				temp2.path[temp2.length] = '\0';
				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1 || visited[temp2.x][temp2.y] == 1)
					continue;
				//	else if(Is_Ghost_Near(state,temp2.x,temp2.y))
				//		continue;
				else
				{
					queue[front] = temp2;
					front++;
					front = front % maxsize;
				}
			}
			if (i == 1)
			{
				temp2.x = temp1.x - 1;
				temp2.y = temp1.y;
				temp2.length = temp1.length + 1;
				strcpy(temp2.path, temp1.path);
				temp2.path[temp2.length - 1] = 'N';
				temp2.path[temp2.length] = '\0';


				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1 || visited[temp2.x][temp2.y] == 1 || Is_Ghost_Near(state, temp2.x, temp2.y))
					continue;
				//	else if(Is_Ghost_Near(state,temp2.x,temp2.y))
				  //       continue;
				else
				{
					queue[front] = temp2;
					front++;
					front = front % maxsize;
				}
			}
			if (i == 2)
			{
				temp2.x = temp1.x;
				temp2.y = temp1.y - 1;
				temp2.length = temp1.length + 1;
				strcpy(temp2.path, temp1.path);
				temp2.path[temp2.length - 1] = 'W';
				temp2.path[temp2.length] = '\0';
				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1 || visited[temp2.x][temp2.y] == 1 || Is_Ghost_Near(state, temp2.x, temp2.y))
					continue;
				//		else if(Is_Ghost_Near(state,temp2.x,temp2.y)) 
				//			continue;
				else
				{
					queue[front] = temp2;
					front++;
					front = front % maxsize;
				}

			}
			if (i == 3)
			{
				temp2.x = temp1.x;
				temp2.y = temp1.y + 1;
				temp2.length = temp1.length + 1;
				strcpy(temp2.path, temp1.path);
				temp2.path[temp2.length - 1] = 'E';
				temp2.path[temp2.length] = '\0';
				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1 || visited[temp2.x][temp2.y] == 1 || Is_Ghost_Near(state, temp2.x, temp2.y))
					continue;
				//		else if(Is_Ghost_Near(state,temp2.x,temp2.y))
				  //           continue;
				else
				{
					queue[front] = temp2;
					front++;
					front = front % maxsize;
				}

			}


		}

	}
	return pa;
}

void printDir(int *path, int m) {
	char dir[MAXV];
	int i = 0;
	for (i = 0; path[i + 1] != -2; i++) {
		if (path[i + 1] - path[i] == 1) {
			dir[i] = 'E';
		}
		else if (path[i + 1] == path[i] - 1) {
			dir[i] = 'W';
		}
		else if (path[i + 1] == path[i] + m) {
			dir[i] = 'S';
		}
		else if (path[i + 1] == path[i] - m) {
			dir[i] = 'N';
		}
	}
	dir[i] = '\0';
	if (i != 0)
		printf("%c", dir[0]);
	else
		return;
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
					if (Is_Ghost_Near(state, x, y + 1))
						p->weight = 9999;
					else
						p->weight = 1;
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
					if (Is_Ghost_Near(state, x, y - 1))
						p->weight = 9999;
					else
						p->weight = 1;
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
					if (Is_Ghost_Near(state, x - 1, y))
						p->weight = 9999;
					else
						p->weight = 1;
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
					if (Is_Ghost_Near(state, x + 1, y))
						p->weight = 9999;
					else
						p->weight = 1;
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

int first_try(int x, int y, game_state_t state)
{
	if (Is_Ghost_Near(state, x, y) == 0)
		return 1;
	else
		return 0;
}

int main() {
	game_state_t state;
	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here
	AdjGraph *G;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));
	Create_list(state, &G);
	int *a;
	game_state_t j;
	game_state_t k;
	j.start_x = state.start_x;
	j.start_y = state.start_y;
	a = BFS(state, j, &k);
	int x = state.start_x;
	int y = state.start_y;
	int x_first;
	int y_first;
	if (a[1] != -2)
	{
		x_first = a[1] / state.m;
		y_first = a[1] % state.m;
	}
	else
		return 0;
	if (first_try(x_first, y_first, state) == 1)
	{
		printDir(a, state.m);
	}
	else if (Is_Ghost_Near(state, x, y) == 1)
	{
		if (Is_Ghost_Near(state, x, y + 1) == 0 && (state.grid[x][y + 1] != 1) && state.grid[x][y + 1] != 1)
		{
			printf("E");
		}
		else if (Is_Ghost_Near(state, x, y - 1) == 0 && (state.grid[x][y - 1] != 1) && state.grid[x][y - 1] != 1)
		{
			printf("W");
		}
		else if (Is_Ghost_Near(state, x + 1, y) == 0 && (state.grid[x + 1][y] != 1) && state.grid[x + 1][y] != 1)
		{
			printf("S");
		}
		else if (Is_Ghost_Near(state, x - 1, y) == 0 && (state.grid[x - 1][y] != 1) && state.grid[x - 1][y] != 1)
		{
			printf("N");
		}
		if (Is_Ghost_Near(state, x, y + 2) == 0 && (state.grid[x][y + 1] != 1) && state.grid[x][y + 2] != 1)
		{
			printf("E");
		}
		else if (Is_Ghost_Near(state, x, y - 2) == 0 && (state.grid[x][y - 1] != 1) && state.grid[x][y - 2] != 1)
		{
			printf("W");
		}
		else if (Is_Ghost_Near(state, x + 2, y) == 0 && (state.grid[x + 1][y] != 1) && state.grid[x + 2][y] != 1)
		{
			printf("S");
		}
		else if (Is_Ghost_Near(state, x - 2, y) == 0 && (state.grid[x - 1][y] != 1) && state.grid[x - 2][y] != 1)
		{
			printf("N");
		}
		/*	else if(Is_Ghost_Near(state,x-1,y-1)==0&&(state.grid[x][y-1]!=1)&&state.grid[x-1][y-1]!=1)
			{
				printf("W");
			}
			else if(Is_Ghost_Near(state,x+1,y+1)==0&&(state.grid[x][y+1]!=1)&&state.grid[x+1][y+1]!=1)
			{
				printf("E");
			}
			else if(Is_Ghost_Near(state,x-1,y+1)==0&&(state.grid[x][y+1]!=1)&&state.grid[x-1][y+1]!=1)
			{
				printf("E");
			}
			else if(Is_Ghost_Near(state,x+1,y-1)==0&&(state.grid[x][y-1]!=1)&&state.grid[x+1][y-1]!=1)
			{
				printf("W");
			}
			else if(Is_Ghost_Near(state,x,y+3)==0&&(state.grid[x][y+1]!=1)&&state.grid[x][y+3]!=1)
			 {
				 printf("E");
			 }
			 else if(Is_Ghost_Near(state,x,y-3)==0&&(state.grid[x][y-1]!=1)&&state.grid[x][y-3]!=1)
			 {
				 printf("W");
			 }
			 else if(Is_Ghost_Near(state,x+3,y)==0&&(state.grid[x+1][y]!=1)&&state.grid[x+3][y]!=1)
			 {
				 printf("S");
			 }
			 else if(Is_Ghost_Near(state,x-3,y)==0&&(state.grid[x-1][y]!=1)&&state.grid[x-3][y]!=1)
			 {
				 printf("N");
			 }*/


	}
	destroy(&state);
	return 0;
}
