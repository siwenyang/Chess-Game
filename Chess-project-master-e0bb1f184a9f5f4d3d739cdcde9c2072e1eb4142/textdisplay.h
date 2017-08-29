#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "view.h"

class TextDisplay : public View {
  std::vector<std::vector<char> > theDisplay;
 public:
  TextDisplay();

  void notify(int oldr,int oldc,int newr,int newc,char name = '*',char color = '*');
  ~TextDisplay();
  void print();
  void clear();
};

#endif
