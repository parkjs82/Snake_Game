#include <fstream>
#include "MakeField.h"
#include "Shapes.cpp"
#include "Snake.h"

void drawField(makeField F,snake S){
  clear();
  for(int i = 0;i<S.length;i++){
    F.field[S.baem[i].colunm][S.baem[i].row] = 3;
  }
  F.field[S.baem[0].colunm][S.baem[0].row]++;
  for(int i = 0; i< F.height;i++)
  {
    for(int j = 0;j<F.width;j++){
      if (F.field[i][j] == 0){appendEmptySpace();}
      else if(F.field[i][j] == 1 || F.field[i][j] == 2){appendWall();}
      else if(F.field[i][j] == 3){appendSnakeHead();}
      else if(F.field[i][j] == 4){appendSnakeBody();}
      else if(F.field[i][j] == 5){appendGrowthItem();}
      else if(F.field[i][j] == 6){appendPoisonItem();}
      else if(F.field[i][j] == 7){appendDoor();}
    }
    printw("\n");
  }
  refresh();
  for(int i = 0;i<S.length;i++){
    F.field[S.baem[i].colunm][S.baem[i].row] = 0;
  }
}
int main()
{
initscr(); // Curses모드시작

std::string mapFile = "plainMap.txt";
makeField F = makeField(21,21,mapFile);
snake S;

initShape();
drawField(F,S);
while(true){
  int pressedKey = getch();
  if(pressedKey == KEY_UP){
    S.move(1);
    drawField(F,S);
  }
  else if(pressedKey == KEY_DOWN){
    S.move(3);
    drawField(F,S);
  }
  else if(pressedKey == KEY_RIGHT){
    S.move(2);
    drawField(F,S);
  }
  else if(pressedKey == KEY_LEFT){
    S.move(4);
    drawField(F,S);
  }
  if(pressedKey == 'q'){
    break;
  }
}

endwin(); // Curses모드종료
return 0;
}
