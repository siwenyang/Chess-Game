#ifndef _PAWN_H_
#define _PAWN_H_
#include "piece.h"

class Pawn : public Piece {
public:
	Pawn(int r, int c,char name, char colour, std::string id, bool isMoved);
	~Pawn() = default;
	void setRange();
	bool getInitPos();
};


#endif