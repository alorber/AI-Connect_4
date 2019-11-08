//
//  main.cpp
//  Connect 4 AI
//
//  Created by Andrew Lorber on 11/8/19.
//  Copyright © 2019 Andrew Lorber. All rights reserved.
//

#include <iostream>

using namespace std;

int currentBoard[6][7] = {0};

void printBoard(){
    cout << " |-1-|-2-|-3-|-4-|-5-|-6-|-7-|\n\n";
    for(int i = 0, j= 0; j < 6; i++){
        cout << " | " << currentBoard[j][i];
        
        if(i == 6){
            cout << " |\n |---|---|---|---|---|---|---|\n";
            i = -1;
            j++;
        }
    }
}





int main(int argc, const char * argv[]) {
    printBoard();
    return 0;
}
