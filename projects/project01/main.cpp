#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip> // std::setw
#include "ValidationPro.h"
#include <cmath> 

// Enumerations
enum class GameState { Playing, Ended };
enum class CellState { Mine = -1, Blank = 0, Revealed = 1 };
enum class ResultState { Win, Lose, Ongoing };
enum class Difficulty { Easy = 1, Normal, Hard, Custom };
enum class Player { One = 1, Two };
enum class Size { Small = 1, Medium, Big, Custom };

struct GameSettings;
GameSettings getGameSettings();

// Game setup structure
struct GameSettings {
    int rows;
    int cols;
    int mines;
};

void gameIntro() {
    std::cout << "Welcome to Minesweeper!\n";
    std::cout << "Rules:\n";
    std::cout << "1. Players alternate turns revealing cells\n";
    std::cout << "2. Surviving a turn (no mine hit): +1 point\n";
    std::cout << "3. Hitting a mine: -2 points for you, +2 for opponent\n";
    std::cout << "4. Winning the game: +3 bonus points\n";
}

void finalResults(int& player1Total, int& player2Total) {
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

// Function to create the Minesweeper board
std::vector<std::vector<int>> makeBoard(int rows, int cols, int mines) {
    std::vector<std::vector<int>> board(rows, std::vector<int>(cols, static_cast<int>(CellState::Blank)));
    std::srand(std::time(0));

    int minesPlaced = 0;
    while (minesPlaced < mines) {
        int row = std::rand() % rows;
        int col = std::rand() % cols;
        if (board[row][col] != static_cast<int>(CellState::Mine)) {
            board[row][col] = static_cast<int>(CellState::Mine);
            minesPlaced++;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == static_cast<int>(CellState::Mine)) continue;

            int mineCount = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    int newRow = i + x;
                    int newCol = j + y;
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && 
                        board[newRow][newCol] == static_cast<int>(CellState::Mine)) {
                        mineCount++;
                    }
                }
            }
            board[i][j] = mineCount;
        }
    }
    return board;
}

GameSettings getGameSettings() {
    GameSettings settings;
    
    // Get board size
    std::cout << "Select board size (1-4):\n";
    std::cout << "1. Small (5x5)\n";
    std::cout << "2. Medium (8x8)\n";
    std::cout << "3. Big (10x10)\n";
    std::cout << "4. Custom\n";
    Size sizeChoice = static_cast<Size>(getValidNumber<int>(1, 4));


    if (sizeChoice == Size::Small) {
        settings.rows = 5;
        settings.cols = 5;
    } else if (sizeChoice == Size::Medium) {
        settings.rows = 8;
        settings.cols = 8;
    } else if (sizeChoice == Size::Big) {
        settings.rows = 10;
        settings.cols = 10;
    } else if (sizeChoice == Size::Custom) {
        std::cout << "Enter number of rows (min 5): ";
        settings.rows = getValidNumber<int>(5);
        std::cout << "Enter number of columns (min 5): ";
        settings.cols = getValidNumber<int>(5);
    }


    // Get difficulty level
    std::cout << "Select difficulty (1-4):\n";
    std::cout << "1. Easy (10% mines)\n";
    std::cout << "2. Normal (20% mines)\n";
    std::cout << "3. Hard (30% mines)\n";
    std::cout << "4. Custom\n";
    Difficulty difficultyChoice = static_cast<Difficulty>(getValidNumber<int>(1, 4));

    if (difficultyChoice == Difficulty::Easy) {
        settings.mines = static_cast<int>(std::round(settings.rows * settings.cols * 0.1));
    } else if (difficultyChoice == Difficulty::Normal) {
        settings.mines = static_cast<int>(std::round(settings.rows * settings.cols * 0.2));
    } else if (difficultyChoice == Difficulty::Hard) {
        settings.mines = static_cast<int>(std::round(settings.rows * settings.cols * 0.3));
    } else if (difficultyChoice == Difficulty::Custom) {
        int max_mines = settings.rows * settings.cols - 1;
        settings.mines = getValidNumber<int>(1,max_mines);
    }
    return settings;
}


void revealCell(int row, int col, const std::vector<std::vector<int>>& board,
               std::vector<std::vector<bool>>& visibilityBoard) {
    int rows = board.size();
    int cols = board[0].size();

    if (row < 0 || row >= rows || col < 0 || col >= cols || visibilityBoard[row][col]) {
        return;
    }

    visibilityBoard[row][col] = true;

    if (board[row][col] == static_cast<int>(CellState::Blank)) {
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                revealCell(row + x, col + y, board, visibilityBoard);
            }
        }
    }
}

// Function to check if the player has won
ResultState checkWin(const std::vector<std::vector<int>>& board, const std::vector<std::vector<bool>>& visibilityBoard) {
    int rows = board.size();
    int cols = board[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] != static_cast<int>(CellState::Mine) && !visibilityBoard[i][j]) {
                return ResultState::Ongoing;
            }
        }
    }
    return ResultState::Win;
}

void printBoard(const std::vector<std::vector<int>>& board, const std::vector<std::vector<bool>>& visibilityBoard) {
    int rows = board.size();
    int cols = board[0].size();

    int maxRowDigits = std::to_string(rows).length();

    std::cout << std::setw(maxRowDigits + 2) << " ";
    std::cout << " ";
    for (int j = 0; j < cols; j++) {
        std::cout << std::setw(2) << j + 1 << " ";
    }
    std::cout << "\n";

    std::cout << std::setw(maxRowDigits + 2) << " " << "+";
    for (int j = 0; j < cols; j++) std::cout << "---";
    std::cout << "+\n";

    for (int i = 0; i < rows; i++) {
        std::cout << std::setw(maxRowDigits) << i + 1 << " |";
    for (int j = 0; j < cols; j++) {
        if (visibilityBoard[i][j]) {
            if (board[i][j] == static_cast<int>(CellState::Mine)) {
                std::cout << std::setw(3) << "M"; 
            } else {
                std::cout << std::setw(3) << board[i][j];
            }
        } else {
            std::cout << std::setw(3) << ".";
        }
    }
        std::cout << " |\n";
    }

    std::cout << std::setw(maxRowDigits + 2) << " " << "+";
    for (int j = 0; j < cols; j++) std::cout << "---";
    std::cout << "+\n";
}

void revealAllMines(const std::vector<std::vector<int>>& board, std::vector<std::vector<bool>>& visibilityBoard) {
    int rows = board.size();
    int cols = board[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == static_cast<int>(CellState::Mine)) {
                visibilityBoard[i][j] = true;
            }
        }
    }
}

void play(int rows, int cols, int mines, int& player1Total, int& player2Total) {
    auto board = makeBoard(rows, cols, mines);
    std::vector<std::vector<bool>> visibility(rows, std::vector<bool>(cols, false));
    GameState gameState = GameState::Playing;
    Player currentPlayer = Player::One;
    int currentPlayer1Score = 0, currentPlayer2Score = 0;

    while (gameState == GameState::Playing) {
        std::cout << "______________________________________________________\n";
        std::cout << "Player " << static_cast<int>(currentPlayer) << "'s turn (Current Points: "
                 << (currentPlayer == Player::One ? currentPlayer1Score : currentPlayer2Score) << "):\n";
        printBoard(board, visibility);

        int row{-1};
        int col{-1};
        bool validInput{false};
        while(!validInput){  // trying to make it more user sensable
            validInput = true;  // had sacrifice an extra line to make it work this way

            std::cout << "Enter row (1-" << rows << "): ";
            row = getValidNumber<int>(1, rows) - 1;
            std::cout << "Enter column (1-" << cols << "): ";
            col = getValidNumber<int>(1, cols) - 1;

            if (visibility[row][col]) {   // if hte given row and col is already in visiibility board - revealed
                std::cout << "This cell is already revealed! Choose another.\n";
                validInput = false;
            }
        }

        if (board[row][col] == static_cast<int>(CellState::Mine)) {
            std::cout << "BOOM! Player " << static_cast<int>(currentPlayer) << " hit a mine! (-2 points)\n";
            std::cout << "Player " << (currentPlayer == Player::One ? 2 : 1) << " gains +2 points!\n";

            if (currentPlayer == Player::One) {
                currentPlayer1Score -= 2;
                currentPlayer2Score += 2;
            } else {
                currentPlayer2Score -= 2;
                currentPlayer1Score += 2;
            }

            revealAllMines(board, visibility);
            gameState = GameState::Ended;
        } else {
            revealCell(row, col, board, visibility);

            if (currentPlayer == Player::One) {
                currentPlayer1Score += 1;
                std::cout << "Player 1 survived! (+1 point)\n";
            } else {
                currentPlayer2Score += 1;
                std::cout << "Player 2 survived! (+1 point)\n";
            }

            if (checkWin(board, visibility) == ResultState::Win) {
                std::cout << "Congratulations! Player " << static_cast<int>(currentPlayer) << " won! (+3 points)\n";
                if (currentPlayer == Player::One) {
                    currentPlayer1Score += 3;
                } else {
                    currentPlayer2Score += 3;
                }
                gameState = GameState::Ended;
            } else {
                currentPlayer = (currentPlayer == Player::One) ? Player::Two : Player::One;
            }
        }
    }

    player1Total += currentPlayer1Score;
    player2Total += currentPlayer2Score;

    std::cout << "\nRound Results:\n";
    std::cout << "Player 1: " << currentPlayer1Score << " points\n";
    std::cout << "Player 2: " << currentPlayer2Score << " points\n";
    printBoard(board, visibility);
}
int main() {
    int player1Total = 0;
    int player2Total = 0;
    bool playing = true;

    gameIntro();

    while (playing) {
        GameSettings settings = getGameSettings();
        play(settings.rows, settings.cols, settings.mines, player1Total, player2Total);

        std::cout << "Total Scores:\n";
        std::cout << "Player 1: " << player1Total << "\n";
        std::cout << "Player 2: " << player2Total << "\n";

        std::cout << "Play again? (1 for Yes, 0 for No): ";
        playing = getValidNumber<int>(0, 1);
    }

    finalResults(player1Total, player2Total);
    return 0;
}

