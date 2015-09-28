#include <SFML/Graphics.hpp>
//#include <SFML/Time.hpp>
//#include <SFML/Clock.hpp>
#include "game.hpp"
#include <stdio.h>
#include <cassert>
#define IMG_TERRAIN "img/maptiles30part1va1nl5.png" 
#define IMG_SPRITES "img/47384.png" 
#define N_SPRITES 5
#define RED 0
#define BLUE 1
#define GREEN 2
#define YELLOW 3
#define WATER 0
#define GRASS 1
#define MONTAIN 2
#define FOREST 3
#define HERO 4
#define TILE_W 16 
#define TILE_H 16
#define MAP_W 15
#define MAP_H 15
game_data game;
sf::RenderTexture canvas;
sf::Image img_terrain;
sf::Image img_sprites;
sf::Texture* textures;

void init_data()
{
	game.new_map(MAP_W,MAP_H);
    sf::Color sprite_mask = sf::Color(128,160,128);
    sf::Vector2f sprite_coord[] = {
                                sf::Vector2f(195,181), 
                                sf::Vector2f(195,212), 
                                sf::Vector2f(195,244)
                              };
    sf::Vector2f tex_coord[] = {
                                sf::Vector2f(1,120),
                                sf::Vector2f(1,  1),
                                sf::Vector2f(1, 69),
                                sf::Vector2f(1,103)
                              };
    unsigned int idle_cycle[] = {0,1,2};
	for(int i = 0; i < game.map_h*game.map_w; i++) game.map[i] = i % 4;
    game.tilemap.load(IMG_TERRAIN, tex_coord, 4, sf::Vector2u(TILE_W,TILE_H), game.map, MAP_W, MAP_H);
    game.hero_sprite.load(IMG_SPRITES,sprite_coord, 3, sf::Vector2u(TILE_W,TILE_H), sprite_mask);
    game.hero_sprite.set_idle(idle_cycle, 3);
	
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(MAP_W * TILE_W, MAP_H * TILE_H), "FEEQU");
	window.setFramerateLimit(60); 
	sf::Sprite sprite_canvas;
	sf::Clock clock;
	init_data();
	bool force_refresh=true;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::A:
							game.hero_x = game.hero_x == 0 ? game.map_w-1 : game.hero_x-1;
							break;
						case sf::Keyboard::D:
							game.hero_x = (game.hero_x+1)%game.map_w;
							break;
						case sf::Keyboard::W:
							game.hero_y = game.hero_y == 0 ? game.map_h-1 : game.hero_y-1;
							break;
						case sf::Keyboard::S:
							game.hero_y=(game.hero_y+1)%game.map_h;
							break;
						default:
						break;
					}	

			}	

		}
		if(clock.getElapsedTime().asSeconds() > 0.2
		   || force_refresh) // ~50fps
		{
            game.move_hero();
            game.hero_sprite.refresh();
			force_refresh=false;
			clock.restart();
	
		}
		window.clear();
		window.draw(game.tilemap);
        window.draw(game.hero_sprite);
		window.display();

	}

    return 0;
}
