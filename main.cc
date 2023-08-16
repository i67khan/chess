#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "window.h"
#include <cctype>
#include "board.h"
#include "chessPiece.h"
#include "game.h"
#include "moves.h"
#include "king.h"
#include <tuple>

using namespace std;

int main(void) {
    //=============================== scoring
    double white_wins = 0;
    double black_wins = 0;
    double ties = 0;
    //=============================== 
    const int black = 1;
    const int white = 0;
    //===============================
    int turn = white; 
    bool finished = false;
    while (!finished || !cin.eof()){
        //===============================
        bool black_computer = false;
        bool white_computer = false;
        //===============================
        int white_computer_level;
        int black_computer_level;
        //===============================
        //=================================================== phase 1 ================================
        if (!cin.eof()) {
            cout << "Welcome to Chess: CS246 Edition" << endl;
            cout << "if you'd like to begin a new game type in: game white-player black-player" << endl;
        }
        string s;
        string white_player;
        string black_player;
        string cmd;
        int white_diff = 0;
        int black_diff = 0;
        getline(cin, s);
        bool cmd_read = false;
        bool player1_read = false; 
        bool player2_read = false;
        int len = s.length();
        int counter = 0;
        int read_in_counter = 0;
        for (char c: s) {
            if (isdigit(c)) {
                if(!white_diff && white_player == "comp") {
                    string s;
                    s += c;
                    white_diff = stoi(s);
                    continue;
                } else if (!black_diff && black_player == "comp") {
                    string s;
                    s += c;
                    black_diff = stoi(s);
                    continue;
                }
            }
            //=============================
            if (counter == len - 1) {
                black_player += c;
                break;
            }
            //=============================
            if (cmd == "resign") {
                break;
            }
            //=============================
            if (cmd == "game" && read_in_counter == 0) {
                read_in_counter++;
                continue;
            }
            //=============================
            if ((white_player == "human" || white_player == "comp") && read_in_counter == 1) {
                read_in_counter++;
                continue;
            } 
            //=============================
            if (isalpha(c)) {
                if (read_in_counter == 0) {
                    cmd += c;
                    continue;
                } else if (read_in_counter == 1) {
                    white_player += c;
                    continue;
                } else if (read_in_counter == 2) {
                    black_player += c;
                    continue;
                }
            }
        }
        if (cin.eof()) {
            finished = true;
            cout << "Final Score:" << endl;
            cout << "White: " << white_wins + (ties/2) << endl;
            cout << "Black: " << black_wins + (ties/2) << endl;
            break;
        }
        if (cmd == "resign") {
            break;
        }
        if (cmd == "game") {
            Game g;
            if (white_player == "comp") {
                white_computer = true;
                white_computer_level = white_diff;
            } else if (white_player == "human") {
                white_computer = false;
            }

            if (black_player == "comp") {
                black_computer = true;
                black_computer_level = black_diff;
            } else if (black_player == "human") {
                black_computer = false;
            }
            cout << "if you would like to play a default game of chess type in: default" << endl;
            cout << "if you would like to configure the board to your liking type in: special" << endl;
            string cmd2;
            cin >> cmd2;
            if (cmd2 == "special" && !cin.eof())
            {
                g.printGraphics();
                bool exit = false;

                cout << "Here are a list of supported commands: " << endl;
                cout << "+ Piece rowcol : enter the piece type followed by the xy coordinate for the position" << endl;
                cout << "- rowcol: enter the xy coordinate to the piece you'd like removed" << endl;
                cout << "= colour: makes it colours turn to go next" << endl;
                cout << "done: exits setup mode" << endl;
                cout << "help: displays commands instructions" << endl;

                while (!exit && !cin.eof()) {
                    string s;
                    string piece;
                    string from;
                    
                    cin >> s;
                    if (s.compare("Help") == 0 || s.compare("help") == 0) {
                        cout << "Here are a list of supported commands: " << endl;
                        cout << "+ Piece rowcol : enter the piece type followed by the xy coordinate for the position" << endl;
                        cout << "- rowcol: enter the xy coordinate to the piece you'd like removed" << endl;
                        cout << "= colour: makes it colours turn to go next" << endl;
                        cout << "done: exits setup mode" << endl;
                        cout << "help: displays commands instructions" << endl;
                    }

                    char oper = s.at(0);
                    if (oper == '+') {
                        cin >> piece >> from;
                        if (piece.length() != 1 || from.length() != 2) {
                            cout << "Invalid command" << endl;
                            continue;
                        }
                        char type = piece.at(0);
                        int col_from = (from.at(0) - 97);
                        int row_from = (from.at(1) - 48) - 1;
                        
                        if (!(row_from >= 0 && row_from <= 7 &&
                            col_from >= 0 && col_from <= 7)) {
                            cout << "Position is out of bounds." << endl;
                            continue;
                        }
                        g.setupGame(oper, type, make_tuple(row_from,col_from));
                    } else if (oper == '-') {
                        cin >> from;
                        if (from.length() != 2) {
                            cout << "Invalid command" << endl;
                            continue;
                        }
                        int col_from = (from.at(0) - 97);
                        int row_from = (from.at(1) - 48) - 1;
                        
                        if (!(row_from >= 0 && row_from <= 7 &&
                            col_from >= 0 && col_from <= 7)) {
                            cout << "Position is out of bounds." << endl;
                            continue;
                        }

                        g.setupGame(oper, 'Z', make_tuple(row_from,col_from));
                    } else if (oper == '=') {
                        string colour;
                        cin >> colour;
                        turn = (colour.compare("Black") != 0 || colour.compare("black") != 0) ? black : white;
                    } else if (s.compare("Done") == 0 || s.compare("done") == 0) {
                        exit = g.validateConfig();
                    } else {
                        cout << "You entered an incorrect operation. Please try again" << endl;
                    }
                }
            }
            
            if (cmd2 == "default" && !cin.eof()) {
                g.initGame();
            }
            bool done = false;
            while (!done) {
                    if (cin.eof()) {
                        break;
                    }
                    cout << "here are a list of supported commands: " << endl;
                    cout << "resign: concedes the game to your opponent" << endl;
                    cout << "move rowcol_from rowcol_to: enter the xy coordinate for the position you’d like to move from to the xy coordinate you’d like to move to" << endl;
                    //=================================================================== computer stuff
                    if (turn == white) {
                        cout << "it is white's turn: " << endl;
                        if (white_computer) {
                            string cmd3;
                            cin >> cmd3; 
                            if (cmd3 == "resign") {
                                if (turn == white) {
                                    cout << "Black wins!" << endl;
                                    black_wins++;
                                } else {
                                    cout << "White wins!" << endl;
                                    white_wins++;
                                }
                                cin.ignore();
                                break;
                            }
                            if (cmd3 == "move") {
                                turn = !turn;
                            if (white_computer_level == 1) { 
                                Moves m = g.player.levelOne(g.chessBoard, 0);
                                g.makeMove(m.getInitialPosition(), m.getFinalPosition(), true);
                                int game_val = g.gameStatus(turn);
                                if (game_val == 0) {
                                    if(g.chessBoard->getBlackCheck()) {
                                        cout << "Black is in check" << endl;
                                    }
                                    continue;
                                } 
                                if (game_val == 1) {
                                    white_wins++;
                                    cout << "Checkmate! White wins!" << endl;
                                    cin.ignore();
                                    break;
                                } 
                                if (game_val == 2) {
                                    ties++;
                                    cout << "Stalemate!" << endl;
                                    cin.ignore();
                                    break;
                                }
                                continue; 
                            } 
                            if (white_computer_level == 2) { 
                                Moves m = g.player.levelTwo(g.chessBoard, 0); 
                                g.makeMove(m.getInitialPosition(), m.getFinalPosition(), true);
                                int game_val = g.gameStatus(turn);
                                if (game_val == 0) {

                                    if(g.chessBoard->getBlackCheck()) {
                                        cout << "Black is in check" << endl;
                                    }
                                    continue;
                                } 
                                if (game_val == 1) {
                                    white_wins++;
                                    cout << "Checkmate! White wins!" << endl;
                                    cin.ignore();
                                    break;
                                } 
                                if (game_val == 2) {
                                    ties++;
                                    cout << "Stalemate!" << endl;
                                    cin.ignore();
                                    break;
                                }
                                continue; 
                            } 
                            if (white_computer_level == 3) { 
                                Moves m = g.player.levelThree(g.chessBoard, 0); 
                                g.makeMove(m.getInitialPosition(), m.getFinalPosition(), true);
                                int game_val = g.gameStatus(turn);
                                if (game_val == 0) {

                                    if(g.chessBoard->getBlackCheck()) {
                                        cout << "Black is in check" << endl;
                                    }
                                    continue;
                                } 
                                if (game_val == 1) {
                                    white_wins++;
                                    cout << "Checkmate! White wins!" << endl;
                                    cin.ignore();
                                    break;
                                } 
                                if (game_val == 2) {
                                    ties++;
                                    cout << "Stalemate!" << endl;
                                    cin.ignore();
                                    break;
                                }
                                continue;      
                            } 
                            if (white_computer_level >= 4) { 
                                Moves m = g.player.minmaxMove(g.chessBoard, 0, white_computer_level - 3); 
                                g.makeMove(m.getInitialPosition(), m.getFinalPosition(), true);
                                int game_val = g.gameStatus(turn);
                                if (game_val == 0) {
                                    if(g.chessBoard->getBlackCheck()) {
                                        cout << "Black is in check" << endl;
                                    }
                                    continue;
                                } 
                                if (game_val == 1) {
                                    white_wins++;
                                    cout << "Checkmate! White wins!" << endl;
                                    cin.ignore();
                                    break;
                                } 
                                if (game_val == 2) {
                                    ties++;
                                    cout << "Stalemate!" << endl;
                                    cin.ignore();
                                    break;
                                }
                                continue; 
                            }
                            
                            } 
                            continue; 
                        }
                    }
                    else {
                        cout << "it is black's turn: " << endl;
                        if (black_computer) {
                            string cmd3;
                            cin >> cmd3; 
                            if (cmd3 == "resign") {
                                if (turn == white) {
                                    cout << "Black wins!" << endl;
                                    black_wins++;
                                } else {
                                    cout << "White wins!" << endl;
                                    white_wins++;
                                }
                                cin.ignore();
                                break;
                            }
                            if (cmd3 == "move") {
                                turn = !turn;
                            if (black_computer_level == 1) {
                                Moves m = g.player.levelOne(g.chessBoard, 1);
                                g.makeMove(m.getInitialPosition(), m.getFinalPosition(), true);
                                int game_val = g.gameStatus(turn);
                                if (game_val = 0) {
                                    if(g.chessBoard->getWhiteCheck()) {
                                        cout << "White is in check" << endl;
                                    }
                                    continue;
                                } 
                                if (game_val == 1) {
                                    black_wins++;
                                    cout << "Checkmate! Black wins!" << endl;
                                    cin.ignore();
                                    break;
                                } 
                                if (game_val == 2) {
                                    ties++;
                                    cout << "Stalemate!" << endl;
                                    cin.ignore();
                                    break;
                                }
                                
                            }  
                            if (black_computer_level == 2) {  
                                Moves m = g.player.levelTwo(g.chessBoard, 1); 
                                g.makeMove(m.getInitialPosition(), m.getFinalPosition(), true);
                                int game_val = g.gameStatus(turn);
                                if (game_val == 0) {
                                    if(g.chessBoard->getWhiteCheck()) {
                                        cout << "White is in check" << endl;
                                    }
                                    continue;
                                } 
                                if (game_val == 1) {
                                    black_wins++;
                                    cout << "Checkmate! Black wins!" << endl;
                                    cin.ignore();
                                    break;
                                } 
                                if (game_val == 2) {
                                    ties++;
                                    cout << "Stalemate!" << endl;
                                    cin.ignore();
                                    break;
                                }
                                continue; 
                            }
                            if (black_computer_level == 3) { 
                                Moves m = g.player.levelThree(g.chessBoard, 1); 
                                g.makeMove(m.getInitialPosition(), m.getFinalPosition(), true);
                                int game_val = g.gameStatus(turn);
                                if (game_val == 0) {
                                    if(g.chessBoard->getWhiteCheck()) {
                                        cout << "White is in check" << endl;
                                    }
                                    continue;
                                } 
                                if (game_val == 1) {
                                    black_wins++;
                                    cout << "Checkmate! Black wins!" << endl;
                                    cin.ignore();
                                    break;
                                } 
                                if (game_val == 2) {
                                    ties++;
                                    cout << "Stalemate!" << endl;
                                    cin.ignore();
                                    break;
                                }
                                continue;     
                            }
                            if (black_computer_level >= 4) {
                                Moves m = g.player.minmaxMove(g.chessBoard, 1, black_computer_level - 3); 
                                g.makeMove(m.getInitialPosition(), m.getFinalPosition(), true);
                                int game_val = g.gameStatus(turn);
                                if (game_val == 0) {
                                    if(g.chessBoard->getWhiteCheck()) {
                                        cout << "White is in check" << endl;
                                    }
                                    continue;
                                } 
                                if (game_val == 1) {
                                    black_wins++;
                                    cout << "Checkmate! Black wins!" << endl;
                                    cin.ignore();
                                    break;
                                } 
                                if (game_val == 2) {
                                    ties++;
                                    cout << "Stalemate!" << endl;
                                    cin.ignore();
                                    break;
                                }
                                continue;  
                                 }
                             } continue; 
                        }
                    }
                    //=================================================================== computer stuff
                    //=================================================================== human stuff
                    cin >> cmd;
                    if (cmd == "move" && !cin.eof()) {
                        string from;
                        string to;
                        cin >> from >> to;
                        int col_from = (from.at(0) - 97);
                        int row_from = (from.at(1) - 48) - 1;
                        int col_to = (to.at(0) - 97);
                        int row_to = (to.at(1) - 48) - 1;
                        if (g.chessBoard->board[row_from][col_from] == nullptr) {
                            cout << "invalid move: there is no piece in initial position" << endl;
                            continue;
                        }
                        if (turn == g.chessBoard->board[row_from][col_from]->getColor()) {
                            cout << "invalid move: you are attempting to move the opposite players piece" << endl;
                            continue; 
                        }
                        int result = g.makeMove(make_tuple(row_from, col_from), make_tuple(row_to, col_to), false);
                        
                        if (result == 0)
                        {
                            int game_val = g.gameStatus(turn);
                                if (game_val == 0) {
                                    King *king;
                                    if (turn == black) {
                                        king = dynamic_cast<King *>(g.chessBoard->getWhiteKing());
                                    } else {
                                        king = dynamic_cast<King *>(g.chessBoard->getBlackKing());
                                    }
                                    if(king->getCheck() && (turn == black)) {
                                        cout << "White is in check" << endl;
                                    } else if (king->getCheck() && (turn == white)) {
                                        cout << "Black is in check" << endl;
                                    }
                                    turn = !turn;
                                    continue;
                                } else if (game_val == 1) {
                                    done = true;
                                    if (turn) {
                                    white_wins++;
                                    cout << "Checkmate! Black wins!" << endl;
                                    cin.ignore();
                                    } else {
                                    black_wins++;
                                    cout << "Checkmate! White wins!" << endl;
                                    cin.ignore();
                                    }
                                } else if (game_val == 2) {
                                    done = true;
                                    ties++;
                                    cout << "Stalemate!" << endl;
                                    cin.ignore();
                                }
                        }
                        if (result == -1){
                            cout << "invalid move: there is no piece in initial position" << endl;
                        }
                        if (result == -2){
                            cout << "invalid move: the move you made is illegal" << endl;
                        }
                        if (result == -3) {
                            cout << "invalid move: the move you made is out of bounds" << endl;
                        }
                    }
                    if (cmd == "resign") {
                        if (turn == white){
                            cout << "Black wins!" << endl;
                            black_wins++;
                        } else {
                            cout << "White wins!" << endl;
                            white_wins++;
                        }
                        cin.ignore();
                        break;
                    }
            }
            //=================================================================== human stuff
        }
    }
}