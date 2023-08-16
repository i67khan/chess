#include "computerPlayer.h"
#include "chessPiece.h"
#include "king.h"
#include <vector>

using namespace std;

bool ComputerPlayer::avoidsCapture(Board *board, int turns, std::tuple<int, int> position) {
    vector <ChessPiece *> enemyPieces;
    if (turns%2 == 0) {
        enemyPieces = board->getWhitePieces();
    } else {
        enemyPieces = board->getBlackPieces();
    }

    for (auto ep: enemyPieces) {
        if (ep == nullptr) continue;

        ep->setPossibleMoves(board);
        ep->setLegalMoves();

        for (auto moves: ep->getLegalMoves()) {
            if (moves.getFinalPosition() == position) {
                return false;
            }
        }
    }
    return true;
}

int ComputerPlayer::minmaxWrapper(Board *board, int turns, int depth, Moves move) {
    auto newBoard =  make_shared<Board>(*move.getBoard());
        
    newBoard->makeMove(move.getInitialPosition(), move.getFinalPosition());

    if (depth == 0) {
        vector <ChessPiece *> enemyPieces;
        vector <ChessPiece *> friendlyPieces;
        if (turns%2 == 0) {
            friendlyPieces = newBoard->getWhitePieces();
            enemyPieces = newBoard->getBlackPieces();
        } else {
            friendlyPieces = newBoard->getBlackPieces();
            enemyPieces = newBoard->getWhitePieces();
        }
        
        int score = 0;

        for (auto p: friendlyPieces) {
            if (p == nullptr) continue;
            if (p->getType() == 'P') score-= PAWNWEIGHT;
            if (p->getType() == 'N') score-= KNIGHTWEIGHT;
            if (p->getType() == 'B') score-= BISHOPWEIGHT;
            if (p->getType() == 'R') score-= ROOKWEIGHT;
            if (p->getType() == 'Q') score-= QUEENWEIGHT;
        }

        for (auto p: enemyPieces) {
            if (p == nullptr) continue;
            if (p->getType() == 'P') score+= PAWNWEIGHT;
            if (p->getType() == 'N') score+= KNIGHTWEIGHT;
            if (p->getType() == 'B') score+= BISHOPWEIGHT;
            if (p->getType() == 'R') score+= ROOKWEIGHT;
            if (p->getType() == 'Q') score+= QUEENWEIGHT;
        }

        return score;
    }

    vector <ChessPiece *> friendlyPieces;

    if (turns%2 == 0) {
        friendlyPieces = newBoard->getWhitePieces();
    } else {
        friendlyPieces = newBoard->getBlackPieces();
    }
    
    Moves bestMove = Moves{make_tuple(0,0), make_tuple(0,0), board};
    bool foundMove = false;
    int maxMove = 0;

    for (auto p : friendlyPieces) {
        if (p == nullptr) continue;

        p->setPossibleMoves(newBoard.get());
        p->setLegalMoves();

        for (auto newMove : p->getLegalMoves()) {
            if (!foundMove) {
                int maxMove = minmaxWrapper(newBoard.get(), turns + 1, depth - 1, newMove) ;
                bestMove = newMove;
            } else  {
                int temp = minmaxWrapper(newBoard.get(), turns + 1, depth - 1, newMove);
                if (maxMove < temp) {
                    maxMove = temp;
                }
            }
        }
    }

    return maxMove;

}


Moves ComputerPlayer::levelOne(Board *board, int turns) {
    vector <ChessPiece *> friendlyPieces;
    if (turns%2 == 0) {
        friendlyPieces = board->getWhitePieces();
    } else {
        friendlyPieces = board->getBlackPieces();
    }

    vector <Moves> allMoves;

    int counter = 0;

    for (auto p: friendlyPieces) {
        if (p == nullptr) continue;
        if (counter > 100) {
            break;
        }

        p->setPossibleMoves(board);
        p->setLegalMoves();
        for (auto move: p->getLegalMoves()) {
            allMoves.emplace_back(move);
        }
    }

    if (allMoves.size() != 0) {
        return allMoves[rand() % allMoves.size()];
    }

    return Moves(make_tuple(0,0), make_tuple(0,0), board);
}


Moves ComputerPlayer::levelTwo(Board *board, int turns) {
    vector <ChessPiece *> friendlyPieces;
    if (turns%2 == 0) {
        friendlyPieces = board->getWhitePieces();
    } else {
        friendlyPieces = board->getBlackPieces();
    }

    for (auto p: friendlyPieces) {
        if (p == nullptr) continue;
        p->setPossibleMoves(board);
        p->setLegalMoves();
        for (auto move: p->getLegalMoves()) {
            if (board->getPiece(get<0>(move.getFinalPosition()), get<1>(move.getFinalPosition())) != nullptr) {
                return move;
            }
        }
    }

    for (auto p: friendlyPieces) {
        if (p == nullptr) continue;
        for (auto move: p->getLegalMoves()) {
            auto board =  make_shared<Board>(*move.getBoard());
            board->makeMove(move.getInitialPosition(), move.getFinalPosition());
            King *enemyKing;
            if (turns%2 == 0) {
                enemyKing = static_cast<King *> (board->getBlackKing());
            } else {
                enemyKing = static_cast<King *> (board->getWhiteKing());
            }
            if (enemyKing->getCheck()) {
                return move;
            }
        }
    }
    return levelOne(board, turns);
}

Moves ComputerPlayer::levelThree(Board *board, int turns) {
    vector <ChessPiece *> enemyPieces;
    vector <ChessPiece *> friendlyPieces;
    if (turns%2 == 0) {
        friendlyPieces = board->getWhitePieces();
        enemyPieces = board->getBlackPieces();
    } else {
        friendlyPieces = board->getBlackPieces();
        enemyPieces = board->getWhitePieces();
    }

    for (auto ep: enemyPieces) {
        if (ep == nullptr) continue;
        ep->setPossibleMoves(board);
        ep->setLegalMoves();
        for (auto enemyMove : ep->getLegalMoves()) {
            auto square = board->getPiece(get<0>(enemyMove.getFinalPosition()), get<1>(enemyMove.getFinalPosition()));
            if (square != nullptr) {
                square->setPossibleMoves(board);
                square->setLegalMoves();
                if (square->getLegalMoves().size() != 0) {
                    for (auto move: square->getLegalMoves()) {
                        auto newBoard =  make_shared<Board>(*board);
                        newBoard->makeMove(move.getInitialPosition(), move.getFinalPosition());
                        if (avoidsCapture(newBoard.get(), turns + 1, move.getFinalPosition())) {
                            return move;
                        }
                    }
                }
            }
        }
    }
    
    return levelTwo(board, turns);
}

Moves ComputerPlayer::minmaxMove(Board *board, int turns, int depth) {
    vector <ChessPiece *> friendlyPieces;

    if (turns%2 == 0) {
        friendlyPieces = board->getWhitePieces();
    } else {
        friendlyPieces = board->getBlackPieces();
    }
    
    Moves bestMove = Moves{make_tuple(0,0), make_tuple(0,0), board};
    bool foundMove = false;
    bool changed = false;
    int maxMove = 0;

    for (auto p : friendlyPieces) {
        if (p == nullptr) continue;

        p->setPossibleMoves(board);
        p->setLegalMoves();

        for (auto move : p->getLegalMoves()) {
            if (!foundMove) {
                int maxMove = minmaxWrapper(board, turns + 1, depth - 1, move);
                bestMove = move;
                foundMove = true;
            } else  {
                int temp = minmaxWrapper(board, turns + 1, depth - 1, move);
                if (temp != maxMove) changed = true;
                if (maxMove < temp) {
                    maxMove = temp;
                    bestMove = move;
                }
            }
        }
    }

    if (!changed) {
        return levelThree(board, turns);
    }

    return bestMove;
}
