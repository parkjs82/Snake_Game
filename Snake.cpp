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
  for(int i = 0;i<length;i++){
    baem[i] = partOfSnake(5,15+i);
  }
}

void snake::move(int direction){
  if(this->full) {growthLength();}
  if(this->addicted) {reduceLength();}
  for(int i = this->length-1;i != 0;i--){
    baem[i].row = baem[i-1].row;
    baem[i].colunm = baem[i-1].colunm;
  }
  if((this->direction-direction)%2 == 0) {moveHead(this->direction);}
  else {moveHead(direction);}
}
void snake::moveHead(int direction){
  this->direction = direction;
  switch (this->direction) {
    case 1:
      this->baem[0].row--;
      break;
    case 2:
      this->baem[0].colunm++;
      break;
    case 3:
      this->baem[0].row++;
      break;
    case 4:
      this->baem[0].colunm--;
      break;
  }
}
void snake::reduceLength(){
  this->length--;
}
void snake::growthLength(){
  this->baem[length] = partOfSnake(baem[length-1].row, baem[length-1].colunm);
  this->length++;
}
bool snake::gameOver(){
  if(this->baem[0].row == 0 || this->baem[0].row == 20)
    return true;
  
  else if(this->baem[0].colunm == 0 || this->baem[0].colunm == 20)
    return true;
  
  return false;
}
