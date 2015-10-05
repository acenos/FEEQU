#include <SFML/Graphics.hpp>
#define G_UP 0
#define G_DOWN 1
#define G_RIGHT 2
#define G_LEFT 3
#define WATER 0
#define GRASS 1
#define MONTAIN 2
#define FOREST 3
#define HERO 4

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

class Puppet : public sf::Drawable, public sf::Transformable
{
private:
    
    sf::VertexArray m_basesprites;
	sf::VertexArray m_vertices;
	sf::Texture m_sprites;
    sf::Vector2u size;
    unsigned int * a_idle;
    unsigned int s_idle;
    unsigned int status;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
    	// apply the transform
    	states.transform *= getTransform();
    
    	// apply the tileset texture
    	states.texture = &m_sprites;
    
    	// draw the vertex array
    	target.draw(m_vertices, states);
    }

public:
     
    bool load(char* texImage, sf::Vector2f * Coord, unsigned int texNum, 
              sf::Vector2u tileSize, sf::Color mask);
    void set_idle(unsigned int * seq, int size); 
    void move(int x, int y);
    void refresh();



};
class game_data {

	public:
		unsigned int map_h;
		unsigned int map_w;
		unsigned int* map;
		unsigned int hero_x;
		unsigned int hero_y;
        sf::Clock cooldown;
        Puppet hero_sprite;
        TileMap tilemap;
		game_data();
		~game_data();
		void new_map(int h, int w);
        void move_hero(int mov);

};
