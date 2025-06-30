#pragma once
#include <cstddef>
#include <vector>

class BowlingGame {
private:
    size_t rollCounter_ = 0U;
    size_t frameCounter_ = 0U;
    size_t totalScore_ = 0U;
    bool gameEnd_ = false;
    const size_t pinsMaxInFrame = 10U;
    const size_t framesMaxWithoutBonus_ = 10U;
    const size_t framesMaxWithBonus_ = 12U;
    const size_t rollsInFrameMax_ = 2U;
    std::vector<std::pair<size_t, size_t>> knockedDownPins_;
    std::pair<size_t, size_t> knockedDownPinsPerFrame_ { 0U, 0U };
    size_t pinsLeft_ = 10U;

    bool isStrike(const std::pair<size_t, size_t>&);
    bool isSpare(const std::pair<size_t, size_t>&);
    void frameIncrease();
    void rollIncrease();
    bool isGameEnd();
    int pointsSum();

public:
    void roll(size_t);
    int getScore() const;
    bool getGameEnd() const;
    BowlingGame();
    ~BowlingGame();
};