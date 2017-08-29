#ifndef _PLAYERAI3_H_
#define _PLAYERAI3_H_
#include "player.h"

class Game;

class PlayerAI3 : public Player{
public:
    PlayerAI3(Game* g, char team);
    void makeMove();
};

#endif