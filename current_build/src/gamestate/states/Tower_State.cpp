#include "Tower_State.hpp"


Tower_State::Tower_State(Imagehandler& imagehandler,Audiohandler& audiohandler):tower_layer("tower_layer"){
	int screen_size_x=2000;
	int screen_size_y=1100;
	tower_layer.set_original_size(screen_size_x,screen_size_y);
	tower_layer.set_original_center(screen_size_x/2,screen_size_y/2);
	//std::cout<<"load map"<<std::endl;
	platform_map.load_from_file("../assets/maps/dry_run_map.map");
	//std::cout<<"set map location"<<std::endl;
	platform_map.set_position(Point((screen_size_x/2)-(platform_map.get_tileset().get_tile_width()*platform_map.get_length_x()/2), 
		(screen_size_y/2)-(platform_map.get_tileset().get_tile_height()*platform_map.get_length_y()/2)));

	//std::cout<<"load sprites"<<std::endl;
	load_sprites(imagehandler);
	state_name="tower_state";

	//std::cout<<"create player"<<std::endl;
	player.create(platform_map.tile_coord_to_position(2,18),platform_map);
	b.Tilemap_Entity::create(Point(0,0),platform_map);
	//std::cout<<"done"<<std::endl;
	update_layer_resolutions();
}


void Tower_State::update_layer_resolutions(){
	Gamestate::update_layer_resolutions();
	tower_layer.resolve_new_resolution();
}



void Tower_State::load_sprites(Imagehandler& imagehandler){
	imagehandler.load_sprite(background,"core_game_background");
	player.load_animations(imagehandler);
	b.load_animations(imagehandler);
}


void Tower_State::update(Mousey& mouse, Keyblade& keyboard, Gamepad& gamepad){
	Duration_Check::start("-Tower update");
	Gamestate::update_gui_layer(mouse,keyboard,gamepad);
	tower_layer.setCenter(player.get_center().get_x(),player.get_center().get_y());
	mouse.set_layer(tower_layer);
	player.update(platform_map,mouse,keyboard);
	if(player.is_firing_bullet()){
		b.create(player.get_bullet_position(),player.get_bulletv_x(),player.get_bulletv_y(),1,20);
		bullets.push_back(b);
		//std::cout<<bullets.at(bullets.size()-1).get_position().get_x()<<","<<bullets.at(bullets.size()-1).get_position().get_y()<<std::endl;
	}

	for(auto it=bullets.begin();it!=bullets.end();){
		if(it->get_destruct_timer()==0){
			it=bullets.erase(it);
			//std::cout<<"destroying"<<std::endl;
		}else{
			it->update(platform_map);
			++it;
		}
	}

	check_gamepad(gamepad);
	check_keyboard(keyboard);

	/*
		UPDATE TOP LAYER AND DESCEND, RENDER BOTTOM LAYER AND ASCEND

		ALWAYS SET MOUSE TO BACKGROUND LAYER LAST
	*/

	mouse.set_layer(background_layer);

	Duration_Check::stop("-Tower update");
}



void Tower_State::render(sf::RenderWindow& window){
	Duration_Check::start("-Tower render");
	Gamestate::render_background_layer(window);
	window.setView(tower_layer);

	window.draw(platform_map);
	window.draw(player);
	player.animate();

	for(int i=0;i<(int)bullets.size();i++){
		window.draw(bullets.at(i));
		//std::cout<<bullets.at(i).get_position().get_x()<<","<<bullets.at(i).get_position().get_y()<<std::endl;
		bullets.at(i).animate();
	}
	Gamestate::render_gui_layer(window);
	Duration_Check::stop("-Tower render");
}
void Tower_State:: execute_data(Data_Packet data){
}

void Tower_State::check_keyboard(Keyblade& keyboard){
	if(keyboard.get_key('E').was_just_pressed()){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
/*
	if(keyboard.get_key('w').is_pressed()){
		pac_man.set_input_dir(Cardinal::North);
	}else if(keyboard.get_key('s').is_pressed()){
		pac_man.set_input_dir(Cardinal::South);
	}else if(keyboard.get_key('a').is_pressed()){
		pac_man.set_input_dir(Cardinal::West);
	}else if(keyboard.get_key('d').is_pressed()){
		pac_man.set_input_dir(Cardinal::East);
	}*/
}

void Tower_State::check_gamepad(Gamepad& gamepad){
	if(gamepad.was_just_pressed(GAMEPAD_START)){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
/*
	if(gamepad.was_just_pressed(GAMEPAD_A)){
	}
	if(gamepad.get_left_stick_y()>0){
		pac_man.set_input_dir(Cardinal::South);
	}else if(gamepad.get_left_stick_y()<0 ){
		pac_man.set_input_dir(Cardinal::North);
	}else if(gamepad.get_left_stick_x()<0 ){
		pac_man.set_input_dir(Cardinal::West);
	}else if(gamepad.get_left_stick_x()>0 ){
		pac_man.set_input_dir(Cardinal::East);
	}*/
}
