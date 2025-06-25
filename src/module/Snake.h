#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>

class PartOfSnake {
 public:
  int row, column, direction = 2;

  PartOfSnake(int row = 0, int column = 0);
};
class Snake {
 public:
  int length;
  int direction;
  bool addicted;
  bool full;
  bool death;
  PartOfSnake baem[30];
  int door[4];
  Snake(int length = 3, int direction = 4);

  void move(int direction);
  void moveHead(int direction);
  void reduceLength();
  void growthLength();
  void go();
};

#endif