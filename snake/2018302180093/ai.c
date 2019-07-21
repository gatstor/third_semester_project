#include "ai.h"
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "file.h"
#include <time.h>
#include <memory.h>
#define N 20
int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

// sx, sy: 源点
// path_x, path_y, top: 已走过的路径
// vis: 被访问过的路径
// a: 地图
// passed: 有没有经过food
// zx, zy: 终点
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
    int sx = game->snake->head->row;
    int sy = game->snake->head->col;
    int m = game->board->cols;
    int n = game->board->rows;
    int vis[20][20];
    memset(vis,0,sizeof(vis));
    int path[111] = { sx * m + sy };
    //检查是不是有食物
    int flag = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (game->board->cells[i*m + j] == CELL_FOOD) {
                flag = 1;
            }
        }
    }
    //如果没有食物
    if (flag == 0) {
        srand(time(NULL));
        int x = sx; int y = sy;
        while (1) {
            int d = rand() % 4;
            if (x + dx[d] >= 0 && x + dy[d] < n
                && y + dy[d] >= 0 && y + dy[d] < m) {
                if (game->board->cells[(x + dx[d])*m + y + dy[d]] == CELL_FOOD
                    || game->board->cells[(x + dx[d])*m + y + dy[d]] == CELL_OPEN)
                    return d;
            }
        }
    }
    //如果有食物，进行以蛇尾为终点经过食物的DFS搜索
    direction_t dir = SOUTH;
    int is_changed;
    int d = 0;
    int passed = 0;
    int length = 0;
    while (d < 4) {
        int tx = sx + dx[d];
        int ty = sy + dy[d];
        is_changed = 0;
        passed = 0;
        if (tx >= 0 && tx < n
            &&ty >= 0 && ty < m) {
            if ((game->board->cells[tx * m + ty] == CELL_OPEN)
                && !vis[tx][ty]||game->board->cells[tx*m + ty] == CELL_FOOD) {
                vis[tx][ty] = 1;
                if (game->board->cells[(tx)*m + ty] == CELL_FOOD)
					passed = 1;
                dfs(game, vis, tx, ty, 1, &length, &is_changed, passed);
                if (is_changed)dir = d;
                vis[tx][ty] = 0;
            }
        }
        d++;
    }
    return dir;

}
