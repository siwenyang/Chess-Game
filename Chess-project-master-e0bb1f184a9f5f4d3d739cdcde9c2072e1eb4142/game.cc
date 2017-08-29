#include "game.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "piece.h"
#include "view.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "player.h"
#include "human.h"
#include "playerAI1.h"
#include "playerAI2.h"
#include "playerAI3.h"
#include <string>
#include <istream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

Game::Game():turn{0},wp{nullptr},bp{nullptr},td{new TextDisplay},gd{new GraphicsDisplay},wwon{0},bwon{0},graphic{false},playing{false},isSetup{false},isEnPassant{false},enPassant{nullptr}{
	for(int i = 0; i < 8; ++i){
		vector<Piece *> row;
		for(int j = 0; j < 8; ++j){
			row.emplace_back(nullptr);
		}
		board.emplace_back(row);
	}
	for(int i = 0; i < 8; ++i){
		vector<vector<pair<char,string>>> row;
		for(int j = 0; j < 8; ++j){
			vector<pair<char,string>> access;
			row.emplace_back(access);
		}
		moveBoard.emplace_back(row);
	}
}

Game::~Game(){
	clearBoard();
	if (wp) delete wp;
	if (bp) delete bp;
	if (td) delete td;
	if (gd) delete gd;
}

void Game::init(){

	board[0][0] = new Rook(0,0,'r','b',"r1",false);
	td->notify(-1,-1,0,0,'r');
	gd->notify(-1,-1,0,0,'r','b');

	board[0][1] = new Knight(0,1,'n','b',"n1",false);
	td->notify(-1,-1,0,1,'n');
	gd->notify(-1,-1,0,1,'n','b');

	board[0][2] = new Bishop(0,2,'b','b',"b1",false);
	td->notify(-1,-1,0,2,'b');
	gd->notify(-1,-1,0,2,'b','b');

	board[0][3] = new Queen(0,3,'q','b',"q1",false);
	td->notify(-1,-1,0,3,'q');
	gd->notify(-1,-1,0,3,'q','b');

	board[0][4] = new King(0,4,'k','b',"k1",false);
	td->notify(-1,-1,0,4,'k');
	gd->notify(-1,-1,0,4,'k','b');

	board[0][5] = new Bishop(0,5,'b','b',"b2",false);
	td->notify(-1,-1,0,5,'b');
	gd->notify(-1,-1,0,5,'b','b');

	board[0][6] = new Knight(0,6,'n','b',"n2",false);
	td->notify(-1,-1,0,6,'n');
	gd->notify(-1,-1,0,6,'n','b');

	board[0][7] = new Rook(0,7,'r','b',"r2",false);
	td->notify(-1,-1,0,7,'r');
	gd->notify(-1,-1,0,7,'r','b');

	for(int i = 0; i < 8; ++i){
		string id = "p" + to_string(i);
		board[1][i] = new Pawn(1,i,'p','b',id,false);
		td->notify(-1,-1,1,i,'p');
		gd->notify(-1,-1,1,i,'p','b');
	}

	for(int i = 0; i < 8; ++i){
		string id = "P" + to_string(i);
		board[6][i] = new Pawn(6,i,'P','w',id,false);
		td->notify(-1,-1,6,i,'P');
		gd->notify(-1,-1,6,i,'P','w');
	}

	board[7][0] = new Rook(7,0,'R','w',"R1",false);
	td->notify(-1,-1,7,0,'R');
	gd->notify(-1,-1,7,0,'R','w');

	board[7][1] = new Knight(7,1,'N','w',"N1",false);
	td->notify(-1,-1,7,1,'N');
	gd->notify(-1,-1,7,1,'N','w');

	board[7][2] = new Bishop(7,2,'B','w',"B1",false);
	td->notify(-1,-1,7,2,'B');
	gd->notify(-1,-1,7,2,'B','w');

	board[7][3] = new Queen(7,3,'Q','w',"Q1",false);
	td->notify(-1,-1,7,3,'Q');
	gd->notify(-1,-1,7,3,'Q','w');

	board[7][4] = new King(7,4,'K','w',"K1",false);
	td->notify(-1,-1,7,4,'K');
	gd->notify(-1,-1,7,4,'K','w');

	board[7][5] = new Bishop(7,5,'B','w',"B2",false);
	td->notify(-1,-1,7,5,'B');
	gd->notify(-1,-1,7,5,'B','w');

	board[7][6] = new Knight(7,6,'N','w',"N2",false);
	td->notify(-1,-1,7,6,'N');
	gd->notify(-1,-1,7,6,'N','w');

	board[7][7] = new Rook(7,7,'R','w',"R2",false);
	td->notify(-1,-1,7,7,'R');
	gd->notify(-1,-1,7,7,'R','w');

	updateMoveBoard();
	// printMoveBoard();
	print();
}

void Game::clearBoard(){
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] != nullptr) {
				Piece *p = board[i][j];
				board[i][j] = nullptr;
				delete p;
			}
		}
	}
	clearMoveBoard();
	clearDisplay();
}

//check if 
bool Game::checkMoveBoardAt(int r,int c,string id,char color){ 
	// cout << "find start" << endl;
	if (moveBoard[r][c].empty()) return false;
	for (auto it = moveBoard[r][c].begin(); it != moveBoard[r][c].end(); ++it) {
		if (color == '*') {
			// cout << "color" << endl;
			if (it->second == id) return true;
		}
		if (id == "*") {
			// cout << "id" << endl;
			if (it->first == color) return true;
		}
	}
	// cout << "find end" << endl;
	return false;
}

void Game::clearMoveBoard(){
	for(int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if (!moveBoard[i][j].empty()) moveBoard[i][j].clear();
		}
	}
}

void Game::printMoveBoard(){
	for(int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if (!moveBoard[i][j].empty()) {
				cout << "(" << i << "," << j << "):";
				for (auto it = moveBoard[i][j].begin(); it != moveBoard[i][j].end(); ++it) {
					cout << " " << it->first << " " << it->second;
				}
				cout << endl;
			}
		}
	}
}

void Game::updateMoveBoard(int a,int b,char t,string s){
	int x = 0,y = 0;
	int r,c;
	int diffr,diffc;
	pair<char,string> info;
	int kr,kc,Kr,Kc;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] != nullptr) {
				string id = board[i][j]->getID();
				char team = board[i][j]->getColour();
				char name = board[i][j]->getName();
				info.first = team;
				info.second = id;
				if (name == 'p') {
					// cout << "p" << endl;
					if (board[i+1][j] == nullptr) {
						// cout << "move 1" << endl;
						moveBoard[i+1][j].emplace_back(info);
					}
					if (!board[i][j]->getIsMoved() && (board[i+2][j] == nullptr) && (board[i+1][j] == nullptr)) {
						// cout << "move 2" << endl;
						moveBoard[i+2][j].emplace_back(info);
					}
					if ((j != 0) && (board[i+1][j-1] != nullptr) && (board[i+1][j-1]->getColour() == 'w')) {
						// cout << "catch left" << endl;
						moveBoard[i+1][j-1].emplace_back(info);
					} 
					if ((j != 7) && (board[i+1][j+1] != nullptr) && (board[i+1][j+1]->getColour() == 'w')) {
						// cout << "catch right" << endl;
						moveBoard[i+1][j+1].emplace_back(info);
					}
					// cout << "no move" << endl;
				} else if (name == 'P') {
					if (board[i-1][j] == nullptr) {
						// cout << "move 1" << endl;
						moveBoard[i-1][j].emplace_back(info);
					}
					if (!board[i][j]->getIsMoved() && (board[i-2][j] == nullptr) && (board[i-1][j] == nullptr)) {
						moveBoard[i-2][j].emplace_back(info);
					}
					if ((j != 0) && (board[i-1][j-1] != nullptr) && (board[i-1][j-1]->getColour() == 'b')) {
						moveBoard[i-1][j-1].emplace_back(info);
					} 
					if ((j != 7) && (board[i-1][j+1] != nullptr) && (board[i-1][j+1]->getColour() == 'b')) {
						moveBoard[i-1][j+1].emplace_back(info);
					}
				} else if (name == 'k') {
					kr = i;
					kc = j;
				} else if (name == 'K') {
					Kr = i;
					Kc = j;
				} else {
					vector<pair<int,int>> range = board[i][j]->getRange();
					// cout << "check piece" << endl;
					for(auto it = range.begin(); it != range.end(); ++it){
						// cout << "check range start" << endl;
						r = it->first;
						c = it->second;
						diffr = i - r;
						diffc = c - j;
						// if(board[i][j]->getName() == 'q'){
						// 	cout << "(" << r << "," << c << ")";
						// }
						if (board[r][c] == nullptr) {
							// cout << "is nullptr" << endl;
							if ((x == 0) && (y==0)){
								// cout << "x y = 0" << endl;
								moveBoard[r][c].emplace_back(info);
							} else {
								bool sameX = false;
								bool sameY = false;
								for(int k = 2; k < 8; ++k){
									if (x * k == diffc) sameX = true;
									if (y * k == diffr) sameY = true;
								}
								if (sameX && sameY) {
									continue;
								} else {
									moveBoard[r][c].emplace_back(info);
									x = 0;
									y = 0;
								}
							}
						} else {
							// cout << "not nullptr" << endl;
							char color = board[r][c]->getColour();
							if (color == board[i][j]->getColour()){
								if (diffr > 0) y = 1;
								if (diffr == 0) y = 0;
								if (diffr < 0) y = -1;
								if (diffc > 0) x = 1;
								if (diffc == 0) x = 0;
								if (diffc < 0) x = -1;
							} else if (color != board[i][j]->getColour()) {
								// cout << "capture" << endl;
								bool sameX = false;
								bool sameY = false;
								for(int k = 2; k < 8; ++k){
									if (x * k == diffc) sameX = true;
									if (y * k == diffr) sameY = true;
								}
								if (sameX && sameY) {
									continue;
								} else {
									moveBoard[r][c].emplace_back(info);
									if (diffr > 0) y = 1;
									if (diffr == 0) y = 0;
									if (diffr < 0) y = -1;
									if (diffc > 0) x = 1;
									if (diffc == 0) x = 0;
									if (diffc < 0) x = -1;
								}
							}
						}
					}
				}
			}
		}
	}
	if ((a != -1) && (b != -1)) {
		info.first = t;
		info.second = s;
		moveBoard[a][b].emplace_back(info);
		isEnPassant = true;
	}
	vector<pair<int,int>> krange = board[kr][kc]->getRange();
	info.first = 'b';
	info.second = "k1";
 	for(auto it = krange.begin(); it != krange.end(); ++it){
 		r = it->first;
		c = it->second;
		if (!board[r][c] && !checkMoveBoardAt(r,c,"*",'w') && !isCheckAfterMove(kr,kc,r,c,'k')) moveBoard[r][c].emplace_back(info);
		if (board[r][c] && (board[r][c]->getColour() == 'w') && !isCheckAfterMove(kr,kc,r,c,'k')) moveBoard[r][c].emplace_back(info);
		if (isCheckAfterMove(kr,kc,r,c,'k')) cout << "check after move" << endl;
 	}
 	if ((kr == 0) && (kc == 4)) {
 		if (!check('k') && !board[0][4]->getIsMoved() && !board[0][5] && !board[0][6] && board[0][7] && (board[0][7]->getName() == 'r') && !board[0][7]->getIsMoved()){
	 		moveBoard[0][6].emplace_back(info);
	 	} else if (!check('k') && !board[0][4]->getIsMoved() && !board[0][3] && !board[0][2] && !board[0][1] && board[0][0] && (board[0][0]->getName() == 'r') && !board[0][0]->getIsMoved()){
	 		moveBoard[0][2].emplace_back(info);
	 	}
 	}
 	info.first = 'w';
	info.second = "K1";
 	vector<pair<int,int>> Krange = board[Kr][Kc]->getRange();
 	for(auto it = Krange.begin(); it != Krange.end(); ++it){
 		r = it->first;
		c = it->second;
		if (!board[r][c] && !checkMoveBoardAt(r,c,"*",'b') && !isCheckAfterMove(Kr,Kc,r,c,'K')) moveBoard[r][c].emplace_back(info);
		if (board[r][c] && (board[r][c]->getColour() == 'b') && !isCheckAfterMove(Kr,Kc,r,c,'K')) moveBoard[r][c].emplace_back(info);
 	}
 	if ((Kr == 7) && (Kc == 4)) {
 		if (!check('K') && !board[7][4]->getIsMoved() && !board[7][5] && !board[7][6] && board[7][7] && (board[7][7]->getName() == 'R') && !board[7][7]->getIsMoved()){
	 		moveBoard[7][6].emplace_back(info);
	 	} else if (!check('K') && !board[Kr][Kc]->getIsMoved() && !board[7][3] && !board[7][2] && !board[7][1] && board[7][0] && (board[7][0]->getName() == 'R') && !board[7][0]->getIsMoved()){
	 		moveBoard[7][2].emplace_back(info);
	 	}
 	}
	printMoveBoard();
}

void Game::move(int oldr,int oldc,int newr,int newc,bool check){
	Piece *p = board[oldr][oldc];
	p->setRow(newr);
	p->setCol(newc);
	char name = p->getName();
	char color = p->getColour();
	// cout << "if start" << endl;
	if (board[newr][newc] != nullptr) {
		// cout << "catch" << endl;
		if (board[newr][newc]->getName() == 'k') {
			Piece *temp = board[newr][newc];
			board[newr][newc] = board[oldr][oldc];
			delete temp;
			board[oldr][oldc] = nullptr;
			td->notify(oldr,oldc,newr,newc,name);
			gd->notify(oldr,oldc,newr,newc,name,color);
			print();
			cout << "White wins!" << endl;
			message("White wins!");
			++wwon;
			playing = false;
			return;
		} 
		if (board[newr][newc]->getName() == 'K') {
			Piece *temp = board[newr][newc];
			board[newr][newc] = board[oldr][oldc];
			delete temp;
			board[oldr][oldc] = nullptr;
			td->notify(oldr,oldc,newr,newc,name);
			gd->notify(oldr,oldc,newr,newc,name,color);
			print();
			cout << "Black wins!" << endl;
			message("Black wins!");
			++bwon;
			playing = false;
			return;
		} 
		Piece *caught = board[newr][newc];
		board[newr][newc] = p;
		delete caught;
	} else {
		// cout << "move" << endl;
		board[newr][newc] = p;
	}
	p->setRange();
	// cout << "if end" << endl;
	board[oldr][oldc] = nullptr;
	if(!check) {
		p->setIsMoved(true);
		td->notify(oldr,oldc,newr,newc,name);
		gd->notify(oldr,oldc,newr,newc,name,color);
		print();
		turn = !turn;
	}
	clearMoveBoard();
	updateMoveBoard();
}

int Game::count(char name){
	int c = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if((board[i][j] != nullptr) && (board[i][j]->getName() == name)){
				++c;
			}
		}
	}
	return c;
}

bool Game::isCheckAfterMove(int oldr,int oldc,int newr,int newc,char king){
	vector<string> checkID;
	for (auto it = moveBoard[oldr][oldc].begin(); it != moveBoard[oldr][oldc].end(); ++it){
		if (king == 'k') {
			if(it->first == 'w') checkID.emplace_back(it->second);
		} else if (king == 'K') {
			if(it->first == 'b') checkID.emplace_back(it->second);
		}
	}
	for (auto it = checkID.begin(); it != checkID.end(); ++it){
		Piece *p;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (!board[i][j]) continue;
				if (board[i][j]->getID() == *it) p = board[i][j];
			}
		}
		std::vector<std::pair<int,int>> range = p->getRange();
		for(auto rit = range.begin(); rit != range.end(); ++rit){
			if ((rit->first == newr) && (rit->second == newc)) return true;
		}
	}
	return false;
}

bool Game::isKingInRange(int oldr,int oldc,int newr,int newc,char color){
	bool retval = false;
	string id = board[oldr][oldc]->getID();
	move(oldr,oldc,newr,newc,true);
	clearMoveBoard();
	updateMoveBoard();
	int r,c;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (!board[i][j]) continue;
			if((color == 'b') && (board[i][j]->getName() == 'K')) {
				r = i;
				c = j;
			} else if ((color == 'w') && (board[i][j]->getName() == 'k')){
				r = i;
				c = j;
			}
		}
	}
	for(auto it = moveBoard[r][c].begin(); it != moveBoard[r][c].end(); ++it){
		if (it->second == id) retval = true;
	}
	move(newr,newc,oldr,oldc,true);
	clearMoveBoard();
	updateMoveBoard();
	return retval;
}

bool Game::checkLegalMove(int oldr,int oldc,int newr,int newc){
	string id = board[oldr][oldc]->getID();
	return checkMoveBoardAt(newr,newc,id,'*');
}

void Game::notify(string cmd){
	istringstream ss{cmd};
	string move;
	ss >> move;
	if (move == "resign") {
		if (turn) {
			cout << "White wins!" << endl;
			message("White wins!");
			++wwon;
			turn = 0;
			playing = false;
		} else {
			cout << "Black wins!" << endl;
			message("Black wins!");
			++bwon;
			turn = 0;
			playing = false;
		}
	} else if (move == "move") {
		string pos1,pos2;
		ss >> pos1 >> pos2;
		int oldr,oldc,newr,newc;
		if ((pos1.length() != 2) || (pos2.length() != 2)) {
			cout << "Invalid input" << endl;
			message("Invalid input");
			if (turn) bp->makeMove();
			else wp->makeMove();
		} else {
			oldr = 8 - (pos1[1] -'0');
			oldc = pos1[0] - 'a';
			newr = 8 - (pos2[1] -'0');
			newc = pos2[0] - 'a';
			int enr = -1,enc = -1;
			if ((oldr > 8) || (oldr < 0) || (oldc > 8) || (oldc < 0) || (newr > 8) || (newr < 0) || (newc > 8) || (newc < 0)) {
				cout << "Invalid position." << endl;
				message("Invalid position");
				if (turn) bp->makeMove();
				else wp->makeMove();
			} else if (board[oldr][oldc] == nullptr) {
				string s = "No piece at " + pos1;
				cout << s << endl;
				message(s);
				if (turn) bp->makeMove();
				else wp->makeMove();
			} else if (turn && (board[oldr][oldc]->getColour() != 'b')) {
				cout << "You can only move your own pieces" << endl;
				message("You can only move your own pieces");
				bp->makeMove();
			} else if (!turn && (board[oldr][oldc]->getColour() != 'w')) {
				cout << "You can only move your own pieces" << endl;
				message("You can only move your own pieces");
				wp->makeMove();
			} else if (!checkLegalMove(oldr,oldc,newr,newc)) {
				cout << "You cannot move there" << endl;
				message("You cannot move there");
				if (turn) bp->makeMove();
				else wp->makeMove();
			} else {
				char name = board[oldr][oldc]->getName();
				if (turn && check('k') && (board[oldr][oldc]->getName() != 'k')) {
					cout << "Your King is in check. Have to move King." << endl;
					message("Your King is in check. Have to move King.");
					bp->makeMove();
					return;
				} else if (!turn && check('K') && (board[oldr][oldc]->getName() != 'K')) {
					cout << "Your King is in check. Have to move King." << endl;
					message("Your King is in check. Have to move King.");
					wp->makeMove();
					return;
				} 
				if (name == 'p'){
					if(newr == 7) {
						string change;
						while(true){
							cin >> change;
							if (cin.eof()) break;
							int ins = count(change[0]);
							++ins;
							string id;
							Piece *p = board[oldr][oldc];
							if((change == "q") || (change == "Q")){
								id = "q" + to_string(ins);
								board[oldr][oldc] = new Queen(oldr,oldr,'q','b',id,true);
								delete p;
								break;
							} else if((change == "b") || (change == "B")){
								id = "b" + to_string(ins);
								board[oldr][oldc] = new Bishop(oldr,oldr,'b','b',id,true);
								delete p;
								break;
							} else if((change == "r") || (change == "R")){
								id = "r" + to_string(ins);
								board[oldr][oldc] = new Rook(oldr,oldr,'r','b',id,true);
								delete p;
								break;
							} else if((change == "n") || (change == "N")){
								id = "n" + to_string(ins);
								board[oldr][oldc] = new Knight(oldr,oldr,'n','b',id,true);
								delete p;
								break;
							} else {
								cout << "Chosen piece invalid" << endl;
								cout << "Please enter a valid piece" << endl;
								message("Chosen piece invalid. Please enter a valid piece");
							}
						}
					} else if (newr - oldr == 2){
						if (newc != 0) {
							if ((board[newr][newc-1] != nullptr) && (board[newr][newc-1]->getName() == 'P')) {
								isEnPassant = true;
								enPassant = board[newr][newc-1];
								enr = newr - 1;
								enc = newc;
							}
						} else if (newc != 7){
							if ((board[newr][newc+1] != nullptr) && (board[newr][newc+1]->getName() == 'P')) {
								isEnPassant = true;
								enPassant = board[newr][newc+1];
								enr = newr - 1;
								enc = newc;
							}
						}
					} else if (isEnPassant) {
						if (board[oldr][oldc] == enPassant) {
							Piece *caught = board[newr+1][newc];
							board[newr+1][newc] = nullptr;
							td->notify(newr+1,newc,-1,-1);
							gd->notify(newr+1,newc,-1,-1);
							delete caught;
						}
						isEnPassant = false;
						enr = -1;
						enc = -1;
					}
				} else if (name == 'P'){
					if(newr == 0) {
						string change;
						while(true){
							cin >> change;
							if (cin.eof()) break;
							int ins = count(change[0]);
							++ins;
							string id;
							Piece *p = board[oldr][oldc];
							if((change == "q") || (change == "Q")){
								id = "Q" + to_string(ins);
								board[oldr][oldc] = new Queen(oldr,oldr,'Q','w',id,true);
								delete p;
								break;
							} else if((change == "b") || (change == "B")){
								id = "B" + to_string(ins);
								board[oldr][oldc] = new Bishop(oldr,oldr,'B','w',id,true);
								delete p;
								break;
							} else if((change == "r") || (change == "R")){
								id = "R" + to_string(ins);
								board[oldr][oldc] = new Rook(oldr,oldr,'R','w',id,true);
								delete p;
								break;
							} else if((change == "n") || (change == "N")){
								id = "N" + to_string(ins);
								board[oldr][oldc] = new Knight(oldr,oldr,'N','w',id,true);
								delete p;
								break;
							} else {
								cout << "Chosen piece invalid" << endl;
								cout << "Please enter a valid piece" << endl;
								message("Chosen piece invalid. Please enter a valid piece");
							}
						}
					} else if (newr - oldr == 2){
						if (newc != 0) {
							if ((board[newr][newc-1] != nullptr) && (board[newr][newc-1]->getName() == 'P')) {
								isEnPassant = true;
								enPassant = board[newr][newc-1];
								enr = newr + 1;
								enc = newc;
							}
						} else if (newc != 7){
							if ((board[newr][newc+1] != nullptr) && (board[newr][newc+1]->getName() == 'P')) {
								isEnPassant = true;
								enPassant = board[newr][newc+1];
								enr = newr + 1;
								enc = newc;
							}
						}
					} else if (isEnPassant) {
						if (board[oldr][oldc] == enPassant) {
							Piece *caught = board[newr+1][newc];
							board[newr+1][newc] = nullptr;
							td->notify(newr+1,newc,-1,-1);
							gd->notify(newr+1,newc,-1,-1);
							delete caught;
						}
						isEnPassant = false;
						enr = -1;
						enc = -1;
					}
				} else if (name == 'k'){
					if ((newr == 0) && (newc == 6)) {
						this->move(0,7,0,5,false);
						turn = !turn;
					} else if ((newr == 0) && (newc == 2)) {
						this->move(0,0,0,3,false);
						turn = !turn;
					}
				} else if (name == 'K'){
					if ((newr == 7) && (newc == 6)) {
						this->move(7,7,7,5,false);
						turn = !turn;
					} else if ((newr == 7) && (newc == 2)) {
						this->move(7,0,7,3,false);
						turn = !turn;
					}
				}
				message();
				this->move(oldr,oldc,newr,newc,false);
				clearMoveBoard();
				if(isEnPassant) {
					updateMoveBoard(enr,enc,enPassant->getColour(),enPassant->getID());
				} else {
					updateMoveBoard();
				}
			}
		}
	}
}

bool Game::check(char king){
	int r,c;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board[i][j] == nullptr) continue;
			if (board[i][j]->getName() == king) {
				r = i;
				c = j;
			}
		}
	}
	// cout << "found king" << endl;
	bool b;
	if(king == 'K'){
		b = checkMoveBoardAt(r,c,"*",'b');
		// if (b) {
		// 	cout << "White King is in check" << endl;
		// 	message("White King is in check");
		// }
	}
	if(king == 'k'){
		b = checkMoveBoardAt(r,c,"*",'w');
		// if (b) {
		// 	cout << "Black King is in check" << endl;
		// 	message("Black King is in check");
		// }
	}
	return b;
}

void Game::readFromFile(string file){
	ifstream f;
	f.exceptions(ifstream::failbit | ifstream::eofbit);
	try{
		f.open(file);
	}
	catch(ifstream::failure &){
		cout << file << " does not exist" << endl;
		return;
	}
	char piece;
	string line;
	int K = 0,k = 0,Q = 0,q = 0,B = 0,b = 0,R = 0,r = 0,N = 0,n = 0,P = 0,p = 0;
	for (int i = 0; i < 8; ++i) {
		getline(f,line);
		istringstream ss{line};
		string id;
		for (int j = 0; j < 8; ++j) {
			ss >> piece;
			if (piece != '_') {
				bool moved = true;
				if (piece == 'K') {
					++K;
					id = "K" + to_string(K);
					if ((i == 7) && (j == 4)) moved = false;
					board[i][j] = new King(i,j,piece,'w',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'w');
				} else if (piece == 'k') {
					++k;
					id = "k" + to_string(k);
					if ((i == 0) && (j == 4)) moved = false;
					board[i][j] = new King(i,j,piece,'b',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'b');
				} else if (piece == 'Q') {
					++Q;
					id = "Q" + to_string(Q);
					board[i][j] = new Queen(i,j,piece,'w',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'w');
				} else if (piece == 'q') {
					++q;
					id = "q" + to_string(q);
					board[i][j] = new Queen(i,j,piece,'b',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'b');
				} else if (piece == 'B') {
					++B;
					id = "B" + to_string(B);
					board[i][j] = new Bishop(i,j,piece,'w',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'w');
				} else if (piece == 'b') {
					++b;
					id = "b" + to_string(b);
					board[i][j] = new Bishop(i,j,piece,'b',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'b');
				} else if (piece == 'R') {
					++R;
					id = "R" + to_string(R);
					if (((i == 7) && (j == 0)) || ((i == 7) && (j == 7))) moved = false;
					board[i][j] = new Rook(i,j,piece,'w',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'w');
				} else if (piece == 'r') {
					++r;
					id = "r" + to_string(r);
					if (((i == 0) && (j == 0)) || ((i == 0) && (j == 7))) moved = false;
					board[i][j] = new Rook(i,j,piece,'b',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'b');
				} else if (piece == 'N') {
					++N;
					id = "N" + to_string(N);
					board[i][j] = new Knight(i,j,piece,'w',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'w');
				} else if (piece == 'n') {
					++n;
					id = "n" + to_string(n);
					board[i][j] = new Knight(i,j,piece,'b',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'b');
				} else if (piece == 'P') {
					++P;
					id = "P" + to_string(P);
					if (i == 6) moved = false;
					board[i][j] = new Pawn(i,j,piece,'w',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'w');
				} else if (piece == 'p') {
					++p;
					id = "p" + to_string(p);
					if (i == 1) moved = false;
					board[i][j] = new Pawn(i,j,piece,'b',id,moved);
					td->notify(-1,-1,i,j,piece);
					gd->notify(-1,-1,i,j,piece,'b');
				} else {
					cout << "Invalid piece" << endl;
					message("Invalid piece");
				}
			}
		}
	}
	print();
	clearMoveBoard();
	updateMoveBoard();
	f >> piece;
	if ((piece == 'B')||(piece == 'b')) {
		turn = 1;
	} else if  ((piece == 'W')||(piece == 'w')) {
		turn = 0;
	} else {
		cout << "Invalid team" << endl;
		message("Invalid team");
	}
	isSetup = true;
}

void Game::play(){
	clearBoard();
	string cmd;
	while(true){
		cin >> cmd;
		if (cin.eof()) break;
		if (cmd == "load") {
			string file;
			cin >> file;
			readFromFile(file);
		} else if (cmd == "setup"){
			if (isSetup) {
				cout << "Board already setup." << endl;
				message("Board already setup.");
				continue;
			}
			int K = 0,k = 0,Q = 0,q = 0,B = 0,b = 0,R = 0,r = 0,N = 0,n = 0,P = 0,p = 0;
			while(true) {
				string op;
				cin >> op;
				if (cin.eof()) break;
				if (op == "+"){
					char piece;
					string pos;
					cin >> piece >> pos;
					int i,j;
					i = 8 - (pos[1] -'0');
					j = pos[0] - 'a';
					string id;
					bool moved = true;
					if ((i > 8) || (i < 0) || (j > 8) || (j < 0)) {
						cout << "Invalid position." << endl;
						message("Invalid position");
						continue; 
					}
					if (board[i][j] != nullptr){
						Piece *p = board[i][j];
						board[i][j] = nullptr;
						delete p;
						td->notify(i,j,-1,-1);
						gd->notify(i,j,-1,-1);
						message();
					}
					if (piece == 'K') {
						++K;
						id = "K1";
						if ((i == 7) && (j == 4)) moved = false;
						board[i][j] = new King(i,j,piece,'w',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'w');
						message();
					} else if (piece == 'k') {
						++k;
						id = "k1";
						if ((i == 0) && (j == 4)) moved = false;
						board[i][j] = new King(i,j,piece,'b',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'b');
						message();
					} else if (piece == 'Q') {
						++Q;
						id = "Q" + to_string(Q);
						board[i][j] = new Queen(i,j,piece,'w',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'w');
						message();
					} else if (piece == 'q') {
						++q;
						id = "q" + to_string(q);
						board[i][j] = new Queen(i,j,piece,'b',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'b');
						message();
					} else if (piece == 'B') {
						++B;
						id = "B" + to_string(B);
						board[i][j] = new Bishop(i,j,piece,'w',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'w');
						message();
					} else if (piece == 'b') {
						++b;
						id = "b" + to_string(b);
						board[i][j] = new Bishop(i,j,piece,'b',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'b');
						message();
					} else if (piece == 'R') {
						++R;
						id = "R" + to_string(R);
						board[i][j] = new Rook(i,j,piece,'w',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'w');
						message();
					} else if (piece == 'r') {
						++r;
						id = "r" + to_string(r);
						board[i][j] = new Rook(i,j,piece,'b',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'b');
						message();
					} else if (piece == 'N') {
						++N;
						id = "N" + to_string(N);
						if (((i == 7) && (j == 1)) || ((i == 7) && (j == 6))) moved = false;
						board[i][j] = new Knight(i,j,piece,'w',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'w');
						message();
					} else if (piece == 'n') {
						++n;
						id = "n" + to_string(n);
						if (((i == 0) && (j == 1)) || ((i == 0) && (j == 6))) moved = false;
						board[i][j] = new Knight(i,j,piece,'b',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'b');
						message();
					} else if (piece == 'P') {
						++P;
						id = "P" + to_string(P);
						if (i == 6) moved = false;
						board[i][j] = new Pawn(i,j,piece,'w',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'w');
						message();
					} else if (piece == 'p') {
						++p;
						id = "p" + to_string(p);
						if (i == 1) moved = false;
						board[i][j] = new Pawn(i,j,piece,'b',id,moved);
						td->notify(-1,-1,i,j,piece);
						gd->notify(-1,-1,i,j,piece,'b');
						message();
					} else {
						cout << "Invalid piece" << endl;
						message("Invalid piece");
					}
					print();
				} else if (op == "-"){
					string pos;
					cin >> pos;
					int i,j;
					i = 8 - (pos[1] -'0');
					j = pos[0] - 'a';
					if ((i > 8) || (i < 0) || (j > 8) || (j < 0)) {
						cout << "Invalid position." << endl;
						message("Invalid position");
						continue; 
					}
					if (board[i][j] != nullptr){
						char name = board[i][j]->getName();
						if (name == 'K') --K;
						else if (name == 'k') --k;
						else if (name == 'Q') --Q;
						else if (name == 'q') --q;
						else if (name == 'B') --B;
						else if (name == 'b') --b;
						else if (name == 'R') --R;
						else if (name == 'r') --r;
						else if (name == 'N') --N;
						else if (name == 'n') --n;
						else if (name == 'P') --P;
						else if (name == 'p') --p;
						Piece *pp = board[i][j];
						board[i][j] = nullptr;
						delete pp;
						td->notify(i,j,-1,-1);
						gd->notify(i,j,-1,-1);
						message();
					} else {
						cout << "No piece on that position" << endl;
						message("No piece on that position");
						continue;
					}
					print();
				} else if (op == "="){
					string color;
					cin >> color;
					if (color == "black") {
						turn = 1;
						message();
					} else if (color == "white") {
						turn = 0;
						message();
					} else {
						cout << "Invalid colour." << endl;
						message("Invalid colour");
					}
				} else if (op == "done") {
					clearMoveBoard();
					updateMoveBoard();
					if (checkSetup()) {
						// cout << "check ok" << endl;
						isSetup = true;
						cout << "Setup done" << endl;
						message("Setup done");
						break;
					}
					else {
						cout << "Cannot leave setup mode" << endl;
						message("Cannot leave setup mode");
					}
					print();
				} else {
					cout << "Invalid command." << endl;
					message("Invalid command");
				}
			}
		} else if(cmd == "game"){
			if (playing) {
				cout << "Game is playing. Cannot start a new game." << endl;
				message("Game is playing. Cannot start a new game.");
				continue;
			}
			string p1,p2;
			while(true){
				cin >> p1 >> p2;
				if (cin.eof()) return;
				if (p1 == "human") {
					wp = new Human(this,'w');
				} else if (p1 == "computer1") {
				 	wp = new PlayerAI1(this,'w');
				} else if (p1 == "computer2") {
				 	wp = new PlayerAI2(this,'w');
				}else if (p1 == "computer3") {
				 	wp = new PlayerAI3(this,'w');
				} else {
					cout << "Invalid player." << endl;
					cout << "Please choose from: human computer[1-4]" << endl;
					message("Invalid player. Please choose from: human computer[1-4]");
					continue;
				}
				if (p2 == "human") {
					bp = new Human(this,'b');
				} else if (p2 == "computer1") {
				 	bp = new PlayerAI1(this,'b');
				} else if (p2 == "computer2") {
				 	bp = new PlayerAI2(this,'b');
				}else if (p2 == "computer3") {
				 	bp = new PlayerAI3(this,'b');
				} else {
					cout << "Invalid player." << endl;
					cout << "Please choose from: human computer[1-4]" << endl;
					message("Invalid player. Please choose from: human computer[1-4]");
					continue;
				}
				if (wp && bp) {
					message();
					break;
				}
			}
			if (!isSetup) {
				init();
				turn = 0;
			} else print();
			playing = true;
			while (playing){
				if (cin.eof()) {
					playing = false;
					break;
				}
				if (turn) {
					if (checkWin()) continue;
					cout << "Black's turn." << endl;
					whoIsNext(turn);
					if (check('k')) {
						cout << "Black King is in check" << endl;
						message("Black King is in check");
					}
					bp->makeMove();
				} else {
					if (checkWin()) continue;
					cout << "White's turn." << endl;
					whoIsNext(turn);
					if (check('K')) {
						cout << "White King is in check" << endl;
						message("White King is in check");
					}
					wp->makeMove();
				}
			}
			clearBoard();
		} else {
			cout << "Invalid command." << endl;
			message("Invalid command");
		}
	}
	cout << "Final Score:" << endl;
	cout << "White: " << wwon << endl;
	cout << "Black: " << bwon << endl;
}

bool Game::checkWin(){
	if (checkMate('K')){
		cout << "Checkmate! Black wins!" << endl;
		message("Checkmate! Black wins!");
		playing = false;
		++bwon;
		return true;
	}
	if (checkMate('k')){
		cout << "Checkmate! White wins!" << endl;
		message("Checkmate! White wins!");
		playing = false;
		++wwon;
		return true;
	}
	if ((staleMate('b')) || (staleMate('w'))) {
		cout << "Stalemate!" << endl;
		message("Stalemate!");
		playing = false;
		bwon += 0.5;
		wwon += 0.5;
		return true;
	}
	return false;
}

void Game::clearDisplay(){
	td->clear();
	gd->clear();
}

void Game::print(){
	if(TextDisplay *t = dynamic_cast<TextDisplay *>(td)) t->print();
}

void Game::message(string msg){
	if(GraphicsDisplay *g = dynamic_cast<GraphicsDisplay *>(gd)) g->message(msg);
}

void Game::whoIsNext(int t){
	if(GraphicsDisplay *g = dynamic_cast<GraphicsDisplay *>(gd)) g->whoIsNext(t);
}

Piece *Game::getBoard(int r,int c){return board[r][c];}

std::vector<std::pair<char,std::string>> Game::getMoveBoard(int r,int c){return moveBoard[r][c];}

bool Game::checkSetup(){
	int wk = 0,bk = 0;
	bool state = true;
	for (int i = 0; i < 8; ++i) {
		// cout << "loop 1" << endl;
		for (int j = 0; j < 8; ++j) {
			// cout << "loop 2" << endl;
			if (board[i][j] == nullptr) continue;
			if ((i == 0) || (i == 7)) {
				// cout << "pawn check" << endl;
				if ((board[i][j]->getName() == 'P') || (board[i][j]->getName() == 'p')){
					string s = "No Pawns allowed on line ";
					s += '8' - i;
					cout << s << endl;
					message(s);
					state = false;
				}
				// cout << "pawn check end" << endl;
			}
			if (board[i][j]->getName() == 'k') {
				++bk;
			}
			if (board[i][j]->getName() == 'K') {
				++wk;
			}
		}
	}
	if (wk != 1) {
		string s = "You have " + to_string(wk) + " white King(s) on the board";
		cout << s << endl;
		message(s);
		state = false;
	} else {
		if (check('K')) {
			cout << "White king is in check" << endl;
			message("White king is in check");
			state = false;
		}
	}
	if (bk != 1) {
		string s = "You have " + to_string(bk) + " black King(s) on the board";
		cout << s << endl;
		message(s);
		state = false;
	} else {
		if (check('k')) {
			cout << "Black king is in check" << endl;
			message("Black king is in check");
			state = false;
		}
	}
	return state;
}

//checkmate
bool Game::checkMate(char king) {
	string id;
	if (!check(king)) return false;
	if (king == 'k') id = "k1";
	else id = "K1";
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (checkMoveBoardAt(i,j,id,'*')) return false;
		}
	}
	return true;
}

//stalemate
bool Game::staleMate(char team){
	if (team == 'b'){
		if (check('k')) return false;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (checkMoveBoardAt(i,j,"*",'b')) return false;
			}
		}
	} else {
		if (check('K')) return false;
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (checkMoveBoardAt(i,j,"*",'w')) return false;
			}
		}
	}
	return true;
}





