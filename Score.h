class Score
{
    double second;
    int growth, posion, gate;
public:
    Score();
    void time();
    void growthItems();
    void posionItems();
    void useGate();

    int getGrowth();
    int getPosion();
    int getGate();
    int getScore();
};