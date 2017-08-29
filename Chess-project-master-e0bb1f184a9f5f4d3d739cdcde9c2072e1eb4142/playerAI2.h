#ifndef _PLAYERAI2_H_
#define _PLAYERAI2_H_
#include "player.h"

class Game;

class PlayerAI2 : public Player{
public:
    PlayerAI2(Game* game, char team);
    void makeMove();
};

#endif
