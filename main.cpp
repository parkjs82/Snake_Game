#include <fstream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <time.h>
#include "MakeField.h"
#include "Shapes.cpp"
#include "Snake.h"
#include "string"
#include "./Score.h"

#define _sleep(x) usleep(x * 1000)

void eventManager(makeField &F, snake &S, Score &score){
  int event = F.field[S.baem[0].row][S.baem[0].colunm];
  switch (event) {
    case 1:
    case 2:
      S.death = true;
      break;
    case 5:
      S.growthLength();
      score.growthItems();
      break;
    case 6:
      S.reduceLength();
      score.posionItems();
      break;
    case 7:
      score.useGate();
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
void makeEvent(makeField& F,snake& S){
  for(int i = 0;i<S.length;i++){
      F.field[S.baem[i].row][S.baem[i].colunm] = 3;
  }
  F.field[S.baem[0].row][S.baem[0].colunm]++;

  srand(time(NULL));
  static int count_temp = 19;
  static int g_x=1, g_y = 1, r_x = 1, r_y = 1;

  count_temp++;

  if(count_temp==20){
    count_temp=0;
    if(F.field[g_x][g_y] == 5){F.field[g_x][g_y] = 0;}
    if(F.field[r_x][r_y] == 6){F.field[r_x][r_y] = 0;}

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
    F.field[S.door[0]][S.door[1]] = 7;
    mk_door1 = false;
  }
  static bool mk_door2 = true;
  while(mk_door2){
    S.door[2] = rand()%21; S.door[3] = rand()%21;
    if((F.field[S.door[2]][S.door[3]] != 1) || (S.door[0]==S.door[2] && S.door[1]==S.door[3])) continue;
    F.field[S.door[2]][S.door[3]] = 7;
    mk_door2 = false;
  }
}
void drawScore(WINDOW* scoreBoard, Score& score, char nickname[]){
  std::string str = "Score: " + std::to_string(score.getScore());
  char* scoreStr = new char[str.size() + 1];
  for(int i = 0; i <= str.size(); i++)
    scoreStr[i] = str[i];

  char plus[2];
  plus[0] = score.getGrowth() + '0'; plus[1] = '\0';

  char minus[2];
  minus[0] = score.getPosion() + '0'; minus[1] = '\0';

  char len[2];
  len[0] = score.getLen() + '0'; len[1] = '\0';

  char G[2];
  G[0] = score.getGate() + '0'; G[1] = '\0';

  wbkgd(scoreBoard, COLOR_PAIR(9));
  wattron(scoreBoard, COLOR_PAIR(9));
  mvwprintw(scoreBoard, 1, 2, "Score Bored");
  mvwprintw(scoreBoard, 2, 1, "User: "); mvwprintw(scoreBoard, 2, 7, nickname);
  mvwprintw(scoreBoard, 3, 1, scoreStr);
  mvwprintw(scoreBoard, 4, 1, "B: "); mvwprintw(scoreBoard, 4, 4, len);
  mvwprintw(scoreBoard, 5, 1, "+: "); mvwprintw(scoreBoard, 5, 4, plus);
  mvwprintw(scoreBoard, 6, 1, "-: "); mvwprintw(scoreBoard, 6, 4, minus);
  mvwprintw(scoreBoard, 7, 1, "G: "); mvwprintw(scoreBoard, 7, 4, G);
  wborder(scoreBoard, '|','|','-','-','+','+','+','+');
  wrefresh(scoreBoard);
}
void drawMission(WINDOW* missionBoard, Score& score){

  // static int plus = rand()%15, minus = rand()%15, G = rand()%6, B;

  wbkgd(missionBoard, COLOR_PAIR(9));
  wattron(missionBoard, COLOR_PAIR(9));
  mvwprintw(missionBoard, 1, 4, "Mission");
  mvwprintw(missionBoard, 2, 1, "B: ");
  mvwprintw(missionBoard, 3, 1, "+: "); //mvwprintw(missionBoard, 3, 4, (char)(plus+48));
  mvwprintw(missionBoard, 4, 1, "-: "); //mvwprintw(missionBoard, 4, 4, (char)(minus+48));
  mvwprintw(missionBoard, 5, 1, "G: "); //mvwprintw(missionBoard, 5, 4, (char)(G+48));
  wborder(missionBoard, '|','|','-','-','+','+','+','+');
  wrefresh(missionBoard);
}

void drawField(makeField& F,snake& S){
  for(int i = 0; i< F.getHeigth();i++){
    move(i + 1, 0);
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
  resize_term(22, 80);
  initscr(); // Curses모드시작

  char nickName[7];
  attron(COLOR_PAIR(8));
  printw("Enter User nickname: ");
  attroff(COLOR_PAIR(8));
  scanw("%s", nickName);

  std::string maps[4] = {"CircleMap.txt", "plainMap.txt", "CrossMap.txt", "CircleMap.txt"};

  bool next = true;
  int test = 2, map_count=0;
  while(next){
    if(test == 0)
      next = false;
    test -= 1;

    WINDOW* scoreBoard;
    WINDOW* missionBoard;
    scoreBoard = newwin(9, 15, 1, 43);
    missionBoard = newwin(7, 15, 12, 43);

    refresh();

    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    std::string mapFile = maps[map_count];
    makeField F = makeField(21,21,mapFile);
    snake S;
    Score score;

    clear();
    initShape();

    while(true){
      _sleep(500);

      score.time();
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

      eventManager(F,S,score);
      makeEvent(F,S);
      if(S.death)
        break;

      drawScore(scoreBoard, score, nickName);
      drawMission(missionBoard, score);
      drawField(F, S);
      refresh();

      for(int i = 0;i < S.length; i++){
        F.field[S.baem[i].row][S.baem[i].colunm] = 0;
      }
    }
    map_count++;
  }

  nodelay(stdscr, FALSE);

  attron(COLOR_PAIR(8));
  printw("\nEscape any press key");
  attroff(COLOR_PAIR(8));

  refresh();
  getchar();

  clear();
  endwin(); // Curses모드종료

  return 0;
}
