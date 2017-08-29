#include "rook.h"
#include "piece.h"
#include <vector>

using namespace std;

Rook::Rook(int r, int c, char name, char colour, string id,bool isMoved):Piece(r, c, name, colour, id,isMoved){
	setRange();
}

void Rook::setRange(){
	int x[] = {0,0,1,-1};
	int y[] = {1,-1,0,0};
	int ar, ac;
	std::pair<int,int> add;
	for (int i = 0; i<4; ++i)
	{
	    for (int k = 0; k < 8; ++k)
	    {
		    ar = r + k * y[i];
		    ac = c + k * x[i];
		    if ((ar >= 0) && (ar < 8) && (ac >= 0) && (ac < 8))
	    	{
			    add.first = ar;
			    add.second = ac;
			    range.emplace_back(add);
		    }
		    else
		    {
			    break;
		    }
		}
	}
}
	