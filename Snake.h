#include <iostream>

class partOfSnake
{
public:
  int row,colunm;

  partOfSnake(int row = 0, int colunm = 0);
};
class snake
{
public:
  int length;
  int direction;
  bool addicted;
  bool full;
  partOfSnake baem[30];
  snake(int length=3,int direction=4);

  snake& move(int direction);
  snake& moveHead(int direction);
  snake& reduceLength();
  snake& growthLength();
};
