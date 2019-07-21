/*#include "ai.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

void DFS(board_t * cur_board, int * distance_map, int row, int col,int distance, int * closest_distance)
	
{
	int *ptr = distance_map + col + (cur_board->cols*row);

	if (row >= 0 && row < cur_board->rows && col >= 0 && cur_board->cols > col)
	{
		if (*(board_cell(cur_board, row, col)) == CELL_OPEN || *(board_cell(cur_board, row, col)) == CELL_FOOD)
		{

			if (distance < *ptr)
			{

				*ptr = distance++;

				if (*(board_cell(cur_board, row, col)) == CELL_FOOD && *ptr < *closest_distance)
				{
					*closest_distance = *ptr;
				}

				DFS(cur_board, distance_map, row + 1, col, distance, closest_distance);
				DFS(cur_board, distance_map, row - 1, col, distance, closest_distance);
				DFS(cur_board, distance_map, row, col + 1, distance, closest_distance);
				DFS(cur_board, distance_map, row, col - 1, distance, closest_distance);
			}
		}
	}

}

int food_distance(board_t * cur_board, int * distance_map, int row, int col)
{
	int index, distance = INT_MAX;
	for (index = 0; index < cur_board->rows * cur_board->cols; index++)
	{
		distance_map[index] = INT_MAX;
	}
	DFS(cur_board, distance_map, row, col, 0, &distance);
	return distance;
}

void avoid_walls(board_t * cur_board, snake_t * cur_snake)
{
	int row = cur_snake->head->row;
	int col = cur_snake->head->col;
	if (*board_cell(cur_board, row + 1, col) == CELL_OPEN)
	{
		cur_snake->heading = SOUTH;
	}
	else if (*board_cell(cur_board, row - 1, col) == CELL_OPEN)
	{
		cur_snake->heading = NORTH;
	}
	else if (*board_cell(cur_board, row, col + 1) == CELL_OPEN)
	{
		cur_snake->heading = EAST;
	}
	else if (*board_cell(cur_board, row, col - 1) == CELL_OPEN)
	{
		cur_snake->heading = WEST;
	}
	
}
direction_t get_action(game_t* cur_game)
{
	int row = cur_game->snake->head->row;
	int col = cur_game->snake->head->col;
	int *distance_map = malloc(sizeof(int)*cur_game->board->rows*cur_game->board->cols);
	int d[4];
	int min;
	int counter;

	d[0] = food_distance(cur_game->board, distance_map, row + 1, col);
	d[1] = food_distance(cur_game->board, distance_map, row - 1, col);
	d[2] = food_distance(cur_game->board, distance_map, row, col + 1);
	d[3] = food_distance(cur_game->board, distance_map, row, col - 1);

	free(distance_map);

	min = d[0];
	for (counter = 0; counter < 4; counter++)
	{
		if (min > d[counter])
			min = d[counter];
	}

	if (min == INT_MAX)
		avoid_walls(cur_game->board, cur_game->snake);
	else if (min == d[0])
	{
		cur_game->snake->heading = SOUTH;
		return SOUTH;
	}
	else if (min == d[1])
	{
		cur_game->snake->heading = NORTH;
		return NORTH;
	}
	else if (min == d[2])
	{
		cur_game->snake->heading = EAST;
		return EAST;
	}
	else if (min == d[3])
	{
		cur_game->snake->heading = WEST;
		return WEST;
	}
}*/




/*#include "ai.h"
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#define N 105

typedef struct
{
	int x;
	int y;
	int dir;
}node;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

void dfs(game_t* game, int vis[][N], int sx, int sy, int cnt, int *length, int *is_changed, int passed)
{
	int cols = game->board->cols;
	int rows = game->board->rows;
	if ((*length) < cnt && passed == 1)
	{
		*length = cnt;
		*is_changed = 1;
	}
	int d = 0;
	while (d < 4)
	{
		int tx = sx + dx[d];
		int ty = sy + dy[d];
		if (tx >= 0 && tx < rows && ty >= 0 && ty < cols)
		{
			if ((game->board->cells[(tx)*cols + ty] == CELL_FOOD
				|| game->board->cells[(tx)*cols + ty] == CELL_OPEN)
				&& !vis[tx][ty])
			{
				if (game->board->cells[(tx)*cols + ty] == CELL_FOOD)
					passed = 1;
				vis[tx][ty] = 1;
				dfs(game, vis, tx, ty, cnt + 1, length, is_changed, passed);
				vis[tx][ty] = 0;
			}
		}
		d++;
	}
}

direction_t get_action(game_t* game) {
	int cols = game->board->cols;
	int rows = game->board->rows;
	int flag = 0;
	node tmp;
	tmp.x = game->snake->head->row;
	tmp.y = game->snake->head->col;
	tmp.dir = 4;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (game->board->cells[i * cols + j] == CELL_FOOD)
				flag = 1;
		}
	}
	if (flag == 0)//there's no food to eat, choose a direction available at random
	{
		srand((unsigned)time(NULL));
		int x = tmp.x;
		int y = tmp.y;
		while (1)
		{
			int d = rand() % 4;
			if (x + dx[d] >= 0 && x + dx[d] < rows
				&& y + dy[d] >= 0 && y + dy[d] < cols)
			{
				if (game->board->cells[(x + dx[d])*cols + y + dy[d]] == CELL_FOOD
					|| game->board->cells[(x + dx[d])*cols + y + dy[d]] == CELL_OPEN)
				{
					return d;
				}
			}
		}
	}
	int vis[N][N];//else,dfs
	memset(vis, 0, sizeof(vis));
	int length = 0;
	int d = 0;
	int sx = tmp.x;
	int sy = tmp.y;
	direction_t direction = SOUTH;
	int is_changed;
	while (d < 4)
	{
		int tx = sx + dx[d];
		int ty = sy + dy[d];
		int passed = 0;
		is_changed = 0;
		if (tx >= 0 && tx < rows
			&& ty >= 0 && ty < cols)
		{
			if ((game->board->cells[(tx)*cols + ty] == CELL_FOOD
				|| game->board->cells[(tx)*cols + ty] == CELL_OPEN)
				&& !vis[tx][ty])
			{
				vis[tx][ty] = 1;
				if (game->board->cells[(tx)*cols + ty] == CELL_FOOD)
					passed = 1;
				dfs(game, vis, tx, ty, 1, &length, &is_changed, passed);
				if (is_changed) direction = d;
				vis[tx][ty] = 0;
			}
		}
		d++;
	}
	return direction;
}
*/

#include "ai.h"
#include "game.h"
#include <string.h>
#include <stdlib.h>
//#include <assert.h>
//三维数组BFS
typedef struct {
	int x, y, t;
}A;

#define MX 1000
#define N 40
int maxxx = 0;
direction_t dd;
int ans_x[111], ans_y[111], cnt = 0;

int dx[4] = { -1, 0, 0, 1 };
int dy[4] = { 0, -1, 1, 0 };
direction_t dr[4] = {NORTH, WEST, EAST, SOUTH};
int exit_flag = 0;

void dfs(int sx, int sy, int ex, int ey, int *path_x, int *path_y,
	int top, int vis[][10], board_t* board, int flag) {
	if (exit_flag == 1)
		return;
	if (board->cells[sx * board->cols + sy] == CELL_FOOD)
		flag += 1;
	if (top > cnt && flag != 0 && ex == sx && ey == sy) {
		cnt = top;
		//exit_flag = 1;
		for (int i = 0; i < cnt; i++) {
			ans_x[i] = path_x[i];
			ans_y[i] = path_y[i];
		}
		return;
	}
	for (int i = 0; i < 4; i++) {
		int tx = sx + dx[i], ty = sy + dy[i];
		if (tx >= 0 && tx < board->rows && ty >= 0 && ty < board->cols && !vis[tx][ty]
			&& (board->cells[tx * board->cols + ty] == CELL_OPEN || board->cells[tx * board->cols + ty] == CELL_FOOD)) {
			vis[tx][ty] = 1;
			path_x[top] = tx, path_y[top] = ty;
			dfs(tx, ty, ex, ey, path_x, path_y, top + 1, vis, board, flag);
			vis[tx][ty] = 0;
		}
	}
}

direction_t get_path(board_t* board, int sx, int sy, int ex, int ey) {
	int vis[10][10] = { 0 };
	vis[sx][sy] = 1;
	int path_x[111] = { sx }, path_y[111] = { sy };
	dfs(sx, sy, ex, ey, path_x, path_y, 1, vis, board, 0);
	if (path_x[1] == sx && path_y[1] == sy - 1)
		return WEST;
	if (path_x[1] == sx && path_y[1] == sy + 1)
		return EAST;
	if (path_x[1] == sx - 1 && path_y[1] == sy)
		return NORTH;
	if (path_x[1] == sx + 1 && path_y[1] == sy)
		return SOUTH;
}

direction_t get_action(game_t* game) {
    int sx = game->snake->head->row, sy = game->snake->head->col;
	int ex = game->snake->tail->row, ey = game->snake->tail->col;
	int foodflag = 0;
	for (int i = 0; i < game->board->rows; i++)
	    for (int j  = 0; j < game->board->cols; j++) {
	        foodflag = 1;
	        break;
	    }
	if (foodflag == 0) {
	    while (1) {
	        int rdd = rand() % 4;
	        if (sx + dx[rdd] >= 0 && sx + dx[rdd] < game->board->rows
	            && sy + dy[rdd] >= 0 && sy + dy[rdd] < game->board->cols
	            && (game->board->cells[(sx + dx[rdd]) * game->board->cols + sy + dy[rdd]] == CELL_OPEN
	            || game->board->cells[(sx + dx[rdd]) * game->board->cols + sy + dy[rdd]] == CELL_FOOD)) 
	            return dr[rdd];   
   	    }
	}    
	return get_path(game->board, sx, sy, ex, ey);
}

