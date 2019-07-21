#include "ai.h"
#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "file.h"
#include "yyz.h"
direction_t get_action(game_t* game) {
	int *path;
	int start;
	start=game->snake->head->row*game->board->cols+game->snake->head->col;
	path=BFS(game, start);
	if(path[1]==-2)
	{

		free(path);
		return game->snake->heading;
	}
    int m=game->board->cols;
     if(path[1]-path[0]==1)
	 {
         free(path);
         if(game->snake->heading==WEST)
             return NORTH;
		 
		return EAST;
	 }
	 else if(path[1]==path[0]-1)
	 {
        
		  free(path);
 if(game->snake->heading==EAST)
             return SOUTH;

		return WEST;		
	}
	 else if(path[1]==path[0]+m)
	 {
		  free(path);
 if(game->snake->heading==NORTH)
             return EAST;
 		return SOUTH;    
 	 }
	 else if(path[1]==path[0]-m)
	 {
		  free(path);
 if(game->snake->heading==SOUTH)
             return WEST;
        return NORTH;
     }
}
