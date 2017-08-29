#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "piece.h"

class Queen : public Piece {
public:
	Queen(int r, int c,char name, char colour, std::string id,bool isMoved);
	~Queen() = default;
	void setRange();
};


#endif