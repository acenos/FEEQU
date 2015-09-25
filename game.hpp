#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
    
    sf::VertexArray m_basetiles;
	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
    	// apply the transform
    	states.transform *= getTransform();
    
    	// apply the tileset texture
    	states.texture = &m_tileset;
    
    	// draw the vertex array
    	target.draw(m_vertices, states);
    }

public:

    bool load(char* texImage, sf::Vector2f * Coord, unsigned int texNum, 
                       sf::Vector2u tileSize, unsigned int* tiles, 
                       unsigned int width, unsigned int height);



};

class game_data {

	public:
		unsigned int map_h;
		unsigned int map_w;
		unsigned int* map;
		unsigned int hero_x;
		unsigned int hero_y;
        TileMap tilemap;
		game_data();
		~game_data();
		void new_map(int h, int w);

};
