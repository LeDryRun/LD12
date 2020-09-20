#ifndef RESOURCETILE_HPP
#define RESOURCETILE_HPP

#include "UtilityTile.hpp"

class ResourceTile : public UtilityTile
{
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	const int kMaxResources = 100;
	const int kTimerMaxTick = 100;

	int m_current_resources = 0;
	int m_resourece_timer = 0;

public:
	ResourceTile();
	UtilityTileType get_tile_type();
	~ResourceTile();
	void update(std::vector<Enemy_Base*> enemies);

	int get_resourece_count();
	int withdraw_resources();
	virtual std::string to_string();
};

#endif RESOURCETILE_HPP //RESOURCETILE_HPP