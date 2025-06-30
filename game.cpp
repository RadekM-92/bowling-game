#include "game.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

bool game::isStrike(const std::pair<int, int>& frame)
{
    if (PinsMax == frame.first) {
        return true;
    } else {
        return false;
    }
};

bool game::isSpare(const std::pair<int, int>& frame)
{
    if (PinsMax == (frame.first + frame.second)) {
        return true;
    } else {
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
    if (framesMaxWithoutBonus_ - 1U <= frameCounter_) {
        if (isStrike(knockedDownPins_[framesMaxWithoutBonus_ - 1U])) {
            if (framesMaxWithBonus_ - 1U <= frameCounter_) {
                return true;
            } else {
                return false;
            }
        } else if (isSpare(knockedDownPins_[framesMaxWithoutBonus_ - 1U])) {
            if (framesMaxWithoutBonus_ - 1U < frameCounter_ && 0U != rollCounter_) {
                return true;
            } else {
                return false;
            }
        } else if (1U < rollCounter_) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

int game::pointsSum()
{
    int frame;
    int extraPoints_ = 0;
    int Sum = 0;

    return Sum;
}

void game::roll(int knockedDownPinsAmount)
{
    if (!gameEnd_) {
        if (PinsMax < knockedDownPinsAmount
            || pinsLeft_ < knockedDownPinsAmount) {
            std::cout << "Pins knocked down out of range!" << std::endl;
        } else {
            rollIncrease();
            if (1 == rollCounter_) {
                knockedDownPinsPerFrame_.first = knockedDownPinsAmount;
                knockedDownPinsPerFrame_.second = 0;
                knockedDownPins_[frameCounter_] = knockedDownPinsPerFrame_;
            } else if (2 == rollCounter_) {
                knockedDownPinsPerFrame_.second = knockedDownPinsAmount;
                knockedDownPins_[frameCounter_] = knockedDownPinsPerFrame_;
            }
            pinsLeft_ = pinsLeft_ - knockedDownPinsAmount;
        }
        std::cout << "{" << knockedDownPinsPerFrame_.first << ", " << knockedDownPinsPerFrame_.second << "}\n";
        isStrike(knockedDownPinsPerFrame_);
        isSpare(knockedDownPinsPerFrame_);
    }

    if (isGameEnd()) {
        gameEnd_ = true;
        std::cout << "End game" << std::endl;
    }

    if (0 == pinsLeft_
        || rollsInFrameMax_ <= rollCounter_) {
        pinsLeft_ = PinsMax;
        frameIncrease();
    }
}

int game::getScore() const
{
    auto score = 0;
    for (const auto& [firstRoll, secondRoll] : knockedDownPins_) {
        score = score + firstRoll + secondRoll;
    }

    return score;
}

bool game::getGameEnd() const{
    return gameEnd_;
}

game::game()
    : knockedDownPins_(framesMaxWithBonus_, { 0, 0 }) {};
game::~game() = default;
