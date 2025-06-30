#pragma once
#include <cstddef>
#include <vector>

class BowlingGame {
private:
    int rollCounter_ = 0;
    int frameCounter_ = 0;
    int totalScore_ = 0;
    bool gameEnd_ = false;
    const size_t pinsMaxInFrame = 10U;
    const size_t framesMaxWithoutBonus_ = 10U;
    const size_t framesMaxWithBonus_ = 12U;
    const size_t rollsInFrameMax_ = 2U;
    std::vector<std::pair<int, int>> knockedDownPins_;
    std::pair<int, int> knockedDownPinsPerFrame_ { 0, 0 };
    int pinsLeft_ = 10U;

    bool isStrike(const std::pair<int, int>&);
    bool isSpare(const std::pair<int, int>&);
    void frameIncrease();
    void rollIncrease();
    bool isGameEnd();
    int pointsSum();

public:
    void roll(int);
    int getScore() const;
    bool getGameEnd() const;
    BowlingGame();
    ~BowlingGame();
};