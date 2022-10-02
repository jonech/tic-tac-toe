*About*
* tic-tac-toe for 2 players.
* Win by capturing the whole row, column or diagonal.


*Require:*
* gcc (tested on version 5.2.1)


*Compile*
```
$gcc -Wall -o tictactoe tictactoe.c
```

*Run*
```
$./tictactoe
```

*Instructions*
 1. Enter the size of the board.			
 2. Enter the position that you wish to place[(row) (column)].
 3. Switch player.
 4. Repeat step 2 - 3.
 5. Win/Draw

*Example*
```
Please select the size of board: 3

- - -
- - -
- - -
Player 1's turn, please enter a position [row(0-2) col(0-2)]: 1 2

- - -
- - O
- - -
Player 2's turn, please enter a position [row(0-2) col(0-2)]: 0 0

X - - 
- - O
- - -
Player 1's turn, please enter a position [row(0-2) col(0-2)]:
```
