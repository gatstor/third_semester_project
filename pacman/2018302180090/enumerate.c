#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define ERROR 0
#define OK 1

typedef struct s
{
	char direct[100];
	int x, y;
	int d;
	int visit;
}S;

typedef struct Queue
{
	S *data;
	int head, tail, length;
}Queue;

S food[100];
S info[100][100];
int min;
char inter[1000];
char answer[1000];
int visit[100][100];
S father[100][100];
int dist[100][100];

void qinit(Queue *q, int length)
{
	q->data = (S *)malloc(sizeof(S) * length);
	q->length = length;
	q->head = 0;
	q->tail = -1;
}

int push(Queue *q, S element)
{
	if (q->tail + 1 >= q->length)
	{
		return ERROR;
	}
	q->tail++;
	q->data[q->tail] = element;
	return OK;
}

S front(Queue *q)
{
	return q->data[q->head];
}

void pop(Queue *q)
{
	q->head++;
}

int empty(Queue *q)
{
	return q->head > q->tail;
}

void clear(Queue *q)
{
	free(q->data);
	free(q);
}

void bfs(game_state_t state, int num, int length)
{	
	memset(visit, 0, sizeof(visit));
	memset(dist, 0, sizeof(dist));
	Queue *q = (Queue *)malloc(sizeof(Queue));
	qinit(q, state.n * state.m);
	push(q, food[num]);
	while (!empty(q))
	{
		S tmp = front(q);
		if (tmp.x + 1 < state.n && !state.grid[tmp.x + 1][tmp.y] && !visit[tmp.x + 1][tmp.y])
		{
			visit[tmp.x + 1][tmp.y] = 1;
			S now;
			now.x = tmp.x + 1;
			now.y = tmp.y;
			now.d = tmp.d + 1;
			push(q, now);
			tmp.direct[0] = 'S';
			dist[now.x][now.y] = now.d;
			father[now.x][now.y] = tmp;
		}
		if (tmp.y + 1 < state.m && !state.grid[tmp.x][tmp.y + 1] && !visit[tmp.x][tmp.y + 1])
		{
			visit[tmp.x][tmp.y + 1] = 1;
			S now;
			now.x = tmp.x;
			now.y = tmp.y + 1;
			now.d = tmp.d + 1;
			push(q, now);
			tmp.direct[0] = 'E';
			dist[now.x][now.y] = now.d;
			father[now.x][now.y] = tmp;
		}
		if (tmp.x - 1 >= 0 && !state.grid[tmp.x - 1][tmp.y] && !visit[tmp.x - 1][tmp.y])
		{
			visit[tmp.x - 1][tmp.y] = 1;
			S now;
			now.x = tmp.x - 1;
			now.y = tmp.y;
			now.d = tmp.d + 1;
			push(q, now);
			tmp.direct[0] = 'N';
			dist[now.x][now.y] = now.d;
			father[now.x][now.y] = tmp;
		}
		if (tmp.y - 1 >= 0 && !state.grid[tmp.x][tmp.y - 1] && !visit[tmp.x][tmp.y - 1])
		{
			visit[tmp.x][tmp.y - 1] = 1;
			S now;
			now.x = tmp.x;
			now.y = tmp.y - 1;
			now.d = tmp.d + 1;
			push(q, now);
			tmp.direct[0] = 'W';
			dist[now.x][now.y] = now.d;
			father[now.x][now.y] = tmp;
		}
		pop(q);
	}

	for (int i = 0; i < length; i++)
	{
		if (i == num)
		{
			continue;
		}
		info[num][i].d = dist[food[i].x][food[i].y];

		int di = dist[food[i].x][food[i].y];
		info[num][i].direct[di] = '\0';
		S tmp = father[food[i].x][food[i].y];
		while (!(tmp.x == food[num].x && tmp.y == food[num].y))
		{
			info[num][i].direct[di - 1] = tmp.direct[0];
			tmp = father[tmp.x][tmp.y];
			di--;
		}
		info[num][i].direct[di - 1] = tmp.direct[0];
	}
}


void enumerate(game_state_t state, int dist, int num, int count, int length)
{
	if (dist >= min)
	{
		return;
	}

	if (count == 0)
	{
		
		if (dist < min)
		{
			min = dist;
			strcpy(answer, inter);
		}
		return;
	}

	for (int i = 0; i < length; i++)
	{
		if (food[i].visit)
		{
			continue;
		}
		food[i].visit = 1;
		char tmp[10000];
		strcpy(tmp, inter);
		strcat(inter, info[num][i].direct);
		enumerate(state, dist + info[num][i].d, i, count - 1, length);
		food[i].visit = 0;
		strcpy(inter, tmp);
	}
}

int main()
{
	game_state_t state;
	memset(&state, 0, sizeof(state));
	init(&state);
	// write your code here

	//printf("WEESSWW\n");
	int num = 0;
	for (int i = 0; i < state.n; i++)
	{
		for (int j = 0; j < state.m; j++)
		{
			if (state.food[i][j] == 1)
			{
				S tmp;
				tmp.x = i;
				tmp.y = j;
				tmp.d = 0;
				tmp.visit = 0;
				food[num] = tmp;
				num++;
			}
		}
	}
	S start;
	start.x = state.start_x;
	start.y = state.start_y;
	start.d = 0;
	start.visit = 0;
	food[num] = start;
	num++;
	for (int i = 0; i < num; i++)
	{
		bfs(state, i, num);
	}

	min = 2147283600;
	for (int i = 0; i < num - 1; i++)
	{
		food[i].d += info[num - 1][i].d;
		strcpy(inter, info[num - 1][i].direct);
		food[i].visit = 1;
		enumerate(state, food[i].d, i, num - 2, num - 1);
		food[i].visit = 0;
		food[i].d -= info[num - 1][i].d;
		memset(inter, 0, sizeof(inter));
	}

	printf("%s\n", answer);
	
	destroy(&state);
	return 0;
}
