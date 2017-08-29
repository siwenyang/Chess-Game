#include "knight.h"
#include "piece.h"
#include <vector>
using namespace std;

Knight::Knight(int r, int c,char name, char colour, string id,bool isMoved):Piece(r,c,name,colour,id,isMoved){
	setRange();
}

void Knight::setRange(){
	int x[] = {1,2,2,1,-1,-2,-2,-1};
	int y[] = {2,1,-1,-2,-2,-1,1,2};
	int ar,ac;
	pair<int,int> add;
	for (int i = 0; i < 8; ++i){
		ar = r + y[i];
		ac = c + x[i];
		if ((ar >= 0) && (ar < 8) && (ac >= 0) && (ac < 8)) {
			add.first = ar;
			add.second = ac;
			range.emplace_back(add);
		} else {
			continue;
		}
	}
}


