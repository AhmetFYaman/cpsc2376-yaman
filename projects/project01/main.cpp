#include <iostream>
#include <cstdlib>
#include <ctime>

#include <cmath>
#include <limits>
#include "minesweeper.h"
#include "minesweeper.cpp"

// Template for input validation
template<typename T>
T getValidNumber(T min, T max = std::numeric_limits<T>::max()) {
    T input;
    while (true) {
        std::cin >> input;
        if (std::cin.fail() || input < min || input > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between " << min;
            if (max != std::numeric_limits<T>::max()) {
                std::cout << " and " << max;
            }
            std::cout << ": ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
    }
}

// Function to get game settings from user
void getGameSettings(int& rows, int& cols, int& mines) {
    // Get board size
    std::cout << "Select board size (1-4):\n";
    std::cout << "1. Small (5x5)\n";
    std::cout << "2. Medium (8x8)\n";
    std::cout << "3. Big (10x10)\n";
    std::cout << "4. Custom\n";
    int sizeChoice = getValidNumber<int>(1, 4);




    if (sizeChoice == SMALL) {
        rows = 5;
        cols = 5;
    } else if (sizeChoice == MEDIUM) {
        rows = 8;
        cols = 8;
    } else if (sizeChoice == BIG) {
        rows = 10;
        cols = 10;
    } else if (sizeChoice == CUSTOMSz) {
        std::cout << "Enter number of rows (min 5): ";
        rows = getValidNumber<int>(5);
        std::cout << "Enter number of columns (min 5): ";
        cols = getValidNumber<int>(5);
    }


    // Get difficulty level
    std::cout << "Select difficulty (1-4):\n";
    std::cout << "1. Easy (10% mines)\n";
    std::cout << "2. Normal (20% mines)\n";
    std::cout << "3. Hard (30% mines)\n";
    std::cout << "4. Custom\n";
    Difficulty difficultyChoice = static_cast<Difficulty>(getValidNumber<int>(1, 4));

    if (difficultyChoice == EASY) {
        mines = static_cast<int>(std::round(rows * cols * 0.1));
    } else if (difficultyChoice == NORMAL) {
        mines = static_cast<int>(std::round(rows * cols * 0.2));
    } else if (difficultyChoice == HARD) {
        mines = static_cast<int>(std::round(rows * cols * 0.3));
    } else if (difficultyChoice == CUSTOMdf) {
        int max_mines = rows * cols - 1;
        mines = getValidNumber<int>(1,max_mines);
    }
    
}

// Display game introduction
void gameIntro() {
    std::cout << "Welcome to Minesweeper!\n";
    std::cout << "Rules:\n";
    std::cout << "1. Players alternate turns revealing cells\n";
    std::cout << "2. Surviving a turn (no mine hit): +1 point\n";
    std::cout << "3. Hitting a mine: -2 points for you, +2 for opponent\n";
    std::cout << "4. Winning the game: +3 bonus points\n";
}

// Display final results
void displayFinalResults(int player1Total, int player2Total) {
    std::cout << "Final Results:\n";
    std::cout << "Player 1: " << player1Total << "\n";
    std::cout << "Player 2: " << player2Total << "\n";
    if (player1Total > player2Total) {
        std::cout << "Player 1 wins!\n";
    } else if (player2Total > player1Total) {
        std::cout << "Player 2 wins!\n";
    } else {
        std::cout << "It's a tie!\n";
    }
    std::cout << "Thanks for playing!\n";
}

// Main game function
void playRound(Minesweeper& game) {
    while (game.status() == ONGOING) {
        std::cout << "______________________________________________________\n";
        std::cout << "Player " << game.getCurrentPlayer() << "'s turn ";
        std::cout << "(Current Points: " << (game.getCurrentPlayer() == 1 ? 
                                           game.getPlayer1Score() : 
                                           game.getPlayer2Score()) << "):\n";
        
        // Display the board
        std::cout << game;
        
        // Get player move
        int row, col;
        bool validInput = false;
        while (!validInput) {
            validInput = true;
            
            std::cout << "Enter row (1-" << game.getRows() << "): ";
            row = getValidNumber<int>(1, game.getRows()) - 1;
            
            std::cout << "Enter column (1-" << game.getCols() << "): ";
            col = getValidNumber<int>(1, game.getCols()) - 1;
            
            if (game.isCellRevealed(row, col)) {
                std::cout << "This cell is already revealed! Choose another.\n";
                validInput = false;
            }
        }
        
        // Process the move
        int prevPlayer = game.getCurrentPlayer();
        int prevScore1 = game.getPlayer1Score();
        int prevScore2 = game.getPlayer2Score();
        
        game.play(row, col);
        
        // Provide feedback based on what happened
        if (game.isCellRevealed(row, col) && game.getCellValue(row, col) == MINE) {
            std::cout << "BOOM! Player " << prevPlayer << " hit a mine! (-2 points)\n";
            std::cout << "Player " << (prevPlayer == 1 ? 2 : 1) << " gains +2 points!\n";
        } else {
            std::cout << "Player " << prevPlayer << " survived! (+1 point)\n";
            
            // Check if the game was won
            if (game.status() == PLAYER_1_WINS || game.status() == PLAYER_2_WINS) {
                std::cout << "Congratulations! Player " << prevPlayer << " won! (+3 points)\n";
            }
        }
    }
    
    // Display round results
    std::cout << "\nRound Results:\n";
    std::cout << "Player 1: " << game.getPlayer1Score() << " points\n";
    std::cout << "Player 2: " << game.getPlayer2Score() << " points\n";
    std::cout << game;
}

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    int player1Total = 0;
    int player2Total = 0;
    bool playing = true;
    
    // Display game introduction
    gameIntro();
    
    // Main game loop
    while (playing) {
        // Get game settings
        int rows, cols, mines;
        getGameSettings(rows, cols, mines);
        
        // Create and play the game
        Minesweeper game(rows, cols, mines);
        playRound(game);
        
        // Update total scores
        player1Total += game.getPlayer1Score();
        player2Total += game.getPlayer2Score();
        
        // Display current totals
        std::cout << "Total Scores:\n";
        std::cout << "Player 1: " << player1Total << "\n";
        std::cout << "Player 2: " << player2Total << "\n";
        
        // Ask to play again
        std::cout << "Play again? (1 for Yes, 0 for No): ";
        playing = getValidNumber<int>(0, 1);
    }
    
    // Display final results
    displayFinalResults(player1Total, player2Total);
    
    return 0;
}