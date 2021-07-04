#include<bits/stdc++.h> 
using namespace std; 

#define Player1 1 
#define Player2 2 
#define Inf 1000000

int user; // to dertermine who is human (i.e Player1 or Player2)

#define WIDTH 3 // Width of the board 

#define Player1_Move 'X' //Player1 will play X
#define Player2_Move 'O' //Player2 will play Y


// To display the board
void displayBoard(char board[][WIDTH]) 
{ 
	printf("\n\n"); 

	printf("\t\t\t -----------\n"); 
	printf("\t\t\t| %c | %c | %c |\n", board[0][0], board[0][1], board[0][2]); 
	printf("\t\t\t|---|---|---|\n"); 
	printf("\t\t\t| %c | %c | %c |\n", board[1][0], board[1][1], board[1][2]); 
	printf("\t\t\t|---|---|---|\n"); 
	printf("\t\t\t| %c | %c | %c |\n", board[2][0], board[2][1], board[2][2]); 
  printf("\t\t\t -----------\n"); 
  printf("\n----------------------------------------------------------------------------------------\n");

	return; 
} 

// A function to show the instructions 
void showInstructions() 
{ 

  printf("\t\t\t INSTRUCTIONS FOR THIS GAME");
	printf("\n----------------------------------------------------------------------------------------\n"); 
	printf("Choose a cell numbered from 1 to 9 as below"
			" and play\n\n"); 
	
	printf("\t\t\t -----------\n"); 
	printf("\t\t\t| 1 | 2 | 3 |\n"); 
	printf("\t\t\t|---|---|---|\n"); 
	printf("\t\t\t| 4 | 5 | 6 |\n"); 
	printf("\t\t\t|---|---|---|\n"); 
	printf("\t\t\t| 7 | 8 | 9 |\n"); 
  	printf("\t\t\t -----------\n"); 	
	printf("\n----------------------------------------------------------------------------------------\n");

	return; 
} 


void initialise(char board[][WIDTH], int moves[]) 
{ 
	// Initially the board is empty 
	for (int i=0; i<WIDTH; i++) 
	{ 
		for (int j=0; j<WIDTH; j++) 
      		board[i][j] = ' '; 
	} 

} 

// A function to declare the winner of the game 
void declareWinner(int currPlayer) 
{ 
	if (currPlayer == Player1) 
		printf("\n\n!!!Congratulations Player1, You are the winner!!!\n\n"); 
	else
		printf("\n\n!!!Congratulations Player2, You are the winner!!!\n\n");
	return; 
} 

// returns 1 if Player1 filled a row
// returns 2 if Player2 filled a row
// returns 0 if no one filled a row
int rowStatus(char board[][WIDTH]) 
{ 
	for (int i=0; i<WIDTH; i++) 
	{ 
		if (board[i][0] == board[i][1] && 
			board[i][1] == board[i][2] && 
			board[i][0] != ' ') 
			{
				if(board[i][0] == Player1_Move) return 1;
				else if(board[i][0] == Player2_Move) return -1;
			}
	} 
	return 0; 
} 

// returns 1 if Player1 filled a col
// returns 2 if Player2 filled a col
// returns 0 if no one filled a col
int colStatus(char board[][WIDTH]) 
{ 
	for (int i=0; i<WIDTH; i++) 
	{ 
		if (board[0][i] == board[1][i] && 
			board[1][i] == board[2][i] && 
			board[0][i] != ' ') 
			{
				if(board[0][i] == Player1_Move) return 1;
				else if(board[0][i] == Player2_Move) return -1;
			}
	} 
	return 0; 
} 

// returns 1 if Player1 filled a diag
// returns 2 if Player2 filled a diag
// returns 0 if no one filled a diag
int diagStatus(char board[][WIDTH]) 
{ 
	if (board[0][0] == board[1][1] && 
		board[1][1] == board[2][2] && 
		board[0][0] != ' ') 
		{
			if(board[0][0] == Player1_Move) return 1;
			else if(board[0][0] == Player2_Move) return -1;
		} 
		
	if (board[0][2] == board[1][1] && 
		board[1][1] == board[2][0] && 
		board[0][2] != ' ') 
		{
			if(board[0][2] == Player1_Move) return 1;
			else if(board[0][2] == Player2_Move) return -1;
		} 

	return 0; 
} 


// to check when the is finished
bool gameOver(char board[][WIDTH]) 
{ 
	return(rowStatus(board) || colStatus(board) || diagStatus(board) ); 
}

// to check if the cell is valid or not
bool validCell(int cell, char board[][WIDTH])
{
	int cell_x = cell / WIDTH;
	int cell_y = cell % WIDTH;

	if(cell < 0 || cell > 8 || board[cell_x][cell_y] != ' ') return false;

	return true;
}

// to find which player is likely to win
int boardScore(char board[][WIDTH])
{
	int rowResult = rowStatus(board);
	int colResult = colStatus(board);
	int diagResult = diagStatus(board);

	if(rowResult == 1 || colResult == 1 || diagResult == 1) return 1;
	else if(rowResult == -1 || colResult == -1 || diagResult == -1) return -1;

	return 0;
}

// find no of blank cells in a tic tac toe
bool movesLeft(char board[][WIDTH])
{
	
	for (int i=0; i<WIDTH; i++) 
	{ 
		for(int j=0; j<WIDTH; j++)
		{
			if(board[i][j] == ' ') 
				return true;
		}
	} 

	return false;

}

//Utility function for the bestMove() function
int minimax(char board[][WIDTH], int depth, bool isMaximizing)  
{
	int score = boardScore(board);

	//base cases
	if(score == 1) return score;
	if(score == -1) return score;
	if(movesLeft(board) == false) return 0;

	if(isMaximizing)
	{
		int bestScore = -Inf;

		for(int i=0; i<WIDTH; i++)
		{
			for(int j=0; j<WIDTH; j++)
			{
				if(board[i][j] == ' ')
				{
					board[i][j] = Player1_Move;
					int score = minimax(board, depth+1, !isMaximizing);
					board[i][j] = ' ';
					bestScore = max(score, bestScore);
				}
			}
		}

		return bestScore;
	}

	else
	{
		int bestScore = Inf;

		for(int i=0; i<WIDTH; i++)
		{
			for(int j=0; j<WIDTH; j++)
			{
				if(board[i][j] == ' ')
				{
					board[i][j] = Player2_Move;
					int score = minimax(board, depth+1, !isMaximizing);
					board[i][j] = ' ';
					bestScore = min(score, bestScore);
				}
			}
		}

		return bestScore;
	}
	
}

// function to find the best possible move
int bestMove(char board[][WIDTH])
{
	int bestCell = -1;

	if(user != Player1)
	{
		int bestScore = -Inf;
		for(int i=0; i<WIDTH; i++)
		{
			for(int j=0; j<WIDTH; j++)
			{
				if(board[i][j] == ' ')
				{
					board[i][j] = Player1_Move;
					int score = minimax(board, 0, false); 
					board[i][j] = ' ';
					if(score > bestScore)
					{
						bestScore = score;
						bestCell = WIDTH*i + j;
					}
				}
			}
		}
	}

	else if(user != Player2)
	{
		int bestScore = Inf;
		for(int i=0; i<WIDTH; i++)
		{
			for(int j=0; j<WIDTH; j++)
			{
				if(board[i][j] == ' ')
				{
					board[i][j] = Player2_Move;
					int score = minimax(board, 0, true);  
					board[i][j] = ' ';
					if(score < bestScore)
					{
						bestScore = score;
						bestCell = WIDTH*i + j;
					}
				}
			}
		}
		
	}
	
	return bestCell; //return the best cell to play for the computer
}

// A function to play Tic-Tac-Toe 
void playTicTacToe(int currPlayer) 
{ 
	char board[WIDTH][WIDTH]; 
	
	int moves[WIDTH*WIDTH]; 
	
	initialise(board, moves); // intialize the board
	
	showInstructions(); // display instructions for the game
	
	int moveIndex = 0; 
	
	while (gameOver(board) == false && moveIndex != WIDTH*WIDTH) 
	{ 
		if (currPlayer == Player1) 
		{ 
			if(user == Player1)
			{
				int user_cell = -1, user_x, user_y;;
				while(!validCell(user_cell-1, board))  //validity of the cell
				{
					cout<<"Which cell do you want to place X?\n";
          			cout<<"Enter your answer here : ";
					cin>>user_cell;
				}

				user_cell -= 1;
				user_x = user_cell / WIDTH;
				user_y = user_cell % WIDTH;

				board[user_x][user_y] = Player1_Move;
				printf("Player1 has put a %c in cell %d\n", Player1_Move, user_cell+1);
			}
			else
			{
				int random_cell = -1, random_x, random_y;
				while(!validCell(random_cell, board))
					random_cell = bestMove(board);
				random_x = random_cell / WIDTH;
				random_y = random_cell % WIDTH; 
				board[random_x][random_y] = Player1_Move;
				printf("Player1 has put a %c in cell %d\n", Player1_Move, random_cell+1); 
				displayBoard(board); 
			}

			currPlayer = Player2;			
		} 
		
		else if (currPlayer == Player2) 
		{ 
			if(user == Player2)
			{
				int user_cell = -1, user_x, user_y;;
				while(!validCell(user_cell-1, board))  //validity of the cell
				{
					cout<<"Which cell do you want to place O?\n";
          			cout<<"Enter your answer here : ";
					cin>>user_cell;
				}

				user_cell -= 1;
				user_x = user_cell / WIDTH;
				user_y = user_cell % WIDTH;

				board[user_x][user_y] = Player2_Move;
				printf("Player2 has put a %c in cell %d\n", Player2_Move, user_cell+1);
			}
			else
			{
				int random_cell = -1, random_x, random_y;
				while(!validCell(random_cell, board))
					random_cell = bestMove(board);
				random_x = random_cell / WIDTH;
				random_y = random_cell % WIDTH; 
				board[random_x][random_y] = Player2_Move;
				printf("Player2 has put a %c in cell %d\n", Player2_Move, random_cell+1); 
				displayBoard(board); 
			}

			currPlayer = Player1;

		} 
		moveIndex++;
	} 

	// If the game has drawn 
	if (gameOver(board) == false && 
			moveIndex == WIDTH * WIDTH) 
		printf("\n\n---------------------------------IT IS A DRAW-------------------------------------\n\n"); 
	else
	{ 
		// Toggling the user to declare the actual 
		// winner 
		if (currPlayer == Player1) 
			currPlayer = Player2; 
		else if (currPlayer == Player2) 
			currPlayer = Player1; 
		
		// Declare the winner 
		displayBoard(board);
		declareWinner(currPlayer); 
	} 
	return; 
} 

// Driver program 
int main() 
{ 
	char playAgain = 'y';

	while(playAgain == 'y')
	{
		printf("\n----------------------------------------------------------------------------------------\n");
		printf("\n\nPlease choose your Player?");
		printf("\n(i)  Enter 1 for Player1");
		printf("\n(ii) Enter 2 for Player2");
		printf("\nEnter your answer here: ");
		cin>>user;
		playTicTacToe(Player1); 

		printf("Do you what to play again?");
		printf("\n(i)  Enter y for YES");
		printf("\n(ii) Enter n for NO");
		printf("\nEnter your answer here: ");
		cin>>playAgain;
	}
	printf("\n\n-----------------------------------------GAME OVER-------------------------------------------\n");
	return 0;
} 
