#include "anino.h"

Anino::Anino(){
	x = y = oldx = oldy = 0;
	smer = 3;
	obrazok = load_bitmap("data/images/anino_down.bmp", NULL);
}
