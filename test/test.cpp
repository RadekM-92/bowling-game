#include <gtest/gtest.h>
#include <vector>
#include "bowling-game.hpp"

TEST(BowlingGame, GameIsOverAfterMaxRollsWithoutBonusFrames) {
    size_t rollsMax = 20U;
    BowlingGame game;

    for(auto rolls=0; rolls<rollsMax; ++rolls) {
        game.roll(2);
    }
    
    EXPECT_TRUE(game.getGameEnd());
}

TEST(BowlingGame, GameIsNotOverBeforeMaxRollsWithoutBonusFrames) {
    size_t rollsMax = 20U;
    BowlingGame game;

    for(auto rolls=0; rolls<rollsMax-1; ++rolls) {
        game.roll(2);
    }
    
    EXPECT_FALSE(game.getGameEnd());
}

TEST(BowlingGame, GameIsOverAfterStrikeInLastFrame) {
    size_t rollsMax = 20U;
    BowlingGame game;

    for(auto rolls=0; rolls<rollsMax-2; ++rolls) {
        game.roll(2);
    }
    game.roll(10);
    game.roll(2);
    game.roll(2);

    EXPECT_TRUE(game.getGameEnd());
}

TEST(BowlingGame, GameIsNotOverAfterStrikeInLastFrame) {
    size_t rollsMax = 20U;
    BowlingGame game;

    for(auto rolls=0; rolls<rollsMax-2; ++rolls) {
        game.roll(2);
    }
    game.roll(10);
    game.roll(2);

    EXPECT_FALSE(game.getGameEnd());
}

TEST(BowlingGame, GameIsOverAfterSpareInLastFrame) {
    size_t rollsMax = 20U;
    BowlingGame game;

    for(auto rolls=0; rolls<rollsMax-2; ++rolls) {
        game.roll(2);
    }
    game.roll(6);
    game.roll(4);
    game.roll(2);

    EXPECT_TRUE(game.getGameEnd());
}

TEST(BowlingGame, GameIsNotOverAfterSpareInLastFrame) {
    size_t rollsMax = 20U;
    BowlingGame game;

    for(auto rolls=0; rolls<rollsMax-2; ++rolls) {
        game.roll(2);
    }
    game.roll(6);
    game.roll(4);

    EXPECT_FALSE(game.getGameEnd());
}