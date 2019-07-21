#include<stdio.h>

#include<malloc.h>

#include<stdlib.h>

#include<assert.h>

#include"file.h"

#include"game.h"

#include <math.h>

void test_create_game(){

        game_t *game=create_game("simple.txt");

        assert(game->board!=NULL);

        assert(game->snake!=NULL);
		
		assert(game!=NULL);

        assert(game->board->rows == 30 );

        assert(fabs(game->time_step - 0.2)<=1e-6 );

        assert(fabs(game->food_probability - 0.1) <= 1e-6 );

        assert(game->growth_per_food == 8);

        assert(game->board->cells[1*game->board->cols+19] == CELL_SNAKE);

        assert(game->board->cells[3*game->board->cols+0] == CELL_WALL);

        assert(game->board->cells[29*game->board->cols+39] == CELL_WALL);

        assert(game->board->cells[2*game->board->cols+12] == CELL_OPEN);

        assert(game->board->cells[28*game->board->cols+38] == CELL_OPEN);
        
        destroy_game(game);

}

int main()
{
    test_create_game();
    return 0;
}
