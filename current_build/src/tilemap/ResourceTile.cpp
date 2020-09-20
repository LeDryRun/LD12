#include "ResourceTile.hpp"


void ResourceTile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

ResourceTile::ResourceTile()
{
	tile_type = kResourceGenerator;
}

UtilityTileType ResourceTile::get_tile_type()
{
	return tile_type;
}

ResourceTile::~ResourceTile()
{
}

void ResourceTile::update(std::vector<Enemy_Base*> enemies)
{
	m_resourece_timer++;
	if (m_resourece_timer >= kTimerMaxTick) {
		if(m_current_resources < kMaxResources)
			m_current_resources++;
		m_resourece_timer = 0;
	}
}

int ResourceTile::get_resourece_count()
{
	return m_current_resources;
}

int ResourceTile::withdraw_resources()
{
	int resources = m_current_resources;
	m_current_resources = 0;
	return resources;
}

std::string ResourceTile::to_string()
{
	return "Type: " + std::to_string(tile_type) + ", Resources: " + std::to_string(m_current_resources);
}