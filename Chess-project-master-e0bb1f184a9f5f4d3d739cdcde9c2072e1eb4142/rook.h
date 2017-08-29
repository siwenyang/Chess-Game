#ifndef _ROOK_H_
#define _ROOK_H_
#include "piece.h"

class Rook : public Piece {
public:
	Rook(int r, int c,char name, char colour, std::string id,bool isMoved);
	~Rook() = default;
	void setRange();
};


#endif