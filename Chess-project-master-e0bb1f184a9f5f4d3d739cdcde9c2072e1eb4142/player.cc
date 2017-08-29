#include "player.h"
#include "game.h"

Player::Player(Game *game, char team):g{game}, team{team} {}

char Player::getTeam(){return team;}
