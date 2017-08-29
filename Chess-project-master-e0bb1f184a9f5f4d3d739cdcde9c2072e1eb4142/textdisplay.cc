#include <iostream>
#include <string>
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(){
	vector<char> row{10,'*'};
	theDisplay.assign(10,row);
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 10; ++j){
			if (i == 8) {
				theDisplay[i][j] = ' ';
			} else if (i == 9) {
				if (j >= 2) {
					theDisplay[i][j] = 'a' + j - 2;
				} else {
					theDisplay[i][j] = ' ';
				}
			} else if (j == 0) {
				theDisplay[i][j] = '8' - i;
			} else if (j == 1){
				theDisplay[i][j] = ' ';
			} else if ((i + j) % 2 == 1){
				theDisplay[i][j] = '_';
			} else {
				theDisplay[i][j] = ' ';;
			}
		}
	}
}

TextDisplay::~TextDisplay() {}

void TextDisplay::clear(){
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			notify(i,j,-1,-1);
		}
	}
}

void TextDisplay::notify(int oldr,int oldc,int newr,int newc,char name,char color) {
	if ((oldr != -1) && (oldc != -1)) {
		if((oldr+oldc)%2==0) {
			theDisplay[oldr][oldc+2] = ' ';
		} else {
			theDisplay[oldr][oldc+2] = '_';
		}
	}
	if ((newr != -1) && (newc != -1)) {
		theDisplay[newr][newc+2] = name;
	}
	// print();
}

void TextDisplay::print(){
	//cerr << "start out td" << endl;
	for(int i = 0; i < 10; ++i){
		for(int k = 0; k < 10; ++k){
			//cerr << "out td" << endl;
			cout << theDisplay[i][k];
		}
		cout << endl;
	}
}
