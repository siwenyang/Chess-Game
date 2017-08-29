#include "king.h"
#include "piece.h"
#include <vector>

using namespace std;

King::King(int r, int c, char name, char colour, string id,bool isMoved):Piece(r, c, name, colour, id,isMoved){
	setRange();
}

void King::setRange(){
	int x[] = {1,0,-1,-1,-1,0,1,1,2,-2};
	int y[] = {1,1,1,0,-1,-1,-1,0,0,0};
	int ar, ac;
	std::pair<int,int> add;
	for (int i = 0; i<10; ++i)
	{
		ar = r + y[i];
		ac = c + x[i];
		if ((ar >= 0) && (ar < 8) && (ac >= 0) && (ac < 8))
		{
			add.first = ar;
			add.second = ac;
			range.emplace_back(add);
		}
		else
		{
			continue;
		}
	}
}