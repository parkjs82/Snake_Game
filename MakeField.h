#include <iostream>
#include <fstream>

class makeField
{
public:
  int width, height;
  int **field;

  makeField(int width = 21, int height = 21,std::string mapFile = "NonInput");
  ~makeField();
  int getWidth(){return width;}
  int getHeigth(){return height;}
};
