#ifndef _PLAYERAI1_H_
#define _PLAYERAI1_H_
#include "player.h"

class Game;

class PlayerAI1 : public Player{
public:
    PlayerAI1(Game* game, char team);
    void makeMove();
};

#endif
