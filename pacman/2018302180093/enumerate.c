#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define M 2000
#define MAXV 20000
#define INF 32767

int ans[M], res = 0x3f3f3f3f;
int cnt = 0,vis[M];
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

//所有权重全部赋值为1.0
int* Dijkstra(AdjGraph *G, int u, int uv) {
    int tmp[MAXV];
    int *temp;
    temp = (int*)malloc(sizeof(int)*MAXV);
    for (int i = 0; i < MAXV; i++)
    {
        temp[i] = -2;
    }
    ArcNode *p = (ArcNode*)malloc(sizeof(ArcNode));
    int dist[MAXV], path[MAXV];
    int S[MAXV];
    int MINdis, i, j, v;
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

int distance(int *path) {
    int sum = 0;
    for (int i = 0; path[i] != -2; i++) {
        sum++;
    }
    return sum;
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
int head_length[M];
int length[M][M];
void dfs(game_state_t *s,AdjGraph*G, int now, int path[], int food[]) {

    if (now == cnt) {
        int temp = path[0];//转编号
        int sum = head_length[food[temp]];
        int i,a,b;
        for (i = 1; i < cnt; i++) {
            a = path[i]; b = path[i - 1];
            sum += length[food[b]][food[a]];
            //BFS计算每两点之间的最短路 
        }
        if (sum < res) {
            res = sum;
            for (i = 0; i < cnt; i++) {
                ans[i] = path[i];
            }
        }
        return;
    }
    int i;
    for (i = 0; i < cnt; i++) {
        if (vis[i] == 0) {
            vis[i] = 1;
            path[now] = i;//第i个食物点 
            dfs(s,G, now + 1, path, food);
            vis[i] = 0;
        }
    }
}


void printDir(int *path, int m) {
    char dir[MAXV];
    int i = 0;
    for (i = 0; path[i+1] != -2; i++) {
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

int main() {
    game_state_t state;
    memset(&state, 0, sizeof(state));
    init(&state);
    // write your code here
    AdjGraph *G;
    G = (AdjGraph *)malloc(sizeof(AdjGraph));
    Create_list(state, &G);
    int path[M];
    for (int i = 0; i < M; i++) {
        path[i] = ans[i] = -2;
    }//初始化
    int now = 0;
    int food[M];
    for (int i = 0; i < state.n; i++) {
        for (int j = 0; j < state.m; j++) {
            if (state.food[i][j] == 1) {
                food[cnt++] = i * state.m + j;
            }
        }
    }//遍历一遍，计算豆子的个数和位置,位置保存在food[]中，个数保存在cnt中
    int start = state.start_x*state.m + state.start_y;
    int sx, sy;
    int *temp;
    for (int i = 0; i < cnt; i++) {
        for (int j = i; j < cnt; j++) {
            if (i == j)
                continue;
            sx = food[i];
            sy = food[j];
            temp = Dijkstra(G, sx, sy);
            length[sx][sy] = distance(temp);
        }
    }
    
    for (int i = 0; i < cnt; i++) {
        sx = food[i];
        temp = Dijkstra(G, start, sx);
        head_length[sx] = distance(temp);
    }

    dfs(&state,G,now,path,food);
    //最终传出
    //最后传入print一个int数组，内容为路径的编号
    int a = ans[0],b;
    temp = Dijkstra(G, start, food[a]);
    printDir(temp, state.m);
    for (int i = 0; i < cnt - 1; i++) {
        a = ans[i];
        b = ans[i + 1];
        temp = Dijkstra(G, food[a], food[b]);
        printDir(temp, state.m);
    }
    //printDir(ans_1,state.m);
    // 
    destroy(&state);
    return 0;
}
