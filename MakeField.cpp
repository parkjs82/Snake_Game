#include "MakeField.h"

makeField::makeField(int width, int height, std::string mapFile)
{
  this->width = width;
  this->height = height;
  field = new int *[height];
  for(int i = 0; i < height; i++){
    field[i] = new int[width];
  }
  std::ifstream inputFile(mapFile);
  char line[25];
  int counter = 0;
  while(!inputFile.eof()){
    inputFile >> line;
    if(!inputFile.eof())
    {
      for(int i = 0;i < width;i++)
      {
        field[counter][i] = int(line[i])-48;
      }
    }
    counter++;
  }
  inputFile.close();
}
makeField::~makeField()
{
  for(int i = 0;i<height;i++){
    delete[] field[i];
  }
  delete[] field;
}
