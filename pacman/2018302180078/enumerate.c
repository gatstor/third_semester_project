#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#define MAX 20000
#define MAXV 20000
#define INF 9999999

int vis[1000];



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

void printDir(int *path, int m){
    char dir[MAXV];
    int i = 0;
    for(i = 0; path[i+1]!=-2;i++){
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


int *Dijkstra(AdjGraph *G, int u, int uv) {
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
   int 	i, j, v;
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
	for (int i = 0; i < G->n - 1; i++) {
		MINdis = INF;
		for (int j = 0; j < G->n; j++) {
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
	int k = 0;
	while (path[uv] != -1) {
		tmp[k] = uv;
		uv = path[uv];
		k++;
	}
	temp[0] = u;
	for (int i = 1; i <= k; i++) {
		temp[i] = tmp[k - i];
	}
	if(k < 1)
		return NULL;
	return temp;
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
					p->weight = 1;
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
					p->weight = 1;
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


int cul_length(int * path)
{	
	int i=0;
	int sum=0;
	for(i=0;path[i]!=-2;i++)
	{
		sum++;
	}
	return sum;
}

int* BFS(game_state_t state,game_state_t u, game_state_t *v)
{
	int *pa;
	pa=(int*)malloc(sizeof(int)*1000);
	int top=0;
	int p[1000];
	for(int i=0;i<1000;i++)
	{
		p[i]=-2;
	}
	p[top]=state.start_x*state.m+state.start_y;
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
		rear = rear%maxsize;
		visited[temp1.x][temp1.y]=1;
		exist[temp1.x][temp1.y] = 0;
		if (state.food[temp1.x][temp1.y]==1&&hav_eat[temp1.x][temp1.y]==0)
		{
			hav_eat[temp1.x][temp1.y]=1;
			for ( int i = 0; i<temp1.length;i++)
			{
				if(temp1.path[i]=='N')
				p[top]=p[top-1]-state.m;
				else if(temp1.path[i]=='S')
				p[top]=p[top-1]+state.m;
				else if(temp1.path[i]=='W')
				p[top]=p[top-1]-1;
				else if(temp1.path[i]=='E')
				p[top]=p[top-1]+1;
			top++;
			}
			(*v).start_x=temp1.x;
			(*v).start_y=temp1.y;
			pa=p;
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
				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1||visited[temp2.x][temp2.y]==1)
					continue;
				else
				{
					queue[front] = temp2;
					front++;
					front = front%maxsize;
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


				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1||visited[temp2.x][temp2.y]==1)
					continue;
				else
				{
					queue[front] = temp2;
					front++;
					front = front %maxsize ;
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
				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1||visited[temp2.x][temp2.y]==1)
					continue;
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
				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1||visited[temp2.x][temp2.y]==1)
					continue;
				else
				{
					queue[front] = temp2;
					front++;
					front = front % maxsize;
				}

			}


		}

	}
}
int res=9999;
int ans[1000];
int cnt=0;
int x[1000];
int y[1000];
int length_list[1000][1000];
int length_list_tou[1000];
void dfs(int now, int path[],game_state_t state,AdjGraph *G) {
    if (now == cnt) {;
        int *road;
		int k=path[0];
		int t=0;
		int sum=0;
	   	sum += length_list_tou[x[k]*state.m+y[k]];	
        for (int i = 1; i < cnt; i++) {
			k=path[i];
			t=path[i-1];
			sum+=length_list[x[t]*state.m+y[t]][x[k]*state.m+y[k]];
            // bfs 计算最短路
        }
        if (sum < res) {
            for (int i = 0; i <cnt; i++){
				res=sum;
                ans[i] = path[i];
            }
        }
        return;
    }
	
     for (int i = 0; i < cnt; i++) {
        if (vis[i]==0) 
		{   vis[i]=1;
            path[now] = i;//i biaoshi dijige douzi
            dfs(now + 1, path , state ,G);
			vis[i]=0;
        }
    }
    
}

int main(){
    game_state_t state;
    memset(&state, 0, sizeof(state));
    init(&state);
    // write your code here
	AdjGraph *G;
	G=(AdjGraph*)malloc(sizeof(AdjGraph));
	Create_list(state,&G);
    for (int i = 0; i <state.n; i++){
        for (int j = 0; j <state.m; j++){
            if (state.food[i][j] == 1) {
                x[cnt] = i;
                y[cnt++] = j;
          }
      }//x,ycunfang douzi weizhi
  }	
	int src=0;
	int des=0;
	int *a;
	int start=0;
	start=state.start_x*state.m+state.start_y;
	for(int i=0;i<cnt;i++)
	{
		for(int j=0;j<cnt;j++)
		{
			if(i==j)
				continue;
			 src=x[i]*state.m+y[i];
			 des=x[j]*state.m+y[j];
			 a=Dijkstra(G,src,des);
		     length_list[src][des]=cul_length(a);
		}
		
	}
	for(int i=0;i<cnt;i++)
	{
		src=x[i]*state.m+y[i];
		a=Dijkstra(G,start,src);
		length_list_tou[src]=cul_length(a);
	}
	int path[1000];
	for(int i=0;i<1000;i++)
	{
		path[i]=-2;
		ans[i]=-2;
	}
	int k=0;
	int t=0;
	
	int *cul_path_douzi;
	dfs(0,path,state,G);


    start=state.start_x*state.m+state.start_y;
	k=ans[0];
	cul_path_douzi=Dijkstra(G,start,x[k]*state.m+y[k]);
	printDir(cul_path_douzi,state.m);
	for(int i=0;i<cnt-1;i++)
	{
		 k=ans[i];
		 t=ans[i+1];
		 cul_path_douzi=Dijkstra(G,x[k]*state.m+y[k],x[t]*state.m+y[t]);
         printDir(cul_path_douzi,state.m);
	}
	destroy(&state);

	return 0;
}

