#include "head.h"

Head::Head(){
	x = y = oldx = oldy = 0;
	smer = 2;
	obrazok = load_bitmap("data/images/head_up.bmp", NULL);
}
