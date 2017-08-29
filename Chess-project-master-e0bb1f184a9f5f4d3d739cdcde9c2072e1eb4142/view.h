#ifndef _VIEW_H_
#define _VIEW_H_

class View {
 public:
  virtual void notify(int oldr,int oldc,int newr,int newc,char name) = 0; 
  virtual ~View() = default;
};
#endif
