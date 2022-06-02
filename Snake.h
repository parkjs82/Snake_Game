#include <iostream>

class partOfSnake
{
public:
  int row, colunm, direction = 2;

  partOfSnake(int row = 0, int colunm = 0);
};
class snake
{
public:
  int length;
  int direction;
  bool addicted;
  bool full;
  bool death;
  partOfSnake baem[30];
  int door[4];
  snake(int length=3,int direction=4);

  void move(int direction);
  void moveHead(int direction);
  void reduceLength();
  void growthLength();
  void go();
  void warp();
};
