#include "game.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "file.h"
void test_create_board() {
    board_t* board = create_board(5, 5);
    assert(board != NULL);
    assert(board_cell(board, 0, 0) != NULL);
    cell_t* cell = board_cell(board, 3, 2);
    assert(cell != NULL && *cell == CELL_OPEN);
    assert(board_cell(board, -1, 0) == NULL);
    assert(board_cell(board, 0, 5) == NULL);
    assert(board_cell(board, 5, 5) == NULL);
    assert(board_cell(board, 4, 4) != NULL);
    destroy_board(board);
}

void test_create_snake(){
	board_t *board = create_board(5,5);
	assert(board != NULL);
    snake_t *snake = create_snake(board,2,3,EAST);
    assert(snake != NULL);	
    cell_t* cell = board_cell(board, 2, 3);
    assert(cell != NULL && *cell == CELL_SNAKE);
    cell_t* cell2 = board_cell(board,1,1);
	assert(*cell2 == CELL_OPEN);
	destroy_board(board);
    destroy_snake(snake);

}
void test_board_cell() {
	board_t* board = create_board(5, 5);
	assert(board != NULL);
	assert(board_cell(board, 5, 5) == NULL);
	assert(board_cell(board, 0, 5) == NULL);
	assert(board_cell(board, 5, 0) == NULL);
	assert(board_cell(board, -1, 5) == NULL);
	assert(board_cell(board, 5, -1) == NULL);
	assert(board_cell(board, 4, 4) != NULL);
	destroy_board(board);
}

void test_add_food()
{
    srand(time(NULL));
    float proability = rand() % 100000;
    proability = proability / 100000;
    proability = 1;//置1测试
    board_t* board = create_board(5, 5);

    //前面是输入的变量，后面是真正的测试
    //概率小于等于1
    assert(proability <= 1);
    assert(board != NULL);
    int open[board->cols * board->rows + 5], cnt = 0;
    for (int i = 0; i < board->cols * board->rows; i++)
    {
        if (board->cells[i] == CELL_OPEN)
            open[cnt++] = i;
    }
    randomly_add_food(board, proability);
    int flag = 0, flagx = 0;
    for (int i = 0; i < cnt; i++)
    {
        if (board->cells[open[i]] == CELL_OPEN)
            flag++;
        else if (board->cells[open[i]] == CELL_FOOD)
            flagx++;
    }
    assert(flag == cnt - 1 && flagx == 1);
    destroy_board(board);
}
void test_set_direction(){
	board_t *board = create_board(5,5);
	assert(board!=NULL);
	snake_t *snake = create_snake(board,2,3,EAST);
	assert(board!=NULL);
	assert(snake->heading == EAST);
	set_direction(snake,SOUTH);
	assert(snake->heading != EAST);
	assert(snake->heading == SOUTH);
//	assert(	set_direction(snake,NORTH));
	destroy_board(board);
	destroy_snake(snake);
}

void test_update_shead(){
	board_t *board=create_board(20,20);
	snake_t *snake=create_snake(board,2,3,SOUTH);

	assert(snake->head->row==2);
	assert(snake->head->col==3);
	update_snake_head(snake,board,4);
	assert(snake->head->row==3);
    assert( snake->head->col ==3);
	board->cells[83]=CELL_FOOD;
	update_snake_head(snake,board,4);

	assert(snake->growth==4);
    destroy_board(board);
	destroy_snake(snake);


}





void test_update_snake_head()
{
	board_t* board = create_board(5, 5);
	assert(board != NULL);
 	snake_t* snake;
	snake=create_snake(board, 1, 2, SOUTH);
	assert(snake!=NULL);
	update_snake_head(snake, board, 4);
	assert(snake->head->row == 2 && snake->head->col== 2);
	assert(snake->tail->row == 1 && snake->tail->col== 2);
	assert(snake->growth==0);
	board->cells[3*5+2]=CELL_FOOD;
	update_snake_head(snake, board, 4);
	assert(snake->head->row == 3 && snake->head->col== 2);
	assert(snake->tail->row == 1 && snake->tail->col== 2);
	assert(snake->growth==4);
	destroy_board(board);
	destroy_snake(snake);
}

void test_update_snake_tail()
{
	board_t* board = create_board(5, 5);
	assert(board != NULL);
	snake_t* snake;
	snake=create_snake(board, 1, 2, SOUTH);
	assert(snake!=NULL);
	update_snake_head(snake, board, 4);
	assert(snake->head->row == 2 && snake->head->col== 2);
	assert(snake->growth == 0);
	update_snake_tail(snake, board);
	board->cells[3*5+2] = CELL_FOOD;
	update_snake_head(snake, board, 4);
	assert(snake->growth == 4);
	update_snake_tail(snake, board);
	assert(snake->tail->row == 2 && snake->tail->col== 2);
	assert(snake->growth == 3);
	destroy_board(board);
	destroy_snake(snake);
}

void test_next_frame()
{
	board_t* board = create_board(5, 5);
	assert(board != NULL);
	snake_t* snake;
	snake=create_snake(board, 1, 2, SOUTH);
	assert(snake!=NULL);
	game_t *cur_game;
	cur_game=(game_t*)malloc(sizeof(game_t));
	cur_game->board = board;
	cur_game->snake = snake;
	cur_game->food_probability = 1;
	cur_game->growth_per_food = 3;
	assert(snake->tail->row == 1 && snake->tail->col == 2);
	assert(snake->head->row == 1 && snake->head->col == 2);
	assert(next_frame(cur_game) == 0);
	assert(snake->head->row == 2 && snake->head->col == 2);
	assert(snake->tail->row == 2 && snake->tail->col == 2);
	cur_game->board->cells[3*5+2] = CELL_WALL;
	assert(next_frame(cur_game) == 1);
	destroy_game(cur_game);
}


int main(){
	test_create_snake();
	test_create_board();
	test_board_cell();
	test_add_food();
	test_set_direction();
	test_update_shead();
    test_update_snake_head();
    test_update_snake_tail();
    test_next_frame();
	return 0;
}


