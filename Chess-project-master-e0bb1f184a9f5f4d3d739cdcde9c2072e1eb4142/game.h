#ifndef _GAME_H_
#define _GAME_H_
#include "player.h"
#include <vector>
#include "piece.h"
#include "view.h"
#include "pawn.h"

//class Player;

class Game {
	std::vector<std::vector<Piece *>> board;
	std::vector<std::vector<std::vector<std::pair<char,std::string>>>> moveBoard;
	int turn;
	Player *wp;
	Player *bp;
	View *td;
	View *gd;
	double wwon;
	double bwon;
	bool graphic;
	bool playing;
	bool isSetup;
	bool isEnPassant;
	Piece *enPassant;

public:
	Game();
	~Game();
	void init();
	void clearBoard();
	void clearMoveBoard();
	void printMoveBoard();
	void print();
	void message(std::string msg);
	void whoIsNext(int t);
	void updateMoveBoard(int a = -1,int b = -1,char t = '*',std::string s = "*");
	bool check(char king);
	// bool isCheckAfterMove(int oldr,int oldc,int newr,int newc,char king);
	void clearDisplay();
	bool isKingInRange(int oldr,int oldc,int newr,int newc,char color);
	bool checkMoveBoardAt(int r,int c,std::string id,char color);
	void play();
	bool checkSetup();
	void readFromFile(std::string);
	void move(int oldr,int oldc,int newr,int newc,bool check);
	bool checkLegalMove(int oldr,int oldc,int newr,int newc);
	void notify(std::string cmd);
	int count(char name);
	bool checkMate(char king);
	bool staleMate(char team);
	bool checkWin();
	Piece *getBoard(int r,int c);
	std::vector<std::pair<char,std::string>> getMoveBoard(int r,int c);

};


#endif
