#ifndef YYZ_H
#define YYZ_H
#include "game.h"
#define MAXV 3000
#define MAX 3000
#define INF 30000

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

typedef struct {
	int x;
	int time;
	int pre;
}node_hao;//time为消失时间，pre为前面一个方位的编号


int cul_length(int * path);
int *Dijkstra(AdjGraph *G, int u, int uv);
void Create_list(game_t* game, AdjGraph **G);
void destroy_list(AdjGraph*G);
void DispAdj(AdjGraph*G);
int* BFS(game_t *game, int start/*, int a[]*/);
#endif
