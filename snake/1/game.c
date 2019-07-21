#include<stdio.h>
#include"game.h"
#include<stdlib.h>
#include<assert.h>
#include<time.h>
#include "yyz.h"
int* BFS(game_t *game, int start/*, int a[]*/) {	//start为起点，a[]为消失时间的数组

	int*path = (int*)malloc(sizeof(int) * MAXV);
     for (int x = 0; x < MAXV; x++) {
         path[x] = -2;
     }

	board_t *board = game->board;
	int a[MAXV];
	snake_t *snake = game->snake;
	//将当前的蛇的所有结点的消失时间存入a[i],结尾是1, 离结尾越远就加一。
	snake_node_t *p = snake->tail;
	snake_node_t *temp = snake->tail->next;
	int cnt = 1;
	while (p != NULL) {
	
		a[p->row*game->board->cols + p->col] = cnt + game->snake->growth;
		p=p->next;
		cnt++;
	}
	for (int x = 0; x < board->rows; x++) {
		for (int y = 0; y < board->cols; y++) {
			int m = x * board->cols + y;
			if (board->cells[m] == CELL_WALL)
				a[m] = INF;
		}
	}

	node_hao Q[30000];

	int front = -1, rear = -1;
	static int visit[MAXV][MAX];
	for (int x = 0; x < MAXV; x++) {
		for (int y = 0; y < MAX; y++)
			visit[x][y] = 0;
	}
	int temp1[MAXV];
	int pathLen = 0;





	int food[MAXV];
	for (int x = 0; x < MAXV; x++) {
		food[x] = 0;//0为没食物，1为有食物
	}
	for (int i = 0; i < game->board->cols*game->board->rows; i++) {
		if (board->cells[i] == CELL_FOOD)
			food[i] = 1;
	}

	rear++;
	Q[rear].x = start;
	Q[rear].time = 0;
	Q[rear].pre = -1;
	visit[start][0] = 1;
	int time = -1;
	while (front < rear) {
		front++;
		if(rear> 28000)
			break;
		node_hao now = Q[front];
		if (food[now.x] == 1) {
			int n = front;
			while (n != -1) {
				temp1[pathLen] = Q[n].x;
				pathLen++;
				n = Q[n].pre;
			}
			for (int x = 0; x < pathLen; x++) {
				path[x] = temp1[pathLen - x - 1];
			}
			return path;
		}

	    time = now.time + 1;//将下一步的时间存下来
		if (a[now.x + board->cols] <= time && visit[now.x + board->cols][time] == 0) {//往下
			rear++;
			Q[rear].x = now.x + board->cols;
			Q[rear].time = time;
			Q[rear].pre = front;
			visit[now.x + board->cols][time] = 1;
		}
		if (a[now.x - board->cols] <= time && visit[now.x - board->cols][time] == 0) {//往上
			rear++;
			Q[rear].x = now.x - board->cols;
			Q[rear].time = time;
			Q[rear].pre = front;
			visit[now.x - board->cols][time] = 1;
		}
		if (a[now.x + 1] <= time && visit[now.x + 1][time] == 0) {//往右
			rear++;
			Q[rear].x = now.x + 1;
			Q[rear].time = time;
			Q[rear].pre = front;
			visit[now.x + 1][time] = 1;
		}
		if (a[now.x - 1] <= time && visit[now.x - 1][time] == 0) {//往左
			rear++;
			Q[rear].x = now.x - 1;
			Q[rear].time = time;
			Q[rear].pre = front;
			visit[now.x - 1][time] = 1;
		}
	}
	return path;
}


int cul_length(int * path)
{	
	int i=0;
	int sum=0;
	for(i = 0;path[i+1]!= -2;i++)
	{ 
		sum++;
	}
	return sum;
}

int *Dijkstra(AdjGraph *G, int u, int uv) {
	int tmp[MAXV];
	int *temp;
	temp = (int*)malloc(sizeof(int)*MAXV);
	for (int i = 0; i < MAXV; i++)
	{
		temp[i] = -2;
	}
	ArcNode *p;/* = (ArcNode*)malloc(sizeof(ArcNode));*/
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
	{	
		return NULL;
	}
	return temp;
}

void DispAdj(AdjGraph *G)
{
	int i;
	ArcNode *p;
	for(int i=0;i<G->n;i++)
	{
		p=G->adjlist[i].firstarc;
		printf("%3d: ",i);
		while(p!=NULL)
		{
			printf("%3d[%d]->",p->adjvex,p->weight);
			p=p->nextarc;
		}
		printf("^\n");
	}
}

/*void SET(int *path, int m, snake_t *snake){
    int i = 0;
    for(i = 0; path[i+1]!=-2;i++){
        if(path[i+1]-path[i]==1){
            set_direction(snake, EAST);
		}else if(path[i+1]==path[i]-1){
            set_direction(snake, WEST);	
        }else if(path[i+1]==path[i]+m){
            set_direction(snake, SOUTH);
        }else if(path[i+1]==path[i]-m){
            set_direction(snake, NORTH);

        }
    }
}*/


void destroy_list(AdjGraph *G)
{
	int i;
	ArcNode *pre;
	ArcNode *p;
	for(int i=0;i<G->n;i++)
	{
		pre=G->adjlist[i].firstarc;
		if(pre!=NULL)
		{
			p=pre->nextarc;
			while(p!=NULL)
			{
				free(pre);
				pre=p;
				p=p->nextarc;
			}
			free(pre);
		}
	}
	free(G);
}



void Create_list(game_t* game, AdjGraph **G)
{
    int x;
    int y;
    ArcNode *p;
    int e = 0;
    board_t *board = game->board;
	int head=game->snake->head->row*game->board->cols+game->snake->head->col;
    for (int i = 0; i < board->cols*board->rows; i++)
    {
        (*G)->adjlist[i].firstarc = NULL;
    }
    for (int i = 0; i < board->cols*board->rows; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            x = i / board->cols;
            y = i % board->cols;
			if(i==head)
				goto flag;
            if (board->cells[i] == CELL_WALL
                || board->cells[i] == CELL_SNAKE)
                break;//当前位置是墙，不做路径考虑
flag:  if (j == 0)//向右寻找
            {
                if (board->cells[i + 1] == CELL_OPEN || board->cells[i + 1] == CELL_FOOD)//右边有路径
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
                if (board->cells[i - 1] == CELL_OPEN || board->cells[i + 1] == CELL_FOOD)//左边有路径
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
                if (board->cells[i - board->cols] == CELL_OPEN || board->cells[i - board->cols] == CELL_FOOD)//上边有路径
                {
                    p = (ArcNode*)malloc(sizeof(ArcNode));
                    p->adjvex = i - board->cols;
                    p->weight = 1;
                    p->nextarc = (*G)->adjlist[i].firstarc;
                    (*G)->adjlist[i].firstarc = p;
                    e++;
                }
            }
            if (j == 3)//向下寻找
            {
                if (board->cells[i + board->cols] == CELL_OPEN || board->cells[i + board->cols] == CELL_FOOD)//下边有路径
				{
					p = (ArcNode*)malloc(sizeof(ArcNode));
                    p->adjvex = i + board->cols;
                    p->weight = 1;
                    p->nextarc = (*G)->adjlist[i].firstarc;
                    (*G)->adjlist[i].firstarc = p;
                    e++;
                }
            }
        }
    }
    (*G)->n = board->cols*board->rows;
    (*G)->e = e;
}




board_t * create_board(int rows, int cols)
{
	board_t *myboard = (board_t*)calloc(1, sizeof(board_t));
	myboard->cells = (cell_t*)calloc(rows*cols, sizeof(cell_t));
	myboard->rows = rows;
	myboard->cols = cols;
	for(int i=0;i<rows*cols;i++)
	{
	    myboard->cells[i]=CELL_OPEN;
    }
	return myboard;
}

void destroy_board(board_t * cur_board)
{
	free(cur_board->cells);
	free(cur_board);
}


snake_t *create_snake(board_t *board, int row, int col, direction_t heading) {	
	snake_t* snake;
	snake=(snake_t*)malloc(sizeof(snake_t));
	snake->head= (snake_node_t*)malloc(sizeof(snake_node_t));
	snake->tail = snake->head;
	snake->heading = heading;
	
	snake->tail->row = row;         	//蛇的初始位置（row,col）
	snake->tail->col = col;
	snake->head->row = row;
	snake->head->col = col;
	snake->tail->next = NULL;
	snake->head->next = NULL;
	board->cells[row *board->cols + col] = CELL_SNAKE;
	snake->growth=0;
	return snake;
}


void destroy_snake(snake_t *snake) {
	if (snake == NULL) {
		return;
	}
//	if(snake->tail->next==NULL)
//	{
//		free(snake->head);
//	}
	snake_node_t *cur = snake->tail;
	while (cur != NULL) {
		snake_node_t *save = cur;
		cur = cur->next;
		free(save);
		//save = NULL;
	}
	free(snake);
}


/* get cell in specific position */
cell_t *board_cell(board_t *board, int row, int col) {
    if (row < 0 || col < 0)
	{
		return NULL;
	}
	else if (row >= board->rows || col >= board->cols)
	{
		return NULL;
	}
	return &board->cells[row * board->cols + col];
}



void randomly_add_food(board_t *board, float probability)
{
    float pro = rand() % 100000;
    pro = pro / 100000;
    int flag = 0;
    if (pro < probability)
        flag = 1;
    //在0-1中等概率分布，当pro大于proability时，赋值。否则不赋值 
    //x,y是board的行数和列数

    if (flag) 
    {
        int num = board->rows * board->cols;//点的个数
        int open[num],cnt = 0;
        for(int i = 0 ; i < num; i++)
        {
            if(board->cells[i] == CELL_OPEN)
                open[cnt++] = i;
        }
    
        if(cnt == 0)//如果一个空的位置都没有了
            return;
        int tmp = rand() % cnt;//从中随机找一个位置赋值
        cell_t temp = board->cells[open[tmp]];
        
        if (temp == CELL_OPEN)
        {
            board->cells[open[tmp]] = CELL_FOOD;
            return;
        }
    }
}




void set_direction(snake_t *snake, direction_t d)
{
	assert(d == EAST || d == SOUTH || d == WEST || d == NORTH);
	if (snake->heading == EAST)
	{
		assert(d != WEST);
	}
	if (snake->heading == WEST)
	{
		assert(d != EAST);
	}
	if (snake->heading == NORTH)
	{
		assert(d != SOUTH);
	}
	if (snake->heading == SOUTH)
	{
		assert(d != NORTH);
	}
	snake->heading = d;
}

void update_snake_head(snake_t *snake, board_t *board, int growth_per_food)
{
	assert(snake != NULL && board != NULL);
	assert(growth_per_food > 0);
	int x;
	int y;
	int gai=0;
	//snake_node_t *tmp=NULL;
	if (snake->head->next == NULL && snake->tail->next == NULL)
	{
		gai=1;
		//tmp=snake->head;
	}
	x = snake->head->row;
	y = snake->head->col;
	snake_node_t *p = NULL;//临时结点
	int position = x * board->cols + y;//position express the number;
	int temp_position = -1;
	if (snake->heading == SOUTH)
	{
		temp_position = position + board->cols;
	    if (board->cells[temp_position] != CELL_FOOD)
		{
			p = (snake_node_t*)malloc(sizeof(snake_node_t));
			p->col = temp_position % board->cols;
			p->row = temp_position / board->cols;//建立新结点
			p->next = NULL;
			snake->head->next = p;//更改头结点
			snake->head=p;
		}
		else
		{
			p = (snake_node_t*)malloc(sizeof(snake_node_t));
			p->col = temp_position % board->cols;
			p->row = temp_position / board->cols;//建立新结点
			p->next = NULL;
			snake->head->next = p;//更改头结点
			snake->growth += growth_per_food;
			 snake->head=p;

		}
	}
	else if (snake->heading == NORTH)
	{
		temp_position = position - board->cols;
		if (board->cells[temp_position] != CELL_FOOD)
		{
			p = (snake_node_t*)malloc(sizeof(snake_node_t));
			p->col = temp_position % board->cols;
			p->row = temp_position / board->cols;//建立新结点
			p->next = NULL;
			snake->head->next = p;//更改头结点
			snake->head=p;

		}
		else
		{
			p = (snake_node_t*)malloc(sizeof(snake_node_t));
			p->col = temp_position % board->cols;
			p->row = temp_position / board->cols;//建立新结点
			p->next = NULL;
			snake->head->next = p;//更改头结点
			snake->growth += growth_per_food;
			 snake->head=p;
		}
	}
	else if (snake->heading == EAST)
	{
		temp_position = position + 1;
		if (board->cells[temp_position] != CELL_FOOD)
		{
			p = (snake_node_t*)malloc(sizeof(snake_node_t));
			p->col = temp_position % board->cols;
			p->row = temp_position / board->cols;//建立新结点
			p->next = NULL;
			snake->head->next = p;//更改头结点
			snake->head=p;

		}
		else
		{
			p = (snake_node_t*)malloc(sizeof(snake_node_t));
			p->col = temp_position % board->cols;
			p->row = temp_position / board->cols;//建立新结点
			p->next = NULL;
			snake->head->next = p;//更改头结点
			snake->growth += growth_per_food;
			snake->head=p;

		}
	}
	else if (snake->heading == WEST)
	{
		temp_position = position - 1;
		if (board->cells[temp_position] != CELL_FOOD)
		{
			p = (snake_node_t*)malloc(sizeof(snake_node_t));
			p->col = temp_position % board->cols;
			p->row = temp_position / board->cols;//建立新结点
			p->next = NULL;
			snake->head->next = p;//更改头结点
			snake->head=p;

		}
		else
		{
			p = (snake_node_t*)malloc(sizeof(snake_node_t));
			p->col = temp_position % board->cols;
			p->row = temp_position / board->cols;//建立新结点
			p->next = NULL;
			snake->head->next = p;//更改头结点
			snake->growth += growth_per_food;
			snake->head=p;

		}
	}
	if(gai == 1)
	{
		snake->tail->next = snake->head;
	}
    //if(tmp!=NULL)
		//free(tmp);
}

void update_snake_tail(snake_t *snake, board_t *board)
{
	assert(snake != NULL && board != NULL);
	assert(snake->growth >= 0);
	if (snake->growth > 0)//snake still can explore
	{
		(snake->growth)--;	
	}
	else// snake can't explore
	{
		int temp_position = -1;
		temp_position = snake->tail->col + snake->tail->row*board->cols;
		board->cells[temp_position] = CELL_OPEN;
		snake_node_t* p;
		p = snake->tail;
		snake->tail = snake->tail->next;
		free(p);
	}
}

int next_frame(game_t*cur_game)
{
	randomly_add_food(cur_game->board, cur_game->food_probability);
	update_snake_head(cur_game->snake, cur_game->board, cur_game->growth_per_food);
	update_snake_tail(cur_game->snake, cur_game->board);
	int temp_position = -1;//to save the head's position;
	temp_position = (cur_game->snake->head->row)*(cur_game->board->cols) + cur_game->snake->head->col;
	if (cur_game->board->cells[temp_position] == CELL_OPEN || cur_game->board->cells[temp_position] == CELL_FOOD)
	{
	    cur_game->board->cells[temp_position] = CELL_SNAKE;
		return 0;
	}
	else
		return 1;
}


