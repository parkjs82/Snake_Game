#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include "./module/MakeField.h"
#include "./module/Snake.h"
#include "./module/Score.h"
#include "./module/Shapes.cpp"

#define _sleep(x) usleep(x * 1000)

void eventManager(makeField &F, snake &S, Score &score)
{
  int event = F.field[S.baem[0].row][S.baem[0].colunm];
  switch (event)
  {
  case 1:
  case 2:
    S.death = true;
    break;
  case 5:
    F.itemCount--;
    S.growthLength();
    score.growthItems();
    break;
  case 6:
    F.itemCount--;
    S.reduceLength();
    score.posionItems();
    break;

  case 7:
    score.useGate();
    if (S.baem[0].row == S.door[0] && S.baem[0].colunm == S.door[1])
    {
      S.baem[0].row = S.door[2];
      S.baem[0].colunm = S.door[3];
      if (S.door[2] == 0)
        S.moveHead(3);
      else if (S.door[2] == 20)
        S.moveHead(1);
      else if (S.door[3] == 0)
        S.moveHead(2);
      else if (S.door[3] == 20)
        S.moveHead(4);
      else
      {
        while(true)
        {
          if (S.direction == 1 && F.field[S.door[2] - 1][S.door[3]] == 0){
            S.moveHead(1);
            break;
          }
          if (S.direction == 2 && F.field[S.door[2]][S.door[3] + 1] == 0){
            S.moveHead(2);
            break;
          }
          if (S.direction == 3 && F.field[S.door[2] + 1][S.door[3]] == 0){
            S.moveHead(3);
            break;
          }
          if (S.direction == 3 && F.field[S.door[2]][S.door[3] - 1] == 0){
            S.moveHead(4);
            break;
          }
          S.direction = (S.direction % 4 + 1);
        }
      }
    }
    else if (S.baem[0].row == S.door[2] && S.baem[0].colunm == S.door[3])
    {
      S.baem[0].row = S.door[0];
      S.baem[0].colunm = S.door[1];
      if (S.door[0] == 0)
        S.moveHead(3);
      else if (S.door[0] == 20)
        S.moveHead(1);
      else if (S.door[1] == 0)
        S.moveHead(2);
      else if (S.door[1] == 20)
        S.moveHead(4);
        else
        {
          while(true)
          {
            if (S.direction == 1 && F.field[S.door[0] - 1][S.door[1]] == 0){
              S.moveHead(1);
              break;
            }
            if (S.direction == 2 && F.field[S.door[0]][S.door[1] + 1] == 0){
              S.moveHead(2);
              break;
            }
            if (S.direction == 3 && F.field[S.door[0] + 1][S.door[1]] == 0){
              S.moveHead(3);
              break;
            }
            if (S.direction == 3 && F.field[S.door[0]][S.door[1] - 1] == 0){
              S.moveHead(4);
              break;
            }
            S.direction = (S.direction % 4 + 1);
          }
        }
      }
      break;
    }
  for (int i = 1; i < S.length; i++)
  {
    if (S.baem[0].row == S.baem[i].row && S.baem[0].colunm == S.baem[i].colunm)
      S.death = true;
  }
  if (S.length < 3)
    S.death = true;
}
void makeEvent(makeField &F, snake &S, Score &score)
{
  for (int i = 0; i < S.length; i++)
  {
    F.field[S.baem[i].row][S.baem[i].colunm] = 3;
  }
  F.field[S.baem[0].row][S.baem[0].colunm]++;

  srand(time(NULL));
  static int g1_x = 1, g1_y = 1, g1_t = 19;
  static int g2_x = 1, g2_y = 1, g2_t = 9;
  static int r_x = 1, r_y = 1, r_t = 19;
  static bool mkP = true;
  g1_t++;
  g2_t++;
  r_t++;

  if (g1_t == 40)
  {
    g1_t = 0;
    if (F.field[g1_x][g1_y] == 5)
    {
      F.field[g1_x][g1_y] = 0;
      F.itemCount--;
    }
    F.mkG1 = true;
  }
  if (g2_t == 40)
  {
    g2_t = 0;
    if (F.field[g2_x][g2_y] == 5)
    {
      F.field[g2_x][g2_y] = 0;
      F.itemCount--;
    }
    F.mkG2 = true;
  }
  if (r_t == 40)
  {
    r_t = 0;
    if (F.field[r_x][r_y] == 6)
    {
      F.field[r_x][r_y] = 0;
      F.itemCount--;
    }
    mkP = true;
  }

  while (mkP)
  {
    r_x = rand() % 20, r_y = rand() % 20;
    if (F.field[r_x][r_y] != 0)
      continue;
    F.field[r_x][r_y] = 6;
    F.itemCount++;
    mkP = false;
  }

  while (F.mkG1)
  {
    if (F.itemCount > 2)
    {
      F.mkG1 = false;
      break;
    }
    g1_x = rand() % 20, g1_y = rand() % 20;
    if (F.field[g1_x][g1_y] != 0)
      continue;
    F.field[g1_x][g1_y] = 5;
    F.itemCount++;
    F.mkG1 = false;
  }
  while (F.mkG2)
  {
    if (F.itemCount > 2)
    {
      F.mkG2 = false;
      break;
    }
    g2_x = rand() % 20, g2_y = rand() % 20;
    if (F.field[g2_x][g2_y] != 0)
      continue;
    F.field[g2_x][g2_y] = 5;
    F.itemCount++;
    F.mkG2 = false;
  }

  static bool mk_door1 = true;
  static bool mk_door2 = true;
  if (S.length == 5)
  {
    while (mk_door1)
    {
      S.door[0] = rand() % 21;
      S.door[1] = rand() % 21;
      if (F.field[S.door[0]][S.door[1]] != 1)
        continue;
      F.field[S.door[0]][S.door[1]] = 7;
      mk_door1 = false;
    }
    while (mk_door2)
    {
      S.door[2] = rand() % 21;
      S.door[3] = rand() % 21;
      if((S.door[0] == S.door[2] || S.door[1] == S.door[3]))
        continue;
      if ((F.field[S.door[2]][S.door[3]] != 1) || (S.door[0] == S.door[2] && S.door[1] == S.door[3]))
        continue;
      F.field[S.door[2]][S.door[3]] = 7;
      mk_door2 = false;
    }
  }

  if (score.clearGame())
  {
    mk_door1 = true;
    mk_door2 = true;
  }
}
void drawScore(WINDOW *scoreBoard, Score &score, char nickname[])
{
  std::string str = "Score: " + std::to_string(score.getScore());
  char *scoreStr = new char[str.size() + 1];
  for (int i = 0; i <= str.size(); i++)
    scoreStr[i] = str[i];

  char plus[3];
  if (score.getGrowth() > 9)
  {
    plus[0] = score.getGrowth() / 10 + '0';
    plus[1] = score.getGrowth() % 10 + '0';
    plus[2] = '\0';
  }
  else
  {
    plus[0] = score.getGrowth() % 10 + '0';
    plus[1] = '\0';
  }

  char minus[3];
  if (score.getPosion() > 9)
  {
    minus[0] = score.getPosion() / 10 + '0';
    minus[1] = score.getPosion() % 10 + '0';
    minus[2] = '\0';
  }
  else
  {
    minus[0] = score.getPosion() % 10 + '0';
    minus[1] = '\0';
  }
  char len[3];
  if (score.getLen() > 9)
  {
    len[0] = score.getLen() / 10 + '0';
    len[1] = score.getLen() % 10 + '0';
    len[2] = '\0';
  }
  else
  {
    len[0] = score.getLen() % 10 + '0';
    len[1] = ' ';
    len[2] = '\0';
  }
  char maxLen[3];
  if (score.getMaxLen() > 9)
  {
    maxLen[0] = score.getMaxLen() / 10 + '0';
    maxLen[1] = score.getMaxLen() % 10 + '0';
    maxLen[2] = '\0';
  }
  else
  {
    maxLen[0] = score.getMaxLen() % 10 + '0';
    maxLen[1] = ' ';
    maxLen[2] = '\0';
  }
  char G[3];
  if (score.getGate() > 9)
  {
    G[0] = score.getGate() / 10 + '0';
    G[1] = score.getGate() % 10 + '0';
    G[2] = '\0';
  }
  else
  {
    G[0] = score.getGate() % 10 + '0';
    G[1] = '\0';
  }

  wbkgd(scoreBoard, COLOR_PAIR(9));
  wattron(scoreBoard, COLOR_PAIR(9));
  mvwprintw(scoreBoard, 1, 2, "Score Bored");
  mvwprintw(scoreBoard, 2, 1, "User: ");
  mvwprintw(scoreBoard, 2, 7, nickname);
  mvwprintw(scoreBoard, 3, 1, scoreStr);
  mvwprintw(scoreBoard, 4, 1, "B: ");
  mvwprintw(scoreBoard, 4, 4, len);
  mvwprintw(scoreBoard, 4, 6, "/");
  mvwprintw(scoreBoard, 4, 7, maxLen);
  mvwprintw(scoreBoard, 5, 1, "+: ");
  mvwprintw(scoreBoard, 5, 4, plus);
  mvwprintw(scoreBoard, 6, 1, "-: ");
  mvwprintw(scoreBoard, 6, 4, minus);
  mvwprintw(scoreBoard, 7, 1, "G: ");
  mvwprintw(scoreBoard, 7, 4, G);
  wborder(scoreBoard, '|', '|', '-', '-', '+', '+', '+', '+');
  wrefresh(scoreBoard);
}
void drawMission(WINDOW *missionBoard, Score &score, int hard)
{

  static int mlen = rand() % (6 * hard), mGrowth = rand() % (4 * hard), mPosion = rand() % (4 * hard), mGate = rand() % (3 * hard);
  while (mGrowth < (3 * hard))
  {
    mGrowth = rand() % (4 * hard);
  }
  while (mPosion < (3 * hard))
  {
    mPosion = rand() % (4 * hard);
  }
  while (mGate < (2 * hard))
  {
    mGate = rand() % (3 * hard);
  }
  while (mlen < (5 * hard))
  {
    mlen = rand() % (6 * hard);
  }

  std::string temp = std::to_string(mlen);
  char *B = new char[temp.size() + 1];
  for (int i = 0; i <= temp.size(); i++)
    B[i] = temp[i];

  temp = std::to_string(mGrowth);
  char *plus = new char[temp.size() + 1];
  for (int i = 0; i <= temp.size(); i++)
    plus[i] = temp[i];

  temp = std::to_string(mPosion);
  char *minus = new char[temp.size() + 1];
  for (int i = 0; i <= temp.size(); i++)
    minus[i] = temp[i];

  temp = std::to_string(mGate);
  char *G = new char[temp.size() + 1];
  for (int i = 0; i <= temp.size(); i++)
    G[i] = temp[i];

  wbkgd(missionBoard, COLOR_PAIR(9));
  wattron(missionBoard, COLOR_PAIR(9));
  mvwprintw(missionBoard, 1, 4, "Mission");
  mvwprintw(missionBoard, 2, 1, "B: ");
  mvwprintw(missionBoard, 2, 4, B);
  if (mlen <= score.getMaxLen())
  {
    mvwprintw(missionBoard, 2, 7, "(O)");
    score.mission1 = true;
  }
  mvwprintw(missionBoard, 3, 1, "+: ");
  mvwprintw(missionBoard, 3, 4, plus);
  if (mGrowth <= score.getGrowth())
  {
    mvwprintw(missionBoard, 3, 7, "(O)");
    score.mission2 = true;
  }
  mvwprintw(missionBoard, 4, 1, "-: ");
  mvwprintw(missionBoard, 4, 4, minus);
  if (mPosion <= score.getPosion())
  {
    mvwprintw(missionBoard, 4, 7, "(O)");
    score.mission3 = true;
  }
  mvwprintw(missionBoard, 5, 1, "G: ");
  mvwprintw(missionBoard, 5, 4, G);
  if (mGate <= score.getGate())
  {
    mvwprintw(missionBoard, 5, 7, "(O)");
    score.mission4 = true;
  }
  wborder(missionBoard, '|', '|', '-', '-', '+', '+', '+', '+');
  wrefresh(missionBoard);
}

void drawField(makeField &F, snake &S)
{
  for (int i = 0; i < F.getHeigth(); i++)
  {
    move(i + 1, 0);
    for (int j = 0; j < F.getWidth(); j++)
    {
      if (F.field[i][j] == 0)
      {
        appendEmptySpace();
      }
      else if (F.field[i][j] == 1 || F.field[i][j] == 2)
      {
        appendWall();
      }
      else if (F.field[i][j] == 3)
      {
        appendSnakeHead();
      }
      else if (F.field[i][j] == 4)
      {
        appendSnakeBody();
      }
      else if (F.field[i][j] == 5)
      {
        appendGrowthItem();
      }
      else if (F.field[i][j] == 6)
      {
        appendPoisonItem();
      }
      else if (F.field[i][j] == 7)
      {
        appendDoor();
      }
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

  std::string maps[4] = {"../map/PlainMap.txt", "../map/CrossMap.txt", "../map/CircleMap.txt", "../map/FinalMap.txt"};

  int next = 1, map_count = 0;
  while (next)
  {
    next -= 1;

    WINDOW *scoreBoard;
    WINDOW *missionBoard;
    scoreBoard = newwin(9, 15, 1, 43);
    missionBoard = newwin(7, 15, 12, 43);

    refresh();

    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    std::string mapFile = maps[map_count];
    makeField F = makeField(21, 21, mapFile);
    snake S;
    Score score;

    clear();
    initShape();

    while (true)
    {
      _sleep(250);

      score.time();
      char pressedKey = getch();

      if (pressedKey == 'w')
      {
        S.move(1);
      }
      else if (pressedKey == 's')
      {
        S.move(3);
      }
      else if (pressedKey == 'd')
      {
        S.move(2);
      }
      else if (pressedKey == 'a')
      {
        S.move(4);
      }
      else
      {
        S.go();
      }
      if (pressedKey == 'q')
      {
        break;
      }

      eventManager(F, S, score);
      makeEvent(F, S, score);
      if (S.death)
        break;
      if (score.clearGame())
      {
        next++;
        break;
      }

      drawScore(scoreBoard, score, nickName);
      drawMission(missionBoard, score, map_count + 1);
      drawField(F, S);
      refresh();

      for (int i = 0; i < S.length; i++)
      {
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
