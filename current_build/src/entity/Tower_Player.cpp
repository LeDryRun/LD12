#include "Tower_Player.hpp"
#include "../input/Mousey.hpp"
#include "../input/Keyblade.hpp"
#include "../image/Imagehandler.hpp"
#include "../tilemap/Tilemap.hpp" 
#include <math.h>


Tower_Player::Tower_Player():valid("valid"),invalid("invalid"),reticule("reticule"),bullet("Effects_Attack"){
	set_state_of_origin("tower_state");
	gravity_acceleration=-1.6f;
	jump_impulse=16;
	jump_acceleration=1.1f;
	bullet_cooldown_timer_max=10;
}

void Tower_Player::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(animations.at(current_animation_int).get_current_frame(), states);
	if(mode=="placing"){
		if(placing_valid){
			target.draw(valid.get_current_frame());
		}else{
			target.draw(invalid.get_current_frame());
		}
	}else{
		target.draw(bullet.get_current_frame());
	}
}

void Tower_Player::load_animations(Imagehandler& imagehandler){
	animations.push_back(Animation("Player_Idle"));
	animations.at(0).set_looping(true);
	animations.push_back(Animation("Player_Scoot"));
	animations.at(1).set_looping(true);
	animations.push_back(Animation("Player_Jump"));
	animations.at(2).set_desired_fps(40);
	animations.push_back(Animation("Player_Land"));
	animations.at(3).set_desired_fps(20);
	animations.push_back(Animation("Player_Cling"));
	animations.push_back(Animation("Player_Pogo"));
	animations.push_back(Animation("Player_Cling_Idle"));
	animations.at(6).set_looping(true);
	for(int i=0;i<(int)animations.size();i++){
		imagehandler.load_animation(animations.at(i));
	}
	imagehandler.load_animation(valid);
	imagehandler.load_animation(invalid);
	imagehandler.load_animation(reticule);
	imagehandler.load_animation(bullet);
	valid.set_looping(true);
	invalid.set_looping(true);
	reticule.set_looping(true);
	bullet.set_looping(true);
}


void Tower_Player::update(Tilemap&  tilemap, Mousey&  mouse, Keyblade& keyboard){

	if(keyboard.get_key('e').was_just_pressed()){
		if(mode=="shooting"){
			mode="placing";
		}else{
			mode="shooting";
		}
	}


	firing_bullet=false;
	if(mode=="shooting"){
		if(mouse.is_pressed() && bullet_cooldown_timer==0){
			firing_bullet=true;

			//std::cout<<mouse.get_window_x()<<","<<mouse.get_window_y()<<" L="<<mouse.get_layer_x()<<","<<mouse.get_layer_y()<<std::endl;
			//std::cout<<get_position().get_x()<<", "<<get_position().get_y()<<std::endl;
			float temp_x=mouse.get_layer_x()-(position.get_x()+hitbox.get_width()/2);
			float temp_y=mouse.get_layer_y()-(position.get_y()+hitbox.get_height()/2);
			float length=sqrt(temp_x*temp_x+temp_y*temp_y);
			bullet_vector_x=temp_x/length;
			bullet_vector_y=temp_y/length;
			bullet_cooldown_timer=bullet_cooldown_timer_max;
			//std::cout<<"PEW! "<<bullet_vector_x<<","<<bullet_vector_y<<std::endl;
		}else if(bullet_cooldown_timer!=0){
			bullet_cooldown_timer--;
		}
	}else if(mode=="placing"){
		placing_valid=false;
		Point mouse_coords=tilemap.position_to_tile_coord(Point(mouse.get_layer_x(),mouse.get_layer_y()));
		if(mouse_coords.get_x()>=0 && mouse_coords.get_x()<tilemap.get_length_x() &&mouse_coords.get_y()>=0 && mouse_coords.get_y()<tilemap.get_length_y()){
			invalid.set_position(tilemap.tile_coord_to_position(mouse_coords)+Point(16,16));
			valid.set_position(tilemap.tile_coord_to_position(mouse_coords)+Point(16,16));
			if(grounded){
				Point distance_to_mouse=mouse_coords-current_tile;
				if(distance_to_mouse.get_x()<5 && distance_to_mouse.get_x()>-5 &&distance_to_mouse.get_y()<5&& distance_to_mouse.get_y()>-5){
					if(tilemap.get_tile(mouse_coords).get_type_s()=="empty"){
						placing_valid=true;
						if(mouse.is_clicked()){
							build_timer=build_timer_max;
							tilemap.set_tile_type(mouse_coords,"wall");
						}
					}else if(mouse.is_right_clicked()){
						tilemap.set_tile_type(mouse_coords,"empty");
					}
				}
			}		
		}	
	}


	movement=Point(0,0);
	Point dir=Point(0,0);
	wall_slide=false;
	if(keyboard.get_key('w').is_pressed()){
		//std::cout<<"W"<<std::endl;
		//dir=Cardinal::North;
		//movement=movement+(dir*speed);
	}
	if(keyboard.get_key('s').is_pressed()){
		//std::cout<<"s"<<std::endl;
		//dir=Cardinal::South;
		//movement=movement+(dir*speed);
	}
	wall_slide=false;
	if(keyboard.get_key('a').is_pressed()){
		//std::cout<<"a"<<std::endl;
		dir=Cardinal::West;
		movement=movement+(dir*speed);
		if(check_tilemap_collision(tilemap)){
			wall_slide=true;
		}
		if(!wall_slide){
			facing_left=true;
		}
	}
	if(keyboard.get_key('d').is_pressed()){
		//std::cout<<"d"<<std::endl;
		dir=Cardinal::East;
		movement=movement+(dir*speed);
		for(int i=0;i<(int)animations.size();i++){
			animations.at(i).set_h_mirror(true);
		}
		if(check_tilemap_collision(tilemap)){
			wall_slide=true;
		}
		if(!wall_slide){
			facing_left=false;
		}
	}
	for(int i=0;i<(int)animations.size();i++){
		animations.at(i).set_h_mirror(!facing_left);
	}


	if(keyboard.get_key(' ').is_pressed()){
		//std::cout<<"space"<<std::endl;
		if(grounded /*&& !anim_wait*/){
			/*anim_wait=true;
			//std::cout<<"jumping"<<std::endl;
			current_animation_int=2;
			animations.at(2).start();*/
			falling_speed+=jump_impulse;
			jumping=true;
			grounded=false;
			current_animation_int=0;
		}else if(jumping /*&& !anim_wait*/){
			falling_speed+=jump_acceleration;
		}
	}else{
		jumping=false;
	}
	/*
	if(current_animation_int==2 && animations.at(2).is_finished()){
		falling_speed+=jump_impulse;
		jumping=true;
		grounded=false;
		anim_wait=false;
		current_animation_int=0;
	}
	if(current_animation_int==3 && animations.at(3).is_finished()){
		anim_wait=false;
		current_animation_int=0;
	}*/
	if(grounded){
		if(animations.at(current_animation_int).is_looping()==true){
			if(movement.get_x()!=0){
				current_animation_int=1;
			}else{
				current_animation_int=0;
			}
		}
	}else{
		if(wall_slide){
			current_animation_int=6;
		}else{
			current_animation_int=0;
		}
		//anim_wait=false;
	}

	if(falling_speed<0){
		jumping=false;
	}

	if(falling_speed<-20){
		falling_speed=-20;
	}else{
		if(wall_slide&& falling_speed<0){
			falling_speed+=gravity_acceleration/4;
		}else{
			falling_speed+=gravity_acceleration;
		}
	}
	movement=movement+(Point(Cardinal::North)*falling_speed);


	//std::cout<<movement.get_x()<<","<<movement.get_y()<<std::endl;
	tilemap_collide_physics(tilemap);
	move();

	

	movement=Point(0,1);
	if(check_tilemap_collision(tilemap)){
		falling_speed=0;
		//if(!grounded){
		//	current_animation_int=3;
		//	animations.at(3).start();
		//	anim_wait=true;
		//}
		//std::cout<<"grounded"<<std::endl;
		grounded=true;
	}else{
		grounded=false;
	}
	movement=Point(0,-1);
	if(check_tilemap_collision(tilemap)){
		falling_speed=-1;
		//std::cout<<"grounded"<<std::endl;
	}
	//movement=Point(0,0);


	if(facing_left){
		if(wall_slide){
			bullet_position=position+Point(54,40);
		}else{
			bullet_position=position+Point(47,13);
		}
	}else{
		if(wall_slide){
			bullet_position=position+Point(10,40);
		}else{
			bullet_position=position+Point(17,13);
		}
	}
	bullet.set_position(bullet_position);
	bullet.animate();
}