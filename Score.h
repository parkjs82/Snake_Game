class Score
{
    double second;
    int growth, posion, gate, len, maxLen;
public:
    Score();
    void time();
    void growthItems();
    void posionItems();
    void useGate();

    int getGrowth();
    int getPosion();
    int getGate();
    int getLen();
    int getMaxLen();
    int getScore();
};
