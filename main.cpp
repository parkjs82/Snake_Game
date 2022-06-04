#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <time.h>
#include "MakeField.h"
#include "Shapes.cpp"
#include "Snake.h"
#include "string"

#define _sleep(x) usleep(x * 1000)

double score = 0.0;

void eventManager(makeField &F, snake &S){
  int event = F.field[S.baem[0].row][S.baem[0].colunm];
  switch (event) {
    case 1:
    case 2:
      S.death = true;
      break;
    case 5:
      S.growthLength();
      score += 10;
      break;
    case 6:
      S.reduceLength();
      score += 10;
      break;
    case 7:
      // S.warp();
      if(S.baem[0].row == S.door[0] && S.baem[0].colunm==S.door[1]){
        S.baem[0].row = S.door[2];
        S.baem[0].colunm = S.door[3];
        if(S.door[2] == 0)
          S.moveHead(3);
        else if(S.door[2] == 20)
          S.moveHead(1);
        else if(S.door[3] == 0)
          S.moveHead(2);
        else if(S.door[3] == 20)
          S.moveHead(4);
        else if(S.direction == 3){
          if(F.field[S.door[2]+1][S.door[3]] == 0)
            S.moveHead(3);
          else
            S.moveHead((S.direction%4)+1);
          }
        else if(S.direction == 1){
          if(F.field[S.door[2]-1][S.door[3]] == 0)
            S.moveHead(1);
          else
            S.moveHead((S.direction%4)+1);
          }
        else if(S.direction == 2){
          if(F.field[S.door[2]][S.door[3]+1] == 0)
            S.moveHead(2);
          else
            S.moveHead((S.direction%4)+1);
          }
        else if(S.direction == 4){
          if(F.field[S.door[2]][S.door[3]-1] == 0)
            S.moveHead(4);
          else
            S.moveHead((S.direction%4)+1);
          }
      }
      else if(S.baem[0].row == S.door[2] && S.baem[0].colunm==S.door[3]){
        S.baem[0].row = S.door[0];
        S.baem[0].colunm = S.door[1];
        if(S.door[0] == 0)
          S.moveHead(3);
        else if(S.door[0] == 20)
          S.moveHead(1);
        else if(S.door[1] == 0)
          S.moveHead(2);
        else if(S.door[1] == 20)
          S.moveHead(4);
        else if(S.direction == 3){
          if(F.field[S.door[0]+1][S.door[1]] == 0)
            S.moveHead(3);
          else
            S.moveHead((S.direction%4)+1);
          }
        else if(S.direction == 1){
          if(F.field[S.door[0]-1][S.door[1]] == 0)
            S.moveHead(1);
          else
            S.moveHead((S.direction%4)+1);
          }
        else if(S.direction == 2){
          if(F.field[S.door[0]][S.door[1]+1] == 0)
            S.moveHead(2);
          else
            S.moveHead((S.direction%4)+1);
          }
        else if(S.direction == 4){
          if(F.field[S.door[0]][S.door[1]-1] == 0)
            S.moveHead(4);
          else
            S.moveHead((S.direction%4)+1);
          }
      }
      break;
  }
  for(int i = 1;i<S.length;i++){
    if(S.baem[0].row == S.baem[i].row && S.baem[0].colunm == S.baem[i].colunm)
      S.death = true;
  }
  if(S.length < 3)
    S.death = true;
}

void drawScore(WINDOW* scoreBoard, double score)
{
  std::string str = "Score: " + std::to_string((int)score);
  char* scoreStr = new char[str.size() + 1];
  for(int i = 0; i <= str.size(); i++)
    scoreStr[i] = str[i];
  
  wbkgd(scoreBoard, COLOR_PAIR(2));
  wattron(scoreBoard, COLOR_PAIR(2));
  mvwprintw(scoreBoard, 1, 1, scoreStr);
  wborder(scoreBoard, '|','|','-','-','+','+','+','+');
  wrefresh(scoreBoard);
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

  static bool mk_door1 = true;
  while(mk_door1){
    S.door[0] = rand()%21; S.door[1] = rand()%21;
    if(F.field[S.door[0]][S.door[1]] != 1) continue;
    S.door[0] = 8;
    S.door[1] = 5;
    F.field[S.door[0]][S.door[1]] = 7;
    mk_door1 = false;
  }
  static bool mk_door2 = true;
  while(mk_door2){
    S.door[2] = rand()%21; S.door[3] = rand()%21;
    if((F.field[S.door[2]][S.door[3]] != 1) || (S.door[0]==S.door[2] && S.door[1]==S.door[3])) continue;
    S.door[2] = 16;
    S.door[3] = 8;
    F.field[S.door[2]][S.door[3]] = 7;
    mk_door2 = false;
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
WINDOW* scoreBoard;
resize_term(22, 80);
initscr(); // Curses모드시작
scoreBoard = newwin(4, 15, 1, 45);

noecho();
curs_set(0);
nodelay(stdscr, TRUE);

std::string mapFile = "plainMap.txt";
makeField F = makeField(21,21,mapFile);
snake S;

initShape();

while(true){
  _sleep(500);

  score += 0.5;
  //std::cout<< score << std::endl;

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

  drawScore(scoreBoard, score);
  drawField(F, S);
  refresh();

  for(int i = 0;i < S.length; i++){
    F.field[S.baem[i].row][S.baem[i].colunm] = 0;
  }
}
endwin(); // Curses모드종료

return 0;
}
