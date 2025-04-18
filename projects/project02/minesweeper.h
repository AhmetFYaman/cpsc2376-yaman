#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>

// Enumerations
enum class GameState { Playing, Ended };
enum class CellState { Mine = -1, Blank = 0, Revealed = 1 };
enum class ResultState { Win, Lose, Ongoing };
enum class Difficulty { Easy = 1, Normal, Hard, Custom };
enum class Player { One = 1, Two };
enum class Size { Small = 1, Medium, Big, Custom };

// Forward declarations
class GameBoard;
class GameUI;

// Game settings structure
struct GameSettings {
    int rows;
    int cols;
    int mines;
};

// Main game class
class MinesweeperGame {
private:
    GameBoard* board;
    GameUI* ui;
    GameSettings settings;
    GameState state;
    Player currentPlayer;
    int player1Score;
    int player2Score;
    int player1Total;
    int player2Total;
    bool playing;

public:
    MinesweeperGame();
    ~MinesweeperGame();
    
    void initialize();
    void gameIntro();
    void getGameSettings();
    void play();
    void finalResults();
    void reset();
    bool isPlaying() const;
};

// Game board class
class GameBoard {
private:
    std::vector<std::vector<int>> board;
    std::vector<std::vector<bool>> visibility;
    int rows;
    int cols;
    int mines;

public:
    GameBoard(int rows, int cols, int mines);
    void initialize();
    bool revealCell(int row, int col);
    void revealAllMines();
    ResultState checkWin() const;
    
    // Getters
    int getRows() const;
    int getCols() const;
    int getMines() const;
    int getCellValue(int row, int col) const;
    bool isCellVisible(int row, int col) const;
    bool isCellMine(int row, int col) const;
};

// UI class
class GameUI {
public:
    void printBoard(const GameBoard& board) const;
    void printGameIntro() const;
    void printFinalResults(int player1Total, int player2Total) const;
    void printRoundResults(int player1Score, int player2Score) const;
    void printPlayerTurn(Player player, int score) const;
    void printMineHit(Player player) const;
    void printSurvived(Player player) const;
    void printWin(Player player) const;
    
    int getRowInput(int maxRows) const;
    int getColInput(int maxCols) const;
    bool getPlayAgainInput() const;
};

#endif // GAME_H