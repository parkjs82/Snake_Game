#include "Draw.h"

#include "Shapes.h"

void intToCharArray(int value, char *buffer, bool fillSpace = false) {
  if (value > 9) {
    buffer[0] = value / 10 + '0';
    buffer[1] = value % 10 + '0';
    buffer[2] = '\0';
  } else {
    buffer[0] = value % 10 + '0';
    buffer[1] = fillSpace ? ' ' : '\0';
    buffer[2] = '\0';
  }
}

void drawScore(WINDOW *scoreBoard, Score &score, char nickname[]) {
  std::string str = "Score: " + std::to_string(score.getScore());
  char *scoreStr = new char[str.size() + 1];
  for (int i = 0; i <= str.size(); i++) scoreStr[i] = str[i];

  char plus[3];
  intToCharArray(score.getGrowth(), plus);
  char minus[3];
  intToCharArray(score.getPotion(), minus);
  char len[3];
  intToCharArray(score.getLen(), len, true);
  char maxLen[3];
  intToCharArray(score.getMaxLen(), maxLen, true);
  char G[3];
  intToCharArray(score.getGate(), G);

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
  if (mPosion <= score.getPotion()) {
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
