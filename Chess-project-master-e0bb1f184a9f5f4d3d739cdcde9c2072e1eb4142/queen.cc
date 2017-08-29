#include "queen.h"
#include "piece.h"
#include <vector>

using namespace std;

Queen::Queen(int r, int c, char name, char colour, string id,bool isMoved):Piece(r, c, name, colour, id,isMoved){
	setRange();
}

void Queen::setRange(){
	int x[] = {1,0,-1,-1,-1,0,1,1};
	int y[] = {1,1,1,0,-1,-1,-1,0};
	int ar, ac;
	std::pair<int,int> add;
	for (int i = 0; i<8; ++i) {
		for (int k = 1; k < 8; ++k) {
			ar = r + k * y[i];
			ac = c + k * x[i];
			if ((ar >= 0) && (ar < 8) && (ac >= 0) && (ac < 8)) {
				add.first = ar;
				add.second = ac;
				range.emplace_back(add);
			} else {
				break;
			}
		}
	}
}