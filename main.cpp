//
//  main.cpp
//  Connect 4 AI
//
//  Created by Andrew Lorber on 11/8/19.
//  Copyright © 2019 Andrew Lorber. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>

using namespace std;

int currentBoard[6][7] = {0};

// Loads user-set board
void initUserBoard(){
    // Reads in file with game board. See board key above.
    string file;
    cout << "Please enter the name of your board file.\nEach space should be either:\n  0 - empty space\n";
    cout << "  1 - player 1 piece\n  2 - player 2 piece\n";
    cin >> file;
    ifstream fin;
    fin.open(file);
    
    // Checks for incorrect input
    while(!fin.is_open()){
        cout << "The file you entered cannot be opened.\nPlease enter a new file.\n";
        cin >> file;
        fin.open(file);
    }
    
    int square;
    
    int i = 0, j = 0;
    while(fin >> square){
        currentBoard[j][i] = square;
        
        i++;
        if(i == 7){
            i = 0;
            j++;
        }
        if(j == 6){
            break;
        }
    }
    
}

void printBoard(){
    cout << " \nKEY:\n  P1: " << "\033[1;31m" << "\u25EF" << "\033[0m\n";
    cout << "  P2: " << "\033[1;34m" << "\u25EF" << "\033[0m\n";
    
    cout << "\n |-1-|-2-|-3-|-4-|-5-|-6-|-7-|\n\n";
    cout << " |---|---|---|---|---|---|---|\n";
    for(int i = 0, j= 0; j < 6; i++){
        cout << " | ";
        if(currentBoard[j][i] == 1){ // Player 1 = red circle
            cout << "\033[1;31m" << "\u25EF" << "\033[0m";
        } else if(currentBoard[j][i] == 2){ // Player 2 = blue circle
            cout << "\033[1;34m" << "\u25EF" << "\033[0m";
        } else {
            cout << " ";
        }
        
        if(i == 6){
            cout << " |\n |---|---|---|---|---|---|---|\n";
            i = -1;
            j++;
        }
    }
}

// Gets starting player
bool player1Starts(bool userPlaying){
    string resp;
    if(userPlaying){
        cout << "Would you like to go first? (Y/N) \n";
    } else {
        cout << "Would you like player 1 to go first? (Y/N) \n";
    }
    
    cin >> resp;
    while(resp.compare("Y") != 0 && resp.compare("N") != 0){
        cout << "That was an invalid response. Please respond with 'Y' or 'N'." << '\n';
        cin >> resp;
    }
    if(resp.compare("Y") == 0){
        return true;
    } else {
        return false;
    }
}

// Checks if game ends
// Returns player number if a player has won, 0 if game is not over, & 3 if all spots are filled and tie.
int gameOver(int board[6][7] = currentBoard){
    bool tie = true;
    for(int i = 0, j = 0; j < 6; i++){
        int piece = board[j][i];
        if(piece == 0){
            tie = false;
        } else {
            // Check left side
            if(i > 2){
                if(board[j][i-1] == piece && board[j][i-2] == piece && board[j][i-3] == piece){
                    return piece;
                }
                
                // check top & bottom left diagonal
                if(j > 2){
                    if(board[j-1][i-1] == piece && board[j-2][i-2] == piece && board[j-3][i-3] == piece){
                        return piece;
                    }
                } else if (j < 3){
                    if(board[j+1][i-1] == piece && board[j+2][i-2] == piece && board[j+3][i-3] == piece){
                        return piece;
                    }
                }
            }
            // Check right side
            if(i < 4){
                if(board[j][i+1] == piece && board[j][i+2] == piece && board[j][i+3] == piece){
                    return piece;
                }
                
                // Check top & bottom right diagonal
                if(j > 2){
                    if(board[j-1][i+1] == piece && board[j-2][i+2] == piece && board[j-3][i+3] == piece){
                        return piece;
                    }
                } else if (j < 3){
                    if(board[j+1][i+1] == piece && board[j+2][i+2] == piece && board[j+3][i+3] == piece){
                        return piece;
                    }
                }
            }
            // Check top
            if(j > 2){
                if(board[j-1][i] == piece && board[j-2][i] == piece && board[j-3][i] == piece){
                    return piece;
                }
            }
            // Check bottom
            if(j < 3){
                if(board[j+1][i] == piece && board[j+2][i] == piece && board[j+3][i] == piece){
                    return piece;
                }
            }
        }
        
        if(i == 6){
            i = -1;
            j++;
        }
    }
    if(tie){
        return 3;
    } else {
        return 0;
    }
}

// Checks for game over and prints dialogue
bool checkEndGame(bool userPlaying = true){
    int winningPlayer = gameOver();
    if(winningPlayer == 0){
        return false;
    } else if(winningPlayer == 3){
        cout << "The game is a tie.\n";
    } else if(winningPlayer == 1){
        if(userPlaying){
            cout << "Congrats! You win!\n";
        } else {
            cout << "Player 1 wins.\n";
        }
        
    } else{
        if(userPlaying){
            cout << "The AI has won.\n";
        } else {
            cout << "Player 2 wins.\n";
        }
    }
    return true;
}

// Implements game move
void implementMove(int moveNum, int piece, int board[6][7] = currentBoard){
    moveNum--;
    for(int i = 1; i < 6; i++){
        if(board[i][moveNum] != 0){
            board[i-1][moveNum] = piece;
            break;
        } else if(i == 5){
            board[i][moveNum] = piece;
        }
    }
}

// Checks if there is only one possible move left
int oneMove(int board[6][7] = currentBoard){
    int move = -1;
    for(int i = 0; i < 7; i++){
        if(board[0][i] == 0){
            if(move > -1){
                return 0;
            } else {
                move = i+1;
            }
        }
    }
    return move;
}

void copyBoard(int from[6][7], int to[6][7]){
    for(int i = 0, j = 0; j < 6; i++){
        
        to[j][i] = from[j][i];
        
        if(i == 6){
            i = -1;
            j++;
        }
    }
}

// Heuristic function
int evalFunc(int board[6][7]){
    int val = 0;
    
    if(gameOver(board) == 2){
        val += 500;
    } else if(gameOver(board) == 1){
        val -= 500;
    }
    
    // Random number added to make it randomly choose between multiple "equal" moves
    val += rand() % 10;
    return val;
}

// Global variable to keep track of time limit
bool timeLimitPassed = false;

// Alpha Beta Search
int alphaBeta(int board[6][7], int depthLeft, int alpha, int beta,
            bool maxPlayer, time_t endTime, bool root = false){
    
    // Checks if time limit has run out
    if(timeLimitPassed || time(nullptr) >= endTime){
        timeLimitPassed = true;
        return 0;
    }
    
    int boardCopy[6][7] = {0};
    int value;
    int tmpValue;
    int bestMove = 1;
    
    // Runs evaluation function at max depth or end-game board
    if(depthLeft <= 0 || gameOver(board) > 0){
        return evalFunc(board);
    }
    
    if(maxPlayer){
        value = -90000;
        for(int i = 1; i <= 7; i++){
            if (board[0][i-1] != 0) {
                continue;
            }
            copyBoard(board, boardCopy);
            implementMove(i, 2, boardCopy);
            
            tmpValue = alphaBeta(boardCopy, depthLeft-1, alpha, beta, false, endTime);
            if(tmpValue > value){
                value = tmpValue;
                
                if(root){
                    bestMove = i;
                }
            }
            
            alpha = max(alpha, value);
            if(alpha >= beta){
                break;
            }
        }
        if(root){
            return bestMove;
        } else {
            return value;
        }
    } else {
        value = 90000;
        for(int i = 1; i <= 7; i++){
            if (board[0][i-1] != 0) {
                continue;
            }
            copyBoard(board, boardCopy);
            implementMove(i, 1, boardCopy);
            
            tmpValue = alphaBeta(boardCopy, depthLeft-1, alpha, beta, true, endTime);
            if(tmpValue < value){
                value = tmpValue;
                
                if(root){
                    bestMove = i;
                }
            }
            
            beta = min(beta, value);
            if(alpha >= beta){
                break;
            }
        }
        if(root){
            return bestMove;
        } else {
            return value;
        }
    }
}

// Implements Iterative Deepening for the Alpha Beta Search
int iterativeDeepening(int seconds, bool player2 = true){
    timeLimitPassed = false;
    int bestMove = 1;
    int move;
    time_t startTime = time(nullptr);
    time_t endTime = startTime + seconds;
    int depth = 1;
    
    // If there is only one move, do it
    if(oneMove() > 0){
        cout << "Depth: 0\nTime Searching: " << time(nullptr) - startTime << " Seconds\n";
        return oneMove();
    }
    
    // If there is less than half the time left, then it won't finish the next iteration, so stop
    while((time(nullptr) + (seconds/2)) <= endTime){
        move = alphaBeta(currentBoard, depth, -90000, 90000, player2, endTime, true);
        if(!timeLimitPassed){
            bestMove = move;
            depth++;
        }
    }
    cout << "Depth: " << depth << "\nTime Searching: " << time(nullptr) - startTime << " Seconds\n";
    return bestMove;
}

void playAIvsAI(int startingPlayer, int seconds){
    if(startingPlayer == 1){
        cout << "Player 1 is thinking...\n";
        implementMove(iterativeDeepening(seconds) , 1);
        printBoard();
    }
    while(true){
        // Player 2 turn
        if(checkEndGame(false)){
            return;
        };
        cout << "Player 2 is thinking...\n";
        implementMove(iterativeDeepening(seconds) , 2);
        printBoard();
        
        
        // Player 1 turn
        if(checkEndGame(false)){
            return;
        };
        cout << "Player 1 is thinking...\n";
        implementMove(iterativeDeepening(seconds) , 1);
        printBoard();
    }
}

// Gets user's move choice
int getMoveChoice(){
    double moveNum;
    cout << "Which column would you like to place your piece in?\n";
    cin >> moveNum;
    moveNum = round(moveNum);
    while(moveNum < 1 || moveNum > 7 || currentBoard[0][int(moveNum)-1] != 0){
        cout << "The move you entered is invalid.\nWhich column would you like to place your piece in?\n";
        cin >> moveNum;
        moveNum = round(moveNum);
    }
    return moveNum;
}

void playGame(){
    
    // User decides game board
    double input;
    cout << "Welcome to checkers!\nPlease respond with the number of your choice:\n";
    cout << "1. Begin a new game\n2. Load a custom board\n";
    cin >> input;
    while(input != 1 && input != 2){
        cout << "That was an invalid choice. Please respond with 1 or 2.\n";
        cin >> input;
    }
    if(input == 2){
        initUserBoard();
    }
    
    // User Vs AI or AI Vs AI
    bool AIvsAI = false;
    cout << "Please choose a game mode:\n";
    cout << "1. User Vs AI\n2. AI Vs AI\n";
    cin >> input;
    while(input != 1 && input != 2){
        cout << "That was an invalid choice. Please respond with 1 or 2.\n";
        cin >> input;
    }
    AIvsAI = (input == 2);
    
    // User inputs time limit
    cout << "Please enter the number of seconds (integer value) that the AI has to move\n";
    cin >> input;
    while(floor(input) <= 1){
        cout << "Please enter an integer value greater than 1\n";
        cin >> input;
    }
    
    // Decides starting player
    int startingPlayer;
    if(player1Starts(!AIvsAI)){
        startingPlayer = 1;
    } else {
        startingPlayer = 2;
    }
    cout << "\nThe starting player is player " << startingPlayer << ".\n\n";
    
    printBoard();
    // Checks if the board can be played
    if(gameOver() > 0){
        cout << "You have loaded a completed game.\n";
        return;
    }
    
    // Differs here if AI vs AI
    if(AIvsAI){
        playAIvsAI(startingPlayer, input);
        return;
    }
    
    
    if(startingPlayer == 1){
        implementMove(getMoveChoice(), 1);
        printBoard();
    }
    while(true){
        // Player 2 turn
        if(checkEndGame()){
            return;
        };
        cout << "I am thinking...\n";
        implementMove(iterativeDeepening(input) , 2);
        printBoard();
        
        // Player 1 turn
        if(checkEndGame()){
            return;
        };
        implementMove(getMoveChoice(), 1);
        printBoard();
    }
    
}

int main(int argc, const char * argv[]) {
    srand(time(nullptr));
    playGame();
    return 0;
}
