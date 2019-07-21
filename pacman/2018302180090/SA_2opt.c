#include "util.h"
#include <stdio.h>
#include <string.h>
#include<math.h>
#include<time.h>
#define INF 32767
#define MaxSize 300

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int cnt = 1;//目标个数
int x[MaxSize], y[MaxSize];//目标位置
int ans[MaxSize], min = 0x3f3f3f3f;//ans[]枚举最短路径顺序,min为最短路径长度

typedef struct node {
	int x, y;//(x,y)表示坐标
}node;

typedef struct NODE { // priority_queue 中每个点的定义
	node location;//坐标(x,y)
	int h;//起点到到终点距离
	int fa;//前一结点
	int step;
} NODE;
/*
int* BFS(AdjGraph *G,int start,int destination)//start is the start_position
{
	static int visited[10000];
 	static box queue[10000];
 	static int exist[10000];
	for(int t=0;t<10000;t++)
	{
		visited[t]=0;
		exist[t]=0;
	}
	int *pa;
	pa=(int*)malloc(sizeof(int)*1000);
	int top=0;
	int p[1000];
	for(int i=0;i<1000;i++)
	{
		p[i]=-2;
	}
	int visited[3000];
    box queue[3000];
    int exist[3000];
	long long int rear = 0;
	long long int maxsize = 10000;
	long long int front = 0;
	ArcNode *pt;
	box temp1;
	box temp2;
	temp1.position=start;
	temp1.length = 1;
	temp1.path[temp1.length-1] = temp1.position;
	//temp1.length++;
	exist[temp1.position] = 1;
	queue[front] = temp1;
	front++;
	front = front % maxsize;
	while (rear != front)
	{
		temp1 = queue[rear];
		rear++;
		rear = rear%maxsize;
		visited[temp1.position]=1;
		exist[temp1.position] = 0;
		if (temp1.position == destination)
		{
			for ( int i = 0; i < temp1.length ; i++)
			{
				p[top]=temp1.path[i];
		    	top++;	
			}
			pa=p;
			return pa;
		}

		pt=G->adjlist[temp1.position].firstarc;
		while(pt!=NULL)
		{		
				temp2.position=pt->adjvex;
				for(int i=0;i<temp1.length;i++)
				{
					temp2.path[i]=temp1.path[i];
				}
				temp2.length = temp1.length + 1;
				temp2.path[temp2.length-1]=temp2.position;
				if (exist[temp2.position] == 1||visited[temp2.position]==1)
				{
					pt=pt->nextarc;
					continue;
				}
				else
				{
					queue[front] = temp2;
					front++;
					front = front%maxsize;
					pt=pt->nextarc;
				}
			
		}
	}//need to xiugai
	printf("123");
	return pa;
}*/
int BFS(game_state_t state, NODE start, NODE to, int function)//function=1输出
{
	start.fa = -1;
	start.step = 0;
	NODE q[MaxSize*MaxSize];//队列初始化
	int front, rear;
	front = rear = -1;
	int visit[MaxSize][MaxSize] = { 0 };//记录是否访问过
	int di;//di表示方向
	rear++;
	q[rear] = start;
	visit[start.location.x][start.location.y] = 1;
	while (front != rear)
	{
		front++;
		NODE tmp = q[front];
		if (tmp.location.x == to.location.x&&tmp.location.y == to.location.y)
		{
			char a[MaxSize];
			int length = -1;
			int count = tmp.step;
			while (tmp.fa != -1)
			{
				length++;
				NODE p1 = q[tmp.fa];
				if (p1.location.x - tmp.location.x == 1)
					a[length] = 'N';
				else if (p1.location.x - tmp.location.x == -1)
					a[length] = 'S';
				else if (p1.location.y - tmp.location.y == 1)
					a[length] = 'W';
				else
					a[length] = 'E';
				tmp = p1;
			}
			while (length != -1)
			{
				if (function == 1)
					printf("%c", a[length]);
				length--;
			}
			return count;
		}
		for (di = 0; di < 4; di++)
		{
			NODE now = tmp;
			now.location.x += dx[di];
			now.location.y += dy[di];
			if (visit[now.location.x][now.location.y] == 0 && state.grid[now.location.x][now.location.y] == 0
				&& now.location.x > 0 && now.location.x < state.n&&now.location.y>0 && now.location.y < state.m)
			{
				rear++;
				now.step++;
				now.fa = front;
				q[rear] = now;
				visit[now.location.x][now.location.y] = 1;
			}
		}
	}
}

void reverse(int path[MaxSize],int a,int b)
{
	int tmp;
	while (b > a)
	{
		tmp = path[a];
		path[a] = path[b];
		path[b] = tmp;
		a++;
		b--;
	}
}

double p(int min,int new,double t)
{
	double e = exp(1);
	return pow(e, (min - new) / t);
}

void minpath(game_state_t state,int length[][MaxSize],int n)//产生随机数找较优解
{
	int t = 0;
	int max_t = 2000;
	int path[MaxSize];
	int sum;
	NODE start, to;
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < cnt; j++)
			path[j] = ans[j];
		int a = 0, b = 0;
		while (a == 0)
			a = rand() % (cnt - 1);
		while (b == 0)
			b = rand() % (cnt - 1);
		reverse(path, a, b);
		sum = 0;
		for (int i = 0; i < cnt - 1; i++)
			sum += length[path[i]][path[i + 1]];//当前路径长度
		if (p(min, sum, max_t / (t + 1)*1e-4) > rand() % 1000000000 * 1e-1) {
			for (int i = 0; i < cnt; i++) {
				ans[i] = path[i];
				min = sum;
			}
		}
	}
}

int main() {
	game_state_t state;
	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here
	x[0] = state.start_x;
	y[0] = state.start_y;
	for (int i = 0; i < state.n; i++) {//统计目标位置
		for (int j = 0; j < state.m; j++) {
			if (state.food[i][j] == 1) {
				x[cnt] = i;
				y[cnt++] = j;
			}
		}
	}

	int length[MaxSize][MaxSize] = { 0 };//统计目标之间距离
	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < cnt; j++)
		{
			if (i != j)
			{
				NODE from, to;
				from.location.x = x[i];
				from.location.y = y[i];
				to.location.x = x[j];
				to.location.y = y[j];
				length[i][j] = BFS(state, from, to, 0);
			}
		}
	}

	int count = 1;//贪心算法找较优路径
	int now = 0, tmp = 0;
	ans[0] = 0;
	int visit[MaxSize] = { 0 };//记录目标是否访问
	visit[0] = 1;
	while (count != cnt)
	{
		int minnow = min;
		for (int i = 0; i < cnt; i++)
		{
			if (length[now][i] < minnow&&i != tmp && visit[i] == 0)
			{
				minnow = length[now][i];
				tmp = i;
			}
		}
		now = tmp;
		visit[now] = 1;
		ans[count] = now;
		count++;
	}

	minpath(state, length, MaxSize);
	for (int i = 0; i < cnt - 1; i++)
	{
		NODE from, to;
		from.location.x = x[ans[i]];
		from.location.y = y[ans[i]];
		to.location.x = x[ans[i + 1]];
		to.location.y = y[ans[i + 1]];
		BFS(state, from, to, 1);
	}
	printf("\n");
	destroy(&state);
	return 0;
}
