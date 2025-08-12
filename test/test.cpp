#include "bowling-game.hpp"
#include <gtest/gtest.h>
#include <vector>

TEST(BowlingGame, GameIsOverAfterMaxRollsWithoutBonusFrames)
{
    size_t rollsMax = 20U;
    BowlingGame game;

    for (auto rolls = 0; rolls < rollsMax; ++rolls) {
        game.roll(2);
    }

    EXPECT_TRUE(game.getGameEnd());
}

TEST(BowlingGame, GameIsNotOverBeforeMaxRollsWithoutBonusFrames)
{
    size_t rollsMax = 20U;
    BowlingGame game;

    for (auto rolls = 0; rolls < rollsMax - 1; ++rolls) {
        game.roll(2);
    }

    EXPECT_FALSE(game.getGameEnd());
}

TEST(BowlingGame, GameIsOverAfterStrikeInLastFrame)
{
    size_t rollsMax = 20U;
    BowlingGame game;

    for (auto rolls = 0; rolls < rollsMax - 2; ++rolls) {
        game.roll(2);
    }
    game.roll(10);
    game.roll(2);
    game.roll(2);

    EXPECT_TRUE(game.getGameEnd());
}

TEST(BowlingGame, GameIsNotOverAfterStrikeInLastFrame)
{
    size_t rollsMax = 20U;
    BowlingGame game;

    for (auto rolls = 0; rolls < rollsMax - 2; ++rolls) {
        game.roll(2);
    }
    game.roll(10);
    game.roll(2);

    EXPECT_FALSE(game.getGameEnd());
}

TEST(BowlingGame, GameIsOverAfterSpareInLastFrame)
{
    size_t rollsMax = 20U;
    BowlingGame game;

    for (auto rolls = 0; rolls < rollsMax - 2; ++rolls) {
        game.roll(2);
    }
    game.roll(6);
    game.roll(4);
    game.roll(2);

    EXPECT_TRUE(game.getGameEnd());
}

TEST(BowlingGame, GameIsNotOverAfterSpareInLastFrame)
{
    size_t rollsMax = 20U;
    BowlingGame game;

    for (auto rolls = 0; rolls < rollsMax - 2; ++rolls) {
        game.roll(2);
    }
    game.roll(6);
    game.roll(4);

    EXPECT_FALSE(game.getGameEnd());
}

TEST(BowlingGame, GameIsOverAfter10StrikesAndStrikeAndStrike)
{
    size_t framesMax = 10;
    BowlingGame game;

    for (auto frame = 0; frame < framesMax; ++frame) {
        game.roll(10);
    }
    EXPECT_FALSE(game.getGameEnd());
    game.roll(10);
    EXPECT_FALSE(game.getGameEnd());
    game.roll(10);
    EXPECT_TRUE(game.getGameEnd());
}

TEST(BowlingGame, GameIsOverAfter10StrikesAndSpare)
{
    size_t framesMax = 10;
    BowlingGame game;

    for (auto frame = 0; frame < framesMax; ++frame) {
        game.roll(10);
    }
    EXPECT_FALSE(game.getGameEnd());
    game.roll(5);
    EXPECT_FALSE(game.getGameEnd());
    game.roll(5);
    EXPECT_TRUE(game.getGameEnd());
}

TEST(BowlingGame, GameIsOverAfter10StrikesAndTwoRolls)
{
    size_t framesMax = 10;
    BowlingGame game;

    for (auto frame = 0; frame < framesMax; ++frame) {
        game.roll(10);
    }
    EXPECT_FALSE(game.getGameEnd());
    game.roll(2);
    EXPECT_FALSE(game.getGameEnd());
    game.roll(2);
    EXPECT_TRUE(game.getGameEnd());
}

TEST(BowlingGame, PointsSum)
{
    size_t gameSamples = 6;
    std::vector<BowlingGame> games(gameSamples);
    std::vector<std::vector<int>> rolls(gameSamples);
    std::vector<int> ExpectedPoints(gameSamples);

    rolls[0] = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
    ExpectedPoints[0] = 300;
    rolls[1] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    ExpectedPoints[1] = 0;
    rolls[2] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    ExpectedPoints[2] = 10;
    rolls[3] = { 5, 5, 3, 4 };
    ExpectedPoints[3] = 20;
    rolls[4] = { 3, 4, 6, 4, 6, 2, 5, 3, 8, 2, 10, 4, 5, 3, 2, 4, 5, 9, 1, 4 };
    ExpectedPoints[4] = 115;
    rolls[5] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 10, 5, 5 };
    ExpectedPoints[5] = 160;

    for (auto i = 0; i < gameSamples; ++i) {
        for (const auto& pins : rolls[i]) {
            games[i].roll(pins);
        }
    }

    for (auto i = 0; i < gameSamples; ++i) {
        EXPECT_EQ(games[i].getScore(), ExpectedPoints[i]);
    }
}