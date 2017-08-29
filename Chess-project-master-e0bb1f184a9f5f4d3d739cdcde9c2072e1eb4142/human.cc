#include "human.h"
#include <iostream>
#include <string>
#include "game.h"

using namespace std;

Human::Human(Game *g,char team):Player(g,team){}

void Human::makeMove(){
	string cmd;
	cin >> cmd;
	if (cin.eof()) return;
	if (cmd == "resign") g->notify(cmd);
	else if (cmd == "move") {
		string pos1,pos2;
		cin >> pos1 >> pos2;
		string line = cmd + " " + pos1 + " " + pos2;
		g->notify(line);
	} else {
		cout << "Invalid command. 3" << endl;
		makeMove();
	}
}


