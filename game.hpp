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

    bool IsStrike(int FrameNo);
    bool IsSpare(int FrameNo);
    void FrameIncrease(void);
    void RollIncrease(void);
    bool IsGameEnd(void);
    int PointsSum(void);

public:
    void roll(int PinsKnockedDown);
    int score(void);
    game();
    ~game();
};