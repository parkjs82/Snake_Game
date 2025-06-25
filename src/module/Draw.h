#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h>

#include <string>

#include "MakeField.h"
#include "Score.h"
#include "Snake.h"

void drawScore(WINDOW *scoreBoard, Score &score, char nickname[]);

void drawMission(WINDOW *missionBoard, Score &score, int hard);

void drawField(MakeField &field, Snake &snake);

#endif
