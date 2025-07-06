#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

struct PinsKoRangeError : public std::range_error {
    PinsKoRangeError(std::string const&);
};

struct Counters_t {
    size_t rollCounter;
    size_t frameCounter;
    size_t totalScore;
    size_t pinsLeft;
    std::pair<size_t, size_t> knockedDownPinsPerFrame;
    bool gameEnd;
};

struct Parameters_t {
    size_t pinsMaxInFrame;
    size_t framesMaxWithoutBonus;
    size_t framesMaxWithBonus;
    size_t rollsInFrameMax;
};

class BowlingGame {
private:
    std::unique_ptr<Counters_t> Counters_ { new Counters_t { 0U, 0U, 0U, 10U, { 0U, 0U }, false } };
    std::unique_ptr<Parameters_t> Parameters_ { new Parameters_t { 10U, 10U, 12U, 2U } };
    std::vector<std::pair<size_t, size_t>> knockedDownPins_;

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