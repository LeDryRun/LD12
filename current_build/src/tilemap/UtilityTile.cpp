#include "UtilityTile.hpp"
#include "TurretTile.hpp"
#include <iostream>

void UtilityTile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

void UtilityTile::update()
{

}

UtilityTile::UtilityTile()
{

}

UtilityTile::~UtilityTile()
{

}

int UtilityTile::get_map_x()
{
	return m_map_x;
}

int UtilityTile::get_map_y()
{
	return m_map_y;
}

sf::Sprite UtilityTile::get_sprite()
{
	return m_sprite;
}

UtilityTileType UtilityTile::get_tile_type()
{
	return tile_type;
}

bool UtilityTile::is_solid()
{
	return solid;
}

void UtilityTile::set_map_x(int x_p)
{
	m_map_x = x_p;
}

void UtilityTile::set_map_y(int y_p)
{
	m_map_y = y_p;
}

void UtilityTile::set_solid(bool b_p)
{
	solid = b_p;
}

void UtilityTile::set_sprite(sf::Sprite sprite)
{
	m_sprite = sprite;
}

void UtilityTile::set_position(int x, int y)
{
	m_sprite.setPosition(x, y);
	m_map_x = x;
	m_map_y = y;
}

UtilityTile* UtilityTile::load(int x_p, int y_p, Tileset tileset_p, std::string load_p) {
	int tile_type = kNone;
	int map_x, map_y;
	int rotation_int;

	UtilityTile *tile;

	char c = '?';
	for (int i = 0; i < (int)load_p.size(); i++) {

		if (tile_type == kNone) {
			if (load_p.at(i) >= '0' &&load_p.at(i) <= '9') {
				for (int j = i; j < (int)load_p.size(); j++) {
					if (load_p.at(j) < '0' || load_p.at(j) > '9') {
						tile_type = (UtilityTileType)std::stoi(load_p.substr(i, j - i));
						i = j - 1;
						break;
					}
					if (j + 1 == load_p.size()) {
						tile_type = (UtilityTileType)std::stoi(load_p.substr(i, (j + 1) - i));
						i = j;
						break;
					}
				}
			}
		}
		else {
			c = load_p.at(i);
			if (c == 'r') {
				if (i + 1 >= load_p.size()) {
					std::cout << "ERROR: bad rotation info at " << map_x << "," << map_y << std::endl;
				}
				rotation_int = load_p.at(i + 1) - 48;
				if (rotation_int < 0 || rotation_int>3) {
					std::cout << "ERROR: bad rotation int: " << rotation_int << " at " << map_x << "," << map_y << std::endl;
					rotation_int = 0;
				}
				i++;
			}
			else if (c == 'd') {

			}
		}

	}

	switch (tile_type)
	{
	case kNone:
		tile = new UtilityTile();
		break;
	case kTurret:
		tile = new TurretTile();
		break;
	default:
		tile = new UtilityTile();
		break;
	}

	tile->set_map_x(map_x);
	tile->set_map_y(map_y);
	

	if (tile_type < 0 || tile_type > tileset_p.get_set_size()) {
		std::cout << "ERROR: invalid tile_type " << tile_type << " at tile: " << map_x << "," << map_y << std::endl;
	}

	if (tile_type < tileset_p.get_solid_threshold()) {
		tile->set_solid(true);
	}

	return tile;
}