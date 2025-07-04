#include "Snake.h"

PartOfSnake::PartOfSnake(int row, int column) {
  this->row = row;
  this->column = column;
}
Snake::Snake(int length, int direction) {
  this->length = length;
  this->direction = direction;
  this->full = false;
  this->addicted = false;
  this->death = false;
  for (int i = 0; i < length; i++) {
    baem[i] = PartOfSnake(5, 15 + i);
  }
}

void Snake::move(int direction) {
  this->direction = direction;
  if (this->full) {
    growthLength();
  }
  if (this->addicted) {
    reduceLength();
  }
  for (int i = this->length - 1; i != 0; i--) {
    baem[i].row = baem[i - 1].row;
    baem[i].column = baem[i - 1].column;
  }
  if ((this->direction - direction) % 2 == 0) {
    moveHead(this->direction);
  } else {
    moveHead(direction);
  }
}
void Snake::moveHead(int direction) {
  this->direction = direction;
  switch (this->direction) {
    case 1:
      this->baem[0].row--;
      break;
    case 2:
      this->baem[0].column++;
      break;
    case 3:
      this->baem[0].row++;
      break;
    case 4:
      this->baem[0].column--;
      break;
  }
}
void Snake::reduceLength() { this->length--; }
void Snake::growthLength() {
  this->baem[length] =
      PartOfSnake(baem[length - 1].row, baem[length - 1].column);
  this->length++;
}
void Snake::go() { move(this->direction); }
