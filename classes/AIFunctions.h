#pragma once
#include "Game.h"
#include "Square.h"
class AIFunctions
{
private:
    /* data */
public:
    AIFunctions(/* args */);
    ~AIFunctions();
    bool checkDrawAI(std::string aiBoardState);
    bool checkPairsAI(std::vector<int> player, std::vector<int> win_triple);
    int checkForWinnerAI(std::string aiBoardState);

};




