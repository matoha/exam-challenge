#include "head.h"

Head::Head(){
	x = y = oldx = oldy = 0;
	smer = 2;
	obrazok = load_bitmap("head_up.bmp", NULL);
}
