#include "Ghost.hpp"
#include "../../communal/Communal.hpp"
#include "../../tilemap/Tilemap.hpp"
#include "../../image/Imagehandler.hpp"
#include <iostream>

Ghost::Ghost(std::string n_p, int i_p, int s_p){
	speed=s_p;
	intelligence=i_p;
	name=n_p;
}



void Ghost::update(Tilemap& tilemap){
	if(respawn_timer==0){

		int r;

		std::vector<Point> valid_movements;
		// std::cout<<std::endl<<name<<" checking valid moves "<<std::endl;

		movement=Cardinal::North;
		movement*=speed;
		if(!check_tilemap_collision(tilemap)){
			valid_movements.push_back(movement);
			//std::cout<<"North valid:"<<movement.get_x()<<","<<movement.get_y()<<std::endl;
		}
		movement=Cardinal::South;
		movement*=speed;
		if(!check_tilemap_collision(tilemap)){
			valid_movements.push_back(movement);
			//std::cout<<"South valid:"<<movement.get_x()<<","<<movement.get_y()<<std::endl;
		}
		movement=Cardinal::East;
		movement*=speed;
		if(!check_tilemap_collision(tilemap)){
			valid_movements.push_back(movement);
			//std::cout<<"East valid:"<<movement.get_x()<<","<<movement.get_y()<<std::endl;
		}
		movement=Cardinal::West;
		movement*=speed;
		if(!check_tilemap_collision(tilemap)){
			//std::cout<<"West valid:"<<movement.get_x()<<","<<movement.get_y()<<std::endl;
			valid_movements.push_back(movement);
		}

		if(dead){
			//std::cout<<name<<" doing dead "<<std::endl;
			if(current_tile==spawn){
				dead=false;
			}else{
				current_animation_int=2;
				movement=tilemap.find_path(current_tile,spawn).at(0)*speed;
				if(check_tilemap_collision(tilemap)){
					movement=momentum;
				}
				if(check_tilemap_collision(tilemap)){
					movement=valid_movements.at(0);
				}
			}
		}else if(afraid){
			//std::cout<<name<<" doing afraid "<<std::endl;
			Point away;
			movement=Point(0,0);
			if(current_tile.get_x()>pac_tile.get_x()){
				away.set_x(1);
			}else if(current_tile.get_x()<pac_tile.get_x()){
				away.set_x(-1);
			}else{
				r=random(0,1);
				(r)?away.set_x(1):away.set_x(-1);
			}
			if(current_tile.get_y()>pac_tile.get_y()){
				away.set_y(1);
			}else if(current_tile.get_y()<pac_tile.get_y()){
				away.set_y(-1);
			}else{
				r=random(0,1);
				(r)?away.set_y(1):away.set_y(-1);
			}
			r=random(0,1);
			if(r==0){
				for(int i=0;i<(int)valid_movements.size();i++){
					if(valid_movements.at(i).get_x()==away.get_x()*speed ||valid_movements.at(i).get_y()==away.get_y()*speed){
						movement=valid_movements.at(i);
					}
				}
			}else{
				for(int i=(int)valid_movements.size()-1;i>=0;i--){
					if(valid_movements.at(i).get_x()==away.get_x()*speed ||valid_movements.at(i).get_y()==away.get_y()*speed){
						movement=valid_movements.at(i);
					}
				}
			}
			current_animation_int=1;
		}else{
			//std::cout<<name<<" doing normal "<<std::endl;
			current_animation_int=0;
			if(valid_movements.size()==1){
				movement=valid_movements.at(0);
			}else{
				r=random(0,99);
				if(intelligence>r){
					//std::cout<<name<<" doing pathfinding"<<std::endl;
					movement=tilemap.find_path(current_tile,pac_tile).at(0)*speed;
					if(check_tilemap_collision(tilemap) || movement==(-momentum)){
						movement=momentum;
					}
				}else{
					//std::cout<<name<<" choosing random"<<std::endl;
					int inverse_momentum=-1;
					int momentum_num=-1;
					for(int i=0;i<(int)valid_movements.size();i++){
						if(valid_movements.at(i)==(-momentum)){
							inverse_momentum=i;
						}
						if(valid_movements.at(i)==momentum){
							momentum_num=i;
						}
					}
					r=random(0,99);
					if(momentum_num!=-1 && r<20/*probability of continuing momentum*/){
						//std::cout<<name<<" continuing momentum"<<std::endl;
						movement=valid_movements.at(momentum_num);
					}else{	
						//std::cout<<name<<" picking new direction"<<std::endl;
						do{
							r=random(0,valid_movements.size()-1);
						}while(r==inverse_momentum);
						movement=valid_movements.at(r);
					}
				}
			}
		}



	//std::cout<<name<<" doing physics "<<std::endl;
	momentum=movement;
	tilemap_collide_physics(tilemap);
			

	}else{
		movement=Point(0,0);
		respawn_timer--;
	}
	//std::cout<<name<<":"<<movement.get_x()<<","<<movement.get_y()<<"->"<<position.get_x()<<","<<position.get_y()<<std::endl;



}


void Ghost::load_animations(Imagehandler& imagehandler){
	animations.push_back(Animation("ghost_"+name));
	animations.push_back(Animation("ghost_afraid"));
	animations.push_back(Animation("ghost_dead"));
	animations.push_back(Animation("ghost_swap"));
	imagehandler.load_animation(animations.at(0));
	imagehandler.load_animation(animations.at(1));
	imagehandler.load_animation(animations.at(2));
	imagehandler.load_animation(animations.at(3));
	animations.at(0).set_looping(true);
	animations.at(1).set_looping(true);
	animations.at(2).set_looping(true);
	animations.at(3).set_looping(true);
}