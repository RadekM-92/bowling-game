#include "bowling-game.hpp"
#include <cstdlib>
#include <iostream>

PinsKoRangeError::PinsKoRangeError(std::string const& msg)
    : std::range_error(msg)
{
}

bool BowlingGame::isStrike(const std::pair<size_t, size_t>& frame)
{
    if (Parameters_->pinsMaxInFrame == frame.first) {
        return true;
    } else {
        return false;
    }
};

bool BowlingGame::isSpare(const std::pair<size_t, size_t>& frame)
{
    if (Parameters_->pinsMaxInFrame == (frame.first + frame.second)) {
        return true;
    } else {
        return false;
    }
};

void BowlingGame::frameIncrease()
{
    Counters_->frameCounter = Counters_->frameCounter + 1U;
    Counters_->rollCounter = 0U;
}

void BowlingGame::rollIncrease()
{
    Counters_->rollCounter = Counters_->rollCounter + 1U;
}

bool BowlingGame::isGameEnd()
{
    if (Parameters_->framesMaxWithoutBonus - 1U <= Counters_->frameCounter) {
        if (isStrike(knockedDownPins_[Parameters_->framesMaxWithoutBonus - 1U])) {
            if (Parameters_->framesMaxWithBonus - 1U <= Counters_->frameCounter) {
                return true;
            } else {
                return false;
            }
        } else if (isSpare(knockedDownPins_[Parameters_->framesMaxWithoutBonus - 1U])) {
            if (Parameters_->framesMaxWithoutBonus - 1U < Counters_->frameCounter && 0U != Counters_->rollCounter) {
                return true;
            } else {
                return false;
            }
        } else if (Parameters_->framesMaxWithoutBonus <= Counters_->frameCounter) {
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

        if (Parameters_->framesMaxWithoutBonus > frame) {
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
    if (!Counters_->gameEnd) {
        if (Parameters_->pinsMaxInFrame < knockedDownPinsAmount || Counters_->pinsLeft < knockedDownPinsAmount) {
            throw PinsKoRangeError { "Pins knocked down out of range!" };
        } else {
            rollIncrease();
            if (1U == Counters_->rollCounter) {
                Counters_->knockedDownPinsPerFrame.first = knockedDownPinsAmount;
                Counters_->knockedDownPinsPerFrame.second = 0U;
                knockedDownPins_[Counters_->frameCounter] = Counters_->knockedDownPinsPerFrame;
            } else if (2U == Counters_->rollCounter) {
                Counters_->knockedDownPinsPerFrame.second = knockedDownPinsAmount;
                knockedDownPins_[Counters_->frameCounter] = Counters_->knockedDownPinsPerFrame;
            }
            Counters_->pinsLeft = Counters_->pinsLeft - knockedDownPinsAmount;
        }
        std::cout << "{" << Counters_->knockedDownPinsPerFrame.first << ", " << Counters_->knockedDownPinsPerFrame.second << "}\n";
        Counters_->totalScore = pointsSum();
    }

    
    if (0U == Counters_->pinsLeft || Parameters_->rollsInFrameMax <= Counters_->rollCounter) {
        Counters_->pinsLeft = Parameters_->pinsMaxInFrame;
        frameIncrease();
    }
    
    if (isGameEnd()) {
        Counters_->gameEnd = true;
        std::cout << "End BowlingGame" << std::endl;
    }
}

int BowlingGame::getScore() const
{
    return Counters_->totalScore;
}

bool BowlingGame::getGameEnd() const
{
    return Counters_->gameEnd;
}

BowlingGame::BowlingGame()
    : knockedDownPins_(Parameters_->framesMaxWithBonus, { 0U, 0U }) {};
BowlingGame::~BowlingGame() = default;
