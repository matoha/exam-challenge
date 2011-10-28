//Copyright (c) 2011 Marian Longa & Martin Holicky. All rights reserved. Licensed under CC-BY-ND-NC
#include <allegro.h>
#include <iostream>
#include <stdio.h>
#include "spravca.h"
#include "images2.h"
using namespace std;

volatile int krok = 0;

void ZvysKrok(){
	krok++;
}
END_OF_FUNCTION(ZvysKrok);

int main(){
	allegro_init();
	install_keyboard();
	//install_mouse();
	install_timer();
	install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
	set_color_depth(32);
	if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 700, 0, 0) != 0)
	{
		set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
		allegro_message("Allegro init failure!\nPlease contact us @\n longaster@gmail.com\nwith folowing message:\n%s\n", allegro_error);
		return 1;
	}	
	
	srand(time(NULL));
	BITMAP *loading;
	loading = load_bitmap("loading.bmp", NULL);
	blit(loading, screen, 0, 0, 310, 240, SCREEN_W, SCREEN_H);
	DATAFILE *images2;
	images2 = load_datafile("images2.dat");
	BITMAP *random1, *random2, *random3, *random4, *random5, *random6, *random7, *random8, *random9, *random10, *logo, *credits, *loading2;
	random1 = (BITMAP*) images2[img2_random1].dat;
	loading2 = (BITMAP*) images2[img2_loading2].dat;
	random2 = (BITMAP*) images2[img2_random2].dat;
	random3 = (BITMAP*) images2[img2_random3].dat;
	random4 = (BITMAP*) images2[img2_random4].dat;
	random5 = (BITMAP*) images2[img2_random5].dat;
	random6 = (BITMAP*) images2[img2_random6].dat;
	random7 = (BITMAP*) images2[img2_random7].dat;
	random8 = (BITMAP*) images2[img2_random8].dat;
	random9 = (BITMAP*) images2[img2_random9].dat;
	random10 = (BITMAP*) images2[img2_random10].dat;
	logo = (BITMAP*) images2[img2_logo].dat;
	credits = (BITMAP*) images2[img2_credits].dat;
	LOCK_VARIABLE(krok);
	LOCK_FUNCTION(ZvysKrok);
	
	krok = 0;
	install_int(ZvysKrok, 200);
	while(krok <= 11 || key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4]) || key[KEY_ENTER]){
		if(krok == 0)blit(random1, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	
		if(krok == 1)blit(random2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	
		if(krok == 2)blit(random3, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	
		if(krok == 3)blit(random4, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	
		if(krok == 4)blit(random5, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	
		if(krok == 5)blit(random6, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	
		if(krok == 6)blit(random7, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	
		if(krok == 7)blit(random8, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	
		if(krok == 8)blit(random9, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);	
		if(krok == 9)blit(random10, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
		
	
	}
	remove_int(ZvysKrok);
	krok = 0;
	blit(logo, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	while(! key[KEY_ENTER]);
	while(key[KEY_ENTER]);
	blit(loading2, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	Spravca s;
	
	install_int(ZvysKrok, s.GetStepSpeed()); //nastav timer na 50Hz
	int krok_old = krok;

	while(!(key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4]))){
		if(krok_old != krok){
			krok_old = krok;
		
			if(key[KEY_LEFT] || key[KEY_A]) s.Pohni(0);
			else if(key[KEY_RIGHT] || key[KEY_D]) s.Pohni(1);
			else if(key[KEY_UP] || key[KEY_W]) s.Pohni(2);
			else if(key[KEY_DOWN] || key[KEY_S]) s.Pohni(3);
			else s.Pohni(-1);
			
			if(key[KEY_F1]) s.Help();
			
			if(s.GetFail() == true){
				while(!(key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4]) || key[KEY_ENTER]));
				while(key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4]) || key[KEY_ENTER]);
				break;
			}
		}
	}
	
	while(key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4]));
		
	s.StopMusic();	
	
	remove_int(ZvysKrok);
	krok = 0;
	install_int(ZvysKrok, 2000);
	
	
	blit(credits, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	unload_datafile(images2);
	/*destroy_bitmap(random1);
	destroy_bitmap(random2);
	destroy_bitmap(random3);
	destroy_bitmap(random4);
	destroy_bitmap(random5);
	destroy_bitmap(random6);
	destroy_bitmap(random7);
	destroy_bitmap(random8);
	destroy_bitmap(random9);
	destroy_bitmap(random10);
	destroy_bitmap(logo);
	destroy_bitmap(credits);
	destroy_bitmap(loading2);
	*/
	while(krok == 0) if(key[KEY_ESC] || (key[KEY_ALT] && key[KEY_F4]) || key[KEY_ENTER]) break;
	
	return 0;
}
END_OF_MAIN();
