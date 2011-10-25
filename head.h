#ifndef HEAD_H
#define HEAD_H
#include <allegro.h>

class Head{
	private:
		int x, y, oldx, oldy, smer;
		BITMAP *obrazok;
	public:
		Head();
		int GetX(){return x;}
		int GetY(){return y;}	
		int GetOldX(){return oldx;}
		int GetOldY(){return oldy;}
		int GetSmer(){return smer;}	
		BITMAP* GetObrazok(){return obrazok;}	

		void SetX(int x1){x = x1;}
		void SetY(int y1){y = y1;}
		void SetOldX(int oldx1){oldx = oldx1;}
		void SetOldY(int oldy1){oldy = oldy1;}
		void SetSmer(int smer1){smer = smer1;}
		void SetObrazok(BITMAP *obrazok1){obrazok = obrazok1;}	
};

#endif
