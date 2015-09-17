#include <stdlib.h>
#include "game.hpp"


game_data::game_data()
{
	map_h=0;
	map_w=0;
	map= 0;	
	hero_x=0;
	hero_y=0;
}

game_data::~game_data()
{
	if(map)delete map;
}

void game_data::new_map(int h, int w)
{
	if(map)delete map;
	map_h = h;
	map_w = w;
	map = (int*)malloc(h*w*sizeof(int));
	
}
