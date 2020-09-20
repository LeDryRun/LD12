#include "Bullet.hpp"
#include "../image/Imagehandler.hpp"
#include "../tilemap/Tilemap.hpp"

Bullet::Bullet(Point p_p, float vx_p, float vy_p, int d_p, int s_p){
	create(p_p,vx_p,vy_p,d_p,s_p);
}

void Bullet::create(Point p_p, float vx_p, float vy_p, int d_p, int s_p){
	set_position(p_p);
	vector_x=vx_p;
	vector_y=vy_p;
	damage=d_p;
	speed=s_p;
	destruct_timer=40;
}


void Bullet::update(Tilemap& tilemap){
	if(destruct_timer==40){
		movement=Point(vector_x*speed,vector_y*speed);
		if(check_tilemap_collision(tilemap)){
			destruct_timer--;
		}
		tilemap_collide_physics(tilemap);
		move();
	}else if(destruct_timer>0){
		current_animation_int=1;
		destruct_timer--;
	}else{
		//destroy?
	}

}
void Bullet::load_animations(Imagehandler& imagehandler){
	animations.push_back(Animation("Effects_Attack"));
	animations.push_back(Animation("bullet_impact"));
	imagehandler.load_animation(animations.at(0));
	imagehandler.load_animation(animations.at(1));
	animations.at(0).set_looping(true);
}