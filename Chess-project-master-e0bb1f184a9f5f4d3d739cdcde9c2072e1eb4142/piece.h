#ifndef _PIECE_H_
#define _PIECE_H_
#include <string>
#include <vector>

class Piece {
protected:
	int r, c;
	char name;
	char colour;
	std::string id;
	std::vector<std::pair<int,int>> range;
	bool isMoved;
public:
	Piece(int r, int c, char name, char colour, std::string id,bool isMoved);
	virtual ~Piece() = default;
	char getName();
	int getRow();
	int getCol();
	void setRow(int r);
	void setCol(int c);
	std::string getID();
	char getColour();
	virtual void setRange() = 0;
	std::vector<std::pair<int,int> > getRange();
	bool getIsMoved();
	void setIsMoved(bool set);
};

#endif