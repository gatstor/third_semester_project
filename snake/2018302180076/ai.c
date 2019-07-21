#include "ai.h"
#include "game.h"
#include <string.h>
#include <stdlib.h>
int ans_x[111], ans_y[111], cnt = 0;
int dx[4] = { -1, 0, 0, 1 };
int dy[4] = { 0, -1, 1, 0 };
direction_t dr[4] = {NORTH, WEST, EAST, SOUTH};
int flag1 = 0;

void dfs(int sx, int sy, int *path_x, int *path_y,
int top, int vis[][100], board_t* board, int flag) {
    if (flag1 == 1)
        return;
    if (board->cells[sx * board->cols + sy] == CELL_FOOD)
        flag += 1;
    if (top > cnt && flag != 0 ) {
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
            dfs(tx, ty, path_x, path_y, top + 1, vis, board, flag);
            vis[tx][ty] = 0;
        }
    }
}

direction_t get_action(game_t* game) {
    memset(ans_x, 0, sizeof(ans_x));
    memset(ans_y, 0, sizeof(ans_y));
    flag1 = 0;
    cnt = 0;
    int sx = game->snake->head->row, sy = game->snake->head->col;
    int flag = 0;
    for (int i = 0; i < game->board->rows; i++)
        for (int j  = 0; j < game->board->cols; j++) {
    	    if(game->board->cells[i * game->board->cols + j] == CELL_FOOD)
                flag = 1;
                break;
        }
    if (flag == 0) {
        while (1) {
            int rdd = rand() % 4;
            if (sx + dx[rdd] >= 0 && sx + dx[rdd] < game->board->rows
               && sy + dy[rdd] >= 0 && sy + dy[rdd] < game->board->cols
               && (game->board->cells[(sx + dx[rdd]) * game->board->cols + sy + dy[rdd]] == CELL_OPEN
               || game->board->cells[(sx + dx[rdd]) * game->board->cols + sy + dy[rdd]] == CELL_FOOD)) 
                return dr[rdd];   
   	    }
    }   
    int vis[100][100] = { 0 };
    vis[sx][sy] = 1;
    int path_x[300] = { sx }, path_y[300] = { sy };
    dfs(sx, sy, path_x, path_y, 1, vis, game->board, 0);
    if (ans_x[1] == sx && ans_y[1] == sy - 1)
        return WEST;
    if (ans_x[1] == sx && ans_y[1] == sy + 1)
        return EAST;
    if (ans_x[1] == sx - 1 && ans_y[1] == sy)
        return NORTH;
    if (ans_x[1] == sx + 1 && ans_y[1] == sy) 
        return SOUTH;
}