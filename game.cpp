#include "game.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

bool game::isStrike(const std::pair<int, int>& frame)
{
    if(PinsMax==frame.first){
        return true;
    }
    else{
        return false;
    }
};

bool game::isSpare(const std::pair<int, int>& frame)
{
    if(PinsMax==(frame.first+frame.second)){
        return true;
    }
    else{
        return false;
    }
};

void game::frameIncrease()
{
    frameCounter_ = frameCounter_ + 1;
    rollCounter_ = 0;
}

void game::rollIncrease()
{
    rollCounter_ = rollCounter_ + 1;
}

bool game::isGameEnd()
{
    bool GameEnd = false;

    // if (FrameLast <= frameCounter_) {
    //     if (isSpare(FrameLast)) {
    //         if (FrameLast < frameCounter_ && FirstRoll < rollCounter_) {
    //             GameEnd = true;
    //         }
    //     } else if (isStrike(FrameLast)) {
    //         if (isStrike(BonusFrame)) {
    //             if (BonusFrame < frameCounter_ && FirstRoll < rollCounter_) {
    //                 GameEnd = true;
    //             }
    //         } else if (FrameLast < frameCounter_ && SecondRoll < rollCounter_) {
    //             GameEnd = true;
    //         }
    //     } else if (RollsMaxInFrame <= rollCounter_) {
    //         GameEnd = true;
    //     }
    // }

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
        rollIncrease();
        if(1==rollCounter_){
            knockedDownPinsPerFrame_.first = knockedDownPinsAmount;
            knockedDownPinsPerFrame_.second = 0;
            knockedDownPins_[frameCounter_]=knockedDownPinsPerFrame_;
        }
        else if(2==rollCounter_){
            knockedDownPinsPerFrame_.second = knockedDownPinsAmount;
            knockedDownPins_[frameCounter_]=knockedDownPinsPerFrame_;
        }
        pinsLeft_ = pinsLeft_ - knockedDownPinsAmount;
    }

    std::cout<<"{"<<knockedDownPinsPerFrame_.first<<", "<< knockedDownPinsPerFrame_.second<<"}\n";
    isStrike(knockedDownPinsPerFrame_);
    isSpare(knockedDownPinsPerFrame_);
    
    if(0==pinsLeft_
        || rollsInFrameMax_ <= rollCounter_){
        pinsLeft_=PinsMax;
        frameIncrease();
    }
}

int game::getScore() const
{
    auto score = 0;
    for( const auto & [firstRoll, secondRoll] : knockedDownPins_){
        score = score + firstRoll + secondRoll;
    }

    return score;
}

game::game()
        : knockedDownPins_(framesMax, {0,0})
        {};
game::~game() = default;
