#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <time.h>
#include "MakeField.h"
#include "Shapes.cpp"
#include "Snake.h"

#define _sleep(x) usleep(x * 1000)

void eventManager(makeField &F, snake &S){
  int event = F.field[S.baem[0].row][S.baem[0].colunm];
  switch (event) {
    case 1:
    case 2:
      S.death = true;
      break;
    case 5:
      S.growthLength();
      break;
    case 6:
      S.reduceLength();
      break;
    case 7:
      break;
  }
  for(int i = 1;i<S.length;i++){
    if(S.baem[0].row == S.baem[i].row && S.baem[0].colunm == S.baem[i].colunm)
      S.death = true;
  }
  if(S.length < 3)
    S.death = true;
}
void drawField(makeField& F,snake& S){
  srand(time(NULL));
  static int count_temp = 0;
  static int g_x=1, g_y = 1, r_x = 1, r_y = 1;

  count_temp++;

  if(count_temp==20){
    count_temp=0;

    F.field[g_x][g_y] = 0;
    F.field[r_x][r_y] = 0;
    bool mk = true;
    while(mk){
      g_x = rand()%20, g_y = rand()%20;
      if(F.field[g_x][g_y] != 0) continue;
      F.field[g_x][g_y] = 5;
      mk=false;
    }
    mk = true;
    while(mk){
      r_x = rand()%20, r_y = rand()%20;
      if(F.field[r_x][r_y] != 0) continue;
      F.field[r_x][r_y] = 6;
      mk=false;
    }
  }

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

int tic = clock();

int main()
{
initscr(); // Curses모드시작
noecho();
curs_set(0);
nodelay(stdscr, TRUE);

std::string mapFile = "plainMap.txt";
makeField F = makeField(21,21,mapFile);
snake S;
// bool gameState = false;
initShape();

while(true){
  _sleep(500);

  char pressedKey = getch();

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
  else{
    S.go();
  }
  if(pressedKey == 'q'){
    break;
  }

  eventManager(F,S);
  if(S.death)
    break;

  clear();
  drawField(F, S);
  refresh();

  for(int i = 0;i < S.length; i++){
    F.field[S.baem[i].row][S.baem[i].colunm] = 0;
  }
}
endwin(); // Curses모드종료
return 0;
}
