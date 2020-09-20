#ifndef RESOURECETILE_HPP
#define RESOURECETILE_HPP

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
	void update();

	int get_resourece_count();
	int withdraw_resources();
	virtual std::string to_string();
};

#endif RESOURECETILE_HPP //RESOURECETILE_HPP