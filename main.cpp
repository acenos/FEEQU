#include <SFML/Graphics.hpp>
#include "game.hpp"
#include <stdio.h>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define IMG_TERRAIN "img/maptiles30part1va1nl5.png" 
#define IMG_SPRITES "img/47384.png" 
#define MAP_FILE "map.txt"
#define N_SPRITES 5
#define RED 0
#define BLUE 1
#define GREEN 2
#define YELLOW 3
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
    string line, full_text;
    ifstream map_file(MAP_FILE);
    if(map_file.is_open())
    {   
        while(getline(map_file,line))full_text.append(line);
        int i,j;
        int w,h;
        i = full_text.find_first_of(",");
        w = atoi(full_text.substr(0,i).c_str());
        j=i+1;
        i = full_text.find_first_of(",",j);
        h = atoi(full_text.substr(j,i).c_str());
        game.new_map(w,h);
        j=i+1;
        i = full_text.find_first_of(",",j);
        game.hero_x = atoi(full_text.substr(j,i).c_str());
        j=i+1;
        i = full_text.find_first_of(",",j);
        game.hero_y = atoi(full_text.substr(j,i).c_str());
        j=i+1;
        i = full_text.find_first_of(",",j);
        for(int k = 0; k < w*h && i < full_text.npos; k++)
        {
            game.map[k]=atoi(full_text.substr(j,i).c_str());
            j=i+1;
            i = full_text.find_first_of(",",j);
        }
        printf("%i,%i\n",game.hero_x,game.hero_y);
    }
    else
    {
        printf("Error opening map file/nUsing default map");
	    game.new_map(MAP_W,MAP_H);
	    for(int i = 0; i < game.map_h*game.map_w; i++) game.map[i] = i % 4;
    }
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
    game.tilemap.load(IMG_TERRAIN, tex_coord, 4, sf::Vector2u(TILE_W,TILE_H), game.map, game.map_w, game.map_h);
    game.hero_sprite.load(IMG_SPRITES,sprite_coord, 3, sf::Vector2u(TILE_W,TILE_H), sprite_mask);
    game.hero_sprite.move(game.hero_x,game.hero_y);
    game.hero_sprite.set_idle(idle_cycle, 3);
	
}

int main()
{
	init_data();
	sf::RenderWindow window(sf::VideoMode(game.map_w * TILE_W, game.map_h * TILE_H), "FEEQU");
	window.setFramerateLimit(60); 
	sf::Sprite sprite_canvas;
	sf::Clock clock;
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
							game.move_hero(G_LEFT);
							break;
						case sf::Keyboard::D:
							game.move_hero(G_RIGHT);
							break;
						case sf::Keyboard::W:
							game.move_hero(G_UP);
							break;
						case sf::Keyboard::S:
							game.move_hero(G_DOWN);
							break;
						default:
						break;
					}	

			}	

		}
		if(clock.getElapsedTime().asSeconds() > 0.2
		   || force_refresh) // ~50fps
		{
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
