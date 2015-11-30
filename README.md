<h1>About</h1>
* tic-tac-toe for 2 players.
* Win by capturing the whole row, or the whole column.
* Doesn't work diagonally (yet).


<h3>Require:</h3>
* gcc (tested on version 5.2.1)


<h3>Compile</h3>
````
$gcc -Wall -o tictactoe tictactoe.c
```

<h3>Run</h3>
```
$./tictactoe
```

<h3>Instructions</h3>
 1. Enter the size of the board.			
 2. Enter the position that you wish to place[(row) (column)].
 3. Switch player.
 4. Repeat step 2 - 3.
 5. Win/Draw

<h3>Example</h3>
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
