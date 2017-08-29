#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "piece.h"

class Bishop : public Piece {
public:
	Bishop(int r, int c,char name, char colour, std::string id,bool isMoved);
	~Bishop() = default;
	void setRange();
};


#endif