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
    cout << "\n |-1-|-2-|-3-|-4-|-5-|-6-|-7-|\n\n";
    for(int i = 0, j= 0; j < 6; i++){
        cout << " | " << currentBoard[j][i];
        
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
        
        if(i == 7){
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

// Implements game move
void implementMove(){
    
}

void playAIvsAI(int startingPlayer, int seconds){
    
}

// Gets user's move choice
int getMove(){
    int moveNum;
    cout << "Which column would you like to place your piece in?\n";
    cin >> moveNum;
    while(moveNum < 1 || moveNum > 7 || currentBoard[0][moveNum-1] != 0){
        cout << "The move you entered is invalid.\nWhich column would you like to place your piece in?\n";
        cin >> moveNum;
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
    cout << "The starting player is player " << startingPlayer << ".\n\n";
    
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
        
    }
    while(true){
        
    }
    
}

int main(int argc, const char * argv[]) {
    printBoard();
    return 0;
}
