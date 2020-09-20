#include "TurretTile.hpp"


TurretTile::TurretTile()
{
	m_turret_texture = sf::Texture();
	m_turret = sf::Sprite();

	m_turret_texture.loadFromFile("../assets/Tower/entities/turret_placeholder.png");
	m_turret.setTexture(m_turret_texture);

	m_turret.setPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);

	m_turret.setOrigin(m_turret_texture.getSize().x / 2, m_turret_texture.getSize().y / 2);

	tile_type = kTurret;

	m_rot = rand() % 4 * 90;

}

TurretTile::~TurretTile()
{

}

void TurretTile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
	target.draw(m_turret, states);
}

void TurretTile::update()
{
	m_turret.setRotation(m_rot);
	m_rot++;
}

UtilityTileType TurretTile::get_tile_type()
{
	return tile_type;
}

void TurretTile::set_position(int x, int y)
{
	m_sprite.setPosition(x, y);
	m_turret.setPosition(x + m_sprite.getTextureRect().width/2, y + m_sprite.getTextureRect().height/2);
	m_map_x = x;
	m_map_y = y;
}
