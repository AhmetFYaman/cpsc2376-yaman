#include "minesweeper.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
#include "ValidationPro.h"

// MinesweeperGame implementation
MinesweeperGame::MinesweeperGame() :
    board(nullptr), ui(new GameUI()), state(GameState::Playing),
    currentPlayer(Player::One), player1Score(0), player2Score(0),
    player1Total(0), player2Total(0), playing(true) {
    srand(time(0));
}

MinesweeperGame::~MinesweeperGame() {
    delete board;
    delete ui;
}

void MinesweeperGame::initialize(bool playAgain) {
    playing = playAgain;
    if (!playing) {
        finalResults();
    }
    ui->printGameIntro();
}

void MinesweeperGame::applyGameSettings(Size sizeChoice, int customRows, int customCols,
    Difficulty difficultyChoice, int customMines) {
    // Set board size based on selection
    if (sizeChoice == Size::Small) {
        settings.rows = 5;
        settings.cols = 5;
    }
    else if (sizeChoice == Size::Medium) {
        settings.rows = 8;
        settings.cols = 8;
    }
    else if (sizeChoice == Size::Big) {
        settings.rows = 10;
        settings.cols = 10;
    }
    else if (sizeChoice == Size::Custom) {
        settings.rows = customRows;
        settings.cols = customCols;
    }

    // Set difficulty based on selection
    if (difficultyChoice == Difficulty::Easy) {
        settings.mines = static_cast<int>(std::round(settings.rows * settings.cols * 0.1));
    }
    else if (difficultyChoice == Difficulty::Normal) {
        settings.mines = static_cast<int>(std::round(settings.rows * settings.cols * 0.2));
    }
    else if (difficultyChoice == Difficulty::Hard) {
        settings.mines = static_cast<int>(std::round(settings.rows * settings.cols * 0.3));
    }
    else if (difficultyChoice == Difficulty::Custom) {
        settings.mines = customMines;
    }

    if (board) delete board;
    board = new GameBoard(settings.rows, settings.cols, settings.mines);
}

void MinesweeperGame::play() {
    player1Score = 0;
    player2Score = 0;
    currentPlayer = Player::One;
    state = GameState::Playing;

    board->initialize();
}

void MinesweeperGame::finalResults() {
    ui->printFinalResults(player1Total, player2Total);
}

void MinesweeperGame::reset() {
    player1Total = 0;
    player2Total = 0;
    playing = true;
}

bool MinesweeperGame::isPlaying() const {
    return playing;
}

void MinesweeperGame::setPlaying(bool play) {
    playing = play;
}

GameUI* MinesweeperGame::getUI() const {
    return ui;
}

GameBoard* MinesweeperGame::getBoard() const {
    return board;
}

GameState MinesweeperGame::getState() const {
    return state;
}

Player MinesweeperGame::getCurrentPlayer() const {
    return currentPlayer;
}

int MinesweeperGame::getPlayer1Score() const {
    return player1Score;
}

int MinesweeperGame::getPlayer2Score() const {
    return player2Score;
}

int MinesweeperGame::getPlayer1Total() const {
    return player1Total;
}

int MinesweeperGame::getPlayer2Total() const {
    return player2Total;
}

// New setter methods
void MinesweeperGame::setState(GameState newState) {
    state = newState;
}

void MinesweeperGame::setCurrentPlayer(Player newPlayer) {
    currentPlayer = newPlayer;
}

void MinesweeperGame::updatePlayer1Score(int points) {
    player1Score += points;
}

void MinesweeperGame::updatePlayer2Score(int points) {
    player2Score += points;
}

void MinesweeperGame::updateTotalScores() {
    player1Total += player1Score;
    player2Total += player2Score;
}

// GameBoard implementation
GameBoard::GameBoard(int rows, int cols, int mines) :
    rows(rows), cols(cols), mines(mines) {
    initialize();
}

void GameBoard::initialize() {
    // Initialize board
    board = std::vector<std::vector<int>>(rows, std::vector<int>(cols, static_cast<int>(CellState::Blank)));
    visibility = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
    flags = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));

    // Place mines
    int minesPlaced = 0;
    while (minesPlaced < mines) {
        int row = std::rand() % rows;
        int col = std::rand() % cols;
        if (board[row][col] != static_cast<int>(CellState::Mine)) {
            board[row][col] = static_cast<int>(CellState::Mine);
            minesPlaced++;
        }
    }

    // Calculate numbers
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
}

void GameBoard::toggleFlag(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols || visibility[row][col]) {
        return; // Can't flag cells that are out of bounds or already visible
    }
    flags[row][col] = !flags[row][col];
}


bool GameBoard::revealCell(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols || visibility[row][col]) {
        return false;
    }

    visibility[row][col] = true;

    if (board[row][col] == static_cast<int>(CellState::Blank)) {
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                revealCell(row + x, col + y);
            }
        }
    }

    return true;
}

bool GameBoard::isCellFlagged(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols || visibility[row][col]) {
        return false; // Can't flag cells that are out of bounds or already visible
    }
    return flags[row][col];
}

void GameBoard::revealAllMines() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == static_cast<int>(CellState::Mine)) {
                visibility[i][j] = true;
            }
        }
    }
}

ResultState GameBoard::checkWin() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] != static_cast<int>(CellState::Mine) && !visibility[i][j]) {
                return ResultState::Ongoing;
            }
        }
    }
    return ResultState::Win;
}

int GameBoard::getRows() const { return rows; }
int GameBoard::getCols() const { return cols; }
int GameBoard::getMines() const { return mines; }

int GameBoard::getCellValue(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return -1;
    }
    return board[row][col];
}

bool GameBoard::isCellVisible(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    return visibility[row][col];
}

bool GameBoard::isCellMine(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }
    return board[row][col] == static_cast<int>(CellState::Mine);
}

// GameUI implementation
void GameUI::printBoard(const GameBoard& board) const {
    int rows = board.getRows();
    int cols = board.getCols();
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
            if (board.isCellVisible(i, j)) {
                if (board.isCellMine(i, j)) {
                    std::cout << std::setw(3) << "M";
                }
                else {
                    std::cout << std::setw(3) << board.getCellValue(i, j);
                }
            }
            else {
                std::cout << std::setw(3) << ".";
            }
        }
        std::cout << " |\n";
    }

    std::cout << std::setw(maxRowDigits + 2) << " " << "+";
    for (int j = 0; j < cols; j++) std::cout << "---";
    std::cout << "+\n";
}

void GameUI::printGameIntro() const {
    std::cout << "Welcome to Minesweeper!\n";
    std::cout << "Rules:\n";
    std::cout << "1. Players alternate turns revealing cells\n";
    std::cout << "2. Surviving a turn (no mine hit): +1 point\n";
    std::cout << "3. Hitting a mine: -2 points for you, +2 for opponent\n";
    std::cout << "4. Winning the game: +3 bonus points\n";
}

void GameUI::printFinalResults(int player1Total, int player2Total) const {
    std::cout << "Final Results:\n";
    std::cout << "Player 1: " << player1Total << "\n";
    std::cout << "Player 2: " << player2Total << "\n";

    if (player1Total > player2Total) {
        std::cout << "Player 1 wins!\n";
    }
    else if (player2Total > player1Total) {
        std::cout << "Player 2 wins!\n";
    }
    else {
        std::cout << "It's a tie!\n";
    }

    std::cout << "Thanks for playing!\n";
}

void GameUI::printRoundResults(int player1Score, int player2Score) const {
    std::cout << "\nRound Results:\n";
    std::cout << "Player 1: " << player1Score << " points\n";
    std::cout << "Player 2: " << player2Score << " points\n";
}

void GameUI::printPlayerTurn(Player player, int score) const {
    std::cout << "Player " << static_cast<int>(player) << "'s turn (Current Points: " << score << "):\n";
}

void GameUI::printMineHit(Player player) const {
    std::cout << "BOOM! Player " << static_cast<int>(player) << " hit a mine! (-2 points)\n";
    std::cout << "Player " << (player == Player::One ? 2 : 1) << " gains +2 points!\n";
}

void GameUI::printSurvived(Player player) const {
    std::cout << "Player " << static_cast<int>(player) << " survived! (+1 point)\n";
}

void GameUI::printWin(Player player) const {
    std::cout << "Congratulations! Player " << static_cast<int>(player) << " won! (+3 points)\n";
}

int GameUI::getRowInput(int maxRows) const {
    std::cout << "Enter row (1-" << maxRows << "): ";
    return getValidNumber<int>(1, maxRows);
}

int GameUI::getColInput(int maxCols) const {
    std::cout << "Enter column (1-" << maxCols << "): ";
    return getValidNumber<int>(1, maxCols);
}

bool GameUI::getPlayAgainInput() const {
    std::cout << "Play again? (1 for Yes, 0 for No): ";
    return getValidNumber<int>(0, 1);
}