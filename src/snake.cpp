#include "snake.h"
#include "winsys.h"
#include "screen.h"
#include <time.h>

CSnake::CSnake(CRect r, char _c): CFramedWindow(r, _c){

  srand(time(NULL));
  restart_game();
}

CSnake::~CSnake(){

  clear_snake_body();
}

void CSnake::clear_snake_body(){

  for (list< CPoint * >::iterator i = snake_body.begin(); i != snake_body.end(); i++){
  
    delete(*i);
  }

  snake_body.clear();
}

void CSnake::paint(){

  CFramedWindow::paint();
  paint_snake();
  paint_food();

  if (game_over){

    paint_game_over();
  }
  else{
    
    paint_level();
  }

  if (help){

    paint_help();
  }

  napms(START_SLEEP - 2 * (snake_body.size() / 3)); //adjust this value
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
  prev_key = KEY_RIGHT;
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

      if ((*i)->x == c.x && (*i)->y == c.y){

        break;
      }
    }

  }while(i != snake_body.end());

  food.x = c.x;
  food.y = c.y;
}

bool CSnake::handleEvent(int key){

  if ((help || !play || game_over)){

          gotoyx(32, 20);
      printl("CHECK sss");

    CFramedWindow::handleEvent(key);

          gotoyx(32, 60);
      printl("CHECK sss2");

    // if (CFramedWindow::handleEvent(key)){
    //       gotoyx(28, 30);
    //   printl("CHECK ttt");
    //   return true;
    // }
    
    return true;
  }

    gotoyx(31, 0);
    printl("CHECK 12 %d", key);


  if (key == 'h'){

    if (help == true){

      play = true;
      help = false;
    }
    else{

      play = false;
      help = true;
    }
  }
  else if (key == 'p'){

    play = !play;
  }
  else if (key == 'r'){

    restart_game();
  }
  else if (){

    
  }
  else if (play && !help && !game_over){
    
    if ((key == KEY_UP && prev_key != KEY_DOWN)
    || (key == KEY_RIGHT && prev_key != KEY_LEFT)
    || (key == KEY_DOWN && prev_key != KEY_UP)
    || (key == KEY_LEFT && prev_key != KEY_RIGHT)){

      move_snake(key);
      prev_key = key;
    }
    else{

      move_snake(prev_key);
    }
  }
  else{

    //move_snake(prev_key);
    return false;
  }

  return true;
}

void CSnake::move_snake(int key){

  CPoint temp;

  switch (key){

    case KEY_UP:
      temp.x = snake_body.back()->x;
      temp.y = snake_body.back()->y - 1;

    case KEY_RIGHT:
      temp.x =snake_body.back()->x + 1;
      temp.y = snake_body.back()->y;

    case KEY_DOWN:
      temp.x = snake_body.back()->x;
      temp.y = snake_body.back()->y + 1;

    case KEY_LEFT:
      temp.x =snake_body.back()->x - 1;
      temp.y = snake_body.back()->y;
  }

  if (temp.x <= 0){

    temp.x = geom.size.x - 2;
  }
  else if (temp.x > geom.size.x - 2){

    temp.x = 1;
  }

  if (temp.y <= 0){

    temp.y = geom.size.y - 2;
  }
  else if (temp.y > geom.size.y - 2){

    temp.y = 1;
  }

  for (list< CPoint * >::iterator i = snake_body.begin(); i != snake_body.end(); ++i){



    if ((*i)->x == temp.x && (*i)->y == temp.y){

    gotoyx(28, 0);
    printl("CHECK 3333");
    napms(1000);

      game_over = true;
      play = false;
      return; // maybe does not required
    }
  }

  snake_body.push_back(new CPoint(temp.x, temp.y));

  if (temp.x == food.x && temp.y == food.y){

    new_food();
  }
  else{

    delete(*snake_body.begin());
    snake_body.pop_front();
  }
}