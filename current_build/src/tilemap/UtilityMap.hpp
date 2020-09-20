#ifndef UTILITYMAP_HPP
#define UTILITYMAP_HPP

#include <vector>
#include "SFML/Graphics.hpp"
#include "UtilityTile.hpp"
#include "Tileset.hpp"


class UtilityMap: public sf::Drawable, public sf::Transformable
{
private: 

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<UtilityTile*> utility_map;
	std::vector<Tileset> tilesets;
	Tileset tileset;
	sf::Texture tile_texture;

	int tileset_num;

	int length_x = -1;
	int length_y = -1;

	Point position;

public:
	UtilityMap();
	~UtilityMap();
	void update(std::vector<Enemy_Base*> enemies);

	void load_from_file(std::string);

	UtilityTile get_tile(int x_p, int y_p) { return *utility_map.at(x_p + y_p * length_x); }
	UtilityTile& ref_tile(int x_p, int y_p) { return *utility_map.at(x_p + y_p * length_x); }

	UtilityTile get_tile(Point p_p) { return *utility_map.at(p_p.get_x() + p_p.get_y()*length_x); }
	UtilityTile& ref_tile(Point p_p) { return *utility_map.at(p_p.get_x() + p_p.get_y()*length_x); }

	int get_length_x() { return length_x; }
	void set_length_x(int i_p) { length_x = i_p; }

	int get_length_y() { return length_y; }
	void set_length_y(int i_p) { length_y = i_p; }

	Point get_position() { return position; }

	void set_position(Point p_p) {
		position = p_p;
		setPosition(position.get_x(), position.get_y());
		for (int i = 0; i < length_x; i++) {
			for (int j = 0; j < length_y; j++) {
				ref_tile(i, j).set_position(position.get_x() + tileset.get_tile_width()*i, position.get_y() + tileset.get_tile_height()*j);
			}
		}
	}
	Tileset get_tileset() { return tileset; }

	//Origin is at top left corner of tile map
	Point tile_coord_to_position(int x_p, int y_p) {
		return Point(x_p*tileset.get_tile_width() + position.get_x(), y_p*tileset.get_tile_height() + position.get_y());
	}
	Point tile_coord_to_position(Point p_p) {
		return Point(p_p.get_x()*tileset.get_tile_width() + position.get_x(), p_p.get_y()*tileset.get_tile_height() + position.get_y());
	}
	
	Point position_to_tile_coord(Point position) { return position_to_tile_coord(position.get_x(), position.get_y()); }
	Point position_to_tile_coord(int x_p, int y_p);

	UtilityTile* get_tile_from_coordinate(Point position) { return get_tile_from_coordiante(position.get_x(), position.get_y()); }
	UtilityTile* get_tile_from_coordiante(int x_p, int y_p);

	void set_utility(Point coordinate, UtilityTile* new_utility);

	void add_tileset(std::string, std::string);

	std::vector<UtilityTile*> get_map() { return utility_map;  }

	std::vector<Point> find_path(Point start, Point end);

};

#endif //UTILITYMAP_HPP