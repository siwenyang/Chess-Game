#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include "window.h"
#include "view.h"

class GraphicsDisplay : public View {
	Xwindow *xw;
public:
	GraphicsDisplay();
	void notify(int oldr,int oldc,int newr,int newc,char name = '*',char color = '*');
	void message(std::string);
	void whoIsNext(int t);
	~GraphicsDisplay();
	void clear();
};

#endif
