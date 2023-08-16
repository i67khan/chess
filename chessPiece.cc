#include "chessPiece.h"
#include "moves.h"
#include "king.h"

using namespace std;

ChessPiece::ChessPiece (bool color, tuple<int, int> initialPosition, char type, bool hasMoved) :
    color{color}, position{initialPosition}, type{type}, hasMoved{hasMoved} {}

ChessPiece::~ChessPiece () {}

bool ChessPiece::getColor() {
    return color;
}

bool ChessPiece::getHasMoved() {
    return hasMoved;
}

char ChessPiece::getType() {
    return type;
}

tuple<int, int> ChessPiece::getPosition() const {
    return position;
}

std::vector<Moves> ChessPiece::getLegalMoves() const{
    return legalMoves;
}

void ChessPiece::setPosition(std::tuple<int, int> newPosition) {
    position = newPosition;
}

std::vector<Moves> ChessPiece::getPossibleMoves() const{
    return possibleMoves;
}

void ChessPiece::setLegalMoves() {
    legalMoves.clear();
    for (auto move : possibleMoves) {
        auto board =  make_shared<Board>(*move.getBoard());
        
        auto targetSquare = board->getPiece(get<0>(move.getFinalPosition()), get<1>(move.getFinalPosition()));

        if (targetSquare != nullptr && targetSquare->getColor() != color && targetSquare->getType() == 'K') {
            continue;
        }

        board->makeMove(move.getInitialPosition(), move.getFinalPosition());

        //board->printText();
        vector<ChessPiece*> enemyPieces;
        King* friendlyKing;


        if (getColor()) {
            enemyPieces = board->getBlackPieces();
            friendlyKing = static_cast<King *> (board->getWhiteKing());
            friendlyKing->uncheckKing();
        } else {
            enemyPieces = board->getWhitePieces();
            friendlyKing = static_cast<King *> (board->getBlackKing());
            friendlyKing->uncheckKing();
        }  


        bool cheked = false;
        for (auto pieces : enemyPieces) {
            if (pieces == nullptr) continue;
            pieces->setPossibleMoves(board.get());
            if (friendlyKing->getCheck()) {
                cheked = true;
                break;
            }
        }

        if (!cheked) {
            legalMoves.emplace_back(move);
        }
    }
}

void ChessPiece::checkForCheck() {
    for (auto move : possibleMoves) {
        ChessPiece* square = move.getBoard()->getPiece(get<0>(move.getFinalPosition()), get<1>(move.getFinalPosition()));
        if (square != nullptr && square->getType() == 'K') {
            if (square->getColor() != getColor()) {
                King *king;
                if (square->getColor()) {
                    king = dynamic_cast<King *>(move.getBoard()->getWhiteKing());
                } else {
                    king = dynamic_cast<King *>(move.getBoard()->getBlackKing());
                }
                king->checkKing();
            }
        }
    }
}


