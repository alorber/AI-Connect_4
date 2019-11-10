# AI-Connect_4
###### This is a Connect 4 playing AI.

On startup the game prompts the user with a series of options for the game:
- Load a new game board or import a custom board.
- Play against the AI or have the AI play itself.
- How many seconds the AI has to “think” of a move.
- The starting player.

The AI is implemented by a mini-max search with alpha-beta pruning and iterative deepening.

Whenever the AI moves, iterative deepening is run. Iterative deepening will successively run the alpha-beta search to a greater depth. If there is only one possible move then that move will be chosen without searching. If at any point while searching, the time limit is passed, the current search will be terminated and the move chosen by the previous search will be done. If half the time limit has passed after concluding the search to a certain depth, then the search will conclude, as it is unlikely that a search to the next depth will finish before the time limit. 

The alpha-beta search begins by checking the time limit, terminating if it has passed. If it is at the maximum depth to be searched or the current player is unable to move, it will return the output of the evaluation function. For each possible move, the alpha-beta search will make a copy of the board, implement the move on the board copy, and will run the alpha-beta search on the new board. 
