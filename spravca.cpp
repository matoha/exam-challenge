#include "spravca.h"

Spravca::Spravca(){
	head = new Head();
	anino = new Anino();
	step_length = 4;
	step_speed = 20; // = 50Hz
	zorne_pole_angle = 120;
	zorne_pole_length = 300;
		loading = load_bitmap("data/images/loading.bmp", NULL);
	blit(loading, screen, 0, 0, 200, 200, SCREEN_W, SCREEN_H);
	anino_up = load_bitmap("data/images/anino_up.bmp", NULL);
	anino_down = load_bitmap("data/images/anino_down.bmp", NULL);
	anino_left = load_bitmap("data/images/anino_left.bmp", NULL);
	anino_right = load_bitmap("data/images/anino_right.bmp", NULL);
	b_chair = load_bitmap("data/images/chair.bmp", NULL);
	b_info_bar = load_bitmap("data/images/info_bar.bmp", NULL);
	b_pozadie = load_bitmap("data/images/podlaha3.bmp", NULL);
	b_win = load_bitmap("data/images/win.bmp", NULL);
	b_u_green_fast = load_bitmap("data/images/u_green_fast.bmp", NULL);
	b_u_green_slow = load_bitmap("data/images/u_green_slow.bmp", NULL);
	b_u_red_fast = load_bitmap("data/images/u_red_fast.bmp", NULL);
	b_u_red_slow = load_bitmap("data/images/u_red_slow.bmp", NULL);
	b_u_time = load_bitmap("data/images/u_time.bmp", NULL);
	b_u_level = load_bitmap("data/images/u_level.bmp", NULL);
	b_time_mini = load_bitmap("data/images/time_mini.bmp", NULL);
	b_level_mini = load_bitmap("data/images/level_mini.bmp", NULL);
	b_odpisovanie_mini = load_bitmap("data/images/odpisovanie_mini.bmp", NULL);
	b_bonus_mini = load_bitmap("data/images/bonus_mini.bmp", NULL);
	b_help_mini = load_bitmap("data/images/help_mini.bmp", NULL);
	level = 0;
	c1 = false;
	s_portal = load_sample("data/music/portal.wav");
	s_krok = load_sample("data/music/krok.wav");
	s_fail = load_sample("data/music/likvidovat.wav");
	s_opisane = load_sample("data/music/opisane.wav");
	s_win = load_sample("data/music/win.wav");
	s_ceruzka = load_sample("data/music/ceruzka.wav");
	s_bonus = load_sample("data/music/bonus.wav");
	
	play_sample(s_ceruzka, 255, 127, 1000, TRUE);
	
	bonus = new Bonus();
	
	NovyLevel();
}
void Spravca::PrvyLevel(){
	level = 1;
	
	head -> SetSmer(2);
	head -> SetObrazok(load_bitmap("data/images/head_up.bmp", NULL));
	
	cout << "Level: " << level << endl;
	
	if(level > 1){
		play_sample(s_win, 255, 128, 1000, FALSE);
		draw_sprite(screen, b_win, SCREEN_W / 2 - 200, SCREEN_H / 2 - 100);
		while(!(key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4]) || key[KEY_ENTER]));
		while(key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4]) || key[KEY_ENTER]);	
	}
	
	if(level >= 2){
		while(prva != NULL){
			Prekazka *pp = prva;
			prva = prva -> GetDalsia();
			delete pp;
		}
	}

	prva = posledna = NULL;
	
	fail = false;
	anino_pohyb_x = 1;
	anino_pohyb_y = 0;
	step_length = 4;
	bonus_time = 0;
	celkovy_time = 0;
	bonus_last_time = 0;
	bonus_last_bool = false;
	bonus_last_type = -1;

	int r = rand() % 3;
	if(r == 2) r = 3;
	anino -> SetSmer(r);
	if(anino -> GetSmer() == 0) {
		anino_pohni_const = 200;
		anino_pohyb_x--;
	} else if(anino -> GetSmer() == 1) {
		anino_pohni_const = 200;
		anino_pohyb_x++;
	} else if(anino -> GetSmer() == 3) {
		anino_pohni_const = 160;
		anino_pohyb_y++;
	}

	anino_pohni_pocet = 0;
	odpisovanie = 0;
	odpisane = false;
	anino_speed = floor(level / 5) + 1;

	head -> SetX(50);
	head -> SetOldX(50);
	head -> SetY(50);
	head -> SetOldY(50);
	
	anino -> SetX(185);
	anino -> SetY(155);

	prva = posledna = new Prekazka();
	prva -> SetX(240);
	prva -> SetY(81);
	//prva -> SetWidth(160);
	//prva -> SetHeight(80);
	prva -> SetObrazok(load_bitmap("data/images/katedra.bmp", NULL));

	int green_head_random = rand() % 15;
	int red_head_random;
	do {red_head_random = rand() % 15;} while (red_head_random == green_head_random);
	
	Prekazka *pp = NULL;
	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 5; i++){
			pp = posledna;
			posledna = new Prekazka();
			posledna -> SetX(i * 200 + 40);
			posledna -> SetY(j * 160 + 200);
			pp -> SetDalsia(posledna);
			
			if(red_head_random != 5 * j + i){
				pp = posledna;
				posledna = new Prekazka();
				posledna -> SetX(i * 200 + 85);
				posledna -> SetY(j * 160 + 271);
				if(green_head_random == 5 * j + i) {
					posledna -> SetObrazok(load_bitmap("data/images/head_green.bmp", NULL));
					green_head_x = i * 200 + 85;
					green_head_y = j * 160 + 271;
				}
				else posledna -> SetObrazok(load_bitmap("data/images/head_brown.bmp", NULL));
				posledna -> SetWidth(40);
				posledna -> SetHeight(40);
				pp -> SetDalsia(posledna);
			} else {
				red_head_x = i * 200 + 85;
				red_head_y = j * 160 + 271;
				head -> SetX(i * 200 + 85);
				head -> SetY(j * 160 + 271);
			}
		}
	}		
	//if(level != 1) play_sample(s_portal, 255, 128, 1000, FALSE);

	BITMAP *head_brown, *head_green, *head_up, *head_right, *head_down, *head_left;
	head_brown = load_bitmap("data/images/head_broen.bmp", NULL);
	head_green = load_bitmap("data/images/head_green.bmp", NULL);	
	head_up = load_bitmap("data/images/head_up.bmp", NULL);
	head_right = load_bitmap("data/images/head_right.bmp", NULL);
	head_down = load_bitmap("data/images/head_down.bmp", NULL);
	head_left = load_bitmap("data/images/head_left.bmp", NULL);
	
	buffer_vsetko = create_bitmap(SCREEN_W, SCREEN_H);
	clear_to_color(buffer_vsetko, makecol(255, 255, 175));
	buffer_objekty = create_bitmap(SCREEN_W, SCREEN_H);
	clear_to_color(buffer_objekty, makecol(255, 0, 255));
	blit(head_up, buffer_objekty, 0, 0, head -> GetX(), head -> GetY(), 40, 40);

	draw_sprite(buffer_vsetko, buffer_objekty, 0, 0);
	destroy_bitmap(head_brown);
	destroy_bitmap(head_green);
	destroy_bitmap(head_up);
	destroy_bitmap(head_right);
	destroy_bitmap(head_down);
	destroy_bitmap(head_left);
	Pohni(-1); //vykresli sa obrazovka
}
void Spravca::NovyLevel(){
	level++;
	
	head -> SetSmer(2);
	head -> SetObrazok(load_bitmap("data/images/head_up.bmp", NULL));
	
	cout << "Level: " << level << endl;
	
	if(level > 1){
		play_sample(s_win, 255, 128, 1000, FALSE);
		draw_sprite(screen, b_win, SCREEN_W / 2 - 200, SCREEN_H / 2 - 100);
		while(!(key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4]) || key[KEY_ENTER]));
		while(key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4]) || key[KEY_ENTER]);	
	}
	
	if(level >= 2){
		while(prva != NULL){
			Prekazka *pp = prva;
			prva = prva -> GetDalsia();
			delete pp;
		}
	}

	prva = posledna = NULL;
	
	fail = false;
	anino_pohyb_x = 1;
	anino_pohyb_y = 0;
	step_length = 4;
	bonus_time = 0;
	celkovy_time = 0;
	bonus_last_time = 0;
	bonus_last_bool = false;
	bonus_last_type = -1;

	int r = rand() % 3;
	if(r == 2) r = 3;
	anino -> SetSmer(r);
	if(anino -> GetSmer() == 0) {
		anino_pohni_const = 200;
		anino_pohyb_x--;
	} else if(anino -> GetSmer() == 1) {
		anino_pohni_const = 200;
		anino_pohyb_x++;
	} else if(anino -> GetSmer() == 3) {
		anino_pohni_const = 160;
		anino_pohyb_y++;
	}

	anino_pohni_pocet = 0;
	odpisovanie = 0;
	odpisane = false;
	anino_speed = floor(level / 5) + 1;

	head -> SetX(50);
	head -> SetOldX(50);
	head -> SetY(50);
	head -> SetOldY(50);
	
	anino -> SetX(185);
	anino -> SetY(155);

	prva = posledna = new Prekazka();
	prva -> SetX(240);
	prva -> SetY(81);
	//prva -> SetWidth(160);
	//prva -> SetHeight(80);
	prva -> SetObrazok(load_bitmap("data/images/katedra.bmp", NULL));

	int green_head_random = rand() % 15;
	int red_head_random;
	do {red_head_random = rand() % 15;} while (red_head_random == green_head_random);
	
	Prekazka *pp = NULL;
	for(int j = 0; j < 3; j++){
		for(int i = 0; i < 5; i++){
			pp = posledna;
			posledna = new Prekazka();
			posledna -> SetX(i * 200 + 40);
			posledna -> SetY(j * 160 + 200);
			pp -> SetDalsia(posledna);
			
			if(red_head_random != 5 * j + i){
				pp = posledna;
				posledna = new Prekazka();
				posledna -> SetX(i * 200 + 85);
				posledna -> SetY(j * 160 + 271);
				if(green_head_random == 5 * j + i) {
					posledna -> SetObrazok(load_bitmap("data/images/head_green.bmp", NULL));
					green_head_x = i * 200 + 85;
					green_head_y = j * 160 + 271;
				}
				else posledna -> SetObrazok(load_bitmap("data/images/head_brown.bmp", NULL));
				posledna -> SetWidth(40);
				posledna -> SetHeight(40);
				pp -> SetDalsia(posledna);
			} else {
				red_head_x = i * 200 + 85;
				red_head_y = j * 160 + 271;
				head -> SetX(i * 200 + 85);
				head -> SetY(j * 160 + 271);
			}
		}
	}		
	//if(level != 1) play_sample(s_portal, 255, 128, 1000, FALSE);

	BITMAP *head_brown, *head_green, *head_up, *head_right, *head_down, *head_left;
	head_brown = load_bitmap("data/images/head_broen.bmp", NULL);
	head_green = load_bitmap("data/images/head_green.bmp", NULL);	
	head_up = load_bitmap("data/images/head_up.bmp", NULL);
	head_right = load_bitmap("data/images/head_right.bmp", NULL);
	head_down = load_bitmap("data/images/head_down.bmp", NULL);
	head_left = load_bitmap("data/images/head_left.bmp", NULL);
	
	buffer_vsetko = create_bitmap(SCREEN_W, SCREEN_H);
	clear_to_color(buffer_vsetko, makecol(255, 255, 175));
	buffer_objekty = create_bitmap(SCREEN_W, SCREEN_H);
	clear_to_color(buffer_objekty, makecol(255, 0, 255));
	blit(head_up, buffer_objekty, 0, 0, head -> GetX(), head -> GetY(), 40, 40);

	draw_sprite(buffer_vsetko, buffer_objekty, 0, 0);
	destroy_bitmap(head_brown);
	destroy_bitmap(head_green);
	destroy_bitmap(head_up);
	destroy_bitmap(head_right);
	destroy_bitmap(head_down);
	destroy_bitmap(head_left);
	Pohni(-1); //vykresli sa obrazovka
}

void Spravca::Pohni(int kam){
	int PoholSa = 0;
	head -> SetOldX(head -> GetX());
	head -> SetOldY(head -> GetY());
	switch(kam){//kam: -1-anino 0-lavo 1-pravo 2-hore 3-dole
		case 0: 
			head -> SetObrazok(load_bitmap("data/images/head_left.bmp", NULL));
			head -> SetSmer(0);
			head -> SetX(head -> GetX() - MozeSaPohnut(0));
			break;
		case 1: 
			head -> SetObrazok(load_bitmap("data/images/head_right.bmp", NULL));
			head -> SetSmer(1);
			head -> SetX(head -> GetX() + MozeSaPohnut(1));
			break;
		case 2: 
			head -> SetObrazok(load_bitmap("data/images/head_up.bmp", NULL));
			head -> SetSmer(2);
			head -> SetY(head -> GetY() - MozeSaPohnut(2));
			break;
		case 3: 
			head -> SetObrazok(load_bitmap("data/images/head_down.bmp", NULL));
			head -> SetSmer(3);
			head -> SetY(head -> GetY() + MozeSaPohnut(3));
			break;
	}
	if(anino_pohni_const - anino_pohni_pocet < anino_speed){
		int as = anino_pohni_const - anino_pohni_pocet;
		switch(anino -> GetSmer()){
			case 0: anino -> SetX(anino -> GetX() - as); break;	
			case 1: anino -> SetX(anino -> GetX() + as); break;	
			case 2: anino -> SetY(anino -> GetY() - as); break;	
			case 3: anino -> SetY(anino -> GetY() + as); break;
		}
		anino_pohni_pocet = anino_pohni_const;
	} else {
		switch(anino -> GetSmer()){
			case 0: anino -> SetX(anino -> GetX() - anino_speed); break;	
			case 1: anino -> SetX(anino -> GetX() + anino_speed); break;	
			case 2: anino -> SetY(anino -> GetY() - anino_speed); break;	
			case 3: anino -> SetY(anino -> GetY() + anino_speed); break;
		}
		anino_pohni_pocet += anino_speed;
	}

	if(anino_pohni_pocet == anino_pohni_const){
		int r;
		if(anino_pohyb_x == 0 && anino_pohyb_y != 0 && anino_pohyb_y != 3) {
			r = rand() % 3;
			if(r == 0) r = 3;
		} else if(anino_pohyb_x == 5 && anino_pohyb_y != 0 && anino_pohyb_y != 3) {
			r = rand() % 3;
			if(r == 1) r = 3;
		} else if(anino_pohyb_y == 0 && anino_pohyb_x != 0 && anino_pohyb_x != 5) {
			r = rand() % 3;
			if(r == 2) r = 3;
		} else if(anino_pohyb_y == 3 && anino_pohyb_x != 0 && anino_pohyb_x != 5) {
			r = rand() % 3;
		} else if(anino_pohyb_x == 0 && anino_pohyb_y == 0) {
			r = rand() % 2;
			if(r == 0) r = 3;
		} else if(anino_pohyb_x == 5 && anino_pohyb_y == 0) {
			r = rand() % 2;
			if(r == 1) r = 3;
		} else if(anino_pohyb_x == 0 && anino_pohyb_y == 3) {
			r = rand() % 2;
			if(r == 0) r = 2;
		} else if(anino_pohyb_x == 5 && anino_pohyb_y == 3) {
			r = rand() % 2;
			if(r == 1) r = 2;
		} else {
			r = rand() % 4;
		}
		
		anino -> SetSmer(r);
		
		if(anino -> GetSmer() == 0) {
			anino_pohni_const = 200;
			anino_pohyb_x--;
		} else if(anino -> GetSmer() == 1) {
			anino_pohni_const = 200;
			anino_pohyb_x++;
		} else if(anino -> GetSmer() == 2) {
			anino_pohni_const = 160;
			anino_pohyb_y--;
		} else if(anino -> GetSmer() == 3) {
			anino_pohni_const = 160;
			anino_pohyb_y++;
		}
		
		anino_pohni_pocet = 0;
	}
		
	//if(PoholSa == 1){//vratim naspat veci ktore boli pod playerom
	blit(b_pozadie, buffer_objekty, 0, 0, 0, 40, SCREEN_W, SCREEN_H - 40);
	int zorne_x = head -> GetX() - anino -> GetX();
	int zorne_y = head -> GetY() - anino -> GetY();
	int zorne_stolicka_x = red_head_x - anino -> GetX();
	int zorne_stolicka_y = red_head_y - anino -> GetY();
	int kruh_x = sqrt(zorne_pole_length * zorne_pole_length / 2);
	bool prehral = false;
	int x = red_head_x;
	int y = red_head_y;
	int hx = head -> GetX();
	int hy = head -> GetY();
	switch(anino -> GetSmer()){
		case 0: 
			draw_sprite(buffer_objekty, anino_left, anino -> GetX() - 560, anino -> GetY() - 280);
			if(
			   !(// hrac nie je na stolicke
			     head -> GetSmer() == 2 &&
			     hx >= x - 15 && 
			     hx <= x + 15 &&
	  		     hy >= y - 2 && 
			     hy <= y + 5
			    ) &&
			    (
			     (// hrac je v zornom poli
			      sqrt(zorne_x * zorne_x + zorne_y * zorne_y) < zorne_pole_length + 20 &&
			      head -> GetY() + 40 >= head -> GetX() + anino -> GetY() - anino -> GetX() &&
			      head -> GetY() - 40 <= - head -> GetX() + anino -> GetY() + anino -> GetX()
			     ) || 
			     (// stolicka je v zornom poli
			      sqrt(zorne_stolicka_x * zorne_stolicka_x + zorne_stolicka_y * zorne_stolicka_y) < zorne_pole_length + 20 &&
			      red_head_y + 40 >= red_head_x + anino -> GetY() - anino -> GetX() &&
			      red_head_y - 40 <= - red_head_x + anino -> GetY() + anino -> GetX()
			     )
			    )		   
			  ) prehral = true; 
			break;
		case 1: 
			draw_sprite(buffer_objekty, anino_right, anino -> GetX(), anino -> GetY() - 280); 
			if(
			   !(// hrac nie je na stolicke
			     head -> GetSmer() == 2 &&
			     hx >= x - 15 && 
			     hx <= x + 15 &&
	  		     hy >= y - 2 && 
			     hy <= y + 5
			    ) &&
			    (
			     (// hrac je v zornom poli
			      sqrt(zorne_x * zorne_x + zorne_y * zorne_y) < zorne_pole_length + 20 &&
			      head -> GetY() - 40 <= head -> GetX() + anino -> GetY() - anino -> GetX() &&
			      head -> GetY() + 40 >= - head -> GetX() + anino -> GetY() + anino -> GetX()
			     ) || 
			     (// stolicka je v zornom poli
			      sqrt(zorne_stolicka_x * zorne_stolicka_x + zorne_stolicka_y * zorne_stolicka_y) < zorne_pole_length + 20 &&
			      red_head_y - 40 <= red_head_x + anino -> GetY() - anino -> GetX() &&
			      red_head_y + 40 >= - red_head_x + anino -> GetY() + anino -> GetX()
			     )
			    )		   
			  ) prehral = true; 
			break;
		case 2: 
			draw_sprite(buffer_objekty, anino_up, anino -> GetX() - 280, anino -> GetY() - 560); 
			if(
			   !(// hrac nie je na stolicke
			     head -> GetSmer() == 2 &&
			     hx >= x - 15 && 
			     hx <= x + 15 &&
	  		     hy >= y - 2 && 
			     hy <= y + 5
			    ) &&
			    (
			     (// hrac je v zornom poli
			      sqrt(zorne_x * zorne_x + zorne_y * zorne_y) < zorne_pole_length + 20 &&
		     	      head -> GetY() - 40 <= head -> GetX() + anino -> GetY() - anino -> GetX() &&
			      head -> GetY() - 40 <= - head -> GetX() + anino -> GetY() + anino -> GetX()
			     ) || 
			     (// stolicka je v zornom poli
			      sqrt(zorne_stolicka_x * zorne_stolicka_x + zorne_stolicka_y * zorne_stolicka_y) < zorne_pole_length + 20 &&
			      red_head_y - 40 <= red_head_x + anino -> GetY() - anino -> GetX() &&
			      red_head_y - 40 <= - red_head_x + anino -> GetY() + anino -> GetX()
			     )
			    )		   
			  ) prehral = true;
			break;
		case 3: 
			draw_sprite(buffer_objekty, anino_down, anino -> GetX() - 280, anino -> GetY()); 
			if(
			   !(// hrac nie je na stolicke
			     head -> GetSmer() == 2 &&
			     hx >= x - 15 && 
			     hx <= x + 15 &&
	  		     hy >= y - 2 && 
			     hy <= y + 5
			    ) &&
			    (
			     (// hrac je v zornom poli
			      sqrt(zorne_x * zorne_x + zorne_y * zorne_y) < zorne_pole_length + 20 &&
			      head -> GetY() + 40 >= head -> GetX() + anino -> GetY() - anino -> GetX() &&
			      head -> GetY() + 40 >= - head -> GetX() + anino -> GetY() + anino -> GetX()
			     ) || 
			     (// stolicka je v zornom poli
			      sqrt(zorne_stolicka_x * zorne_stolicka_x + zorne_stolicka_y * zorne_stolicka_y) < zorne_pole_length + 20 &&
			      red_head_y + 40 >= red_head_x + anino -> GetY() - anino -> GetX() &&
			      red_head_y + 40 >= - red_head_x + anino -> GetY() + anino -> GetX()
			     )
			    )		   
			  ) prehral = true;
			break;
	}
	//odpisovanie
	if(
	   odpisane == false &&
	   head -> GetSmer() == 2 &&
	   (
	    (
	     head -> GetX() + 49 >= green_head_x &&
	     head -> GetX() + 35 <= green_head_x &&
	     head -> GetY() + 2 >= green_head_y &&
	     head -> GetY() - 5 <= green_head_y
	    ) ||
	    (
	     head -> GetX() + -38 >= green_head_x &&
	     head -> GetX() + -45 <= green_head_x &&
	     head -> GetY() + 2 >= green_head_y &&
	     head -> GetY() - 5 <= green_head_y
	    )
	   )
	  ) odpisovanie++;
	
	if(odpisovanie >= 50 * level) {// 1s
		odpisovanie = 0;
		odpisane = true;
		play_sample(s_opisane, 255, 128, 1000, FALSE);
	}

	if(bonus_last_bool == true) bonus_last_time++;
	
	if(bonus_last_time == 500){
		bonus_last_time = 0;
		bonus_last_bool = false;
		switch(bonus_last_type){
			case 0: step_length++; break;
			case 1: anino_speed--; break;
			case 2: anino_speed++; break;
			case 3: step_length--; break;
		}
		bonus_last_type = -1;
	}

	//zobral hrac bonus?
	if(bonus != NULL){
		if(
		    (head -> GetX() - bonus -> GetX()) * (head -> GetX() - bonus -> GetX()) + 
		    (head -> GetY() - bonus -> GetY()) * (head -> GetY() - bonus -> GetY()) <= 1600
		  ) {
		  	play_sample(s_bonus, 255, 128, 1000, FALSE);
		  	switch(bonus -> GetTyp()){
		  		case 0:
		  			switch(bonus_last_type){
						case 0: step_length++; break;
						case 1: anino_speed--; break;
						case 2: anino_speed++; break;
						case 3: step_length--; break;
					}
					step_length--;
		  			bonus_last_time = 0;
		  			bonus_last_type = 0;
		  			bonus_last_bool = true;
		  			break;
		  		case 1:
		  			switch(bonus_last_type){
						case 0: step_length++; break;
						case 1: anino_speed--; break;
						case 2: anino_speed++; break;
						case 3: step_length--; break;
					}
		  			anino_speed++;
		  			bonus_last_time = 0;
		  			bonus_last_type = 1;
		  			bonus_last_bool = true;
		  			break;
		  		case 2:
		  			switch(bonus_last_type){
						case 0: step_length++; break;
						case 1: anino_speed--; break;
						case 2: anino_speed++; break;
						case 3: step_length--; break;
					}
		  			anino_speed--;
		  			bonus_last_time = 0;
		  			bonus_last_type = 2;
		  			bonus_last_bool = true;
		  			break;
		  		case 3:
		  			switch(bonus_last_type){
						case 0: step_length++; break;
						case 1: anino_speed--; break;
						case 2: anino_speed++; break;
						case 3: step_length--; break;
					}
		  			step_length++;
		  			bonus_last_time = 0;
		  			bonus_last_type = 3;
		  			bonus_last_bool = true;
		  			break;
		  		case 4:
		  			switch(bonus_last_type){
						case 0: step_length++; break;
						case 1: anino_speed--; break;
						case 2: anino_speed++; break;
						case 3: step_length--; break;
					}
		  			celkovy_time -= 500;
		  			bonus_last_time = 0;
		  			bonus_last_type = -1;
		  			bonus_last_bool = false;
		  			break;
		  		case 5:
		  			switch(bonus_last_type){
						case 0: step_length++; break;
						case 1: anino_speed--; break;
						case 2: anino_speed++; break;
						case 3: step_length--; break;
					}
		  			NovyLevel();
		  			bonus_last_time = 0;
		  			bonus_last_type = -1;
		  			bonus_last_bool = false;
		  			break;
		  	}
		  	bonus -> SetX(-100);	  	
		}
	}
	
	bonus_time++;
	
	//generovanie u-cka (bonusu)
	//typy: 0-red_slow, 1-red_fast, 2-green_slow, 3-green_fast, 4-time, 5-level
	if(bonus_time >= 250){
		bonus -> SetX(-100);
		bonus -> SetY(-100);
		int r = rand() % 3000;
		if(r >= 0 && r <= 5){
			bonus -> SetX(rand() % (SCREEN_W - 40));
			bonus -> SetY(155 + 160 * (rand() % 4));
			bonus_time = 0;
		}
		switch(r){
			case 0:	bonus -> SetTyp(0); bonus -> SetObrazok(b_u_red_slow); break;
			case 1:	bonus -> SetTyp(1); bonus -> SetObrazok(b_u_red_fast); break;
			case 2:	bonus -> SetTyp(2); bonus -> SetObrazok(b_u_green_slow); break;
			case 3:	bonus -> SetTyp(3); bonus -> SetObrazok(b_u_green_fast); break;
			case 4:	bonus -> SetTyp(4); bonus -> SetObrazok(b_u_time); break;
			case 5:	bonus -> SetTyp(5); bonus -> SetObrazok(b_u_level); break;
		}
	}
	
	celkovy_time++;


	Prekazka *p = NULL;
	for(p = prva; p != NULL; p = p -> GetDalsia())
		draw_sprite(buffer_objekty, p -> GetObrazok(), p -> GetX(), p -> GetY());
	draw_sprite(buffer_objekty, bonus -> GetObrazok(), bonus -> GetX(), bonus -> GetY());
	draw_sprite(buffer_objekty, b_chair, red_head_x, red_head_y);
	draw_sprite(buffer_objekty, head -> GetObrazok(), head -> GetX(), head -> GetY());
	
	char c_time[50], c_odpisovanie[50], c_level[50], c_bonus[50];
	sprintf(c_level,"%d", level);
	sprintf(c_time,"%ds", level + 60 - celkovy_time / 50);
	
	draw_sprite(buffer_objekty, b_info_bar, 0, 0);
	
	draw_sprite(buffer_objekty, b_time_mini, 2, 2);
	draw_sprite(buffer_objekty, b_level_mini, 300, 2);
	draw_sprite(buffer_objekty, b_odpisovanie_mini, 600, 2);
	
	draw_sprite(buffer_objekty, b_help_mini, SCREEN_W - 40, SCREEN_H - 40);
	
	switch(bonus_last_type){
		case -1: draw_sprite(buffer_objekty, b_bonus_mini, 900, 0); break;
		case 0: draw_sprite(buffer_objekty, b_u_red_slow, 900, 0); break;
		case 1: draw_sprite(buffer_objekty, b_u_red_fast, 900, 0); break;
		case 2: draw_sprite(buffer_objekty, b_u_green_slow, 900, 0); break;
		case 3: draw_sprite(buffer_objekty, b_u_green_fast, 900, 0); break;
		case 4: draw_sprite(buffer_objekty, b_u_time, 900, 0); break;
		case 5: draw_sprite(buffer_objekty, b_u_level, 900, 0); break;
	}
	
	textout_ex(buffer_objekty, font, c_time, 45, 15, makecol(255, 255, 255), -1);
	textout_ex(buffer_objekty, font, c_level, 343, 15, makecol(255, 255, 255), -1);
	
	if(bonus_last_time == 0) {
		sprintf(c_bonus,"--");
		textout_ex(buffer_objekty, font, c_bonus, 943, 15, makecol(255, 0, 0), -1);	
	}
	else {
		sprintf(c_bonus,"%ds", 10 - bonus_last_time / 50);
		textout_ex(buffer_objekty, font, c_bonus, 943, 15, makecol(255, 255, 255), -1);
	}
	
	if(odpisane == false) {
		sprintf(c_odpisovanie,"%ds", (50 * level - odpisovanie) / 50);
		textout_ex(buffer_objekty, font, c_odpisovanie, 643, 15, makecol(255, 255, 255), -1);
	} else {
		sprintf(c_odpisovanie,"Odpisane!");
		textout_ex(buffer_objekty, font, c_odpisovanie, 643, 15, makecol(0, 255, 0), -1);
	}
	
	vsync();
	blit(buffer_objekty, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	
	if(//vyhral level
	   odpisane == true &&
	   head -> GetSmer() == 2 &&
	   hx >= x - 15 && 
	   hx <= x + 15 &&
	   hy >= y - 2 && 
	   hy <= y + 5
	  ) NovyLevel();
	
	if(celkovy_time >= 50 * level + 3000){//cas na odpisanie + minnuta
		prehral = true;
	}
	
	if(prehral == true) {
		play_sample(s_fail, 255, 128, 1000, FALSE);
		
		draw_sprite(screen, load_bitmap("data/images/fail.bmp", NULL), SCREEN_W / 2 - 200, SCREEN_H / 2 - 100);
			while(! key[KEY_ENTER]);
	while(key[KEY_ENTER]);
		PrvyLevel();
		//fail = true;
	}
}

int Spravca::MozeSaPohnut(int smer){
	Prekazka *p = NULL;
	int l = step_length;
	switch(smer){
		case 0:
			for(p = prva; p != NULL; p = p -> GetDalsia())
				while(
					(head -> GetX() - l < p -> GetX2()) && 
					(head -> GetX() - l > p -> GetX()) &&
					(head -> GetY() + 40 > p -> GetY()) &&
					(head -> GetY() < p -> GetY2()) &&
					l > 0	
				) l--;
			while(head -> GetX() - l < 0 && l > 0) l--;
			return l;
		case 1:
			for(p = prva; p != NULL; p = p -> GetDalsia())
				while(
					(head -> GetX() + 40 + l < p -> GetX2()) && 
					(head -> GetX() + 40 + l > p -> GetX()) &&
					(head -> GetY() + 40 > p -> GetY()) &&
					(head -> GetY() < p -> GetY2()) &&
					l > 0	
				) l--;
			while(head -> GetX() + 40 + l > SCREEN_W && l > 0) l--;
			return l;
		case 2:
			for(p = prva; p != NULL; p = p -> GetDalsia())
				while(
					(head -> GetY() - l > p -> GetY()) &&
					(head -> GetY() - l < p -> GetY2()) &&
					(head -> GetX() < p -> GetX2()) && 
					(head -> GetX() + 40 > p -> GetX()) &&
					l > 0	
				) l--;
			while(head -> GetY() - l < 41 && l > 0) l--;
			return l;
		case 3:
			for(p = prva; p != NULL; p = p -> GetDalsia())
				while(
					(head -> GetY() + 40 + l > p -> GetY()) &&
					(head -> GetY() + 40 + l < p -> GetY2()) &&
					(head -> GetX() < p -> GetX2()) && 
					(head -> GetX() + 40 > p -> GetX()) &&
					l > 0			      
				  ) l--;
			while(head -> GetY() + 40 + l > SCREEN_H && l > 0) l--;
			return l;
	}
}

void Spravca::Help(){
	stop_sample(s_ceruzka);
	blit(load_bitmap("data/images/info1.bmp", NULL), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	while(! key[KEY_ENTER]);
	while(key[KEY_ENTER]);
	blit(load_bitmap("data/images/info2.bmp", NULL), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	while(! key[KEY_ENTER]);
	while(key[KEY_ENTER]);
	blit(load_bitmap("data/images/info3.bmp", NULL), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	while(! key[KEY_ENTER]);
	while(key[KEY_ENTER]);
	blit(load_bitmap("data/images/info4.bmp", NULL), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	while(! key[KEY_ENTER]);
	while(key[KEY_ENTER]);
	blit(load_bitmap("data/images/info5.bmp", NULL), screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	while(! key[KEY_ENTER]);
	while(key[KEY_ENTER]);
	play_sample(s_ceruzka, 255, 127, 1000, TRUE);
}

Spravca::~Spravca(){
	destroy_bitmap(buffer_objekty);
	destroy_bitmap(anino_up);
	destroy_bitmap(anino_down);
	destroy_bitmap(anino_left);
	destroy_bitmap(anino_right);
	destroy_bitmap(b_chair);
	destroy_bitmap(b_info_bar);
	destroy_bitmap(b_pozadie);
	destroy_bitmap(b_u_green_slow);
	destroy_bitmap(b_u_green_fast);
	destroy_bitmap(b_u_red_slow);
	destroy_bitmap(b_u_red_fast);
	destroy_bitmap(b_u_time);
	destroy_bitmap(b_u_level);
	destroy_bitmap(b_win);
	destroy_bitmap(b_time_mini);
	destroy_bitmap(b_level_mini);
	destroy_bitmap(b_odpisovanie_mini);
	destroy_bitmap(b_bonus_mini);
	destroy_bitmap(b_help_mini);
	
	destroy_sample(s_portal);
	destroy_sample(s_krok);
	destroy_sample(s_fail);
	destroy_sample(s_opisane);
	destroy_sample(s_ceruzka);
	destroy_sample(s_win);
	destroy_sample(s_bonus);	
}

