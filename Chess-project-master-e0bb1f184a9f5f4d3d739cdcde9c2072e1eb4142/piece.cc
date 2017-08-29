#include "piece.h"
#include <string>
#include <vector>
using namespace std;

Piece::Piece(int r, int c, char name, char colour,string id,bool isMoved):r{r},c{c},name{name},colour{colour},id{id},isMoved{isMoved}{}

char Piece::getName(){return name;}

string Piece::getID(){return id;}

int Piece::getRow(){return r;}

int Piece::getCol(){return c;}

void Piece::setRow(int row){r = row;}

void Piece::setCol(int col){c = col;}

char Piece::getColour(){return colour;}

vector<std::pair<int,int> > Piece::getRange(){return range;}

bool Piece::getIsMoved(){return isMoved;}

void Piece::setIsMoved(bool set){isMoved = set;}
