#ifndef SHAPES
#define SHAPES

#include <curses.h>

#define EMPTY_SPACE 1
#define WALL 2
#define SNAKE_HEAD 3
#define SNAKE_BODY 4
#define GROWTH_ITEM 5
#define POISON_ITEM 6
#define DOOR 7
#define TEXT 8
#define BOARD 9

void initShape(){
  start_color();
  init_pair(EMPTY_SPACE, COLOR_BLACK, COLOR_GREEN);
  init_pair(WALL, COLOR_BLACK, COLOR_BLUE);
  init_pair(SNAKE_HEAD, COLOR_BLACK, COLOR_RED);
  init_pair(SNAKE_BODY, COLOR_BLACK, COLOR_YELLOW);
  init_pair(GROWTH_ITEM, COLOR_BLACK, COLOR_CYAN);
  init_pair(POISON_ITEM, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(DOOR, COLOR_BLACK, COLOR_WHITE);
  init_pair(TEXT, COLOR_WHITE, COLOR_BLACK);
  init_pair(BOARD, COLOR_BLACK, COLOR_WHITE);
}

void appendEmptySpace(){
  attron(COLOR_PAIR(EMPTY_SPACE));
  printw(" ");
  printw(" ");
  attroff(COLOR_PAIR(EMPTY_SPACE));
}

void appendWall(){
  attron(COLOR_PAIR(WALL));
  addch(' ');
  addch(' ');
  attroff(COLOR_PAIR(WALL));
}

void appendSnakeHead(){
  attron(COLOR_PAIR(SNAKE_HEAD));
  addch(' ');
  addch(' ');
  attroff(COLOR_PAIR(SNAKE_HEAD));
}

void appendSnakeBody(){
  attron(COLOR_PAIR(SNAKE_BODY));
  addch(' ');
  addch(' ');
  attroff(COLOR_PAIR(SNAKE_BODY));
}

void appendGrowthItem(){
  attron(COLOR_PAIR(GROWTH_ITEM));
  addch(' ');
  addch(' ');
  attroff(COLOR_PAIR(GROWTH_ITEM));
}

void appendPoisonItem(){
  attron(COLOR_PAIR(POISON_ITEM));
  addch(' ');
  addch(' ');
  attroff(COLOR_PAIR(POISON_ITEM));
}

void appendDoor(){
  attron(COLOR_PAIR(DOOR));
  addch(' ');
  addch(' ');
  attroff(COLOR_PAIR(DOOR));
}

#endif
