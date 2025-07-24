// tictactoc.cpp
// Phuong Anh Vu, CISP 360
// 07/27/2025

#include <iostream>
#include <iomanip>
#include <cstdlib> // for rand, srand
#include <ctime> // Required for time-related functions

using namespace std;

void displayBoard(char board[3][3]);
int startMainMenu();
char randomStart();
void startGame(char board[3][3]);
bool checkWinner(char board[3][3], char playerSymbol);
bool checkDraw(char board[3][3]);

int main() {
    // Specification A3 - Array Data Type
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    }; // Initialize the game board
    
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
            srand(time(0)); // prevent the same random sequence on each run
            startGame(board); // Start a new game
            break;
        case 3:
            cout << "Exiting the game. Goodbye!" << endl;
            exit(0); // Exit the program

    }
    return 0;
}

// Specification B1 - Start Menu
int startMainMenu() {
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
void displayBoard(char board[3][3]) {
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
            if (board[i][j] == ' ') {
                cout << " " << number << " "; // Display the number if the cell is empty
            } else {
                cout << " " << board[i][j] << " ";
            }
            cout << "| ";
            number++;
        }
        cout << endl;
    }
    cout << "---------------" << endl; 
};

void playerChooseCell(char board[3][3], char playerSymbol) {
    int cell;
    cout << "Please choose a cell (1-9): ";
    cin >> cell; // Get the player's choice

    // while loop for invalid input numbers
    while (cell < 1 || cell > 9) {
        cout << "Invalid choice! Please choose an empty cell: ";
        cin >> cell; // Get the player's choice again
    }

    // Specification B3 - Valid Move
    if (cell <= 9 && cell >= 7) {
        if (board[2][cell - 7] != ' ') {
            cout << "Cell already taken! Please choose another cell." << endl;
            playerChooseCell(board, playerSymbol); // Recursive call to choose again
        } else {
            board[2][cell - 7] = playerSymbol; // Place the player's symbol in the chosen cell
        }
    } else if (cell <= 6 && cell >= 4) {
        if (board[1][cell - 4] != ' ') {
            cout << "Cell already taken! Please choose another cell." << endl;
            playerChooseCell(board, playerSymbol); // Recursive call to choose again
        } else {
            board[1][cell - 4] = playerSymbol; // Place the player's symbol in the chosen cell
        }
    } else if (cell <= 3 && cell >= 1) {
        if (board[0][cell - 1] != ' ') {
            cout << "Cell already taken! Please choose another cell." << endl;
            playerChooseCell(board, playerSymbol); // Recursive call to choose again
        } else {
            board[0][cell - 1] = playerSymbol; // Place the player's symbol in the chosen cell
        }
    }
}

// Specification C1 - Random Start
char randomStart() {
    int random_binary = std::rand() % 2;
    return (random_binary == 0) ? 'X' : 'O'; // Randomly return 'X' or 'O'
}

void startGame(char board[3][3]) {
    cout << "Starting a new game..." << endl;
    cout << "X will be your symbol and O will be the computer's symbol." << endl;
    cout << "You will be prompted to enter a number corresponding to the cell you want to mark." << endl;
    char symbol = randomStart();
    if (symbol == 'X') {
        displayBoard(board);
        cout << "You go first!" << endl;
    } else {
        cout << "The computer goes first!" << endl;
    }

    bool isWinner = false;
    bool isDraw = false;
    
    do {
        if (symbol == 'X') {
            playerChooseCell(board, symbol); // Player's turn to choose a cell
            symbol = 'O'; // Switch to computer's turn
        } else {
            // Specification C3 - AI
            cout << "Computer's turn..." << endl;
            int cell;
            do {
                cell = rand() % 9 + 1; // Randomly choose a cell from 1 to 9
            } while (board[(cell - 1) / 3][(cell - 1) % 3] != ' '); // Ensure the cell is empty
            board[(cell - 1) / 3][(cell - 1) % 3] = symbol; // Place the computer's symbol in the chosen cell
            displayBoard(board); // Display the updated board after the computer's move
            symbol = 'X'; // Switch back to player's turn
        }
    
        // check winner or draw after each turn
        isWinner = checkWinner(board, symbol); 
        isDraw = checkDraw(board); 
    } while (!isWinner && !isDraw); // Continue until there's no winner or draw

    if (isWinner || isDraw)
    {
        // Specification A1 - Main Game Loop
        char choice;
        // Specification A2 - Simple Prompt
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            // Reset the board for a new game
            char newBoard[3][3] = {
                {' ', ' ', ' '},
                {' ', ' ', ' '},
                {' ', ' ', ' '}};
            startGame(newBoard); // start a new game
        }
        else
        {
            cout << "Thank you for playing! Goodbye!" << endl; // Exit the game
            exit(0);
        }
    }
}

bool checkDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false; // return false if any cell is empty
            }
        }
    }
    cout << "It's a tie! There is no winner!" << endl;
    return true;
}

bool checkWinner(char board[3][3], char playerSymbol) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol) || // Rows
            (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i] == playerSymbol)) { // Columns
            cout << "Player " << playerSymbol << " wins!" << endl;
            return true;
        }
    }
    if ((board[0][0] == playerSymbol && board[1][1] == playerSymbol && board[2][2] == playerSymbol) ||
        (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0] == playerSymbol)) { // Diagonal 
        cout << "Player " << playerSymbol << " wins!" << endl;
        return true;
    }
    return false;
}