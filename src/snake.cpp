#include "snake.h"
#include "screen.h"
#include "time.h"

CSnake::CSnake(CRect r, char _c): CFramedWindow(r, _c){

  srand(time(NULL));
  restart_game();
}

CSnake::~CSnake(){

  clear_snake_body();
}

void CSnake::clear_snake_body(){

  snake_body.clear();
}

void CSnake::paint(){

  CFramedWindow::paint();
  paint_snake();
  paint_food();

  if (game_over == true){

    paint_game_over();
  }
  else{
    
    paint_level();
  }

  if (help == true){

    paint_help();
  }
}

void CSnake::paint_help(){

  gotoyx(geom.topleft.y + 4, geom.topleft.x + 3);
  printl("h - toggle help information");
  gotoyx(geom.topleft.y + 5, geom.topleft.x + 3);
  printl("p - toggle pause/play mode");
  gotoyx(geom.topleft.y + 6, geom.topleft.x + 3);
  printl("r - restart game");
  gotoyx(geom.topleft.y + 7, geom.topleft.x + 3);
  printl("arrows - move snake (in play mode) or");
  gotoyx(geom.topleft.y + 8, geom.topleft.x + 12);
  printl("move window (in pause mode)");
}

void CSnake::paint_level(){

  gotoyx(geom.topleft.y - 1, geom.topleft.x);
  printl("| LEVEL: %d |", snake_body.size() / 3);
}

void CSnake::paint_game_over(){

  gotoyx(geom.topleft.y + 1, geom.topleft.x + 1);
  printl("GAME OVER, result: %d", snake_body.size());
}

void CSnake::paint_snake(){

  for (list< CPoint * >::iterator i = snake_body.begin(); i != snake_body.end(); i++){
  
    gotoyx(geom.topleft.y + (*i)->y, geom.topleft.x + (*i)->x);

    if ((*i)->x == snake_body.back()->x && (*i)->y == snake_body.back()->y){

      printl("*");
    }
    else{

      printl("+");
    }
  }
}

void CSnake::paint_food(){

  gotoyx(geom.topleft.y + food.y, geom.topleft.x + food.x);
  printl("O");
}

void CSnake::restart_game(){

  clear_snake_body();

  snake_body.push_back(new CPoint(3, 2));
  snake_body.push_back(new CPoint(4, 2));
  snake_body.push_back(new CPoint(5, 2));

  food.x = geom.size.x/2;
  food.y = geom.size.y/2;
  help = true;
  play = true;
  game_over = false;
}

void CSnake::new_food(){

  CPoint c;
  list< CPoint * >::iterator i;

  do{

    c.x = rand() % (geom.size.x - 2) + 1;
    c.y = rand() % (geom.size.y - 2) + 1;

    for (i = snake_body.begin(); i != snake_body.end(); i++){

      if ((*i)->x != c.x || (*i)->y != c.y){

        break;
      }
    }

  }while(i == snake_body.end());

  food.x = c.x;
  food.y = c.y;
}

bool CSnake::handleEvent(){

}
