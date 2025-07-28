// tictactoc.cpp
// Phuong Anh Vu, CISP 360
// 07/27/2025

#include <iostream>
#include <iomanip>
#include <cstdlib> // for rand, srand
#include <ctime>   // Required for time-related functions

using namespace std;

void displayBoard(char board[3][3]);
int startMainMenu();
char randomStart();
void startGame(char board[3][3]);
bool checkWinner(char board[3][3], char playerSymbol);
bool isValidValue(int cell, char board[3][3]);
void setMoveforPlayer_AI(char board[3][3], char playerSymbol);
void displayAfterGame();

int main()
{
    // Specification A3 - Array Data Type
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}}; // Initialize the game board

    int choice = startMainMenu();
    switch (choice)
    {
    case 1:
        cout << "Tic Tac Toe is a simple game played on a 3x3 grid." << endl;
        cout << "Two players take turns marking a square with their symbol (X or O)." << endl;
        cout << "The first player to get three of their symbols in a row (horizontally, vertically, or diagonally) wins." << endl;
        cout << "If all squares are filled and no player has three in a row, the game is a draw." << endl;
        cout << "In this game, you will play against the computer." << endl;
        cout << endl;
        break;
    case 2:
        srand(time(0));   // prevent the same random sequence on each run
        startGame(board);
        break;
    case 3:
        cout << "Exiting the game. Goodbye!" << endl;
        exit(0); // Exit the program
    }
    return 0;
}

// Specification B1 - Start Menu
int startMainMenu()
{
    int choice;
    cout << "This is a simple Tic Tac Toe game." << endl;
    cout << "==================================" << endl;
    // Specification B2 - Valid Menu Choices
    do {
        cout << "1 - Explain the game" << endl;
        cout << "2 - Play a new game" << endl;
        cout << "3 - Exit" << endl;
        cout << "Please select an option (1-3): ";
        cin >> choice;
    } while (choice < 1 || choice > 3); // Ensure valid input
    return choice; // Return the user's choice
}

// Specification C2 - Simple Display
void displayBoard(char board[3][3])
{
    cout << "Current Tic Tac Toe Board:" << endl;
    int number = 1;
    for (int i = 0; i < 3; i++) {
        cout << "---";
        for (int j = 0; j < 3; j++) {
            cout << "----";
        }
        cout << endl;
        cout << "|";
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                cout << " " << number << " "; // Display the number if the cell is empty
            else
                cout << " " << board[i][j] << " "; // Display the cell's symbol
            cout << "| ";
            number++;
        }
        cout << endl;
    }
    cout << "---------------" << endl;
};

// Specification C1 - Random Start
char randomStart()
{
    int random_binary = rand() % 2;
    return (random_binary == 0) ? 'X' : 'O'; // Randomly return 'X' or 'O'
}

void startGame(char board[3][3])
{
    cout << "Starting a new game..." << endl;
    cout << "X will be your symbol and O will be the computer's symbol." << endl;
    cout << "You will be prompted to enter a number corresponding to the cell you want to mark." << endl;
    char symbol = randomStart();
    if (symbol == 'X') {
        displayBoard(board);
        cout << "You go first!" << endl;
    }
    else {
        cout << "The computer goes first!" << endl;
    }

    bool isWinner = false;
    int totalMove = 0;
    do {
        totalMove++;
        if (symbol == 'X') {
            setMoveforPlayer_AI(board, symbol);
            // after atleast 5 moves then check for winner
            isWinner = (totalMove >= 5) ? checkWinner(board, symbol) : false; // Check for winner after 5 moves
            if(isWinner) {
                displayBoard(board); // Display the board if there's a winner
                break; // Exit the loop if there's a winner
            }
            symbol = 'O'; // Switch to computer's turn
        }
        else {
            cout << "Computer's turn..." << endl;
            setMoveforPlayer_AI(board, symbol); // Computer's turn
            displayBoard(board); // Display the updated board after the computer's move
            // after atleast 5 moves then check for winner
            isWinner = (totalMove >= 5) ? checkWinner(board, symbol) : false; // Check for winner after 5 moves
            symbol = 'X'; // Switch back to player's turn
        }
    } while (!isWinner && totalMove < 9); // Continue until there's no winner or draw

    if (isWinner || totalMove == 9) {
        if (totalMove == 9 && !isWinner) {
            cout << "It's a draw! There is no winner!" << endl; // If all cells are filled and no winner
        }
        displayAfterGame();
    }
}

void displayAfterGame()
{
    // Specification A1 - Main Game Loop
    char choice;
    do {
        // Specification A2 - Simple Prompt
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "Starting a new game... Ready to have more fun!" << endl;
            // Create a new board
            char board[3][3] = {
                {' ', ' ', ' '},
                {' ', ' ', ' '},
                {' ', ' ', ' '}};
    
            startGame(board);  // Start a new game
        }
        else { //exit the game if the user chooses other than 'y' or 'Y'
            cout << "Thank you for playing! Goodbye!" << endl;
            exit(0); // Exit the program
        }
    } while (choice == 'y' || choice == 'Y'); 
}

bool checkWinner(char board[3][3], char playerSymbol)
{
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol) || // Rows
            (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i] == playerSymbol))   // Columns
        {
            cout << (playerSymbol == 'O' ? " Computer is the winner!" : " You are the winner!") << endl;
            return true;
        }
    }
    if ((board[0][0] == playerSymbol && board[1][1] == playerSymbol && board[2][2] == playerSymbol) ||
        (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0] == playerSymbol)) { // Diagonal (left to right and right to left)
        cout << (playerSymbol == 'O' ? " Computer is the winner!" : " You are the winner!") << endl;
        return true;
    }
    return false;
}

bool isValidValue(int cell, char board[3][3])
{
    if (cell < 1 || cell > 9) {
        cout << "Invalid cell number! Please choose a number between 1 and 9." << endl;
        return false; // Invalid cell number
    }
    return board[(cell - 1) / 3][(cell - 1) % 3] == ' '; // Check if the cell is empty
}

void setMoveforPlayer_AI(char board[3][3], char playerSymbol)
{
    int cell;
    bool isValidMove = false; 
    // Specification C3 - AI
    if (playerSymbol == 'O') {
        do
        {
            cell = rand() % 9 + 1; // Randomly choose a cell from 1 to 9
            isValidMove = isValidValue(cell, board);
        } while (!isValidMove); // Ensure the cell is empty
    }
    // Player's turn
    else {
        // Specification B3 - Valid Move
        do {
            cout << "Please choose a cell (1-9): ";
            cin >> cell; // Get the player's choice
            isValidMove = isValidValue(cell, board);
            if (!isValidMove) {
                cout << "Cell already taken! Please choose another cell." << endl; // Prompt for a valid move
            }
        } while (!isValidMove); 
    }
    board[(cell - 1) / 3][(cell - 1) % 3] = playerSymbol; // Place the player's symbol in the chosen cell
}
