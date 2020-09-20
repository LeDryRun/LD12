#ifndef UTILITYTILE_HPP
#define UTILITYTILE_HPP

#include <SFML/Graphics.hpp>
#include "../entity/Point.hpp"
#include "Tileset.hpp"

enum UtilityTileType
{
	kNone,
	kTurret,
	kResourceGenerator
};

class UtilityTile : public sf::Drawable
{

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	int m_map_x = 0;
	int m_map_y = 0;
	bool solid = false;
	UtilityTileType tile_type = kNone;
	int rotation_int = 0;
	sf::Sprite m_sprite;

public:

	UtilityTile();
	~UtilityTile();

	static UtilityTile* load(int, int, Tileset, std::string);

	virtual void update();

	int get_map_x();
	int get_map_y();
	bool is_solid();
	sf::Sprite get_sprite();
	UtilityTileType get_tile_type();

	virtual void set_map_x(int x_p);
	virtual void set_map_y(int y_p);
	virtual void set_solid(bool b_p);
	virtual void set_sprite(sf::Sprite sprite);
	virtual void set_position(int x, int y);

};

#endif // UTILITYTILE_HPP
