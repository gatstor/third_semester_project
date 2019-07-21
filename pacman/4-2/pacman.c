#include "util.h"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<malloc.h>
#define MAXV 500
#define MAX 10000
#define INF 9999
typedef struct l {
	long long 	int x;
	long long 	int y;
	char path[200];
	long long 	int length;
}box;

int visited[100][100];
box queue[10000];
int exist[100][100];
int hav_eat[100][100];


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



int Is_Ghost_Near_second(game_state_t state, int x, int y)//x,y is the position now,to judge 5*5
 {
     int pos_now=x*state.m+y;
     int ghost_now[100];
     int m=state.m;
     for(int i=0;i<state.num_ghosts;i++)
     {
         ghost_now[i]=state.m*state.ghost_x[i]+state.ghost_y[i];
         if(pos_now-ghost_now[i]==1||pos_now-ghost_now[i]==-1||pos_now-ghost_now[i]==m||pos_now-ghost_now[i]==-m||pos_now-ghost_now[i]==0)
              return 1;
	}
	 return 0;
 }
int Is_Ghost_Near(game_state_t state, int x, int y)//x,y is the position now,to judge 5*5
{
	int pos_now=x*state.m+y;
	int ghost_now[100];
	int m=state.m;
	for(int i=0;i<state.num_ghosts;i++)
	{		
		if(state.timer[i]>0)
			continue;
		ghost_now[i]=state.m*state.ghost_x[i]+state.ghost_y[i];	
		if(pos_now-ghost_now[i]==1||pos_now-ghost_now[i]==-1||pos_now-ghost_now[i]==m||pos_now-ghost_now[i]==-m||pos_now-ghost_now[i]==0)
             return 1;
	}
	/*	else if(pos_now-ghost_now[i]==2||pos_now-ghost_now[i]==-2||pos_now-ghost_now[i]==2*m||pos_now-ghost_now[i]==-2*m||pos_now-ghost_now[i]==m+1||pos_now-ghost_now[i]==m-1||pos_now-ghost_now[i]==-m+1||pos_now-ghost_now[i]==-m-1)
			return 1;*/
			/*	if(pos_now-ghost_now[i]<3&&pos_now-ghost_now[i]>-3)
			return 1;
		else if(pos_now-ghost_now[i]<m+3&&pos_now-ghost_now[i]>m-3)
			return 1;
		else if(pos_now-ghost_now[i]<2*m+3&&pos_now-ghost_now[i]>2*m-3)
			return 2;
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
	
	return 0;
	
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
	pa=(int*)malloc(sizeof(int)*500);
	int top=0;
	int p[500];
	for(int i=0;i<500;i++)
	{
		p[i]=-2;
	}
	pa=p;
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
			//	else if(Is_Ghost_Near(state,temp2.x,temp2.y))
			//		continue;
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
			//	else if(Is_Ghost_Near(state,temp2.x,temp2.y))
              //       continue;
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
				if (state.grid[temp2.x][temp2.y] == 1 || exist[temp2.x][temp2.y] == 1||visited[temp2.x][temp2.y]==1)
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
	if(i!=0)
    printf("%c",dir[0]);
	else
		return ;
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
					if(Is_Ghost_Near(state,x,y+1))
						p->weight=9999;
					else
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

int first_try(int x,int y, game_state_t state)
{
	if(Is_Ghost_Near_second(state,x,y)==0)
		return 1;
	else
		return 0;
}

int need_eat(game_state_t state, int ghost_length[], int superbean_length[])
{
	int min =9999;
	int min_i=-1;
	for(int i=0;i<state.num_ghosts;i++)
	{
		if(ghost_length[i]<7&&state.timer[i]<=0)//this ghost is dangerous
		{
			for(int j=0;j<state.num_capsule;j++)
			{
				if(superbean_length[j]<min)
				{
					min=superbean_length[j];
					min_i=j;
				}
			}
		}
	}
	return min_i;
}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here
  AdjGraph *G;
  G=(AdjGraph*)malloc(sizeof(AdjGraph));
  Create_list(state,&G);
  int *a;
  game_state_t j;
  game_state_t k;
  j.start_x=state.start_x;
  j.start_y=state.start_y;
  a=BFS(state,j,&k);
  int x=state.start_x;
  int y=state.start_y;
  int x_first;
  int y_first;
  int now;
  int *length;
  now=state.start_x*state.m+state.start_y;
  int superbean[40];
  int superbean_length[40];
  int ghost[30];
  int ghost_length[200];
  for(int i=0;i<state.num_capsule;i++)
  {
	   superbean[i]=state.capsule_x[i]*state.m+state.capsule_y[i];
  }
  for(int i=0;i<state.num_ghosts;i++)
  {
       ghost[i]=state.ghost_x[i]*state.m+state.ghost_y[i];
  }
  for(int i=0;i<state.num_capsule;i++)
  {
	  length=Dijkstra(G,now,superbean[i]);
      superbean_length[i]=cul_length(length);
	  free(length);
  }
  for(int i=0;i<state.num_ghosts;i++)
  {
	  length=Dijkstra(G,now,ghost[i]);
	  ghost_length[i]=cul_length(length);
	  free(length);
  }
  int r=0;
  r=need_eat(state, ghost_length, superbean_length);
  if(r!=-1)//shou dao weixie ,chi jiaonang
  {
	length=Dijkstra(G, now, superbean[r]);
	if(length[1]!=-2)
	{	
		int x1=length[1]/state.m;
		int y1=length[1]%state.m;
		if(Is_Ghost_Near(state, x1, y1)==0)
		{
			printDir(length,state.m);
			free(length);
			destroy(&state);
			return 0;
		}
 		else
		{
			goto flag;
		}
	}
	else 
	{
	goto flag;
	}
  }
 if(a[1]!=-2)
  {
    x_first=a[1]/state.m;
    y_first=a[1]%state.m;
  }
  else 
  {		  
	  destroy(&state);
	  return 0;
  }
  if(first_try(x_first,y_first,state)==1)
  {
	  if(Is_Ghost_Near_second(state,x_first,y_first)==1)
		  goto flag;
flag2:  printDir(a,state.m);
		destroy(&state);
		return 0;
  }
  else if (Is_Ghost_Near(state,x,y)==1)
	{	
flag:	 if(Is_Ghost_Near(state,x,y+1)==0&&(state.grid[x][y+1]!=1)&&state.grid[x][y+1]!=1)
         {
             printf("E");
         }
         else if(Is_Ghost_Near(state,x,y-1)==0&&(state.grid[x][y-1]!=1)&&state.grid[x][y-1]!=1)
         {
             printf("W");
         }
         else if(Is_Ghost_Near(state,x+1,y)==0&&(state.grid[x+1][y]!=1)&&state.grid[x+1][y]!=1)
         {
             printf("S");
         }
         else if(Is_Ghost_Near(state,x-1,y)==0&&(state.grid[x-1][y]!=1)&&state.grid[x-1][y]!=1)
         {
             printf("N");
		}
	/*	if(Is_Ghost_Near(state,x,y+2)==0&&(state.grid[x][y+1]!=1)&&state.grid[x][y+2]!=1)
		{
			printf("E");
		}
		else if(Is_Ghost_Near(state,x,y-2)==0&&(state.grid[x][y-1]!=1)&&state.grid[x][y-2]!=1)
		{
			printf("W");
		}
		else if(Is_Ghost_Near(state,x+2,y)==0&&(state.grid[x+1][y]!=1)&&state.grid[x+2][y]!=1)
		{
			printf("S");
		}
		else if(Is_Ghost_Near(state,x-2,y)==0&&(state.grid[x-1][y]!=1)&&state.grid[x-2][y]!=1)
		{
			printf("N");
		}
		else if(Is_Ghost_Near(state,x-1,y-1)==0&&(state.grid[x][y-1]!=1)&&state.grid[x-1][y-1]!=1)
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

	goto flag2;
	}
  destroy(&state);
  return 0;
}
