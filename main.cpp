#include <iostream>
#include <cstdlib>
#include "game.hpp"

using namespace std;


int main(void)
{
    game player1;
    int PinsKO=0;
    int cnt = 20;

    cout << "Bowling Game Start\r\n";
    while(cnt)
    {
        cout << "\r\n";
        cout << "Input PinsKO = ";
        cin >>  PinsKO;
        player1.roll(PinsKO);
        cout << "Score: " << player1.score() << "\r\n";
    }
 
    

    return 0;
}