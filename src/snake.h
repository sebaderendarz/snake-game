#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#define START_SLEEP 100

class CSnake:public CFramedWindow
{
  list< CPoint * > snake_body;
  CPoint food;
  int prev_key;
  bool play;
  bool help;
  bool game_over;
public:
  CSnake(CRect r, char _c = ' ');
  ~CSnake();

  void paint();
  void paint_help();
  void paint_level();
  void paint_game_over();
  void paint_snake();
  void paint_food();
  void restart_game();
  void clear_snake_body();
  void new_food(); // maybe bool
  void move_snake(int key);
  bool handleEvent(int key);

};

#endif
