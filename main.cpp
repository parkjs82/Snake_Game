#include <fstream>
#include "MakeField.h"
#include "Shapes.cpp"
#include "Snake.h"
int main()
{
initscr(); // Curses모드시작

std::string mapFile = "plainMap.txt";
makeField F = makeField(21,21,mapFile);
initShape();
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
refresh(); //실제스크린에출력
getch(); //사용자입력대기
endwin(); // Curses모드종료
return 0;
}
