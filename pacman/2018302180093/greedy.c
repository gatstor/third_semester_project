#include "util.h"
#include <stdio.h>
#include <string.h>

#define INF 1e9
#define M 1000

int pre[M][M], dis[M][M], used[M][M];
int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};
char dir[] = {NORTH, WEST, EAST, SOUTH};

typedef struct{
    int qx[M*20];
    int qy[M*20];
    int rear;
    int front;
}QUEUE;
void bfs(game_state_t *state, int sx, int sy) {
  char dir[] = {NORTH, WEST, EAST, SOUTH};
  memset(dis, -1, sizeof(dis));
  dis[sx][sy] = 1;//distance start
  pre[sx][sy] = -1;//
  QUEUE qu;
  qu.rear = qu.front = 0;
  qu.qx[qu.rear] = sx,qu.qy[qu.rear] = sy, qu.rear++;
  while (qu.front < qu.rear) {
    int x = qu.qx[qu.front], y = qu.qy[qu.front];
    qu.front++;//队尾出队
    int i, tx, ty;
    for (i = 0; i < 4; i++) {
      tx = x + dx[i];
      ty = y + dy[i];
      if (tx >= 0 && tx < state->n && ty >= 0 && ty < state->m &&
          !state->grid[tx][ty]) {//在图内并且没有访问过
        if (dis[tx][ty] == -1) {
          dis[tx][ty] = dis[x][y] + 1;//现在的位置比上一个位置多1
          pre[tx][ty] = i;//标志方向
          qu.qx[qu.rear] = tx, qu.qy[qu.rear] = ty, qu.rear++;//当前位置入队
        }
      }
    }
  }
}

int main() {
  game_state_t state;
  memset(&state, 0, sizeof(state));
  init(&state);
  // write your code here

  int path[M * 10], top = 0, i, j;

  int nx = state.start_x, ny = state.start_y;
  while (1) {
    bfs(&state, nx, ny);
    int mx = INF, zx = 0, zy = 0;
    for (i = 0; i < state.n; i++) {
      for (j = 0; j < state.m; j++) {
        if (state.food[i][j] && dis[i][j] < mx) {
          mx = dis[i][j], zx = i, zy = j;
        }
      }
    }
    if (mx == INF)
      break;
    state.food[zx][zy] = 0;
    int x = zx, y = zy;
    top = 0;
    while (x != nx || y != ny) {
      int d = pre[x][y];
      path[top++] = d;
      x -= dx[d], y -= dy[d];
    }
    while (--top >= 0) {
      printf("%c", dir[path[top]]);
    }
    nx = zx, ny = zy;
  }
  //
  destroy(&state);
  return 0;
}

