#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "piece.h"

class Knight : public Piece {
public:
	Knight(int r, int c,char name, char colour, std::string id,bool isMoved);
	~Knight() = default;
	void setRange();
};


#endif
