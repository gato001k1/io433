#ifndef SIMPLEMENU_H
#define SIMPLEMENU_H

#define _SM_MAXCHILD 4

class SimpleMenu {
  
protected:
  
  int ci = 0;
  int selected = 0;
  
public:
  char* name = "NULL";
  SimpleMenu *parent = NULL;
  SimpleMenu *child[_SM_MAXCHILD];
  bool alertDone = true;
  typedef void (*Callback)();
  typedef void (*CallbackWithParam)(int);
  int param = -1;
  Callback actionSelect = NULL;
  Callback actionEnd = NULL;
  CallbackWithParam actionSelectWithParam = NULL;
  
  SimpleMenu(char* value);
  SimpleMenu(char* value, SimpleMenu* par);
  SimpleMenu(char* value, SimpleMenu* par, Callback action);
  SimpleMenu(char* value, SimpleMenu* par, CallbackWithParam action, int param);
  SimpleMenu(char* value, SimpleMenu* par, Callback action, Callback actionend);
  void setParent(SimpleMenu *par); 
  void addChild(SimpleMenu *par);
  int  getChildNum();  
  void setAction(Callback action);
  void setActionWithParam(CallbackWithParam action);
  void setSelectedChild(int s);
  int getSelectedChild();
    
};

#endif

