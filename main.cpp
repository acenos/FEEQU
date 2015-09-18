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

game_data game;
sf::RenderTexture canvas;
sf::Image img_terrain;
sf::Image img_sprites;
sf::Texture* textures;

void init_data()
{
	game.new_map(9,9);
	
	for(int i = 0; i < game.map_h*game.map_w; i++) game.map[i] = i % 4;
	
	// Loading terrain sprites
	assert(img_terrain.loadFromFile(IMG_TERRAIN));
	textures = new sf::Texture[N_SPRITES];
	textures[WATER].loadFromImage(img_terrain,sf::IntRect(1,120,TILE_W,TILE_H));
	textures[GRASS].loadFromImage(img_terrain,sf::IntRect(1,1,TILE_W,TILE_H));
	textures[MONTAIN].loadFromImage(img_terrain,sf::IntRect(1,69,TILE_W,TILE_H));
	textures[FOREST].loadFromImage(img_terrain,sf::IntRect(1,103,TILE_W,TILE_H));

	// Loading character sprites
	assert(img_sprites.loadFromFile(IMG_SPRITES));
	img_sprites.createMaskFromColor(sf::Color(128,160,128));
	textures[HERO].loadFromImage(img_sprites,sf::IntRect(195,244,TILE_W,TILE_H));
	
}

void draw_game()
{
	canvas.create(300,300);
	sf::RectangleShape tile(sf::Vector2f(TILE_W,TILE_H));
	canvas.clear();
	// Print scenario
	for(int i = 0; i < game.map_h; i++)
		for(int j = 0; j < game.map_w; j++)
		{
			switch(game.map[i*game.map_h+j])
			{
				case RED:
					tile.setTexture(&textures[WATER]);
					break;
				case BLUE:
					tile.setTexture(&textures[FOREST]);
					break;
				case GREEN:
					tile.setTexture(&textures[MONTAIN]);
					break;
				case YELLOW:
					tile.setTexture(&textures[GRASS]);
					break;
				default:
					tile.setFillColor(sf::Color::Magenta);

			}
			tile.setPosition(j*TILE_W,i*TILE_H);
			canvas.draw(tile);
		}
	// Print Hero
	tile.setTexture(&textures[HERO]);
	tile.setPosition(game.hero_x*TILE_W,game.hero_y*TILE_H);
	canvas.draw(tile);
	canvas.display();
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!");
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
					force_refresh=true;
					switch (event.key.code)
					{
						case sf::Keyboard::A:
							game.hero_x--;
							if(game.hero_x < 0) game.hero_x = game.map_w-1;
							break;
						case sf::Keyboard::D:
							game.hero_x=(game.hero_x+1)%game.map_w;
							break;
						case sf::Keyboard::W:
							game.hero_y--;
							if(game.hero_y < 0) game.hero_y = game.map_h-1;
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
			force_refresh=false;
			clock.restart();
			draw_game();
			sprite_canvas.setTexture(canvas.getTexture());
	
		}
		window.clear();
		window.draw(sprite_canvas);
		window.display();
	}

    return 0;
}
