#pragma once
#include <cstddef>
#include <vector>

#define PinsMax 10
#define FramesMax 10
#define FramesExtraMax 2
#define RollsMaxInFrame 2
#define RollsExtraMax 2
#define FrameLast FramesMax - 1
#define BonusFrame 10

class game {
private:
    int rollCounter_ = 0;
    int frameCounter_ = 0;
    int totalScore_ = 0;
    int extraPoints_ = 0;
    const size_t framesMax = 12U;
    const size_t rollsInFrameMax_ = 2U;
    std::vector<std::pair<int, int>> knockedDownPins_;
    std::pair<int, int> knockedDownPinsPerFrame_{0,0};
    int pinsLeft_=10U;

    bool isStrike(int);
    bool isSpare(int);
    void frameIncrease();
    void rollIncrease();
    bool isGameEnd();
    int pointsSum();

public:
    void roll(int);
    int getScore() const;
    game();
    ~game();
};