#include "util.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1024

void init(game_state_t *s) {
	char buf[MAX_LENGTH];
	int i, j;

	scanf("%d%d", &s->n, &s->m);
	s->grid = malloc(sizeof(int *) * s->n);
	for (i = 0; i < s->n; i++) {
		s->grid[i] = malloc(sizeof(int) * s->m);
		scanf("%s", buf);
		for (j = 0; j < s->m; j++) {
			s->grid[i][j] = buf[j] == 'T';
		}
	}
	scanf("%d%d", &s->start_x, &s->start_y);
	scanf("%d%d", &s->goal_x, &s->goal_y);

	s->cost = malloc(sizeof(double *) * s->n);
	for (i = 0; i < s->n; i++) {
		s->cost[i] = malloc(sizeof(double) * s->m);
		for (j = 0; j < s->m; j++) {
			scanf("%lf", &s->cost[i][j]);
		}
	}
}

void destroy(game_state_t *s) {
	int i;
	for (i = 0; i < s->n; i++) {
		free(s->grid[i]);
		free(s->cost[i]);
	}
	free(s->grid);
	free(s->cost);
}