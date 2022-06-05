#include "./Score.h"

Score::Score()
{
    second = 0.0;
    growth = posion = gate = 0;
}

void Score::time() { second += 0.5; }

void Score::growthItems() { growth += 1; }

void Score::posionItems() { posion += 1; }

void Score::useGate() { gate += 1; }

int Score::getGrowth() { return growth; }

int Score::getPosion() { return posion; }

int Score::getGate() { return gate; }

int Score::getScore() { 
    return second + 10 * (growth + posion + gate); 
}