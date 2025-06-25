#include <fstream>
#include <iostream>

class MakeField {
 public:
  int itemCount;
  bool mkG1;
  bool mkG2;
  int width, height;
  int **field;

  MakeField(int width = 21, int height = 21, std::string mapFile = "NonInput");
  ~MakeField();
  int getWidth() { return width; }
  int getHeigth() { return height; }
};
