#include"game.h"
#include"file.h"
#include<stdio.h>
#include<stdlib.h>


game_t * create_game(const char * file_name)
{
	FILE *f;
	if ((f = fopen(file_name, "r")) == NULL) {
		printf("UNABLE TO OPEN FILE");
		return NULL;
	}
	game_t *my_game;
    
	if ((my_game = (game_t*)malloc(sizeof(game_t))) == NULL)
	{
		printf("Insufficient memory for game");
		return NULL;
	}
	int rows = -1;
	int cols = -1;
	fscanf(f,"%d %d %f %f %d\n", &rows, &cols, &my_game->time_step, &my_game->food_probability, &my_game->growth_per_food);	
	my_game->board = create_board(rows, cols);
	char c = fgetc(f);
	int row = 0;
	int col = 0;
	while (c != EOF)
	{
		switch (c)
		{

		case 'X':
			*board_cell(my_game->board, row, col) = CELL_WALL;
			break;
		case '-':
			*board_cell(my_game->board, row, col) = CELL_OPEN;
			break;
		case 'N':
			my_game->snake = create_snake(my_game->board, row, col, NORTH);
			break;
		case 'S':
			my_game->snake = create_snake(my_game->board, row, col, SOUTH);
			break;
		case 'E':
			my_game->snake = create_snake(my_game->board, row, col, EAST);
			break;
		case 'W':
			my_game->snake = create_snake(my_game->board, row, col, WEST);
			break;
		}
		if (c != '\n')
		{
			col++;
			if (col >= cols) 
			{
				col = 0;
				row++;
				if (row >= rows)
				{
					break;
				}
			}
		}
		c = fgetc(f);
	}
	fclose(f);
	return my_game;
}

void destroy_game(game_t * cur_game)
{
	destroy_snake(cur_game->snake);
	destroy_board(cur_game->board);
	free(cur_game);
}
