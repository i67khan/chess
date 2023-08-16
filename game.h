#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <vector>
#include "board.h"
#include "computerPlayer.h"

class Board;


/*
    This class hanldes the setup for the chess game, including the default and custom 
    setups for the board. Furthermore it displays the empty chessboard which will later 
    be populated by pieces. The game class makes moves by calling on the necessary helper
    methods to execute those instructions for cases like move to empty, capturing, en-passsant,
    and castling. Finally, it checks the status of the board as it updates after each turn looking
    for stalemates, checks, and checkmates. 
*/

class Game {
    public:
    // Computer player class.
    ComputerPlayer player;
    //Graphical window vairable
    Xwindow w;
    //Record of the pieces locations on the board
    Board* chessBoard;
    //Constructor
    Game();
    //Destructor
    ~Game();
    //Starts a basic game by setting pointers and initializing vectors and the board
    void initGame();
    //This fucntion prints the basic board background and outputs the labels for the board 
    void printGraphics();
    //Updates the tile at row,col with the necessary colour to cover a piece
    void updateGraphics(int row, int col);
    //Draws the new piece at location row,col after moving a piece
    void drawPiece(int row, int col);
    //Goes through the various cases for moving a piece and calls board.h for pointer allocation
    // and update the graphical interface
    int makeMove(tuple<int,int> initial,tuple<int,int> dest, bool compPlayer);//plays a move
    //Intializes a custom board with user input and updates necessary board and piece vectors
    void setupGame(char, char, tuple<int,int> pos);
    //This validates whether the custom board from setupGame follows the requirements for the 'setup' command
    bool validateConfig();
    //Checks the current status of the board and returns int for cases: Stalemate, Check, or Checkmate
    int gameStatus(bool);
};

#endif