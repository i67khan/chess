#ifndef __COMPUTERPLAYER_H__
#define __COMPUTERPLAYER_H__

#include "moves.h"

/**
 * Computer player class that processes possible moves for a 
 * computer player.
 */
class ComputerPlayer {
        // Weight of each piece.
        const int PAWNWEIGHT = 1;
        const int KNIGHTWEIGHT = 3;
        const int BISHOPWEIGHT = 3;
        const int ROOKWEIGHT = 5;
        const int QUEENWEIGHT = 9;

        // wraps min-max function by calculating score of positions.
        int minmaxWrapper(Board *board, int turns, int depth, Moves move);

        bool avoidsCapture(Board *board, int turns, std::tuple<int, int> position);
    public:
        // Returns random move.
        Moves levelOne(Board *board, int turns);
        // Returns a move that captures or checks the king, else calls level 1.
        Moves levelTwo(Board *board, int turns);
        // Returns a move that avoids piece capture, else calls level 2.
        Moves levelThree(Board *board, int turns);
        // Returns move with highest score using min-max algorithim.
        Moves minmaxMove(Board *board, int turns, int depth);
};

#endif