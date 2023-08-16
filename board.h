#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include "window.h"
using namespace std;
class ChessPiece;
class King;

/*
    A class containing the logic for handling all the game logic
    necessary for making moves, intializing a board and outputing
    the desired information. This class is the centre of our project
    as all the instructions for successfully executing a game
    must flow through this file into the respective sub-classes.
*/

class Board {
    //Vector containing all the white pieces
    vector<ChessPiece *> whitePieces;
    //Vector containing all the black pieces
    vector<ChessPiece *> blackPieces;
    //Pointer to the white king piece
    ChessPiece * whiteKing;
    //Pointer to the black king piece
    ChessPiece * blackKing;
    //Bool holds if black king is in check
    bool blackCheck;
    //Bool holds if white king is in check
    bool whiteCheck;

    //Variables which determing the type of castling possible
    bool whiteQueenCastle;
    bool whiteKingCastle;
    bool blackQueenCastle;
    bool blackKingCastle;

    public:
        //2-D vector containing pointers to pieces on the board 
        vector<vector< ChessPiece * >> board;
        //Constructor
        Board();
        //Constructor
        Board(const Board&);
        //Destructor
        ~Board();
        //Assignment Operator using deep copy
        Board &operator=(const Board &other);
        //Retrieves piece pointer at row,col position
        ChessPiece* getPiece(const int row,const int col);
        //Text output method that prints out the board and pieces
        void printText();
        //This method updates the information for executing a move including
        // moves to empty, occupied and promoting positions. It returns an int
        // based on the outcome of the move request.
        int makeMove(tuple<int,int> initial,tuple<int,int> dest);
        //Creates a piece using the decorator pattern with the specified parameters
        ChessPiece* createPiece(int row, int col, char c, bool color, bool moved);
        //Retreives a vector containing all the White Pieces
        vector<ChessPiece *> getWhitePieces();
        //Retreives a vector containing all the Black Pieces
        vector<ChessPiece *> getBlackPieces();
        //Adds a chess piece to the white piece vector
        void setWhitePieces(ChessPiece *);        
        //Adds a chess piece to the black piece vector
        void setBlackPieces(ChessPiece *); 
        //Removes the chess piece at row,col from its respective vector (whitePieces or blackPieces)
        void removePieceFromVector(const int, const int);
        //Retreives the pointer to the white king
        ChessPiece * getWhiteKing();
        //Retreives the pointer to the black king
        ChessPiece * getBlackKing();
        //Sets piece 'king' to the white king
        void setWhiteKing(ChessPiece *king);
        //Sets piece 'king' to the black king
        void setBlackKing(ChessPiece *king);
        //Retrieves value for whether black king is in check or not  
        bool getBlackCheck();
        //Retrieves value for whether white king is in check or not  
        bool getWhiteCheck();
};

#endif