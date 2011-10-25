#include "prekazka.h"

Prekazka::Prekazka(){
	dalsia = NULL;
	x = y = 0;
	width = 130;
	height = 70;
	obrazok = load_bitmap("data/images/lavica.bmp", NULL);
}

