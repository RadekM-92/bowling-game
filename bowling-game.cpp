#include "bowling-game.hpp"
#include <cstdlib>
#include <iostream>

PinsKoRangeError::PinsKoRangeError(std::string const& msg)
    : std::range_error(msg)
{
}

bool BowlingGame::isStrike(const std::pair<size_t, size_t>& frame)
{
    if (pinsMaxInFrame == frame.first) {
        return true;
    } else {
        return false;
    }
};

bool BowlingGame::isSpare(const std::pair<size_t, size_t>& frame)
{
    if (pinsMaxInFrame == (frame.first + frame.second)) {
        return true;
    } else {
        return false;
    }
};

void BowlingGame::frameIncrease()
{
    frameCounter_ = frameCounter_ + 1U;
    rollCounter_ = 0U;
}

void BowlingGame::rollIncrease()
{
    rollCounter_ = rollCounter_ + 1U;
}

bool BowlingGame::isGameEnd()
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

int BowlingGame::pointsSum()
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

void BowlingGame::roll(size_t knockedDownPinsAmount)
{
    if (!gameEnd_) {
        if (pinsMaxInFrame < knockedDownPinsAmount || pinsLeft_ < knockedDownPinsAmount) {
            throw PinsKoRangeError { "Pins knocked down out of range!" };
        } else {
            rollIncrease();
            if (1U == rollCounter_) {
                knockedDownPinsPerFrame_.first = knockedDownPinsAmount;
                knockedDownPinsPerFrame_.second = 0U;
                knockedDownPins_[frameCounter_] = knockedDownPinsPerFrame_;
            } else if (2U == rollCounter_) {
                knockedDownPinsPerFrame_.second = knockedDownPinsAmount;
                knockedDownPins_[frameCounter_] = knockedDownPinsPerFrame_;
            }
            pinsLeft_ = pinsLeft_ - knockedDownPinsAmount;
        }
        std::cout << "{" << knockedDownPinsPerFrame_.first << ", " << knockedDownPinsPerFrame_.second << "}\n";
        totalScore_ = pointsSum();
    }

    if (isGameEnd()) {
        gameEnd_ = true;
        std::cout << "End BowlingGame" << std::endl;
    }

    if (0U == pinsLeft_ || rollsInFrameMax_ <= rollCounter_) {
        pinsLeft_ = pinsMaxInFrame;
        frameIncrease();
    }
}

int BowlingGame::getScore() const
{
    return totalScore_;
}

bool BowlingGame::getGameEnd() const
{
    return gameEnd_;
}

BowlingGame::BowlingGame()
    : knockedDownPins_(framesMaxWithBonus_, { 0U, 0U }) {};
BowlingGame::~BowlingGame() = default;
