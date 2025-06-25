#include <unistd.h>

#include <cstdlib>
#include <fstream>

#include "./module/Draw.h"
#include "./module/Event.h"
#include "./module/MakeField.h"
#include "./module/Score.h"
#include "./module/Shapes.cpp"
#include "./module/Snake.h"

#define _sleep(x) usleep(x * 1000)

int main() {
  resize_term(22, 80);
  initscr();  // Curses모드시작

  char nickName[7];
  attron(COLOR_PAIR(8));
  printw("Enter User nickname: ");
  attroff(COLOR_PAIR(8));
  scanw("%s", nickName);

  std::string maps[4] = {"../map/PlainMap.txt", "../map/CrossMap.txt",
                         "../map/CircleMap.txt", "../map/FinalMap.txt"};

  int next = 1, map_count = 0;
  while (next) {
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
    MakeField F = MakeField(21, 21, mapFile);
    Snake S;
    Score score;

    clear();
    initShape();

    while (true) {
      _sleep(250);

      score.time();
      char pressedKey = getch();

      if (pressedKey == 'w') {
        S.move(1);
      } else if (pressedKey == 's') {
        S.move(3);
      } else if (pressedKey == 'd') {
        S.move(2);
      } else if (pressedKey == 'a') {
        S.move(4);
      } else {
        S.go();
      }
      if (pressedKey == 'q') {
        break;
      }

      eventManager(F, S, score);
      makeEvent(F, S, score);
      if (S.death) break;
      if (score.clearGame()) {
        next++;
        break;
      }

      drawScore(scoreBoard, score, nickName);
      drawMission(missionBoard, score, map_count + 1);
      drawField(F, S);
      refresh();

      for (int i = 0; i < S.length; i++) {
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
  endwin();  // Curses모드종료

  return 0;
}
