#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <iostream>

// Plain enumerations as required
enum CellType { BLANK = 0, MINE = -1 };
enum GameStatus { ONGOING, PLAYER_1_WINS, PLAYER_2_WINS, DRAW };
enum Difficulty { EASY = 1, NORMAL, HARD, CUSTOMdf };
enum BoardSize { SMALL = 1, MEDIUM, BIG, CUSTOMSz };

class Minesweeper {
private:
    // Board representation
    std::vector<std::vector<int>> board;
    std::vector<std::vector<bool>> visibility;
    
    // Game state
    int rows;
    int cols;
    int mines;
    int currentPlayer;  // 1 or 2
    int player1Score;
    int player2Score;
    int player1TotalScore;
    int player2TotalScore;
    bool gameOver;
    
    // Helper methods
    void initializeBoard();
    void initializeVisibility();
    void placeMines();
    void calculateAdjacentMines();
    void revealCell(int row, int col);
    void revealAllMines();
    bool isValidMove(int row, int col) const;
    GameStatus checkGameStatus() const;

public:
    // Constructors
    Minesweeper();
    Minesweeper(int rows, int cols, int mines);
    
    // Required methods
    void play(int row, int col);
    GameStatus status() const;
    
    // Game setup and management
    void newGame(int rows, int cols, int mines);
    void resetScores();
    
    // Getters
    int getRows() const;
    int getCols() const;
    int getMines() const;
    int getCurrentPlayer() const;
    int getPlayer1Score() const;
    int getPlayer2Score() const;
    int getPlayer1TotalScore() const;
    int getPlayer2TotalScore() const;
    bool isGameOver() const;
    bool isCellRevealed(int row, int col) const;
    int getCellValue(int row, int col) const;
    
    // Friend operator for printing the board
    friend std::ostream& operator<<(std::ostream& os, const Minesweeper& game);
};

#endif // MINESWEEPER_H