#include "UtilityMap.hpp"
#include <fstream>
#include <iostream>


UtilityMap::UtilityMap()
{

}

UtilityMap::~UtilityMap()
{
	for (int i = 0; i < utility_map.size(); i++)
		delete utility_map.at(i);
}

Point UtilityMap::position_to_tile_coord(int x_p, int y_p)
{
	int x_local = x_p - position.get_x();
	int y_local = y_p - position.get_y();

	int x_tile = x_local / tileset.get_tile_width();
	int y_tile = y_local / tileset.get_tile_height();

	return Point(x_tile, y_tile);
}

UtilityTile * UtilityMap::get_tile_from_coordiante(int x_p, int y_p)
{
	Point p = position_to_tile_coord(x_p, y_p);

	int x_tile = p.get_x();
	int y_tile = p.get_y();
	
	int index = x_tile + y_tile * length_x;
	
	if (index > utility_map.size() || index < 0)
		return nullptr;

	return utility_map.at(index);
}

void UtilityMap::set_utility(Point coordinate, UtilityTile* new_utility)
{

	int index = coordinate.get_x() + coordinate.get_y()*length_x;

	if (index > utility_map.size() || index < 0)
		return;

	int x, y;
	x = utility_map.at(index)->get_map_x();
	y = utility_map.at(index)->get_map_y();

	int tu = (new_utility->get_tile_type() % tileset.get_size_x());
	int tv = (new_utility->get_tile_type() / tileset.get_size_x());

	if (utility_map.at(index) != nullptr)
		delete utility_map.at(index);

	utility_map.at(index) = new_utility;

	utility_map.at(index)->set_sprite(sf::Sprite(tile_texture, sf::IntRect(tu*tileset.get_tile_width(), tv*tileset.get_tile_height(), tileset.get_tile_width(), tileset.get_tile_height())));

	utility_map.at(index)->set_position(x, y);

}

void UtilityMap::add_tileset(std::string file_p, std::string n_p)
{
	tilesets.push_back(Tileset(file_p, n_p));
}

void UtilityMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < utility_map.size(); i++)
		target.draw(*utility_map.at(i));
}

void UtilityMap::update(std::vector<Enemy_Base*> enemies)
{
	for (int i = 0; i < utility_map.size(); i++)
		utility_map.at(i)->update(enemies);
}

void UtilityMap::load_from_file(std::string file_p)
{
	std::ifstream map_stream(file_p);

	int max = 100;
	char*raw;
	raw = (char*)malloc(max);

	if (map_stream.is_open()) {

		map_stream.get(raw, max, ':');
		tileset_num = atoi(raw);
		map_stream.get();

		tileset = tilesets.at(tileset_num);
		tile_texture.loadFromFile(tileset.get_file_name());

		map_stream.get(raw, max, 'X');
		length_x = atoi(raw);
		map_stream.get();

		map_stream.get(raw, max, '\n');
		length_y = atoi(raw);
		map_stream.get();

		if (length_y != -1 && length_x != -1) {
			utility_map.resize(length_x*length_y);


			for (int j = 0; j < length_y; j++) {
				for (int i = 0; i < length_x; i++) {

					map_stream.get(raw, max, ',');
					utility_map.at(i + j * length_x) = UtilityTile::load(i, j, tileset, raw);
					map_stream.get();

					int tile_type = utility_map.at(i + j * length_x)->get_tile_type();
					if (tile_type > tileset.get_obj_threshold()) {
						tile_type = tileset.get_solid_threshold();
					}

					int tu = (tile_type % tileset.get_size_x());
					int tv = (tile_type / tileset.get_size_x());					

					if (tile_type == kResourceGenerator)
						std::cout << tu;

					utility_map.at(i + j * length_x)->set_sprite(sf::Sprite(tile_texture, sf::IntRect(tu*tileset.get_tile_width(), tv*tileset.get_tile_height(), tileset.get_tile_width(), tileset.get_tile_height())));
					utility_map.at(i + j * length_x)->set_position(i * tileset.get_tile_width() + position.get_x(), j*tileset.get_tile_height() + position.get_y());

				}
				map_stream.get();
			}

		}
		else {
			std::cout << "ERROR: map width and height not read!" << std::endl;
		}

	}
	else {
		std::cout << "ERROR: map stream didn't open!" << std::endl;
	}
}
