#include "util.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include<stdlib.h>
#define INF 1e8
#define M 1000
#define MAXV 2000
int pre[M][M], dis_1[M][M], used[M][M];
int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, -1, 1, 0 };
char dir[] = { NORTH, WEST, EAST, SOUTH };
typedef struct ANode {
    int adjvex;
    struct ANode *nextarc;
    int weight;
}ArcNode;

typedef struct Vnode {
    int info;
    ArcNode *firstarc;
}VNode;

typedef struct {
    VNode adjlist[MAXV];
    int n, e;
}AdjGraph;

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
                    p->weight = 1.0;
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
                    p->weight = 1.0;
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
                    p->weight = 1.0;
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
                    p->weight = 1.0;
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
//所有权重全部赋值为1.0
int Dijkstra(AdjGraph *G, int u, int uv) {
    int tmp[MAXV];
    int *temp;
    temp = (int*)malloc(sizeof(int)*MAXV);
    for (int i = 0; i < MAXV; i++)
    {
        temp[i] = -2;
    }
    ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
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
    if (k < 1)
        return -1;
    return k;
}

int *Dijkstra_1(AdjGraph *G, int u, int uv) {
    int tmp[MAXV];
    int *temp;
    temp = (int*)malloc(sizeof(int)*MAXV);
    for (int i = 0; i < MAXV; i++)
    {
        temp[i] = -2;
    }
    ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
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
    if (k < 1)
        return NULL;
    return temp;
}

void printDir(int *path, int m) {
    char dir[MAXV];
    int i = 0;
    for (i = 0; path[i + 1] != -2; i++) {
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

typedef struct {
    int qx[M * 20];
    int qy[M * 20];
    int rear;
    int front;
}QUEUE;

void bfs(game_state_t *state, int sx, int sy) {
    char dir[] = { NORTH, WEST, EAST, SOUTH };
    memset(dis_1, -1, sizeof(dis_1));
    dis_1[sx][sy] = 1;//distance start
    pre[sx][sy] = -1;//
    QUEUE qu;
    qu.rear = qu.front = 0;
    qu.qx[qu.rear] = sx, qu.qy[qu.rear] = sy, qu.rear++;
    while (qu.front < qu.rear) {
        int x = qu.qx[qu.front], y = qu.qy[qu.front];
        qu.front++;//队尾出队
        int i, tx, ty;
        for (i = 0; i < 4; i++) {
            tx = x + dx[i];
            ty = y + dy[i];
            if (tx >= 0 && tx < state->n && ty >= 0 && ty < state->m &&
                !state->grid[tx][ty]) {//在图内并且没有访问过
                if (dis_1[tx][ty] == -1) {
                    dis_1[tx][ty] = dis_1[x][y] + 1;//现在的位置比上一个位置多1
                    pre[tx][ty] = i;//标志方向
                    qu.qx[qu.rear] = tx, qu.qy[qu.rear] = ty, qu.rear++;//当前位置入队
                }
            }
        }
    }
}

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int min(int a, int b) {
    return (a > b) ? b : a;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

double p(int s, int sNew, double t) {
    double res =  exp((s - sNew) / t);
    return res;
}
int main() {
    game_state_t state;
    memset(&state, 0, sizeof(state));
    init(&state);
    // write your code here
    AdjGraph *G;
    G = (AdjGraph *)malloc(sizeof(AdjGraph));
    Create_list(state, &G);
    int food[M], cnt = 0;
    int path[M];
    for (int i = 0; i < state.n; i++) {
        for (int j = 0; j < state.m; j++) {
            if (state.food[i][j] == 1) {
                food[cnt++] = i * state.m + j;
            }//遍历一遍，计算豆子的个数和位置,位置保存在path[]中，个数保存在cnt中
        }
    }
    static int dis[M][M];
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt; j++) {
            if (i >= j) {
                dis[i][j] = 0;
                continue;
            }
            dis[j][i] = dis[i][j] = Dijkstra(G, food[i], food[j]);//计算每两点之间的最短距离
        }
    }

    /////////////////////////greedy算法找较优路///////////////////////////
    int min_ans = 99999;
    int nx = state.start_x, ny = state.start_y;
    int i, j, top = 0, w = 0;
    static int path_1[M];
    for (i = 0; i < cnt; i++) {
        path_1[i] = -2;
    }
    while (1) {
        bfs(&state, nx, ny);
        int zx = 0, zy = 0;
        int mx = INF;
        for (i = 0; i < state.n; i++) {
            for (j = 0; j < state.m; j++) {
                if (state.food[i][j] && dis_1[i][j] < mx) {
                    mx = dis_1[i][j], zx = i, zy = j;
                }
            }
        }
        
        if (mx == INF)
            break;
        state.food[zx][zy] = 0;
        path[w++] = zx * state.m + zy;
        int x = zx, y = zy;
        top = 0;
        while (x != nx || y != ny) {
            int d = pre[x][y];
            path_1[top++] = d;
            x -= dx[d], y -= dy[d];
        }
        top = -1;
        nx = zx, ny = zy;
    }


    /////////////////
    srand(time(NULL));
    int t = 0;
    int max_t = 1000;
    while (t < max_t) {
        int x = rand() % cnt; //豆子个数 起点也是豆子
        int y = rand() % cnt;
        //swap(&path[x], &path[y]); // 路径
        int i = min(x, y);
        int j = max(x, y);
        int a = i;
        int b = j;
        for (int k = 0; k < (b - a) / 2; i++, j--, k++) {
            swap(&path[i], &path[j]);
        }
        int sum = 0;
        for (int i = cnt; i > 0; i--) {
            sum += dis[path[i]][path[i - 1]];
        }
        if (t == 0)
            min_ans = sum;
        double random;
        random = rand() % 10000000;
        random = random / 10000000;
	    double T = max_t/(double)(t+1);
        if(p(min_ans,sum,T)>=random){
       // if (sum < min_ans) {
            min_ans = sum;
            t = 0;
        }
        else {
            //swap(&path[x], &path[y]);
            for (int k = 0; k < (b - a) / 2; i++, j--, k++) {
                swap(&path[i], &path[j]);
            }
        }
        t++;
    }

    int start = state.start_x*state.m + state.start_y;
    int *temp = Dijkstra_1(G, start, path[0]);
    printDir(temp, state.m);
    for (int i = 1; i < cnt; i++) {
        temp = Dijkstra_1(G, path[i - 1], path[i]);
        printDir(temp, state.m);
    }
    //
    destroy(&state);
    return 0;
}

