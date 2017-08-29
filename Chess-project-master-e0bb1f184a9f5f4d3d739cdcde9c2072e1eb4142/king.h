#ifndef _KING_H_
#define _KING_H_
#include "piece.h"

class King : public Piece {
public:
	King(int r, int c,char name, char colour, std::string id,bool isMoved);
	~King() = default;
	void setRange();
};


#endif