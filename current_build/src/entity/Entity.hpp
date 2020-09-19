#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Hitbox.hpp"
#include "Point.hpp"
#include "../image/Animation.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

class Imagehandler;

class Entity:public sf::Drawable{

protected:
	Hitbox hitbox;
	Point hitbox_offset=Point(0,0);
	std::vector<Animation> animations;
	int current_animation_int=0;

	Point position=Point(0,0);

	Point movement=Point(0,0);

	std::vector<Point> tiles_colliding;

	Hitbox projected_hitbox;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Entity(){};

	virtual void create(Point p_p);
	virtual void create_hitbox(Point size_p, Point offset_p);

	Animation& ref_animation(int i_p){return animations.at(i_p);}
	void set_current_animation(int i_p){current_animation_int=i_p;}
	virtual void animate();

	void add_animation(std::string name_p){animations.push_back(Animation(name_p));}

	Hitbox get_hitbox(){return hitbox;}
	Hitbox& ref_hitbox(){return hitbox;}

	Point get_movement(){return movement;}
	Point& ref_movement(){return movement;}
	void set_movement(Point p_p){movement=p_p;}

	void set_position(Point p_p);
	Point get_position(){return position;}

	virtual void move();
	virtual void load_animations(Imagehandler&);

};


#endif