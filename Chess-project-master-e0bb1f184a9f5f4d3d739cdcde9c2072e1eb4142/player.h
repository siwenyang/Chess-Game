#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "game.h"

class Player {
protected:
	Game *g;
	char team;
public:
    Player(Game *game, char team);
	virtual void makeMove() = 0;
	virtual ~Player() = default;
	char getTeam();
};

#endif

