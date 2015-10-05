#include <stdlib.h>
#include "game.hpp"

bool TileMap::load(char* texImage, sf::Vector2f * Coord, unsigned int texNum, 
                   sf::Vector2u tileSize, unsigned int* tiles, 
                   unsigned int width, unsigned int height)
{

	// load the tileset texture
	if (!m_tileset.loadFromFile(texImage))
		return false;
    m_basetiles.setPrimitiveType(sf::Quads);
    m_basetiles.resize(texNum*4);
    sf::Vertex* tex_quad;
    sf::Vector2f v1 = sf::Vector2f(tileSize.x,0);
    sf::Vector2f v2 = sf::Vector2f(tileSize.x,tileSize.y);
    sf::Vector2f v3 = sf::Vector2f(0,tileSize.y);
    for(int i = 0; i < texNum; i++)
    {
        tex_quad=&m_basetiles[i*4];
        tex_quad[0].texCoords = Coord[i];
        tex_quad[1].texCoords = Coord[i]+v1; 
        tex_quad[2].texCoords = Coord[i]+v2;
        tex_quad[3].texCoords = Coord[i]+v3;

    }

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * 4);

	// populate the vertex array, with one quad per tile
	for (unsigned int i = 0; i < width; ++i)
		for (unsigned int j = 0; j < height; ++j)
		{
			// get the current tile number
			int tileNumber = i + j * width;
            int type = tiles[tileNumber];
            
			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * 4];
            tex_quad = &m_basetiles[type*4];
			// define its 4 corners
			quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

			// define its 4 texture coordinates
			quad[0].texCoords = tex_quad[0].texCoords;
			quad[1].texCoords = tex_quad[1].texCoords;
			quad[2].texCoords = tex_quad[2].texCoords;
			quad[3].texCoords = tex_quad[3].texCoords;
		}

	return true;

}

bool Puppet::load(char* texImage, sf::Vector2f * Coord, unsigned int texNum, 
          sf::Vector2u tileSize, sf::Color mask)
{
    size = tileSize;
    sf::Image img_temp;   
	// load the tileset texture
	if (!img_temp.loadFromFile(texImage))
		return false;
    img_temp.createMaskFromColor(mask);
    m_sprites.loadFromImage(img_temp); 
    m_basesprites.setPrimitiveType(sf::Quads);
    m_basesprites.resize(texNum*4);
    sf::Vertex* tex_quad;
    sf::Vector2f v1 = sf::Vector2f(tileSize.x,0);
    sf::Vector2f v2 = sf::Vector2f(tileSize.x,tileSize.y);
    sf::Vector2f v3 = sf::Vector2f(0,tileSize.y);
    for(int i = 0; i < texNum; i++)
    {
        tex_quad=&m_basesprites[i*4];
        tex_quad[0].texCoords = Coord[i];
        tex_quad[1].texCoords = Coord[i]+v1; 
        tex_quad[2].texCoords = Coord[i]+v2;
        tex_quad[3].texCoords = Coord[i]+v3;

    }

	// resize the vertex array to fit the level size
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(4);
    m_vertices[0].position = sf::Vector2f(0,0);
    m_vertices[1].position = sf::Vector2f(tileSize.x,0);
    m_vertices[2].position = sf::Vector2f(tileSize.x,tileSize.y);
    m_vertices[3].position = sf::Vector2f(0,tileSize.y);

    m_vertices[0].texCoords = m_basesprites[0].texCoords;
    m_vertices[1].texCoords = m_basesprites[1].texCoords;
    m_vertices[2].texCoords = m_basesprites[2].texCoords;
    m_vertices[3].texCoords = m_basesprites[3].texCoords;
	return true;
}
void Puppet::move(int x, int y)
{
    this->setPosition(size.x*x, size.y*y);
}

void Puppet::set_idle(unsigned int * seq, int size)
{
    if(a_idle) delete a_idle;
    a_idle = new unsigned int[size];
    s_idle =  size;
    for(int i = 0; i < size; i++) a_idle[i] = seq[i];

}

void Puppet::refresh()
{
    status++;
    sf::Vertex* tex_quad;
    tex_quad=&m_basesprites[(status % s_idle)*4];
    m_vertices[0].texCoords = tex_quad[0].texCoords;
    m_vertices[1].texCoords = tex_quad[1].texCoords;
    m_vertices[2].texCoords = tex_quad[2].texCoords;
    m_vertices[3].texCoords = tex_quad[3].texCoords;

}

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
	if(map)delete[] map;
}

void game_data::new_map(int h, int w)
{
	if(map)delete[] map;
	map_h = h;
	map_w = w;
	map = new unsigned int[w*h];
	
}
void game_data::move_hero(int mov)
{
    if(cooldown.getElapsedTime() < sf::milliseconds(10)) return;
    cooldown.restart();
    int new_x,  new_y;
	switch (mov)
	{
		case G_LEFT:
			new_x = hero_x == 0 ? map_w-1 : hero_x-1;
            new_y = hero_y;
			break;
		case G_RIGHT:
			new_x = (hero_x+1)%map_w;
            new_y = hero_y;
			break;
		case G_UP:
			new_y = hero_y == 0 ? map_h-1 : hero_y-1;
            new_x = hero_x;
			break;
		case G_DOWN:
			new_y=(hero_y+1)%map_h;
            new_x = hero_x;
			break;
		default:
		break;
	}
    int new_pos = map[new_y*map_h+new_x];
    if(new_pos== WATER) return;
    hero_x=new_x;
    hero_y=new_y;    
    hero_sprite.move(hero_x,hero_y);
}
