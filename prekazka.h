#ifndef PREKAZKA_H
#define PREKAZKA_H
#include <allegro.h>

class Prekazka{
	private:
		int x, y, width, height;
		BITMAP *obrazok;
		Prekazka *dalsia;
	public:
		Prekazka();
		int GetX(){return x;}
		int GetY(){return y;}	
		int GetWidth(){return width;}
		int GetHeight(){return height;}	
		int GetX2(){return x + width;}
		int GetY2(){return y + height;}
		BITMAP* GetObrazok(){return obrazok;}
		Prekazka* GetDalsia(){return dalsia;}

		void SetX(int x1){x = x1;}
		void SetY(int y1){y = y1;}
		void SetWidth(int width1){width = width1;}
		void SetHeight(int height1){height = height1;}	
		void SetX2(int x2_1){width = x2_1 - x;}
		void SetY2(int y2_1){height = y2_1 - y;}
		void SetDalsia(Prekazka *dalsia1){dalsia = dalsia1;}
		void SetObrazok(BITMAP *obrazok1){obrazok = obrazok1;}	
};

#endif
