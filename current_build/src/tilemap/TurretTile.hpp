#ifndef TURRETTILE_HPP
#define TURRETTILE_HPP

#include "UtilityTile.hpp"

class TurretTile : public UtilityTile
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_turret_texture;
	sf::Sprite m_turret;
	double m_rot = 0;

public:
	TurretTile();
	UtilityTileType get_tile_type();
	void set_position(int x, int y);
	~TurretTile();
	void update();
};

#endif //TURRETTILE_HPP