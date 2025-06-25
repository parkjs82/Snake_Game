#include "Draw.h"

#include "Shapes.h"

void drawScore(WINDOW *scoreBoard, Score &score, char nickname[]) {
  std::string str = "Score: " + std::to_string(score.getScore());
  char *scoreStr = new char[str.size() + 1];
  for (int i = 0; i <= str.size(); i++) scoreStr[i] = str[i];

  char plus[3];
  if (score.getGrowth() > 9) {
    plus[0] = score.getGrowth() / 10 + '0';
    plus[1] = score.getGrowth() % 10 + '0';
    plus[2] = '\0';
  } else {
    plus[0] = score.getGrowth() % 10 + '0';
    plus[1] = '\0';
  }

  char minus[3];
  if (score.getPosion() > 9) {
    minus[0] = score.getPosion() / 10 + '0';
    minus[1] = score.getPosion() % 10 + '0';
    minus[2] = '\0';
  } else {
    minus[0] = score.getPosion() % 10 + '0';
    minus[1] = '\0';
  }
  char len[3];
  if (score.getLen() > 9) {
    len[0] = score.getLen() / 10 + '0';
    len[1] = score.getLen() % 10 + '0';
    len[2] = '\0';
  } else {
    len[0] = score.getLen() % 10 + '0';
    len[1] = ' ';
    len[2] = '\0';
  }
  char maxLen[3];
  if (score.getMaxLen() > 9) {
    maxLen[0] = score.getMaxLen() / 10 + '0';
    maxLen[1] = score.getMaxLen() % 10 + '0';
    maxLen[2] = '\0';
  } else {
    maxLen[0] = score.getMaxLen() % 10 + '0';
    maxLen[1] = ' ';
    maxLen[2] = '\0';
  }
  char G[3];
  if (score.getGate() > 9) {
    G[0] = score.getGate() / 10 + '0';
    G[1] = score.getGate() % 10 + '0';
    G[2] = '\0';
  } else {
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

void drawMission(WINDOW *missionBoard, Score &score, int hard) {
  static int mlen = rand() % (6 * hard), mGrowth = rand() % (4 * hard),
             mPosion = rand() % (4 * hard), mGate = rand() % (3 * hard);
  while (mGrowth < (3 * hard)) {
    mGrowth = rand() % (4 * hard);
  }
  while (mPosion < (3 * hard)) {
    mPosion = rand() % (4 * hard);
  }
  while (mGate < (2 * hard)) {
    mGate = rand() % (3 * hard);
  }
  while (mlen < (5 * hard)) {
    mlen = rand() % (6 * hard);
  }

  std::string temp = std::to_string(mlen);
  char *B = new char[temp.size() + 1];
  for (int i = 0; i <= temp.size(); i++) B[i] = temp[i];

  temp = std::to_string(mGrowth);
  char *plus = new char[temp.size() + 1];
  for (int i = 0; i <= temp.size(); i++) plus[i] = temp[i];

  temp = std::to_string(mPosion);
  char *minus = new char[temp.size() + 1];
  for (int i = 0; i <= temp.size(); i++) minus[i] = temp[i];

  temp = std::to_string(mGate);
  char *G = new char[temp.size() + 1];
  for (int i = 0; i <= temp.size(); i++) G[i] = temp[i];

  wbkgd(missionBoard, COLOR_PAIR(9));
  wattron(missionBoard, COLOR_PAIR(9));
  mvwprintw(missionBoard, 1, 4, "Mission");
  mvwprintw(missionBoard, 2, 1, "B: ");
  mvwprintw(missionBoard, 2, 4, B);
  if (mlen <= score.getMaxLen()) {
    mvwprintw(missionBoard, 2, 7, "(O)");
    score.mission1 = true;
  }
  mvwprintw(missionBoard, 3, 1, "+: ");
  mvwprintw(missionBoard, 3, 4, plus);
  if (mGrowth <= score.getGrowth()) {
    mvwprintw(missionBoard, 3, 7, "(O)");
    score.mission2 = true;
  }
  mvwprintw(missionBoard, 4, 1, "-: ");
  mvwprintw(missionBoard, 4, 4, minus);
  if (mPosion <= score.getPosion()) {
    mvwprintw(missionBoard, 4, 7, "(O)");
    score.mission3 = true;
  }
  mvwprintw(missionBoard, 5, 1, "G: ");
  mvwprintw(missionBoard, 5, 4, G);
  if (mGate <= score.getGate()) {
    mvwprintw(missionBoard, 5, 7, "(O)");
    score.mission4 = true;
  }
  wborder(missionBoard, '|', '|', '-', '-', '+', '+', '+', '+');
  wrefresh(missionBoard);
}

void drawField(MakeField &field, Snake &snake) {
  for (int i = 0; i < field.getHeigth(); i++) {
    move(i + 1, 0);
    for (int j = 0; j < field.getWidth(); j++) {
      if (field.field[i][j] == 0) {
        appendEmptySpace();
      } else if (field.field[i][j] == 1 || field.field[i][j] == 2) {
        appendWall();
      } else if (field.field[i][j] == 3) {
        appendSnakeHead();
      } else if (field.field[i][j] == 4) {
        appendSnakeBody();
      } else if (field.field[i][j] == 5) {
        appendGrowthItem();
      } else if (field.field[i][j] == 6) {
        appendPoisonItem();
      } else if (field.field[i][j] == 7) {
        appendDoor();
      }
    }
  }
}
