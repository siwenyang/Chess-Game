#include "computer.h"
#include "piece.h"
#include "game.h"
#include "player.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

PlayerAI3(Game *g, char team):g(g),team(team){}

char oppositeTeam(char team){
	if (team == 'b')
	{
		return 'w';
	}
	else if (team == 'w')
	{
		return 'b'
	}
}
					

void PlayerAI3::makemove(){
	vector<pair<string, string>> Movelists;
    vector<pair<string, string>> captureCheckLists;
    pair<string, string> moves;
	string idstring;
	string finalmove;

	string cmd;
	cin >> cmd;

	if (cin.eof()) return;

	if (cmd == "move")
	{

		if(team = 'w'){
            if(g->check('K')){
                for(int i=0; i<8; i++){
                    for(int j=0; j<8; j++){
                        if(g->getBoard(i, j)->getID() == "K1"){
                            kr = i;
                            kc = j;
                        }
                    }
                }
                for(int k=0; k<8; k++){
                    for(int l=0; l<8; l++){
                        for(int x=0; x<g->getMoveBoard(k,l).size(); x++){
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
            }
        }

        if(team = 'b'){
            if(g->check('k')){
                for(int i=0; i<8; i++){
                    for(int j=0; j<8; j++){
                        if(g->getBoard(i, j)->getID() == "k1"){
                            kr = i;
                            kc = j;
                        }
                    }
                }
                for(int k=0; k<8; k++){
                    for(int l=0; l<8; l++){
                        for(int x=0; x<g->getMoveBoard(k,l).size(); x++){
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
            }
        }

		for (int i = 0; i<8; ++i)
		{
			for (int j = 0; j<8; ++j)
			{
			 	Piece *temp = g->getBoard(i,j);

			 	if(temp->getColour() == team)
			 	{

			 		idstring = temp->getID();

			 		for (int m = 0; m < 8; ++m)
			 		{
			 			for (int n = 0; n < 8; ++n)
			 			{
			 				for (int k = 0; k < g->getMoveBoard(m,n)[k].size(); ++k)
			 				{

			 					if (g->getMoveBoard(m,n)[k].second == idstring)
			 					{
			 						if (!checkMoveBoardAt(m,n,"*",oppositeTeam(team)))
			 						{
			 							moves.first = "  ";
			 							moves.first[0] = 'a' + j;
			 							moves.first[1] = '8' - 'i';
			 							moves.second = "  ";
			 							moves.second[0] = 'a' + n;
			 							moves.second[1] = '8' - m;
			 							catureCheckLists.emplace_back(moves);
			 						}

				 					else if (!g->getBoard(m,n).empty())
				 					{
				 						moves.first = "  ";
				 						moves.first[0] = 'a' + j;
				 						moves.first[1] = '8' - i;
				 						moves.second = "  ";
				 						moves.second[0] = 'a' + n;
				 						moves.second[1] = '8' - m;
				 						captureCheckLists.emplace_back(moves);
				 					}

				 					else if(g->isKingInRange(i, j, k, l, team))
				 					{
	                                    moves.first = "  ";
	                                    moves.first[0] = 'a' + j;
					                    moves.first[1] =  '8' - i;
					                    moves.second = "  ";
					                    moves.second[0] = 'a'+l;
					                    moves.second[1] = '8' - k;
	                                    Movelists.emplace_back(moves);
                                	}

				 					else 
				 					{
				 						moves.first = "  ";
				 						moves.first[0] = 'a' + j;
				 						moves.first[1] = '8' - i;
				 						moves.second = "  ";
				 						moves.second[0] = 'a' + n;
				 						moves.second[1] = '8' - m;
				 						MoveLists.emplace_back(moves);
				 					}
				 				}
				 			}
				 		}
				 	}
				}
			}
		}
	}

	if(captureCheckLists.size() == 0)
	{
        int index = rand() % Movelists.size();
        finalMove = "move " +  Movelists[index].first + " " + Movelists[index].second;
    }
    else
    {
        int index = rand() % captureCheckLists.size();
        finalMove = "move " +  capyureCheckLists[index].first + " " + captureCheckLists[index].second;
    }

	g->notify(finalmove);

	else
	{
		cout << "Invalid command, please try again!" << endl;
		g->message("Invalid command, please try again");
	}
}

	//checkMoveBoardAt(r,c, "*", color(opposite));