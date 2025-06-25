#include "Event.h"

#include <cstdlib>
#include <ctime>

void eventManager(MakeField &F, Snake &S, Score &score) {
  int event = F.field[S.baem[0].row][S.baem[0].colunm];
  switch (event) {
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
      if (S.baem[0].row == S.door[0] && S.baem[0].colunm == S.door[1]) {
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
        else {
          while (true) {
            if (S.direction == 1 && F.field[S.door[2] - 1][S.door[3]] == 0) {
              S.moveHead(1);
              break;
            }
            if (S.direction == 2 && F.field[S.door[2]][S.door[3] + 1] == 0) {
              S.moveHead(2);
              break;
            }
            if (S.direction == 3 && F.field[S.door[2] + 1][S.door[3]] == 0) {
              S.moveHead(3);
              break;
            }
            if (S.direction == 3 && F.field[S.door[2]][S.door[3] - 1] == 0) {
              S.moveHead(4);
              break;
            }
            S.direction = (S.direction % 4 + 1);
          }
        }
      } else if (S.baem[0].row == S.door[2] && S.baem[0].colunm == S.door[3]) {
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
        else {
          while (true) {
            if (S.direction == 1 && F.field[S.door[0] - 1][S.door[1]] == 0) {
              S.moveHead(1);
              break;
            }
            if (S.direction == 2 && F.field[S.door[0]][S.door[1] + 1] == 0) {
              S.moveHead(2);
              break;
            }
            if (S.direction == 3 && F.field[S.door[0] + 1][S.door[1]] == 0) {
              S.moveHead(3);
              break;
            }
            if (S.direction == 3 && F.field[S.door[0]][S.door[1] - 1] == 0) {
              S.moveHead(4);
              break;
            }
            S.direction = (S.direction % 4 + 1);
          }
        }
      }
      break;
  }
  for (int i = 1; i < S.length; i++) {
    if (S.baem[0].row == S.baem[i].row && S.baem[0].colunm == S.baem[i].colunm)
      S.death = true;
  }
  if (S.length < 3) S.death = true;
}

void makeEvent(MakeField &F, Snake &S, Score &score) {
  for (int i = 0; i < S.length; i++) {
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

  if (g1_t == 40) {
    g1_t = 0;
    if (F.field[g1_x][g1_y] == 5) {
      F.field[g1_x][g1_y] = 0;
      F.itemCount--;
    }
    F.mkG1 = true;
  }
  if (g2_t == 40) {
    g2_t = 0;
    if (F.field[g2_x][g2_y] == 5) {
      F.field[g2_x][g2_y] = 0;
      F.itemCount--;
    }
    F.mkG2 = true;
  }
  if (r_t == 40) {
    r_t = 0;
    if (F.field[r_x][r_y] == 6) {
      F.field[r_x][r_y] = 0;
      F.itemCount--;
    }
    mkP = true;
  }

  while (mkP) {
    r_x = rand() % 20, r_y = rand() % 20;
    if (F.field[r_x][r_y] != 0) continue;
    F.field[r_x][r_y] = 6;
    F.itemCount++;
    mkP = false;
  }

  while (F.mkG1) {
    if (F.itemCount > 2) {
      F.mkG1 = false;
      break;
    }
    g1_x = rand() % 20, g1_y = rand() % 20;
    if (F.field[g1_x][g1_y] != 0) continue;
    F.field[g1_x][g1_y] = 5;
    F.itemCount++;
    F.mkG1 = false;
  }
  while (F.mkG2) {
    if (F.itemCount > 2) {
      F.mkG2 = false;
      break;
    }
    g2_x = rand() % 20, g2_y = rand() % 20;
    if (F.field[g2_x][g2_y] != 0) continue;
    F.field[g2_x][g2_y] = 5;
    F.itemCount++;
    F.mkG2 = false;
  }

  static bool mk_door1 = true;
  static bool mk_door2 = true;
  if (S.length == 5) {
    while (mk_door1) {
      S.door[0] = rand() % 21;
      S.door[1] = rand() % 21;
      if (F.field[S.door[0]][S.door[1]] != 1) continue;
      F.field[S.door[0]][S.door[1]] = 7;
      mk_door1 = false;
    }
    while (mk_door2) {
      S.door[2] = rand() % 21;
      S.door[3] = rand() % 21;
      if ((S.door[0] == S.door[2] || S.door[1] == S.door[3])) continue;
      if ((F.field[S.door[2]][S.door[3]] != 1) ||
          (S.door[0] == S.door[2] && S.door[1] == S.door[3]))
        continue;
      F.field[S.door[2]][S.door[3]] = 7;
      mk_door2 = false;
    }
  }

  if (score.clearGame()) {
    mk_door1 = true;
    mk_door2 = true;
  }
}
