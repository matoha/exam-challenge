#ifndef SPRAVCA_H
#define SPRAVCA_H
#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "head.h"
#include "anino.h"
#include "bonus.h"
#include "prekazka.h"
#include <math.h>
#include "images.h"
#include "music.h"
using namespace std;

class Spravca{
	private:
		DATAFILE *images, *music;
		BITMAP *buffer_vsetko, *buffer_objekty;
		Head *head;
		Anino *anino;
		Prekazka *prva, *posledna;
		Bonus *bonus;
		int level, step_speed, step_length, anino_speed, zorne_pole_length, zorne_pole_angle, anino_pohni_pocet, anino_pohni_const, red_head_x, red_head_y, green_head_x, green_head_y, odpisovanie, anino_pohyb_x, anino_pohyb_y, bonus_time, celkovy_time, bonus_last_time, bonus_last_type;
		
		bool c1, fail, odpisane, bonus_last_bool;
		SAMPLE *s_portal, *s_krok, *s_fail, *s_opisane, *s_win, *s_ceruzka, *s_bonus;
		BITMAP *anino_down, *anino_up, *anino_left, *anino_right, *b_chair, *b_info_bar, *b_pozadie, *b_win, *b_u_red_fast, *b_u_red_slow, *b_u_green_fast, *b_u_green_slow, *b_u_time, *b_u_level, *b_time_mini, *b_odpisovanie_mini, *b_level_mini, *b_bonus_mini, *b_help_mini, *loading, *head_brown, *head_green, *head_up, *head_right, *head_down, *head_left;
	protected:
	public:
		Spravca();
		~Spravca();
		void NovyLevel();
		void PrvyLevel();
		void Pohni(int kam);
		
		//void Pricap();
		int GetStepSpeed(){return step_speed;}
		int GetStepLength(){return step_length;}
		int GetAninoSpeed(){return anino_speed;}
		int GetLevel(){return level;}
		int MozeSaPohnut(int smer);
		bool GetC1(){return c1;}
		bool GetFail(){return fail;}
		
		void SetStepSpeed(int step_speed1){step_speed = step_speed1;}
		void SetStepLength(int step_length1){step_length = step_length1;}
		void SetAninoSpeed(int anino_speed1){anino_speed = anino_speed1;}
		void SetLevel(int level1){level = level1;}
		void SetC1(bool c1_1){c1 = c1_1;}	
		void Help();	
		void StopMusic(){stop_sample(s_ceruzka);}
};

#endif
