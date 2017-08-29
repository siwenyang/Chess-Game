#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "game.h"
#include "player.h"

class Human : public Player{
public:
	Human(Game *g,char team);
	void makeMove();
	~Human() = default;
};

#endif
