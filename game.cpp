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
