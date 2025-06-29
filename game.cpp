#include "game.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

bool game::IsStrike(int FrameNo)
{
    bool result;

    if (0 <= FrameNo && FramesMax + FramesExtraMax > FrameNo) {
        result = (PinsMax == pinsKOMem_[FrameNo][0]) ? true : false;
    } else {
        result = false;
    }

    return result;
};

bool game::IsSpare(int FrameNo)
{
    bool result;

    if (0 <= FrameNo && FramesMax + FramesExtraMax > FrameNo) {
        result = (PinsMax > pinsKOMem_[FrameNo][0] && PinsMax > pinsKOMem_[FrameNo][1] && PinsMax == pinsKOMem_[FrameNo][0] + pinsKOMem_[FrameNo][1]) ? true : false;
    } else {
        result = false;
    }

    return result;
};

void game::FrameIncrease(void)
{
    frameCounter_ = frameCounter_ + 1;
}

void game::RollIncrease(void)
{
    rollCounter_ = rollCounter_ + 1;
}

bool game::IsGameEnd(void)
{
    bool GameEnd = false;

    if (FrameLast <= frameCounter_) {
        if (IsSpare(FrameLast)) {
            if (FrameLast < frameCounter_ && FirstRoll < rollCounter_) {
                GameEnd = true;
            }
        } else if (IsStrike(FrameLast)) {
            if (IsStrike(BonusFrame)) {
                if (BonusFrame < frameCounter_ && FirstRoll < rollCounter_) {
                    GameEnd = true;
                }
            } else if (FrameLast < frameCounter_ && SecondRoll < rollCounter_) {
                GameEnd = true;
            }
        } else if (RollsMaxInFrame <= rollCounter_) {
            GameEnd = true;
        }
    }

    return GameEnd;
}

int game::PointsSum(void)
{
    int frame;
    int extraPoints_ = 0;
    int Sum = 0;

    for (frame = 0; FramesMax + FramesExtraMax > frame; frame++) {
        extraPoints_ = 0;

        if (IsStrike(frame) && FrameLast > frame) {
            if (IsStrike(frame + 1)) {
                if (frame + 1 < frameCounter_) {
                    extraPoints_ = pinsKOMem_[frame + 1][FirstRoll] + pinsKOMem_[frame + 2][FirstRoll];
                }
            } else {
                if (SecondRoll < rollCounter_) {
                    extraPoints_ = pinsKOMem_[frame + 1][FirstRoll] + pinsKOMem_[frame + 1][SecondRoll];
                }
            }
        } else if (IsSpare(frame)) {
            if (frame < frameCounter_) {
                extraPoints_ = pinsKOMem_[frame + 1][FirstRoll];
            }
        }

        Sum = Sum + pinsKOMem_[frame][0] + pinsKOMem_[frame][1] + extraPoints_;

        // cout << frame << ": " << pinsKOMem_[frame][0] << " " << pinsKOMem_[frame][1] << \
                // " " <<  "Strike=" << IsStrike(frame) << " " << "Spare=" << IsSpare(frame) <<   "\r\n";

        if (frame > frameCounter_ - 1) {
            break;
        }
    }
    return Sum;
}

void game::roll(int PinsKnockedDown)
{
    pinsKOMem_[frameCounter_][rollCounter_] = PinsKnockedDown;

    if (pinsKOMem_[frameCounter_][FirstRoll] > PinsMax || pinsKOMem_[frameCounter_][SecondRoll] > PinsMax || pinsKOMem_[frameCounter_][FirstRoll] + pinsKOMem_[frameCounter_][SecondRoll] > PinsMax) {
        cout << "Pins knocked down out of range!"
             << "\r\n";
    } else {

        RollIncrease();
        totalScore_ = PointsSum();

        // cout << "F:"<<frameCounter_<<" R:"<<rollCounter_<<"\r\n";
        // cout << "Total: " << "Points= " << totalScore_ << "\r\n";

        if (IsGameEnd()) {
            cout << "End Game\r\n";
            exit(2);
        }

        if (RollsMaxInFrame <= rollCounter_ || IsStrike(frameCounter_)) {
            rollCounter_ = 0;
            FrameIncrease();
        }
    }
}

int game::score(void)
{
    return totalScore_;
}

game::game() = default;
game::~game() = default;
