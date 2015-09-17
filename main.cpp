#include <SFML/Graphics.hpp>
#include "game.hpp"
#include <stdio.h>
#include <cassert>
#define IMG_ADDR "img/maptiles30part1va1nl5.png" 
#define N_SPRITES 4
#define RED 0
#define BLUE 1
#define GREEN 2
#define YELLOW 3
#define WATER 0
#define GRASS 1
#define MONTAIN 2
#define FOREST 3
#define TILE_W 18 
#define TILE_H 18

game_data game;
sf::RenderTexture canvas;
sf::Image main_img;
sf::Texture* textures;

void init_data()
{
	game.new_map(9,9);
	
	for(int i = 0; i < game.map_h*game.map_w; i++) game.map[i] = i % 4;

	assert(main_img.loadFromFile(IMG_ADDR));
	textures = new sf::Texture[N_SPRITES];
	textures[WATER].loadFromImage(main_img,sf::IntRect(0,119,18,18));
	textures[GRASS].loadFromImage(main_img,sf::IntRect(0,0,18,18));
	textures[MONTAIN].loadFromImage(main_img,sf::IntRect(0,68,18,18));
	textures[FOREST].loadFromImage(main_img,sf::IntRect(0,102,18,18));
	
}

void draw_game()
{
	canvas.create(300,300);
	sf::RectangleShape tile(sf::Vector2f(TILE_H,TILE_W));
	tile.setOutlineThickness(1);
	tile.setOutlineColor(sf::Color::Black);
	canvas.clear();
	for(int i = 0; i < game.map_h; i++)
		for(int j = 0; j < game.map_w; j++)
		{
			switch(game.map[i*game.map_h+j])
			{
				case RED:
					//tile.setFillColor(sf::Color::Red);
					tile.setTexture(&textures[WATER]);
					break;
				case BLUE:
					//tile.setFillColor(sf::Color::Blue);
					tile.setTexture(&textures[FOREST]);
					break;
				case GREEN:
					//tile.setFillColor(sf::Color::Green);
					tile.setTexture(&textures[MONTAIN]);
					break;
				case YELLOW:
					tile.setTexture(&textures[GRASS]);
					//tile.setFillColor(sf::Color::Yellow);
					break;
				default:
					tile.setFillColor(sf::Color::Magenta);

			}
			tile.setPosition(i*TILE_H,j*TILE_W);
			canvas.draw(tile);
		}
	canvas.display();
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!");
	window.setFramerateLimit(60); 
	sf::Sprite sprite_canvas;
	init_data();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
	draw_game();
	sprite_canvas.setTexture(canvas.getTexture());
        window.draw(sprite_canvas);
        window.display();
    }

    return 0;
}
