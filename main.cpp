#include <fstream>
#include "MakeField.h"
#include "Shapes.cpp"
#include "Snake.h"

void drawField(makeField& F,snake& S){
  for(int i = 0;i<S.length;i++){
    F.field[S.baem[i].row][S.baem[i].colunm] = 3;
  }
  F.field[S.baem[0].row][S.baem[0].colunm]++;

  for(int i = 0; i< F.getHeigth();i++){
    move(i+1,2);
    for(int j = 0;j<F.getWidth();j++){
      if (F.field[i][j] == 0){appendEmptySpace();}
      else if(F.field[i][j] == 1 || F.field[i][j] == 2){appendWall();}
      else if(F.field[i][j] == 3){appendSnakeHead();}
      else if(F.field[i][j] == 4){appendSnakeBody();}
      else if(F.field[i][j] == 5){appendGrowthItem();}
      else if(F.field[i][j] == 6){appendPoisonItem();}
      else if(F.field[i][j] == 7){appendDoor();}
    }
  }
}

int main()
{
initscr(); // Curses모드시작
noecho();


std::string mapFile = "plainMap.txt";
makeField F = makeField(21,21,mapFile);
snake S;

initShape();
while(true){
  if(S.gameOver())
    break;

  if(F.field[S.baem[0].row][S.baem[0].colunm] == 5){
    S.growthLength();
  }
  if(F.field[S.baem[0].row][S.baem[0].colunm] == 6){
    S.reduceLength();
  }

  clear();

  drawField(F, S);
  
  refresh();
  for(int i = 0;i<S.length;i++){
    F.field[S.baem[i].row][S.baem[i].colunm] = 0;
  }

  F.field[11][11] = 5;
  F.field[9][9] = 6;

  int pressedKey = getch();
  if(pressedKey == 'w'){
    S.move(1);
  }
  else if(pressedKey == 's'){
    S.move(3);
  }
  else if(pressedKey == 'd'){
    S.move(2);
  }
  else if(pressedKey == 'a'){
    S.move(4);
  }
  if(pressedKey == 'q'){
    break;
  }
}
endwin(); // Curses모드종료
return 0;
}
