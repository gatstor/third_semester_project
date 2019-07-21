#include <stdio.h>
#include <assert.h>
#include "ai1.h"
#include "file.h"

void test_ai(){
	game_t *game = create_game("simple.txt");
	direction_t d = get_action(game);
	assert(d==NORTH||d==EAST||d==SOUTH||d==WEST);
	destroy_game(game);

}

int main(){
	test_ai();
	return 0;
}
