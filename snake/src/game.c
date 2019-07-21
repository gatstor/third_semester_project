#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

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
	snake_node_t *cur = snake->tail;
	while (cur != NULL) {
		snake_node_t *save = cur;
		cur = cur->next;
		free(save);
		//save = NULL;
	}
	free(snake);
}

board_t * create_board(int rows, int cols)
{
	board_t *myboard = (board_t*)calloc(1, sizeof(board_t));
	myboard->cells = (cell_t*)calloc(rows*cols, sizeof(cell_t));
	myboard->rows = rows;
	myboard->cols = cols;
	for (int i = 0; i < rows*cols; i++)
	{
		myboard->cells[i] = CELL_OPEN;
	}
	return myboard;
}

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

void destroy_board(board_t * cur_board)
{
	free(cur_board->cells);
	free(cur_board);
}


void randomly_add_food(board_t *board, float probability)
{   
    static int is_random = 0;
    if(!is_random){
        srand(time(NULL));
        is_random = 1;
    }
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


