#include "game.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

bool game::isStrike(int FrameNo)
{
    bool result=false;

    // if (0 <= FrameNo && FramesMax + FramesExtraMax > FrameNo) {
    //     result = (PinsMax == pinsKOMem_[FrameNo][0]) ? true : false;
    // } else {
    //     result = false;
    // }

    return result;
};

bool game::isSpare(int FrameNo)
{
    bool result=false;

    // if (0 <= FrameNo && FramesMax + FramesExtraMax > FrameNo) {
    //     result = (PinsMax > pinsKOMem_[FrameNo][0] && PinsMax > pinsKOMem_[FrameNo][1] && PinsMax == pinsKOMem_[FrameNo][0] + pinsKOMem_[FrameNo][1]) ? true : false;
    // } else {
    //     result = false;
    // }

    return result;
};

void game::frameIncrease()
{
    frameCounter_ = frameCounter_ + 1;
}

void game::rollIncrease()
{
    rollCounter_ = rollCounter_ + 1;
}

bool game::isGameEnd()
{
    bool GameEnd = false;

    if (FrameLast <= frameCounter_) {
        if (isSpare(FrameLast)) {
            if (FrameLast < frameCounter_ && FirstRoll < rollCounter_) {
                GameEnd = true;
            }
        } else if (isStrike(FrameLast)) {
            if (isStrike(BonusFrame)) {
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

int game::pointsSum()
{
    int frame;
    int extraPoints_ = 0;
    int Sum = 0;

    // for (frame = 0; FramesMax + FramesExtraMax > frame; frame++) {
    //     extraPoints_ = 0;

    //     if (isStrike(frame) && FrameLast > frame) {
    //         if (isStrike(frame + 1)) {
    //             if (frame + 1 < frameCounter_) {
    //                 extraPoints_ = pinsKOMem_[frame + 1][FirstRoll] + pinsKOMem_[frame + 2][FirstRoll];
    //             }
    //         } else {
    //             if (SecondRoll < rollCounter_) {
    //                 extraPoints_ = pinsKOMem_[frame + 1][FirstRoll] + pinsKOMem_[frame + 1][SecondRoll];
    //             }
    //         }
    //     } else if (isSpare(frame)) {
    //         if (frame < frameCounter_) {
    //             extraPoints_ = pinsKOMem_[frame + 1][FirstRoll];
    //         }
    //     }

    //     Sum = Sum + pinsKOMem_[frame][0] + pinsKOMem_[frame][1] + extraPoints_;

    //     // cout << frame << ": " << pinsKOMem_[frame][0] << " " << pinsKOMem_[frame][1] << \
    //             // " " <<  "Strike=" << isStrike(frame) << " " << "Spare=" << isSpare(frame) <<   "\r\n";

    //     if (frame > frameCounter_ - 1) {
    //         break;
    //     }
    // }
    return Sum;
}

// void game::roll(int PinsKnockedDown)
// {
//     pinsKOMem_[frameCounter_][rollCounter_] = PinsKnockedDown;

//     if (pinsKOMem_[frameCounter_][FirstRoll] > PinsMax 
// || pinsKOMem_[frameCounter_][SecondRoll] > PinsMax 
// || pinsKOMem_[frameCounter_][FirstRoll] + pinsKOMem_[frameCounter_][SecondRoll] > PinsMax) {
//         cout << "Pins knocked down out of range!"
//              << "\r\n";
//     } else {

//         rollIncrease();
//         totalScore_ = pointsSum();

//         // cout << "F:"<<frameCounter_<<" R:"<<rollCounter_<<"\r\n";
//         // cout << "Total: " << "Points= " << totalScore_ << "\r\n";

//         if (isGameEnd()) {
//             cout << "End Game\r\n";
//             exit(2);
//         }

//         if (RollsMaxInFrame <= rollCounter_ || isStrike(frameCounter_)) {
//             rollCounter_ = 0;
//             frameIncrease();
//         }
//     }
// }

void game::roll(int knockedDownPinsAmount){
    if(PinsMax < knockedDownPinsAmount
        || pinsLeft_ < knockedDownPinsAmount){
        std::cout<<"Pins knocked down out of range!"<<std::endl;
    }
    else
    {
        knockedDownPins_.push_back(knockedDownPinsAmount);
        pinsLeft_ = pinsLeft_ - knockedDownPinsAmount;
    }

    rollIncrease();
    if(0==pinsLeft_
        || rollsInFrameMax_ <= rollCounter_){
        pinsLeft_=PinsMax;
        frameIncrease();
    }
}

int game::score()
{
    return totalScore_;
}

game::game()
        : knockedDownPins_(rollsMax_)
        {};
game::~game() = default;
