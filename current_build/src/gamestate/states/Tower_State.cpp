#include "Tower_State.hpp"
#include "../../communal/Communal.hpp"


Tower_State::Tower_State(Imagehandler& imagehandler,Audiohandler& audiohandler):tower_layer("tower_layer"){
	int screen_size_x=1366;
	int screen_size_y=768;
	tower_layer.set_original_size(screen_size_x,screen_size_y);
	tower_layer.set_original_center(screen_size_x/2,screen_size_y/2);
	//std::cout<<"load map"<<std::endl;
	utility_map.add_tileset("../assets/image/tilesets/utility_tileset","utility_tiles");
	platform_map.load_from_file("../assets/maps/dry_run_map.map");
	utility_map.load_from_file("../assets/maps/dry_run_map_utility.map");
	//std::cout<<"set map location"<<std::endl;
	platform_map.set_position(Point(0,0));
	utility_map.set_position(Point(0,0));
	//std::cout<<"load sprites"<<std::endl;
	flier.add_animation("Enemy_Fly_Flying");
	flier.ref_animation(0).set_looping(true);
	load_sprites(imagehandler);
	flier.create(Point(-500,-500));
	state_name="tower_state";

	//std::cout<<"create player"<<std::endl;
	player.create(platform_map.tile_coord_to_position(2,18),platform_map);
	b.Tilemap_Entity::create(Point(0,0),platform_map);
	//std::cout<<"done"<<std::endl;
	update_layer_resolutions();
	//std::cout<<"tower state"<<std::endl;

	spawn_locations.push_back(Point(-200,-200));
	spawn_locations.push_back(Point(2600,-200));
	spawn_locations.push_back(Point(-200,1600));
	spawn_locations.push_back(Point(2600,1600));
}


void Tower_State::update_layer_resolutions(){
	Gamestate::update_layer_resolutions();
	tower_layer.resolve_new_resolution();
}



void Tower_State::load_sprites(Imagehandler& imagehandler){
	imagehandler.load_sprite(background,"core_game_background");
	player.load_animations(imagehandler);
	b.load_animations(imagehandler);
	flier.load_animations(imagehandler);
	imagehandler.load_sprite(lizerd,"lizerd");
	lizerd.scale(7,7);
	lizerd.setPosition(-1900,-100);
	imagehandler.load_sprite(hotbar,"hotbar");
	hotbar.setPosition(500,620);
}


void Tower_State::update(Mousey& mouse, Keyblade& keyboard, Gamepad& gamepad){
	Duration_Check::start("-Tower update");
	Gamestate::update_gui_layer(mouse,keyboard,gamepad);
	tower_layer.setCenter(player.get_center().get_x(),player.get_center().get_y());
	mouse.set_layer(tower_layer);

	if(wave_timer==0){
		wave_timer=wave_timer_max;//*difficulty_level;
		for(int i=0;i<difficulty_level*10;i++){
			int r=random(0,1);
			Enemy_Base* e;
			if(r=1){
				e=new Flier_Enemy;
				*e=flier;
			}else{
				e=new Flier_Enemy;
				*e=flier;
			}

			r=random(0,spawn_locations.size()-1);
			e->create(spawn_locations.at(r));
			enemies.push_back(e);
		}
	}else{
		wave_timer--;
	}


	utility_map.update();

	for(int i=0;i<(int)enemies.size();i++){
		enemies.at(i)->update();
		enemies.at(i)->animate();
	};

	player.update(platform_map,utility_map,mouse,keyboard);
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
	window.draw(lizerd);
	window.draw(utility_map);
	window.draw(platform_map);
	window.draw(player);

	for(int i=0;i<(int)enemies.size();i++){
		window.draw(*enemies.at(i));
	}

	player.animate();

	for(int i=0;i<(int)bullets.size();i++){
		window.draw(bullets.at(i));
		//std::cout<<bullets.at(i).get_position().get_x()<<","<<bullets.at(i).get_position().get_y()<<std::endl;
		bullets.at(i).animate();
	}
	Gamestate::render_gui_layer(window);
	if(player.get_mode()=="placing"){
		window.draw(hotbar);
	}
	Duration_Check::stop("-Tower render");
}
void Tower_State:: execute_data(Data_Packet data){
}

void Tower_State::check_keyboard(Keyblade& keyboard){
	if(keyboard.get_key('E').was_just_pressed()){
		send_data.push_back(Data_Packet("set_state",MANAGER,{"pause_menu"}));
	}
	if(keyboard.get_key('q').was_just_pressed()){
		if(zoom){
			int screen_size_x=5000;
			int screen_size_y=2500;
			tower_layer.set_original_size(screen_size_x,screen_size_y);
			tower_layer.set_original_center(screen_size_x/2,screen_size_y/2);
			zoom=false;
			player.lock_player_controls(true);
		}else{
			int screen_size_x=1366;
			int screen_size_y=768;
			tower_layer.set_original_size(screen_size_x,screen_size_y);
			tower_layer.set_original_center(screen_size_x/2,screen_size_y/2);
			zoom=true;
			player.lock_player_controls(false);
		}
		
	}
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
