#pragma once

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
    int pinsKOMem_[FramesMax + FramesExtraMax][RollsMaxInFrame] = { 0 };

    bool isStrike(int);
    bool isSpare(int);
    void frameIncrease();
    void rollIncrease();
    bool isGameEnd();
    int pointsSum();

public:
    void roll(int PinsKnockedDown);
    int score();
    game();
    ~game();
};