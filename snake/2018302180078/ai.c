#include "ai.h"
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "file.h"




// 存路径
int ans_x[2000], ans_y[2000], cnt = 0;
int only = 0;
int two = 0;
int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, -1, 1, 0 };

// sx, sy: 源点
// path_x, path_y, top: 已走过的路径
// vis: 被访问过的路径
// a: 地图
// passed: 有没有经过food
// zx, zy: 终点


int have_food(game_t * game)
{
	for (int i = 0; i < game->board->rows*game->board->cols; i++)
	{
		if (game->board->cells[i] == CELL_FOOD)
			return 1;
	}
	return 0;
}



int judge_huitou(int tx, int ty, game_t* game)// fanhui 1 biaoshi huitou
{
	int sx = game->snake->head->row;
	int sy = game->snake->head->col;
	if (game->snake->heading == SOUTH)
	{
		if (tx - sx == -1 && sy == ty)
			return 1;
	}
	if (game->snake->heading == NORTH)
	{
		if (tx - sx == 1 && sy == ty)
			return 1;
	}
	if (game->snake->heading == WEST)
	{
		if (sx == tx && ty - sy == 1)
			return 1;
	}
	if (game->snake->heading == EAST)
	{
		if (sx == tx && ty - sy == -1)
			return 1;
	}
	return 0;
}

int tmp_flag = 0;
int tmp_ans_x[200];
int tmp_ans_y[200];
int tmp_cnt = 1;
int youfood = 0;

void dfs(int sx, int sy, int *path_x, int *path_y,
	int top, int vis[][7], game_t *a, int passed,
	int zx, int zy) {
	// 更新答案
	int m = a->board->cols;
	if (sx == zx && sy == zy && tmp_flag == 0)
	{
		tmp_cnt = top;
		tmp_flag = 1;
		for (int i = 0; i < tmp_cnt; i++)
		{
			tmp_ans_x[i] = path_x[i];
			tmp_ans_y[i] = path_y[i];
		}
	}

	if (passed && top > cnt && sx == zx && sy == zy) {
		cnt = top;
		for (int i = 0; i < cnt; i++) {
			ans_x[i] = path_x[i];
			ans_y[i] = path_y[i];
		}
		youfood = 1;
	}


	for (int i = 0; i < 4; i++) {
		int tx = sx + dx[i], ty = sy + dy[i];
		if (tx == a->snake->tail->row && ty == a->snake->tail->col && (passed == 1 || two == 0))
			goto flag;
		if (tx >= 0 && tx < 7 && ty >= 0 && ty < 7 && !vis[tx][ty]
			&& a->board->cells[tx*m + ty] != CELL_WALL) {
			if (a->board->cells[tx*m + ty] == CELL_SNAKE)
				continue;
		flag:	if (only == 1 && judge_huitou(tx, ty, a) == 1)//only=1 express the snake is 1 box
			continue;

				vis[tx][ty] = 1;
				path_x[top] = tx, path_y[top] = ty;
				dfs(tx, ty, path_x, path_y, top + 1, vis, a,
					passed | (a->board->cells[tx*m + ty] == CELL_FOOD), zx, zy);
				vis[tx][ty] = 0;
		}
	}
}

direction_t get_path(game_t *a, int sx, int sy, int zx, int zy) {
	if (a->snake->head == a->snake->tail)
	{
		only = 1;
	}
	else only = 0;
	if (a->snake->head == a->snake->tail->next)
	{
		two = 1;
	}
	else two = 0;
	youfood = 0;
	tmp_flag = 0;
	int position = sx * a->board->cols + sy;
	int m = a->board->cols;
	for (int i = 0; i < 200; i++)
	{
		tmp_ans_x[i] = sx;
		tmp_ans_y[i] = sy;
	}
	tmp_cnt = 0;
	if ((only || two) && !have_food(a))
	{
		if (a->snake->heading == SOUTH)
		{
			if (a->board->cells[position - 1] != CELL_WALL)
				return WEST;
			if (a->board->cells[position + 1] != CELL_WALL)
				return EAST;
		}
		if (a->snake->heading == NORTH)
		{
			if (a->board->cells[position - 1] != CELL_WALL)
				return WEST;
			if (a->board->cells[position + 1] != CELL_WALL)
				return EAST;
		}
		if (a->snake->heading == EAST)
		{
			if (a->board->cells[position + m] != CELL_WALL)
				return SOUTH;
			if (a->board->cells[position - m] != CELL_WALL)
				return NORTH;
		}
		if (a->snake->heading == WEST)
		{
			if (a->board->cells[position + m] != CELL_WALL)
				return SOUTH;
			if (a->board->cells[position - m] != CELL_WALL)
				return NORTH;
		}
	}
	int vis[7][7] = { 0 };
	cnt = 0;
	vis[sx][sy] = 1;
	int path_x[2000] = { sx }, path_y[2000] = { sy };
	if (only == 0)
		dfs(sx, sy, path_x, path_y, 1, vis, a, 0, zx, zy);
	if (only == 1)
		dfs(sx, sy, path_x, path_y, 1, vis, a, 0, 3, 3);
	if (youfood == 0)
	{
		if (tmp_ans_x[1] - sx == 1 && tmp_ans_y[1] - sy == 0)
			return SOUTH;
		else if (tmp_ans_x[1] - sx == 0 && tmp_ans_y[1] - sy == 1)
			return EAST;
		else if (tmp_ans_x[1] - sx == -1 && tmp_ans_y[1] - sy == 0)
			return NORTH;
		else if (tmp_ans_x[1] - sx == 0 && tmp_ans_y[1] - sy == -1)
			return WEST;

	}
	if (ans_x[1] - sx == 1 && ans_y[1] - sy == 0)
		return SOUTH;
	else if (ans_x[1] - sx == 0 && ans_y[1] - sy == 1)
		return EAST;
	else if (ans_x[1] - sx == -1 && ans_y[1] - sy == 0)
		return NORTH;
	else if (ans_x[1] - sx == 0 && ans_y[1] - sy == -1)
		return WEST;
	return a->snake->heading;
}


direction_t get_action(game_t* game) {
	int sx = game->snake->head->row;
	int sy = game->snake->head->col;
	int tail_x = game->snake->tail->row;
	int tail_y = game->snake->tail->col;
	for (int i = 0; i < 2000; i++)
	{
		ans_x[i] = 0;
		ans_y[i] = 0;
	}
	return get_path(game, sx, sy, tail_x, tail_y);
}
