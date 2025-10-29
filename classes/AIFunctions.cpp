#include "AIFunctions.h"

AIFunctions::AIFunctions(/* args */) {

}
AIFunctions::~AIFunctions() {

    }

 bool AIFunctions::checkDrawAI(std::string aiBoardState) {
    for (size_t i = 0; i < aiBoardState.size(); i++) {
        if(aiBoardState[i] == '0') return false;
    }
    return true;
    }
bool AIFunctions::checkPairsAI(std::vector<int> player, std::vector<int> win_triple) {
     for (int element : win_triple) {
        if (std::find(player.begin(), player.end(), element) == player.end()) {
            return false; //Element not found.
        }

     }
     return true;
}

int AIFunctions::checkForWinnerAI(std::string aiBoardState)
{
    // check all the winning triples
    // if any of them have the same owner return that player
    // winning triples are:
    // 0,1,2
    // 3,4,5
    // 6,7,8
    // 0,3,6
    // 1,4,7
    // 2,5,8
    // 0,4,8
    // 2,4,6
    // you can use the ownerAt helper function to get the owner of a square
    // for example, ownerAt(0) returns the owner of the top-left square
    // if there is no bit in that square, it returns nullptr
    // if you find a winning triple, return the player who owns that triple
    // otherwise return nullptr

    //Using vectors to get an ordered list on who owns what bit on each indext
    std::vector<int> player1, player2;
        player1.reserve(5);
        player2.reserve(4);

    for (size_t i = 0; i <= aiBoardState.size(); ++i) {
            if (aiBoardState[i] == '1') player1.push_back(i);
            else if(aiBoardState[i] == '2') player2.push_back(i);
        }
    
    
    //First check if player size is big enough for a winning tripple which is 3 or greater
    //only need to check first player on this condition.

    //finally run through each possible winning tripples

    if(player1.size() >= 3) {
        
        //declare all lists at this point
        std::vector<int> win_triple1,win_triple2,win_triple3,win_triple4,win_triple5,win_triple6,win_triple7, win_triple8;

        //check for 0 win_triples first and declare this as follows:
        win_triple1.reserve(3);
        win_triple2.reserve(3);
        win_triple3.reserve(3);
        win_triple1 = {0, 1, 2};
        win_triple2 = {0, 3, 6};
        win_triple3 = {0, 4, 8};

    //since lists are ordered check if & who placed on index 0 and run winnerHelper() on each possible winning list with player list.
    //these check continues for each winning triple.
    if(player1.front() == 0) {
        
            //player one has any of these 3 triples so return with ownerAt(0)

        if(checkPairsAI(player1, win_triple1) || checkPairsAI(player1, win_triple2) || checkPairsAI(player1, win_triple3)) {
            return 1;
        }
        //remove and continue if not found
        player1.erase(player1.begin());

    } else if(player2.front() == 0) {

         if(checkPairsAI(player2, win_triple1) || checkPairsAI(player2, win_triple2) || checkPairsAI(player2, win_triple3)) {
            return 2;
        }
        //remove and continue if not found
        player2.erase(player2.begin());
   
   
    } 
    //do the check with {1,4,7}
    win_triple4.reserve(3);
    win_triple4 = {1,4,7};
    if (player1.front() == 1) {
        if(checkPairsAI(player1, win_triple4)) {
            return 1;
        }
         //remove and continue if not found
        player1.erase(player1.begin());

    }   else if (player2.front() == 1) {
        if(checkPairsAI(player2, win_triple4)) {
            return 2;
        }
         //remove and continue if not found
        player2.erase(player2.begin());
    }

    //do check with {2,5,8}, {2,4,6}
    win_triple5.reserve(3);
    win_triple6.reserve(3);
    win_triple5 = {2,5,8};
    win_triple6 = {2,4,6};

     if (player1.front() == 2) {
        if(checkPairsAI(player1, win_triple5) || checkPairsAI(player1, win_triple6)) {
            return 1;
        }
         //remove and continue if not found
        player1.erase(player1.begin());

    }   else if (player2.front() == 2) {
        if(checkPairsAI(player2, win_triple5) || checkPairsAI(player2, win_triple6)) {
            return 2;
        }
         //remove and continue if not found
        player2.erase(player2.begin());
    }

    //check for {3,4,5}
    win_triple7.reserve(3);
    win_triple7 = {3,4,5};

     if (player1.front() == 3) {
        if(checkPairsAI(player1, win_triple7)) {
            return 1;
        }
         //remove and continue if not found
        player1.erase(player1.begin());

    }   else if (player2.front() == 3) {
        if(checkPairsAI(player2, win_triple7)) {
            return 2;
        }
         //remove and continue if not found
        player2.erase(player2.begin());
    }

    //check for {6,7,8}
    win_triple8.reserve(3);
    win_triple8 = {6,7,8};

     if (player1.front() == 6) {
        if(checkPairsAI(player1, win_triple8)) {
            return 1;
        }
         

    }   else if (player2.front() == 6) {
        if(checkPairsAI(player2, win_triple8)) {
            return 2;
        }
    }
    }


    //if no winning triple is found just return 0? until found with checkForWinner() or checkForDraw().
    //
    
    return 0;

    // Hint: Consider using an array to store the winning combinations
    // to avoid repetitive code
}