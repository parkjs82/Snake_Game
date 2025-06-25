#include "Event.h"

#include <cstdlib>
#include <ctime>

void eventManager(MakeField &field, Snake &snake, Score &score) {
  int event = field.field[snake.baem[0].row][snake.baem[0].column];
  switch (event) {
    case 1:
    case 2:
      snake.death = true;
      break;
    case 5:
      field.itemCount--;
      snake.growthLength();
      score.growthItems();
      break;
    case 6:
      field.itemCount--;
      snake.reduceLength();
      score.posionItems();
      break;
    case 7:
      score.useGate();
      if (snake.baem[0].row == snake.door[0] &&
          snake.baem[0].column == snake.door[1]) {
        snake.baem[0].row = snake.door[2];
        snake.baem[0].column = snake.door[3];
        if (snake.door[2] == 0)
          snake.moveHead(3);
        else if (snake.door[2] == 20)
          snake.moveHead(1);
        else if (snake.door[3] == 0)
          snake.moveHead(2);
        else if (snake.door[3] == 20)
          snake.moveHead(4);
        else {
          while (true) {
            if (snake.direction == 1 &&
                field.field[snake.door[2] - 1][snake.door[3]] == 0) {
              snake.moveHead(1);
              break;
            }
            if (snake.direction == 2 &&
                field.field[snake.door[2]][snake.door[3] + 1] == 0) {
              snake.moveHead(2);
              break;
            }
            if (snake.direction == 3 &&
                field.field[snake.door[2] + 1][snake.door[3]] == 0) {
              snake.moveHead(3);
              break;
            }
            if (snake.direction == 3 &&
                field.field[snake.door[2]][snake.door[3] - 1] == 0) {
              snake.moveHead(4);
              break;
            }
            snake.direction = (snake.direction % 4 + 1);
          }
        }
      } else if (snake.baem[0].row == snake.door[2] &&
                 snake.baem[0].column == snake.door[3]) {
        snake.baem[0].row = snake.door[0];
        snake.baem[0].column = snake.door[1];
        if (snake.door[0] == 0)
          snake.moveHead(3);
        else if (snake.door[0] == 20)
          snake.moveHead(1);
        else if (snake.door[1] == 0)
          snake.moveHead(2);
        else if (snake.door[1] == 20)
          snake.moveHead(4);
        else {
          while (true) {
            if (snake.direction == 1 &&
                field.field[snake.door[0] - 1][snake.door[1]] == 0) {
              snake.moveHead(1);
              break;
            }
            if (snake.direction == 2 &&
                field.field[snake.door[0]][snake.door[1] + 1] == 0) {
              snake.moveHead(2);
              break;
            }
            if (snake.direction == 3 &&
                field.field[snake.door[0] + 1][snake.door[1]] == 0) {
              snake.moveHead(3);
              break;
            }
            if (snake.direction == 3 &&
                field.field[snake.door[0]][snake.door[1] - 1] == 0) {
              snake.moveHead(4);
              break;
            }
            snake.direction = (snake.direction % 4 + 1);
          }
        }
      }
      break;
  }
  for (int i = 1; i < snake.length; i++) {
    if (snake.baem[0].row == snake.baem[i].row &&
        snake.baem[0].column == snake.baem[i].column)
      snake.death = true;
  }
  if (snake.length < 3) snake.death = true;
}

void makeEvent(MakeField &field, Snake &snake, Score &score) {
  for (int i = 0; i < snake.length; i++) {
    field.field[snake.baem[i].row][snake.baem[i].column] = 3;
  }
  field.field[snake.baem[0].row][snake.baem[0].column]++;

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
    if (field.field[g1_x][g1_y] == 5) {
      field.field[g1_x][g1_y] = 0;
      field.itemCount--;
    }
    field.mkG1 = true;
  }
  if (g2_t == 40) {
    g2_t = 0;
    if (field.field[g2_x][g2_y] == 5) {
      field.field[g2_x][g2_y] = 0;
      field.itemCount--;
    }
    field.mkG2 = true;
  }
  if (r_t == 40) {
    r_t = 0;
    if (field.field[r_x][r_y] == 6) {
      field.field[r_x][r_y] = 0;
      field.itemCount--;
    }
    mkP = true;
  }

  while (mkP) {
    r_x = rand() % 20, r_y = rand() % 20;
    if (field.field[r_x][r_y] != 0) continue;
    field.field[r_x][r_y] = 6;
    field.itemCount++;
    mkP = false;
  }

  while (field.mkG1) {
    if (field.itemCount > 2) {
      field.mkG1 = false;
      break;
    }
    g1_x = rand() % 20, g1_y = rand() % 20;
    if (field.field[g1_x][g1_y] != 0) continue;
    field.field[g1_x][g1_y] = 5;
    field.itemCount++;
    field.mkG1 = false;
  }
  while (field.mkG2) {
    if (field.itemCount > 2) {
      field.mkG2 = false;
      break;
    }
    g2_x = rand() % 20, g2_y = rand() % 20;
    if (field.field[g2_x][g2_y] != 0) continue;
    field.field[g2_x][g2_y] = 5;
    field.itemCount++;
    field.mkG2 = false;
  }

  static bool mk_door1 = true;
  static bool mk_door2 = true;
  if (snake.length == 5) {
    while (mk_door1) {
      snake.door[0] = rand() % 21;
      snake.door[1] = rand() % 21;
      if (field.field[snake.door[0]][snake.door[1]] != 1) continue;
      field.field[snake.door[0]][snake.door[1]] = 7;
      mk_door1 = false;
    }
    while (mk_door2) {
      snake.door[2] = rand() % 21;
      snake.door[3] = rand() % 21;
      if ((snake.door[0] == snake.door[2] || snake.door[1] == snake.door[3]))
        continue;
      if ((field.field[snake.door[2]][snake.door[3]] != 1) ||
          (snake.door[0] == snake.door[2] && snake.door[1] == snake.door[3]))
        continue;
      field.field[snake.door[2]][snake.door[3]] = 7;
      mk_door2 = false;
    }
  }

  if (score.clearGame()) {
    mk_door1 = true;
    mk_door2 = true;
  }
}
