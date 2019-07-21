#include "util.h"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <math.h>
#define MAXV 2000
#define MAX 10000
#define INF 999999

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

int judge_no_douzi(game_state_t state)
{
	for(int i=0;i<state.n;i++)
	{
		for(int j=0;j<state.m;j++)
		{
			if(state.food[i][j]==1&&hav_eat[i][j]!=1)
				return 0;//to express not eat all douzi
		}
	}
	return 1;// to express have eaten all
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


double P(int E_s,int E_new,double T)
{
	double result=0;
	result=exp((E_s-E_new)/T);
	return result;
}


 int length_list[5000][5000];
 int length_head[10000];



int main() {
	game_state_t state;
	memset(&state, 0, sizeof(state));
	init(&state);
	AdjGraph *G;
	G=(AdjGraph *)malloc(sizeof(AdjGraph));
	Create_list(state,&G);
	int douzi_pos[1000];
	int temp[1000];
	long long int douzi_length=0;
	long long int temp_length=0;
	int top=0;
	game_state_t u;
	game_state_t v;
	u.start_x=state.start_x;
	u.start_y=state.start_y;
	// write your code here
	while(!judge_no_douzi(state))
	{
		for(int i=0;i<1000;i++)
		{
			for(int j=0;j<1000;j++)
				{
					exist[i][j]=0;
					visited[i][j]=0;
				}
		}
		BFS(state,u,&v);
		douzi_pos[top]=v.start_x*state.m+v.start_y;
		temp[top]=v.start_x*state.m+v.start_y;
		top++;
		u=v;
	}
	int start=0;
	start=state.start_x*state.m+state.start_y;
	
	
     for(int i=0;i<top;i++)
     {
         for(int j=0;j<top;j++)
         {
             length_list[i][j]=0;
         }
     }
     for(int j=0;j<top;j++)
     {
         length_head[j]=0;
     }
     int* temp_list;
     for(int i=0;i<top;i++)
     {
             temp_list=Dijkstra(G,start,douzi_pos[i]);
             length_head[douzi_pos[i]]+=cul_length(temp_list);
     }
     for(int i=0;i<top;i++)
     {
         for(int j=0;j<top;j++)
         {
             if(i==j)
                 continue;
             temp_list=Dijkstra(G,douzi_pos[i],douzi_pos[j]);
             length_list[douzi_pos[i]][douzi_pos[j]]+=cul_length(temp_list);
         }

     }

	
	int k;
	int l;
	int swap;
	int *cul_path_douzi;
	int *cul_path_temp;
	int times=0;
	douzi_length+=length_head[douzi_pos[0]];
	for(int j=0;j<top-1;j++)
	{
		douzi_length+=length_list[douzi_pos[j]][douzi_pos[j+1]];
		
	}
	for(int y=0;y<1000;y++)
	{
		double T=1000/(double)(y+1);
		T=T*0.0001;
		if(times==200)
			break;
		 k=rand()%top;
         l=rand()%top;
         if(k==l)
				continue;
		 else
         {
             temp_length=0;
             swap=temp[k];
             temp[k]=temp[l];
             temp[l]=swap;
             for(int j=0;j<top-1;j++)
             { 
			   	 if(j == 0)
                 {
                 
                     temp_length+=length_head[temp[0]];
                 }
                 
                 temp_length+=length_list[temp[j]][temp[j+1]];
             }
			 double random;
			 random=rand()%1000000;
			 random=random/1000000;
             if(P(douzi_length,temp_length,T)>=random)
               {
                  swap=douzi_pos[k];
                  douzi_pos[k]=douzi_pos[l];
                  douzi_pos[l]=swap;
                  douzi_length=temp_length;
                  times=0;
               }
             else
             {
                 swap=temp[k];
                 temp[k]=temp[l];
                 temp[l]=swap;
                 times++;
             }   
         }

	}
	/*for(int i=0;i<10000;i++)
	{
		if(times==1000)
			break;
		k=rand()%top;
		l=rand()%top;
		if(k==l)
			continue;
 
		
		else
		{
			temp_length=0;
			swap=temp[k];
			temp[k]=temp[l];
			temp[l]=swap;
			for(int j=0;j<top-1;j++)
			{	if(j == 0)
				{
				
					temp_length+=length_head[temp[0]];
				}
				
				temp_length+=length_list[temp[j]][temp[j+1]];
			}
		 	if(temp_length < douzi_length)
              {
                 swap=douzi_pos[k];
                 douzi_pos[k]=douzi_pos[l];
                 douzi_pos[l]=swap;
                 douzi_length=temp_length;
				 times=0;
              }
			else
			{
				swap=temp[k];
				temp[k]=temp[l];
				temp[l]=swap;
				times++;
			}	
		}
	

	}*/
	
	cul_path_douzi=Dijkstra(G,start,douzi_pos[0]);
	printDir(cul_path_douzi,state.m);
	for(int i=0;i<top-1;i++)
	{
		 cul_path_douzi=Dijkstra(G,douzi_pos[i],douzi_pos[i+1]);
         printDir(cul_path_douzi,state.m);
	}
	destroy(&state);
	return 0;
}
