#ifndef SCORE_H
#define SCORE_H

class Score {
  double second;
  int growth, potion, gate, len, maxLen;

 public:
  Score();
  void time();
  void growthItems();
  void posionItems();
  void useGate();

  int getGrowth();
  int getPotion();
  int getGate();
  int getLen();
  int getMaxLen();
  int getScore();

  bool mission1, mission2, mission3, mission4;
  bool clearGame();
};

#endif