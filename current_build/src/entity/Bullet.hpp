#ifndef BULLET_HPP
#define BULLET_HPP

#include "Tilemap_Entity.hpp"

class Bullet:public Tilemap_Entity{
private:
	float vector_x=0.0f;
	float vector_y=0.0f;
	int damage=1;
	int speed=10;
	int destruct_timer=40;
public:
	Bullet(){};

	Bullet(Point p_p,float vx_p, float vy_p, int d_p, int s_p);
	void create(Point p_p,float vx_p, float vy_p, int d_p, int s_p);

	void update(Tilemap&);
	void load_animations(Imagehandler&) override;
	int get_destruct_timer(){return destruct_timer;}

};

#endif