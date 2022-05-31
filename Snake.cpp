#include "Snake.h"

partOfSnake::partOfSnake(int row, int colunm){
  this->row = row;
  this->colunm = colunm;
}
snake::snake(int length, int direction){
  this->length = length;
  this->direction = direction;
  this->full = false;
  this->addicted = false;
  for(int i = 0;i<length;i++)
  {
    baem[i] = partOfSnake(5,15+i);
  }
}

snake& snake::move(int direction){
  if(this->full) {growthLength();}
  if(this->addicted) {reduceLength();}
  for(int i = this->length-1;i != 0;i--){
    baem[i].row = baem[i-1].row;
    baem[i].colunm = baem[i-1].colunm;
  }
  if((this->direction-direction)%2) {moveHead(this->direction);}
  else {moveHead(direction);}
  return *this;
}
snake& snake::moveHead(int direction){
  switch (this->direction) {
    case 1:
      this->baem[0].row++;
      break;
    case 2:
      this->baem[0].colunm++;
      break;
    case 3:
      this->baem[0].row--;
      break;
    case 4:
      this->baem[0].colunm--;
      break;
  }
  return *this;
}
snake& snake::reduceLength(){
  this->length--;
  return *this;
}
snake& snake::growthLength(){
  this->baem[length] = partOfSnake(baem[length].row, baem[length].colunm);
  this->length++;
  return *this;
}
