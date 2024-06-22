#include <iostream>
#include <cstdlib>

using namespace std;

#define PinsMax 10
#define FramesMax 10
#define FramesExtraMax 2
#define RollsMaxInFrame 2
#define RollsExtraMax 2
#define FirstRoll 0
#define SecondRoll 1
#define FrameLast FramesMax - 1
#define BonusFrame 10

class game
{
    private:
        int Roll_PV;
        int Frame_PV;
        int TotalScore;
        int ExtraPoints;
        int PinsKO_Mem[FramesMax+FramesExtraMax][RollsMaxInFrame];

        bool IsStrike(int FrameNo)
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

        bool IsSpare(int FrameNo)
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

        void FrameIncrease(void)
        {
            Frame_PV = Frame_PV + 1;
        }

        void RollIncrease(void)
        {
            Roll_PV = Roll_PV + 1;
        }

        bool IsGameEnd(void)
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
    
        int PointsSum(void)
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
        
    public:
        void roll(int PinsKnockedDown)
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

        int score(void)
        {
            return TotalScore;
        }

    game()
    {
        Roll_PV = 0;
        Frame_PV = 0;
        TotalScore = 0;
        ExtraPoints = 0;
    }
};

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