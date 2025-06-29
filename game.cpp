#include "game.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;



        bool game::IsStrike(int FrameNo)
        {
            bool result;

            if (0 <= FrameNo && FramesMax+FramesExtraMax > FrameNo)
            {
                result = (PinsMax == PinsKO_Mem[FrameNo][0]) ? true : false;
            }
            else
            {
                result = false;
            }

            return result;
        };

        bool game::IsSpare(int FrameNo)
        {
            bool result;

            if (0 <= FrameNo && FramesMax+FramesExtraMax > FrameNo)
            {
                result = (PinsMax > PinsKO_Mem[FrameNo][0] && \
                          PinsMax > PinsKO_Mem[FrameNo][1] && \
                          PinsMax == PinsKO_Mem[FrameNo][0] + PinsKO_Mem[FrameNo][1]) ? true : false;
            }
            else
            {
                result = false;
            }

            return result;
        };

        void game::FrameIncrease(void)
        {
            Frame_PV = Frame_PV + 1;
        }

        void game::RollIncrease(void)
        {
            Roll_PV = Roll_PV + 1;
        }

        bool game::IsGameEnd(void)
        {
            bool GameEnd = false;

            if (FrameLast <= Frame_PV)
            {
                if(IsSpare(FrameLast))
                {
                    if (FrameLast < Frame_PV && FirstRoll < Roll_PV)
                    {
                        GameEnd = true;
                    }
                }
                else if(IsStrike(FrameLast))
                {
                    if (IsStrike(BonusFrame))
                    {
                        if (BonusFrame < Frame_PV && FirstRoll < Roll_PV)
                        {
                            GameEnd = true;
                        }
                    }
                    else if (FrameLast < Frame_PV && SecondRoll < Roll_PV)
                    {
                       GameEnd = true; 
                    }
                }
                else if(RollsMaxInFrame <= Roll_PV)
                {
                    GameEnd = true;
                }
            } 

            return GameEnd;
        }
    
        int game::PointsSum(void)
        {
            int frame;
            int ExtraPoints=0;
            int Sum=0;

            for(frame=0; FramesMax+FramesExtraMax>frame; frame++)
            {
                ExtraPoints = 0;

                if(IsStrike(frame) && FrameLast > frame)
                {
                    if(IsStrike(frame+1))
                    {
                        if(frame + 1 < Frame_PV)
                        {
                            ExtraPoints = PinsKO_Mem[frame+1][FirstRoll] + PinsKO_Mem[frame+2][FirstRoll];
                        }
                    }
                    else
                    {
                        if (SecondRoll < Roll_PV)
                        {
                            ExtraPoints = PinsKO_Mem[frame+1][FirstRoll] + PinsKO_Mem[frame+1][SecondRoll];
                        }
                    }
                }
                else if(IsSpare(frame))
                {
                    if(frame < Frame_PV)
                    {
                        ExtraPoints = PinsKO_Mem[frame+1][FirstRoll];
                    }
                }

                Sum = Sum + PinsKO_Mem[frame][0] + PinsKO_Mem[frame][1] + ExtraPoints;

                // cout << frame << ": " << PinsKO_Mem[frame][0] << " " << PinsKO_Mem[frame][1] << \
                // " " <<  "Strike=" << IsStrike(frame) << " " << "Spare=" << IsSpare(frame) <<   "\r\n";

                if (frame > Frame_PV-1)
                {
                    break;
                } 
            }
            return Sum;
        }
        
        void game::roll(int PinsKnockedDown)
        {
            PinsKO_Mem[Frame_PV][Roll_PV] = PinsKnockedDown;

            if(PinsKO_Mem[Frame_PV][FirstRoll] > PinsMax || \
                PinsKO_Mem[Frame_PV][SecondRoll] > PinsMax || \
                PinsKO_Mem[Frame_PV][FirstRoll] + PinsKO_Mem[Frame_PV][SecondRoll] > PinsMax)
            {
                cout << "Pins knocked down out of range!" << "\r\n";
            }
            else
            {

                RollIncrease();
                TotalScore = PointsSum();


                // cout << "F:"<<Frame_PV<<" R:"<<Roll_PV<<"\r\n";
                // cout << "Total: " << "Points= " << TotalScore << "\r\n";

                if (IsGameEnd())
                {
                    cout << "End Game\r\n";
                    exit(2);
                }


                if (RollsMaxInFrame <= Roll_PV || IsStrike(Frame_PV))
                {
                    Roll_PV = 0;
                    FrameIncrease();
                }
            }
        }

        int game::score(void)
        {
            return TotalScore;
        }

        game::game() = default;
        game::~game() = default;
