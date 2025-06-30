#include "game.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

bool game::isStrike(const std::pair<int, int>& frame)
{
    if (pinsMaxInFrame == frame.first) {
        return true;
    } else {
        return false;
    }
};

bool game::isSpare(const std::pair<int, int>& frame)
{
    if (pinsMaxInFrame == (frame.first + frame.second)) {
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
    auto score = 0U;
    auto frame = 1U;
    for (auto it = knockedDownPins_.begin(); it != knockedDownPins_.end(); it++, frame++) {
        const auto& [firstRoll, secondRoll] = *it;

        score = score + firstRoll + secondRoll;

        if (framesMaxWithoutBonus_ > frame) {
            if (isStrike(*it)) {
                if (isStrike(*(it + 1))) {
                    score = score + (it + 1)->first + (it + 2)->first;
                } else {
                    score = score + (it + 1)->first + (it + 1)->second;
                }
            } else {
                if (isSpare(*it)) {
                    score = score + (it + 1)->first;
                }
            }
        }
    }

    return score;
}

void game::roll(int knockedDownPinsAmount)
{
    if (!gameEnd_) {
        if (pinsMaxInFrame < knockedDownPinsAmount
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
        totalScore_ = pointsSum();
    }

    if (isGameEnd()) {
        gameEnd_ = true;
        std::cout << "End game" << std::endl;
    }

    if (0 == pinsLeft_
        || rollsInFrameMax_ <= rollCounter_) {
        pinsLeft_ = pinsMaxInFrame;
        frameIncrease();
    }
}

int game::getScore() const
{
    return totalScore_;
}

bool game::getGameEnd() const
{
    return gameEnd_;
}

game::game()
    : knockedDownPins_(framesMaxWithBonus_, { 0, 0 }) {};
game::~game() = default;
