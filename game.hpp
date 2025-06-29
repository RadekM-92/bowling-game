#pragma once
#include <cstddef>
#include <vector>

#define PinsMax 10
#define FramesMax 10
#define FramesExtraMax 2
#define RollsMaxInFrame 2
#define RollsExtraMax 2
#define FirstRoll 0
#define SecondRoll 1
#define FrameLast FramesMax - 1
#define BonusFrame 10

class game {
private:
    int rollCounter_ = 0;
    int frameCounter_ = 0;
    int totalScore_ = 0;
    int extraPoints_ = 0;
    const size_t rollsMax_ = 21U;
    std::vector<int> knockedDownPins_;

    bool isStrike(int);
    bool isSpare(int);
    void frameIncrease();
    void rollIncrease();
    bool isGameEnd();
    int pointsSum();

public:
    void setKnockedDownPins(int);
    int score();
    game();
    ~game();
};