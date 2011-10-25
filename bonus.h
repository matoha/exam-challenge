#ifndef BONUS_H
#define BONUS_H
#include <allegro.h>

class Bonus{
	private:
		int x, y, typ;
		BITMAP *obrazok;
	public:
		Bonus();
		int GetX(){return x;}
		int GetY(){return y;}	
		int GetTyp(){return typ;}	
		BITMAP* GetObrazok(){return obrazok;}

		void SetX(int x1){x = x1;}
		void SetY(int y1){y = y1;}
		void SetTyp(int typ1){typ = typ1;}
		void SetObrazok(BITMAP *obrazok1){obrazok = obrazok1;}	
};

#endif
