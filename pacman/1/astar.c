#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include "util.h"
#define MAX 32767
#define N 60
#define MAXV 2000
#define INF 999999


typedef struct edge {
	int v, w, next;
} edge;

typedef struct Queue {
	int data[N * N * 2];
	int l, r;
} Queue;

typedef struct Node {
	int x, y, step;
	int parent;
}Node;

typedef struct Queue1 {
	Node data[MAX];
	int front, rear;
	int max_size;
}Queue1;

typedef struct queue {
	int data[N];
	int l, r;
} queue;

typedef struct node {
	int v, g, h;
	queue path;
} node;

typedef struct priority_queue {
	node data[N * N * 200];
	int size;
} priority_queue;

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


void Queue_init(Queue *q);
int Queue_size(Queue *q);
void Queue_push(Queue *q, int val);
int Queue_pop(Queue *q);
int minmy(int a, int b);


void Init(Queue1 *);
void enqueue(Queue1 *, Node);
Node dequeue(Queue1 *);

void pq_init(priority_queue* q);
void swap(node *x, node *y);
int pq_cmp(node a, node b);
void pq_push(priority_queue *q, node val);
node pq_pop(priority_queue *q);
int pq_size(priority_queue *q);

void queue_init(queue *q);
int queue_size(queue *q);
void queue_push(queue *q, int val);
int queue_pop(queue *q);
int queue_cmp(queue* a, queue* b);
int ok(queue *q, int v);

void Queue_init(Queue *q) {
	q->l = 1;
	q->r = 0;
}

int Queue_size(Queue *q) {
	return q->r - q->l + 1;
}

void Queue_push(Queue *q, int val) {
	if (q->r >= N * N * 2) {
		printf("Queue_push\n");
		exit(0);
	}
	q->data[++q->r] = val;
}

int Queue_pop(Queue *q) {
	if (Queue_size(q) <= 0) {
		printf("Queue_pop\n");
		exit(0);
	}
	return q->data[q->l++];
}

int minmy(int a, int b) {
	return a < b ? a : b;
}

void queue_init(queue *q) {
	q->l = 1;
	q->r = 0;
}

int queue_size(queue *q) {
	return q->r - q->l + 1;
}

void queue_push(queue *q, int val) {
	if (q->r >= N) {
		printf("queue_push\n");
		exit(0);
	}
	q->data[++q->r] = val;
}

int queue_pop(queue *q) {
	if (queue_size(q) <= 0) {
		printf("queue_pop\n");
		exit(0);
	}
	return q->data[q->l++];
}


int queue_cmp(queue* a, queue* b) {
	int n = minmy(queue_size(a), queue_size(b));
	for (int i = 0; i < n; i++) {
		if (a->data[a->l + i] != b->data[b->l + i]) {
			return a->data[a->l + i] < b->data[b->l + i];

		}
	}
	return queue_size(a) < queue_size(b);
}

void pq_init(priority_queue* q) {
	q->size = 0;
}

void swap(node *x, node *y) {
	struct node tmp = *x;
	*x = *y;
	*y = tmp;
}

int pq_cmp(node a, node b) {
	if (a.g + a.h != b.g + b.h) {
		return a.g + a.h < b.g + b.h;
	}
	return queue_cmp(&a.path, &b.path);
}

void pq_push(priority_queue *q, node val) {/*{{{*/
	if (q->size >= N * N * 200) {
		printf("pq_push\n");
		exit(0);
	}
	int p = ++q->size;
	q->data[p] = val;
	while (p > 1 && pq_cmp(q->data[p], q->data[p / 2])) {
		swap(&q->data[p / 2], &q->data[p]);
		p /= 2;
	}
};

node pq_pop(priority_queue *q) {/*{{{*/
	if (q->size <= 0) {
		printf("pq_pop\n");
		exit(0);
	}
	node res = q->data[1];
	q->data[1] = q->data[q->size--];
	int p = 1, t;
	while (p * 2 <= q->size) {
		if (p * 2 + 1 > q->size || pq_cmp(q->data[p * 2], q->data[p * 2 + 1])) {
			t = p * 2;
		}
		else {
			t = p * 2 + 1;
		}
		if (pq_cmp(q->data[t], q->data[p])) {
			swap(&q->data[p], &q->data[t]);
			p = t;
		}
		else {
			break;
		}
	}
	return res;
};

int pq_size(priority_queue *q) {
	return q->size;
}

int ok(queue *q, int v) {
	for (int i = q->l; i <= q->r; i++) {
		if (q->data[i] == v) {
			return 1;
		}
	}
	return 0;
}


void Init(Queue1 *qu) {
	qu->front = qu->rear = 0;
	qu->max_size = MAX;
}

void enqueue(Queue1 *qu, Node val) {
	if (qu->rear > qu->max_size) {
		printf("Failed to enqueue!\n");
		exit;
	}
	qu->rear++;
	qu->data[qu->rear] = val;
}

Node dequeue(Queue1 *qu) {
	if (qu->rear == qu->front) {
		printf("Failed to dequeue!\n");
		exit;
	}
	qu->front++;
	return qu->data[qu->front];
}
int *A_star(AdjGraph *G, int u, int uv, game_state_t state) {
	int h[MAXV];
	int tmp[MAXV];
	int *temp;
	int *path_yang;
	temp = (int*)malloc(sizeof(int)*MAXV);
	for (int i = 0; i < MAXV; i++)
	{
		temp[i] = -2;
	}
	ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
	double dist[MAXV];
	int path[MAXV];
	int S[MAXV];
	double MINdis;
	int i, j, v;
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
			int tx = j / state.m;
			int ty = j % state.m;
			int vx = uv / state.m;
			int vy = uv % state.m;
			h[j] = abs(tx-vx) + abs(ty-vy);
			if (S[j] == 0 && dist[j] + h[j] < MINdis) {
				v = j;
				MINdis = dist[j] + h[j];
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
	if (k < 1)
		return NULL;
	return temp;
}

void printDir(int *path, int m) {
	char dir[MAXV];
	int i = 0;
	for (i = 0; i <= m * 100; i++) {
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
	printf("%s", dir);
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
					p->weight = state.cost[x][y + 1];
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
	(*G)->n = state.m*state.n;
	(*G)->e = e;
}



int main() {
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
	path = (int *)malloc(sizeof(int) * 20000);
	path = A_star(G, u, v, state);
	int m = state.m;
	printDir(path, m);
	destroy(&state);

	return 0;
}

