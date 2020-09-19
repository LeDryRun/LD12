#include "Pac_man.hpp"
#include "../../tilemap/Tilemap.hpp"
#include "../../image/Imagehandler.hpp"



Pac_man::Pac_man(){
	momentum*=speed;
	movement=momentum;
	add_sound("pac_man",sound_category::SFX);
	add_sound("pellet",sound_category::SFX);
	add_sound("cherry",sound_category::SFX);
	add_sound("pac_man_dies",sound_category::SFX);
	loop_sound("cherry",true);
	loop_sound("pac_man",true);
	set_state_of_origin("pac_man");
};

void Pac_man::update(Tilemap& tilemap){
	if(death_timer==-1){
		if(cherry_timer!=0){
			cherry_timer--;
			if(!is_sound_playing("cherry")){
				play_sound("cherry");
				stop_sound("pac_man");
			}
		}else{
			cherry=false;
			if(!is_sound_playing("pac_man")){
				play_sound("pac_man");
				stop_sound("cherry");
			}
		}

		if(input_dir!=Point(0,0)){
			movement=input_dir*speed;
			tilemap_collide_physics(tilemap);
		}
		if(movement!=input_dir*speed){
			movement=momentum;
			tilemap_collide_physics(tilemap);
		}
		momentum=movement;
		if(movement!=Point(0,0)){
			animations.at(0).set_rotation(Cardinal::to_degrees(movement/speed));
		}

		if(tilemap.get_tile(current_tile).get_type_s()=="pellet"){
			tilemap.set_tile_type(current_tile.get_x(),current_tile.get_y(),tilemap.get_tileset().type_s_to_int("empty"));
			score+=1;
			play_sound("pellet");
		}
		if(tilemap.get_tile(current_tile).get_type_s()=="cherry"){
			tilemap.set_tile_type(current_tile.get_x(),current_tile.get_y(),tilemap.get_tileset().type_s_to_int("empty"));
			cherry=true;
			cherry_timer=cherry_timer_max;
		}
	}else{
		if(!is_sound_playing("pac_man_dies")){
			play_sound("pac_man_dies");
			stop_sound("pac_man");
			stop_sound("cherry");
			stop_sound("pellet");
		}
		death_timer--;
		movement=Point(0,0);
	}


}


void Pac_man::load_animations(Imagehandler& imagehandler){
	animations.push_back(Animation("pac_man"));
	animations.push_back(Animation("pac_man_dies"));
	imagehandler.load_animation(animations.at(0));
	imagehandler.load_animation(animations.at(1));
	animations.at(0).set_looping(true);
}


void Pac_man::respawn(){
	death_timer=-1;
	cherry_timer=0;
	current_animation_int=0;
	input_dir=Point(-1,0);
	momentum=Point(-1*speed,0);
	movement=Point(-1*speed,0);
}