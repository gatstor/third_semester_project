#include "ai1.h"

typedef struct node {
	int x, y;//坐标(x,y)
	int fa;//前一结点位置
}node;

direction_t get_action(game_t* game) {
	int visit[100][100] = { 0 };//标记是否访问过
	node tmp;
	tmp.x = game->snake->head->row;//蛇头的位置
	tmp.y = game->snake->head->col;
	tmp.fa = -1;
	visit[tmp.x][tmp.y] = 1;
	node queue[3000];//队列初始化
	int rear, front;
	rear = front = -1;
	rear++;//蛇头进栈
	queue[rear] = tmp;
	while (rear != front) {
		front++;//出栈
		tmp = queue[front];
		if (game->board->cells[tmp.x*game->board->cols + tmp.y] == CELL_FOOD) {
			node pre;
			while (tmp.fa != -1) {
				pre = tmp;
				tmp = queue[tmp.fa];
			}
			if (pre.x - game->snake->head->row == 1) {
				return SOUTH;
			}
			if (pre.x - game->snake->head->row == -1) {
				return NORTH;
			}
			if (pre.y - game->snake->head->col == 1) {
				return EAST;
			}
			if (pre.y - game->snake->head->col == -1) {
				return WEST;
			}
		}
		for (int d = 0; d < 4; d++) {
			node now = tmp;
			switch (d) {
			case 0:
				now.y++;
				now.fa = front;
				break;
			case 1:
				now.x ++;
				now.fa = front;
				break;
			case 2:
				now.y--;
				now.fa = front;
				break;
			case 3:
				now.x --;
				now.fa = front;
				break;
			}
			if (now.x < game->board->rows&&now.y < game->board->cols&&now.x >= 0 && now.y >= 0) {
				if (visit[now.x][now.y] == 0 &&
					(game->board->cells[now.x*game->board->cols + now.y] == CELL_FOOD ||
						game->board->cells[now.x*game->board->cols + now.y] == CELL_OPEN)) {
					visit[now.x][now.y] = 1;
					rear++;
					queue[rear] = now;
				}
			}
		}
	}
	tmp.x = game->snake->head->row;//蛇头的位置
	tmp.y = game->snake->head->col;
	for (int d = 0; d < 4; d++) {
		switch (d) {
		case 0:
			tmp.y++;
			break;
		case 1:
			tmp.x += game->board->cols;
			break;
		case 2:
			tmp.y--;
			break;
		case 3:
			tmp.x -= game->board->cols;
			break;
		}
		if (tmp.x < game->board->rows&&tmp.y < game->board->cols&&tmp.x >= 0 && tmp.y >= 0) {
			if (game->board->cells[tmp.x*game->board->cols + tmp.y] == CELL_OPEN) {
				switch (d) {
				case 0:
					return EAST;
					break;
				case 1:  
					return SOUTH;
					break;
				case 2:
					return WEST;
					break;
				case 3:
					return NORTH;
					break;
				}
			}
		}
	}
}

