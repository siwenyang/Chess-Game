#include <iostream>
#include "graphicsdisplay.h"
#include "view.h"
#include "window.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(): xw{new Xwindow()}{
	xw->fillRectangle(0,0,500,500, Xwindow::Black);
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			if ((i + j) % 2 == 1){
				xw->fillRectangle((j+1)*50,i*50+25,50,50,Xwindow::Brown);
			} else {
				xw->fillRectangle((j+1)*50,i*50+25,50,50,Xwindow::Orange);
			}
		}
	}
	for(int i = 0; i < 8; ++i){
		string s = " ";
		s[0] = '8' - i;
		xw->drawBigString(25,i*50+62,s,Xwindow::Yellow);
	}
	for(int i = 0; i < 8; ++i){
		string s = " ";
		s[0] = 'a' + i;
		xw->drawBigString((i+1)*50+20,455,s,Xwindow::Yellow);
	}
}

GraphicsDisplay::~GraphicsDisplay(){
	delete xw;
}

void GraphicsDisplay::clear(){
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			notify(i,j,-1,-1);
		}
	}
}

void GraphicsDisplay::notify(int oldr,int oldc,int newr,int newc,char name,char color){
	if ((oldr != -1) && (oldc != -1)) {
		if((oldr+oldc)%2==0) {
			// cout << "a" << endl;
			xw->fillRectangle((oldc+1)*50,oldr*50+25,50,50,Xwindow::Orange);
			// theDisplay[oldr][oldc+2] = ' ';
		} else {
			// cout << "b" << endl;
			xw->fillRectangle((oldc+1)*50,oldr*50+25,50,50,Xwindow::Brown);
			// theDisplay[oldr][oldc+2] = '_';
		}
	}
	if ((newr != -1) && (newc != -1)) {
		string s = " ";
		s[0] = name;
		if((newr+newc)%2==0) {
			// cout << "a" << endl;
			xw->fillRectangle((newc+1)*50,newr*50+25,50,50,Xwindow::Orange);
			// theDisplay[oldr][oldc+2] = ' ';
		} else {
			// cout << "b" << endl;
			xw->fillRectangle((newc+1)*50,newr*50+25,50,50,Xwindow::Brown);
			// theDisplay[oldr][oldc+2] = '_';
		}
		if (color == 'b') {
			xw->drawBigString((newc+1)*50+15,newr*50+60,s,Xwindow::Black);
		} else {
			xw->drawBigString((newc+1)*50+15,newr*50+60,s,Xwindow::White);
		}
		// theDisplay[newr][newc+2] = name;
	}
}

void GraphicsDisplay::whoIsNext(int t){
	if (t) {
		xw->fillRectangle(0,0,500,25,Xwindow::Black);
		xw->drawString(230,12,"Black's turn",Xwindow::White);
	} else {
		xw->fillRectangle(0,0,500,25,Xwindow::Black);
		xw->drawString(230,12,"White's turn",Xwindow::White);
	}
}

void GraphicsDisplay::message(string msg){
	xw->fillRectangle(0,465,500,40,Xwindow::Black);
	xw->drawString(100,475,msg,Xwindow::Green);
}



