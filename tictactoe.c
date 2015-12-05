/*	================================================================
 *		tic-tac-toe(Simplified)
 *		Author: Jone Chee
 *		Email: jone@live.hk
 *		Description: 
 *		- tic-tac-toe for 2 players.
 *		- Win by capturing the whole row, column or diagonal.
 *
 *		Instructions:
 *		1 - Enter the size of the board(nxn).			
 *		2 - Enter the position that you wish to place[(row) (column)].
 *		3 - Switch player.
 *		4 - Repeat step 2 - 3.
 *		5 - Win/Draw
 *	=================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define PLAYER1 1  	// Player 1   
#define PLAYER2 2	// Player 2 
#define EMPTY 0 	// Empty spot on board 

/* structure for input */
typedef struct 
{
	int row;
	int col;
} position_t;


/* function declaration */
void playGame(int **board, int board_size);
void printBoard(int **board, int board_size);
int isBoardFull(int **board, int board_size);
int checkHorizontal(int **board, int player, int row, int board_size);
int checkVertical(int **board, int player, int col, int board_size);
int checkPlayerInput(int **board, int player, position_t post, int board_size);
position_t takePlayerInput(int **board, int player, int board_size);
int checkDiagonal(int **board, int player, int row, int col, int board_size);
int checkDescending(int **board, int player, int board_size);
int checkAscending(int **board, int player, int board_size);


int
main(int argc, char *argv[])
{	
	int i;
	int board_size;
	int **board;

	printf("===================================\n");
	printf("Welcome to verTIC-horizonTAC-TOE!\n");
	printf("===================================\n");
	printf("Please select the size of the board: ");

	/* take input for the size of board, exit program if input not valid */
	if (scanf("%d", &board_size) != 1) {
		printf ("Input Error!\n");
    	return EXIT_FAILURE;
	}

	/* allocate memory to the board array */
	board =  calloc(board_size, sizeof *board);
	for (i=0; i<board_size; i++) {
		board[i] = calloc(board_size, sizeof *board[i]);
	}

	/* start playing tic-tac-toe */
	playGame(board, board_size);

	return 0;
}


/*
 *	Begin game of tic-tac-toe
 */
void
playGame(int **board, int board_size)
{	
	int winner = 0;
	int current_player = PLAYER1;

	position_t input;

	// if no winner, and board is not full yet, proceed playing
	while (winner == 0 && !isBoardFull(board, board_size)) {

		int move = 0;

		// scan the player input, if it is not valid, prompt player and scan again
		while (!move) {

			printBoard(board, board_size);
			input = takePlayerInput(board, current_player, board_size);

			// input is valid, place input on the board, and escape the scan loop
			if (checkPlayerInput(board, current_player, input, board_size) == 1)
			{	
				move = 1;
				board[input.row][input.col] = current_player;
			}
		}

		// check if input is winning move, escape play loop if it is, or else switch player.
		if (checkHorizontal(board, current_player, input.row, board_size) == 1 ||
			checkVertical(board, current_player, input.col, board_size) == 1 ||
			checkDiagonal(board, current_player, input.row, input.col, board_size) == 1) {

			printf("~~~~Player %d wins!~~~~\n", current_player);
			winner = 1; 
		}
		else {
			// switch player
			if (current_player == PLAYER1)
				current_player = PLAYER2;
			else
				current_player = PLAYER1;
		}
	}

	/* print the final status of the board */
	printBoard(board, board_size);
}


/*
 *	Scan the player's input.
 *	Store the input in a structure and return the structure,
 *	so that it can be used for checking validity and winning.
 */
position_t
takePlayerInput(int **board, int player, int board_size)
{	
	position_t input;

	printf("Player %d's turn, please enter a position [row(0-%d) col(0-%d)]: ", 
			player, board_size-1, board_size-1);

	scanf("%d %d", &input.row, &input.col);

	return input;
}


/*
 *	Check if the player input is valid, and also prompt player
 *	Return 0 if not valid. Return 1 if it is valid.
 */
int
checkPlayerInput(int **board, int player, position_t input, int board_size)
{	
	int row = input.row;
	int col = input.col;

	// value out of the bound 
	if (row >= board_size || row < 0 || col >= board_size || col < 0) {
		printf("Input out of bound!\n");
		return 0;
	}

	// the position has already been filled 
	else if (board[row][col] != EMPTY) {
		printf("(%d %d) is not an available spot!\n", row, col);
		return 0;
	}
	else {
		return 1;
	}
		
}


/*
 * Check if the board is full, no more spot to place.
 */
int
isBoardFull(int **board, int board_size)
{
	int i, j;

	for (i=0; i<board_size; i++) {
		for (j=0; j<board_size; j++) {
			if (board[i][j] == EMPTY) {
				return 0;
			}
		}
	}

	printf("-----DRAW!-----");
	return 1;
}


/*
 * Check horizontally if the current move makes the player a winner
 * Return 1 if it is. Return 0 if it isn't.
 */
int
checkHorizontal(int **board, int player, int row, int board_size)
{
	int j = 0;
	int total = 0;

	// increment the board column and compare if it's similar to current player
	while (j<board_size && player == board[row][j]) {
		total += 1;
		j += 1;
	}

	/* if the total is equal to board size
		determines that the player has captured the whole row */
	if (total == board_size) {
		return 1;
	}

	return 0;
}


/*
 * Check vertically if the current move makes the player a winner
 * Return 1 if it is. Return 0 if it isn't.
 */
int 
checkVertical(int **board, int player, int col, int board_size)
{
	int i = 0;
	int total = 0;

	// increment the board row and compare if it's similar to current player
	while (i<board_size && player == board[i][col]){
		total += 1;
		i += 1;
	}

	/* if the total is equal to board size
		determines that the player has captured the whole column */
	if (total == board_size) {
		return 1;
	}

	return 0;
}


/*
*  Does diagonal checking. 3 cases:
*  - the position is in the middle of the board
*  - the position lies in the descending diagonal line (from left to right)
*  - the position lies in the ascending diagonal line (from left to right)
*/
int 
checkDiagonal(int **board, int player, int row, int col, int board_size) 
{

	// middle position, need to check ascending and descending
	// the row is always equal to column
	// also row + column is equal to boardsize - 1
	if (row == col && row+col == board_size-1) {
		if (checkAscending(board, player, board_size) && checkDescending(board, player, board_size)) 
			return 1;
	}

	// descending diagonal line
	// the row is always equal to column in descending diagonal line
	// but row + column is not equal to boardsize - 1
	else if (row == col && row+col != board_size-1) {
		if (checkDescending(board, player, board_size))
			return 1;
	}

	// ascending diagonal line
	// the row is not equal to column in ascending diagonal line
	// but row + column is always equal to boardsize - 1
	else if (row != col && row+col == board_size-1) {
		if (checkAscending(board, player, board_size))
			return 1;
	}

	return 0;
}


// Check descending diagonal line if player capture the whole line
int 
checkDescending(int **board, int player, int board_size) 
{
	int total = 0;
	int n = 0;

	// the row is always equal to column in descending diagonal line
	// so increment both row and column together, starting from top left
	while (n < board_size && player == board[n][n]) {
		total += 1;
		n += 1;
	}
	// total equal to size of board determines winner
	if (total == board_size)
		return 1;
	
	return 0;
}


// Check ascending diagonal line 
int 
checkAscending(int **board, int player, int board_size) 
{
	int total = 0;

	// row+column will always equal to boardsize-1
	// so start from bottom left corner of board
	// then decrement row and increment column for checking
	int i = board_size-1;
	int j = 0;
	while (i >= 0 && j < board_size && player == board[i][j]) {
		total += 1;
		i -= 1;
		j += 1;
	}
	// total equal to size of board determines winner
	if (total == board_size)
		return 1;
	
	return 0;
}


/*
 * Print out the board array.
 */
void 
printBoard(int **board, int board_size)
{
	int i, j;

	char player1 = 'O';
	char player2 = 'X';
	char empty = '-';

	printf("\n");
	
	for (i=0; i<board_size; i++) {
		for (j=0; j<board_size; j++) {

			if (board[i][j] == PLAYER1)
				printf("%c ", player1);
			else if (board[i][j] == PLAYER2)
				printf("%c ", player2);
			else if (board[i][j] == EMPTY)
				printf("%c ", empty);
		}

		printf("\n");
	}
}
