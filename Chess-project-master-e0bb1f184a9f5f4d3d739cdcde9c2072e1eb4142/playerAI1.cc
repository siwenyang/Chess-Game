#include <cstdlib>
#include <ctime>
#include "playerAI1.h"
#include "game.h"
#include <string>
#include <iostream>
using namespace std;

PlayerAI1::PlayerAI1(Game* game, char team) : Player(game,team){}

void PlayerAI1::makeMove(){
	string cmd;
	cin >> cmd;
    if(cin.eof()) return;
	if (cmd == "move") {
		vector<pair<string, string>> Movelists;
        vector<pair<string, string>> kingMovelists;
        pair<string, string> moves;
        string idstring;
        string finalMove;
        int kr, kc;
        if(team == 'w'){
            if(g->check('K')){
                for(int i=0; i<8; i++){
                    for(int j=0; j<8; j++){
                        if (g->getBoard(i,j) == nullptr) continue;
                        if(g->getBoard(i, j)->getID() == "K1"){
                            kr = i;
                            kc = j;
                        }
                    }
                }
                for(int k=0; k<8; k++){
                    for(int l=0; l<8; l++){
                        int size = g->getMoveBoard(k,l).size();
                        for(int x=0; x < size; x++){
                             if(g->getMoveBoard(k,l)[x].second == "K1"){
                                moves.first = "  ";
                                moves.first[0] = 'a' + kc;
				                moves.first[1] =  '8' - kr;
				                moves.second = "  ";
				                moves.second[0] = 'a'+l;
				                moves.second[1] = '8' - k;
                                kingMovelists.emplace_back(moves);
                            }
                        }
                    }
                }
            } else {
                for(int i=0; i < 8; i++){
                    for(int j=0; j < 8; j++){
                        if (g->getBoard(i,j) == nullptr) continue;
                        if (g->getBoard(i,j)->getColour != 'w') continue;
                        idstring = g->getBoard(i, j)->getID();
                        for(int k=0; k < 8; k++){
                            for(int l=0; l < 8; l++){
                                int size = g->getMoveBoard(k,l).size();
                                for(int m=0; m < size; m++){
                                    if(g->getMoveBoard(k, l)[m].second == idstring) {//i,j 移动前坐标; k,l 移动后坐标
                                        moves.first = "  ";
                                        moves.first[0] = 'a' + j;
                                        moves.first[1] =  '8' - i;
                                        moves.second = "  ";
                                        moves.second[0] = 'a' + l;
                                        moves.second[1] = '8' - k;
                                        Movelists.emplace_back(moves);
                                    }
                                }   
                            }   
                        }
                    }
                }
            }
        }

        if(team == 'b'){
            if(g->check('k')){
                for(int i=0; i<8; i++){
                    for(int j=0; j<8; j++){
                        if (g->getBoard(i,j) == nullptr) continue;
                        if(g->getBoard(i, j)->getID() == "k1"){
                            kr = i;
                            kc = j;
                        }
                    }
                }
                for(int k=0; k<8; k++){
                    for(int l=0; l<8; l++){
                        int size = g->getMoveBoard(k,l).size();
                        for(int x=0; x<size; x++){
                             if(g->getMoveBoard(k,l)[x].second == "k1"){
                                moves.first = "  ";
                                moves.first[0] = 'a' + kc;
				                moves.first[1] =  '8' - kr;
				                moves.second = "  ";
				                moves.second[0] = 'a' + l;
				                moves.second[1] = '8' - k;
                                kingMovelists.emplace_back(moves);
                            }
                        }
                    }
                }
            } else {
                for(int i=0; i < 8; i++){
                    for(int j=0; j < 8; j++){
                        if (g->getBoard(i,j) == nullptr) continue;
                        if (g->getBoard(i,j)->getColour != 'b') continue;
                        idstring = g->getBoard(i, j)->getID();
                        for(int k=0; k < 8; k++){
                            for(int l=0; l < 8; l++){
                                int size = g->getMoveBoard(k,l).size();
                                for(int m=0; m < size; m++){
                                    if(g->getMoveBoard(k, l)[m].second == idstring) {//i,j 移动前坐标; k,l 移动后坐标
                                        moves.first = "  ";
                                        moves.first[0] = 'a' + j;
                                        moves.first[1] =  '8' - i;
                                        moves.second = "  ";
                                        moves.second[0] = 'a' + l;
                                        moves.second[1] = '8' - k;
                                        Movelists.emplace_back(moves);
                                    }
                                }   
                            }   
                        }
                    }
                }
            }
        }
        if(!kingMovelists.empty()){    
            srand (time(NULL));
            int size = kingMovelists.size();
            int index = rand() % size;
            finalMove = "move " +  kingMovelists[index].first + " " + kingMovelists[index].second;
        }else{
            srand (time(NULL));
            int size = Movelists.size();
            int index = rand() % size;
            finalMove = "move " +  Movelists[index].first + " " + Movelists[index].second;
        }
        g->notify(finalMove);
	} else {
		cout << "Invalid command." << endl;
		makeMove();
	}
}
