#include "bowling-game.hpp"
#include <cstdlib>
#include <iostream>

int main(void)
{
    BowlingGame MyBowlingGame;
    int PinsKO = 0;

    std::cout << "Bowling Game Start\r\n";
    while (!MyBowlingGame.getGameEnd()) {
        std::cout << "\r\n";
        std::cout << "Input PinsKO = ";
        std::cin >> PinsKO;
        try {
            MyBowlingGame.roll(PinsKO);
        } catch (PinsKoRangeError const& pkre) {
            std::cout << pkre.what() << std::endl;
        }
        std::cout << "Score: " << MyBowlingGame.getScore() << "\r\n";
    }

    return 0;
}