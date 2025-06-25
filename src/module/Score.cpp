#include "./Score.h"

Score::Score() {
  second = 0.0;
  growth = potion = gate = 0;
  maxLen = len = 3;
  mission1 = mission2 = mission3 = mission4 = false;
}

void Score::time() { second += 0.25; }

void Score::growthItems() {
  growth += 1;
  len += 1;
  maxLen = (len > maxLen) ? len : maxLen;
}

void Score::posionItems() {
  potion += 1;
  len -= 1;
}

void Score::useGate() { gate += 1; }

int Score::getGrowth() { return growth; }

int Score::getPotion() { return potion; }

int Score::getGate() { return gate; }

int Score::getLen() { return len; }

int Score::getMaxLen() { return maxLen; }

int Score::getScore() { return second + 10 * (growth + potion + gate); }

bool Score::clearGame() {
  return (mission1 && mission2 && mission3 && mission4);
}
