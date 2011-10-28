#include "anino.h"

Anino::Anino(){
	x = y = oldx = oldy = 0;
	smer = 3;
	obrazok = load_bitmap("anino_down.bmp", NULL);
}
