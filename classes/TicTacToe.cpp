#include "TicTacToe.h"

// -----------------------------------------------------------------------------
// TicTacToe.cpp
// -----------------------------------------------------------------------------
// This file is intentionally *full of comments* and gentle TODOs that guide you
// through wiring up a complete Tic‑Tac‑Toe implementation using the game engine’s
// Bit / BitHolder grid system.
//
// Rules recap:
//  - Two players place X / O on a 3x3 grid.
//  - Players take turns; you can only place into an empty square.
//  - First player to get three-in-a-row (row, column, or diagonal) wins.
//  - If all 9 squares are filled and nobody wins, it’s a draw.
//
// Notes about the provided engine types you'll use here:
//  - Bit              : a visual piece (sprite) that belongs to a Player
//  - BitHolder        : a square on the board that can hold at most one Bit
//  - Player           : the engine’s player object (you can ask who owns a Bit)
//  - Game options     : let the mouse know the grid is 3x3 (rowX, rowY)
//  - Helpers you’ll see used: setNumberOfPlayers, getPlayerAt, startGame, etc.
//
// I’ve already fully implemented PieceForPlayer() for you. Please leave that as‑is.
// The rest of the routines are written as “comment-first” TODOs for you to complete.
// -----------------------------------------------------------------------------

const int AI_PLAYER   = 1;      // index of the AI player (O)
const int HUMAN_PLAYER= 0;      // index of the human player (X)

TicTacToe::TicTacToe()
{
}

TicTacToe::~TicTacToe()
{
}

// -----------------------------------------------------------------------------
// make an X or an O
// -----------------------------------------------------------------------------
// DO NOT CHANGE: This returns a new Bit with the right texture and owner
Bit* TicTacToe::PieceForPlayer(const int playerNumber)
{
    // depending on playerNumber load the "x.png" or the "o.png" graphic
    Bit *bit = new Bit();
    bit->LoadTextureFromFile(playerNumber == 1 ? "x.png" : "o.png");
    bit->setOwner(getPlayerAt(playerNumber));
    return bit;
}

//
// setup the game board, this is called once at the start of the game
//
void TicTacToe::setUpBoard()
{
    // here we should call setNumberOfPlayers to 2 and then set up the game options so the mouse knows to draw a 3x3 grid
    // _gameOptions has a rowX and rowY property we should set to 3
    // then we need to setup our 3x3 array in _grid with the correct position of the square, and load the "square.png" sprite for each square
    // we will use the initHolder function on each square to do this
    // finally we should call startGame to get everything going

    //set # of players and rows in total
    setNumberOfPlayers(2);
    setAIPlayer(0);
    _gameOptions.rowX = 3;
    _gameOptions.rowY = 3;
    
    
    //looping through from left-to-right & top-to-bottom
    //load all needed squares (9) spaced out by multiplying by 100
    for(int i = 0; i < _gameOptions.rowX; ++i) {
        for (int j = 0; j < _gameOptions.rowY; ++j) {
            _grid[j][i].initHolder(ImVec2(j * 100,i * 100), "square.png", j, i);
        }
    }

    //call startGame() after creating the gameBoard
    startGame();
}

//
// about the only thing we need to actually fill out for tic-tac-toe
//
bool TicTacToe::actionForEmptyHolder(BitHolder *holder)
{
    // 1) Guard clause: if holder is nullptr, fail fast.
    //    (Beginner hint: always check pointers before using them.)
    //    if (!holder) return false;
    if(!holder) return false;

    // 2) Is it actually empty?
    //    Ask the holder for its current Bit using the bit() function.
    //    If there is already a Bit in this holder, return false.
    if(holder->bit()) return false;

    // 3) Place the current player's piece on this holder:
    //    - Figure out whose turn it is (getCurrentPlayer()->playerNumber()).
    //    - Create a Bit via PieceForPlayer(currentPlayerIndex).
    //    - Position it at the holder's position (holder->getPosition()).
    //    - Assign it to the holder: holder->setBit(newBit);


    //I created a bit & figure out whos turn it is in one line.
    Bit* newPlace = PieceForPlayer(getCurrentPlayer()->playerNumber());
    
    //made a variable for clarity to get Position from holder
    ImVec2 getPos = holder->getPosition();

    //set position of the bit I created (newPlace)
    newPlace->setPosition(getPos);

    //assign the bit to given holder.
    holder->setBit(newPlace);

    // 4) Return whether we actually placed a piece. true = acted, false = ignored.
    return true; // replaced with true when able to place successfully  
}

bool TicTacToe::canBitMoveFrom(Bit *bit, BitHolder *src)
{
    // you can't move anything in tic tac toe
    return false;
}

bool TicTacToe::canBitMoveFromTo(Bit* bit, BitHolder*src, BitHolder*dst)
{
    // you can't move anything in tic tac toe
    return false;
}

//
// free all the memory used by the game on the heap
//
void TicTacToe::stopGame()
{
    // clear out the board
    // loop through the 3x3 array and call destroyBit on each square

     for(int i = 0; i < _gameOptions.rowX; ++i) {
        for (int j = 0; j < _gameOptions.rowY; ++j) {
            _grid[j][i].destroyBit();
        }
    } 
}

//
// helper function for the winner check
// Note for Alfredo:
//possibly flip _grid[x][y] if not working?

//ownerAt will return who owns a bit at given index if it exists. (not nullptr)
Player* TicTacToe::ownerAt(int index ) const
{
    // index is 0..8, convert to x,y using:
    int y = index / 3;
    int x = index % 3;
   Bit* what = _grid[x][y].bit();    
   if(!what) return nullptr;
    // if there is no bit at that location (in _grid) return nullptr
    // otherwise return the owner of the bit at that location using getOwner()
    return what->getOwner();
}





//created to help with clarity and used only in checkForWinner()
//NOTE: might want to set this to a private helper function instead of a function inside TicTacToe.cpp file

//WHAT IT DOES: this compares a players list and a win_triple list and returns true or false if a player has
//a winning triple
bool winnerHelper(std::vector<int> player, std::vector<int> win_triple) {
     for (int element : win_triple) {
        if (std::find(player.begin(), player.end(), element) == player.end()) {
            return false; //Element not found.
        }

     }
     return true;
}




//how I implemented:
//created  2 ordered list of both players 
//made it so the winning checks runs past a player list with a size of 3 or greater
//check in order of which winning triple starts with the lowest index
// ex) {0,1,2} {0,3,6} {0.4,8}
// if none is found and a player has this index I pop it out of the list and continue with
// {1, 4, 7}
//do this all the way till {6,7,8}.
// if no winner is found return nullprt
Player* TicTacToe::checkForWinner()
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
    for (int i = 0; i <= 8; ++i) {
        Player* owner = ownerAt(i);
        if(owner) {
            if(owner->playerNumber() == 0) {
                player1.push_back(i);
            } else {player2.push_back(i);}
        }
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

        if(winnerHelper(player1, win_triple1) || winnerHelper(player1, win_triple2) || winnerHelper(player1, win_triple3)) {
            return ownerAt(0);
        }
        //remove and continue if not found
        player1.erase(player1.begin());

    } else if(player2.front() == 0) {

         if(winnerHelper(player2, win_triple1) || winnerHelper(player2, win_triple2) || winnerHelper(player2, win_triple3)) {
            return ownerAt(0);
        }
        //remove and continue if not found
        player2.erase(player2.begin());
   
   
    } 
    //do the check with {1,4,7}
    win_triple4.reserve(3);
    win_triple4 = {1,4,7};
    if (player1.front() == 1) {
        if(winnerHelper(player1, win_triple4)) {
            return ownerAt(1);
        }
         //remove and continue if not found
        player1.erase(player1.begin());

    }   else if (player2.front() == 1) {
        if(winnerHelper(player2, win_triple4)) {
            return ownerAt(1);
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
        if(winnerHelper(player1, win_triple5) || winnerHelper(player1, win_triple6)) {
            return ownerAt(2);
        }
         //remove and continue if not found
        player1.erase(player1.begin());

    }   else if (player2.front() == 2) {
        if(winnerHelper(player2, win_triple5) || winnerHelper(player2, win_triple6)) {
            return ownerAt(2);
        }
         //remove and continue if not found
        player2.erase(player2.begin());
    }

    //check for {3,4,5}
    win_triple7.reserve(3);
    win_triple7 = {3,4,5};

     if (player1.front() == 3) {
        if(winnerHelper(player1, win_triple7)) {
            return ownerAt(3);
        }
         //remove and continue if not found
        player1.erase(player1.begin());

    }   else if (player2.front() == 3) {
        if(winnerHelper(player2, win_triple7)) {
            return ownerAt(3);
        }
         //remove and continue if not found
        player2.erase(player2.begin());
    }

    //check for {6,7,8}
    win_triple8.reserve(3);
    win_triple8 = {6,7,8};

     if (player1.front() == 6) {
        if(winnerHelper(player1, win_triple8)) {
            return ownerAt(6);
        }
         

    }   else if (player2.front() == 6) {
        if(winnerHelper(player2, win_triple8)) {
            return ownerAt(6);
        }
    }
    }


    //if no winning triple is found just return nullptr until found with checkForWinner() or checkForDraw().
    //
    
    return nullptr;

    // Hint: Consider using an array to store the winning combinations
    // to avoid repetitive code
}





//How I implemented:
//only return true if there are no empty squares
//otherwise it will return false if one is found in the for loop
bool TicTacToe::checkForDraw()
{

    // is the board full with no winner?
    // if any square is empty, return false
    // otherwise return true
    for (int i = 0; i <= 8; ++i) {
        Player* owner = ownerAt(i);
        if(!owner) {
            return false;
        }
    }

    return true;
}

//
// state strings
//
std::string TicTacToe::initialStateString()
{
    return "000000000";
}







//
// this still needs to be tied into imguis init and shutdown
// we will read the state string and store it in each turn object
//
//How I implemented:
//create an empty string and loop through _grid[y][x] left-to-right, top-to-bottom
//if a bit exist on that part of a grid add what player that is and +1 to show if its player 1 or 2.
// used += and to_string() 
//if no bit exist then make it 0 with else.
//one done return that string.

std::string TicTacToe::stateString() const
{
    // return a string representing the current state of the board
    // the string should be 9 characters long, one for each square
    // each character should be '0' for empty, '1' for player 1 (X), and '2' for player 2 (O)
    // the order should be left-to-right, top-to-bottom
    // for example, the starting state is "000000000"
    // if player 1 has placed an X in the top-left and player 2 an O in the center, the state would be "100020000"
    // you can build the string using a loop and the to_string function
    // for example, to convert an integer to a string, you can use std::to_string(1) which returns "1"
    // you can get the bit at each square using _grid[y][x].bit()
    // if the bit is not null, you can get its owner using bit->getOwner()->playerNumber()
    // remember that player numbers are zero-based, so add 1 to get '1' or '2'
    // if the bit is null, add '0' to the string
    // finally, return the constructed string
    
   
    std::string current_state;
     for(int i = 0; i < _gameOptions.rowX; ++i) {
        for (int j = 0; j < _gameOptions.rowY; ++j) {
            if(_grid[j][i].bit()) {
            
           current_state += std::to_string(_grid[j][i].bit()->getOwner()->playerNumber() + 1);
            }
            else {
                current_state += "0";
            }
        }
    } 
    return current_state;
}



//not done
//Implementation so far:
//itterate through string s, get player number by subtracting 1
//create a new bit if any player placed on that square prior
//set position for new bit
//setbit on holder found with [index / 3] [index % 3]

//
// this still needs to be tied into imguis init and shutdown
// when the program starts it will load the current game from the imgui ini file and set the game state to the last saved state
//
void TicTacToe::setStateString(const std::string &s)
{
    // set the state of the board from the given string
    // the string will be 9 characters long, one for each square
    // each character will be '0' for empty, '1' for player 1 (X), and '2' for player 2 (O)
    // the order will be left-to-right, top-to-bottom
    // for example, the starting state is "000000000"
    // if player 1 has placed an X in the top-left and player 2 an O in the center, the state would be "100020000"
    // you can loop through the string and set each square in _grid accordingly
    // for example, if s[0] is '1', you would set _grid[0][0] to have player 1's piece
    // if s[4] is '2', you would set _grid[1][1] to have player 2's piece
    // if s[8] is '0', you would set _grid[2][2] to be empty
    // you can use the PieceForPlayer function to create a new piece for a player
    // remember to convert the character to an integer by subtracting '0'
    // for example, int playerNumber = s[index] - '0';
    // if playerNumber is 0, set the square to empty (nullptr)
    // if playerNumber is 1 or 2, create a piece for that player and set it in the square
    // finally, make sure to position the piece at the holder's position
    // you can get the position of a holder using holder->getPosition()
    // loop through the 3x3 array and set each square accordingly
    // the string should always be valid, so you don't need to check its length or contents
    // but you can assume it will always be 9 characters long and only contain '0', '1', or '2'
    
    for(size_t i = 0; i < s.length(); i++) {
        int playerNumber = s[i] - '0';
        int y = i / 3;
        int x = i % 3;
        if(playerNumber == 1 || playerNumber == 2) {
         Bit* savePlace = PieceForPlayer(playerNumber - 1);
         BitHolder*  getHol = _grid[x][y].bit()->getHolder();
         ImVec2 getPos = getHol->getPosition();

         savePlace->setPosition(getPos);
         getHol->setBit(savePlace);

        }
        
    }

}

//helper to end recursion in miniMax.

//max is X: +1
//min is O: -1
//tie is: 0
//implementation of the minimax algorithm for tictactoe
int TicTacToe::miniMax(std::string &currentBoard, int &index, AIFunctions runAI, bool Maximizing, int depth) {
    int winner = runAI.checkForWinnerAI(currentBoard);

    if(winner == 1) return 1;
    if(winner == 2) return -1;  
    if(runAI.checkDrawAI(currentBoard)) return 0;

    
    if(Maximizing) {
        int bestScore = -10000;
        for(size_t i = 0; i < currentBoard.size(); i++) {
            if(currentBoard[i] == '0') {
                currentBoard[i] = '1';
                int score = miniMax(currentBoard, index, runAI, false, depth++);
                currentBoard[i] = '0';
                bestScore = std::max(score, bestScore);
                if(bestScore == 1) index = i;
            }
        }
        return bestScore;
    } else {
        int bestScore = 10000;
        for(size_t i = 0; i < currentBoard.size(); i++) {
            if(currentBoard[i] == '0') {
                currentBoard[i] = '2';
                int score = miniMax(currentBoard, index, runAI, true, depth++);
                currentBoard[i] = '0';
                bestScore = std::min(score, bestScore);
                if(bestScore == -1) index = i;
            }
        }

        return bestScore;
    }
}



//
// this is the function that will be called by the AI
//will use current state string to get how the board is?
//this function will use 3 int variables
//bestScore: will save what is the highest score move for AI
//bestmove: will save what position the bestScore was found at
//score: in the loop will hold what is the score for that position.
void TicTacToe::updateAI() 
{
    if(checkForDraw()) return; //check if game is full
    AIFunctions runAI;
    std::string currentBoard = stateString();
    int index = 0;
    int bestScore = -10000; //basically inf..

    for(size_t i = 0; i < currentBoard.size(); i++) {
         if(currentBoard[i] == '0') {
            currentBoard[i] = '1';
            int score = miniMax(currentBoard, index, runAI, false, 0);
            currentBoard[i] = '0';
            bestScore = std::max(score, bestScore);
         }
        }
      
    
    
    



        std::cout << "AI Final Score: " << bestScore << std::endl;
            std::cout << "At Index: " << index << std::endl << std::endl;
        int y = index / 3;
        int x = index % 3;
        BitHolder &holder = getHolderAt(y, x);

    if(actionForEmptyHolder(&holder)) {
        endTurn();
    }
    
    

    // we will implement the AI in the next assignment!
}

