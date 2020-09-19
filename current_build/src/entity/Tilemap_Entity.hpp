#ifndef Tilemap_Entity_HPP
#define Tilemap_Entity_HPP

#include "Entity.hpp"

class Tilemap;

class Tilemap_Entity: public Entity{
protected:
	Point current_tile=Point(0,0);

	std::vector<Point> tiles_colliding;

	Point hitbox_size_in_tiles=Point(0,0);
	Point tile_size=Point(0,0);

public:
	Tilemap_Entity(){};

	void create(Point p_p, Tilemap);
	void create_hitbox(Point size_p, Point offset_p) override;

	Point get_current_tile(){return current_tile;}


	virtual void update(Tilemap&);
	virtual void tilemap_collide_physics(Tilemap&);
	virtual bool check_tilemap_collision(Tilemap& tilemap);
};

#endif