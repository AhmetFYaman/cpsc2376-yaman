#include "minesweeper.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>

// Constructors
Minesweeper::Minesweeper() : rows(8), cols(8), mines(10) {
    currentPlayer = 1;
    player1Score = 0;
    player2Score = 0;
    player1TotalScore = 0;
    player2TotalScore = 0;
    gameOver = false;
    
    initializeBoard();
    initializeVisibility();
    placeMines();
    calculateAdjacentMines();
}

Minesweeper::Minesweeper(int r, int c, int m) : rows(r), cols(c), mines(m) {
    currentPlayer = 1;
    player1Score = 0;
    player2Score = 0;
    player1TotalScore = 0;
    player2TotalScore = 0;
    gameOver = false;
    
    initializeBoard();
    initializeVisibility();
    placeMines();
    calculateAdjacentMines();
}

// Initialize the game board with blanks
void Minesweeper::initializeBoard() {
    board.resize(rows, std::vector<int>(cols, BLANK));
}

// Initialize visibility board with all cells hidden
void Minesweeper::initializeVisibility() {
    visibility.resize(rows, std::vector<bool>(cols, false));
}

// Place mines randomly on the board
void Minesweeper::placeMines() {
    int minesPlaced = 0;
    while (minesPlaced < mines) {
        int row = std::rand() % rows;
        int col = std::rand() % cols;
        if (board[row][col] != MINE) {
            board[row][col] = MINE;
            minesPlaced++;
        }
    }
}

// Calculate the number of adjacent mines for each cell
void Minesweeper::calculateAdjacentMines() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == MINE) continue;

            int mineCount = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    int newRow = i + x;
                    int newCol = j + y;
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && 
                        board[newRow][newCol] == MINE) {
                        mineCount++;
                    }
                }
            }
            board[i][j] = mineCount;
        }
    }
}

// Check if a move is valid
bool Minesweeper::isValidMove(int row, int col) const {
    // Check if coordinates are within bounds
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    
    // Check if cell is already revealed
    if (visibility[row][col]) {
        return false;
    }
    
    return true;
}

// Play a move
void Minesweeper::play(int row, int col) {
    // If game is over or move is invalid, do nothing
    if (gameOver || !isValidMove(row, col)) {
        return;
    }
    
    // Reveal the selected cell
    if (board[row][col] == MINE) {
        // Hit a mine
        visibility[row][col] = true;
        
        // Update scores
        if (currentPlayer == 1) {
            player1Score -= 2;
            player2Score += 2;
        } else {
            player2Score -= 2;
            player1Score += 2;
        }
        
        // Reveal all mines
        revealAllMines();
        gameOver = true;
    } else {
        // Reveal cell and its surroundings if empty
        revealCell(row, col);
        
        // Update score
        if (currentPlayer == 1) {
            player1Score += 1;
        } else {
            player2Score += 1;
        }
        
        // Check if game is won
        if (checkGameStatus() == PLAYER_1_WINS || checkGameStatus() == PLAYER_2_WINS) {
            if (currentPlayer == 1) {
                player1Score += 3; // Bonus for winning
            } else {
                player2Score += 3; // Bonus for winning
            }
            gameOver = true;
        } else {
            // Switch player
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
    }
}

// Recursive function to reveal cells
void Minesweeper::revealCell(int row, int col) {
    // Check bounds and if already revealed
    if (row < 0 || row >= rows || col < 0 || col >= cols || visibility[row][col]) {
        return;
    }
    
    // Reveal the cell
    visibility[row][col] = true;
    
    // If it's blank (0), reveal neighboring cells
    if (board[row][col] == BLANK) {
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                revealCell(row + x, col + y);
            }
        }
    }
}

// Reveal all mines on the board
void Minesweeper::revealAllMines() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == MINE) {
                visibility[i][j] = true;
            }
        }
    }
}

// Check the current game status
GameStatus Minesweeper::checkGameStatus() const {
    // If game is over, determine winner
    if (gameOver) {
        if (player1Score > player2Score) {
            return PLAYER_1_WINS;
        } else if (player2Score > player1Score) {
            return PLAYER_2_WINS;
        } else {
            return DRAW;
        }
    }
    
    // Check if all non-mine cells are revealed (win condition)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] != MINE && !visibility[i][j]) {
                return ONGOING; // Game still ongoing
            }
        }
    }
    
    // All non-mine cells revealed, current player wins
    return (currentPlayer == 1) ? PLAYER_1_WINS : PLAYER_2_WINS;
}

// Get the current game status
GameStatus Minesweeper::status() const {
    return checkGameStatus();
}

// Start a new game
void Minesweeper::newGame(int r, int c, int m) {
    rows = r;
    cols = c;
    mines = m;
    currentPlayer = 1;
    player1Score = 0;
    player2Score = 0;
    gameOver = false;
    
    board.clear();
    visibility.clear();
    
    initializeBoard();
    initializeVisibility();
    placeMines();
    calculateAdjacentMines();
}

// Reset total scores
void Minesweeper::resetScores() {
    player1TotalScore = 0;
    player2TotalScore = 0;
}

// Getters
int Minesweeper::getRows() const { return rows; }
int Minesweeper::getCols() const { return cols; }
int Minesweeper::getMines() const { return mines; }
int Minesweeper::getCurrentPlayer() const { return currentPlayer; }
int Minesweeper::getPlayer1Score() const { return player1Score; }
int Minesweeper::getPlayer2Score() const { return player2Score; }
int Minesweeper::getPlayer1TotalScore() const { return player1TotalScore; }
int Minesweeper::getPlayer2TotalScore() const { return player2TotalScore; }
bool Minesweeper::isGameOver() const { return gameOver; }
bool Minesweeper::isCellRevealed(int row, int col) const { return visibility[row][col]; }
int Minesweeper::getCellValue(int row, int col) const { return board[row][col]; }

// Output operator to display the game board
std::ostream& operator<<(std::ostream& os, const Minesweeper& game) {
    int maxRowDigits = std::to_string(game.rows).length();

    os << std::setw(maxRowDigits + 2) << " ";
    os << " ";
    for (int j = 0; j < game.cols; j++) {
        os << std::setw(2) << j + 1 << " ";
    }
    os << "\n";

    os << std::setw(maxRowDigits + 2) << " " << "+";
    for (int j = 0; j < game.cols; j++) os << "---";
    os << "+\n";

    for (int i = 0; i < game.rows; i++) {
        os << std::setw(maxRowDigits) << i + 1 << " |";
        for (int j = 0; j < game.cols; j++) {
            if (game.visibility[i][j]) {
                if (game.board[i][j] == MINE) {
                    os << std::setw(3) << "M";
                } else {
                    os << std::setw(3) << game.board[i][j];
                }
            } else {
                os << std::setw(3) << ".";
            }
        }
        os << " |\n";
    }

    os << std::setw(maxRowDigits + 2) << " " << "+";
    for (int j = 0; j < game.cols; j++) os << "---";
    os << "+\n";
    
    return os;
}