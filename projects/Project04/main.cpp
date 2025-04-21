#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include "minesweeper.h"
#include "ValidationPro.h"
#include <string>
#include <vector>

// Constants for GUI
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 650;
const int CELL_SIZE = 40;
const int BOARD_OFFSET_X = 150;  // Increased x offset
const int BOARD_OFFSET_Y = 150;  // Increased y offset
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 40;

// Game states for the GUI
enum class GuiState {
    MainMenu,
    SizeSelection,
    DifficultySelection,
    InGame
};

// Structure for buttons
struct Button {
    SDL_Rect rect;
    std::string text;
    bool isHovered;
};

// Function prototypes
void renderBoard(SDL_Renderer* renderer, TTF_Font* font, MinesweeperGame& game);
void renderUI(SDL_Renderer* renderer, TTF_Font* font, MinesweeperGame& game, GuiState state);
void renderButton(SDL_Renderer* renderer, TTF_Font* font, Button& button);
void handleMouseClick(int x, int y, MinesweeperGame& game);
Button createButton(int x, int y, const std::string& text);
bool isPointInRect(int x, int y, const SDL_Rect& rect);
void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color);
void renderSizeSelection(SDL_Renderer* renderer, TTF_Font* font, std::vector<Button>& sizeButtons);
void renderDifficultySelection(SDL_Renderer* renderer, TTF_Font* font, std::vector<Button>& difficultyButtons);
void handleCustomSizeInput(int& customRows, int& customCols);
int handleCustomMinesInput(Size sizeChoice, int customRows, int customCols);

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Minesweeper",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        std::cerr << "Window could not be created! Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Load font
    TTF_Font* font = TTF_OpenFont("Ubuntu-B.ttf", 16);
    if (font == nullptr) {
        std::cerr << "Failed to load font! Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Initialize game
    MinesweeperGame game;
    game.initialize();

    // Set up GUI state
    GuiState guiState = GuiState::MainMenu;
    Size selectedSize = Size::Small;
    Difficulty selectedDifficulty = Difficulty::Easy;
    int customRows = 0, customCols = 0, customMines = 0;

    // Create main menu buttons
    Button newGameButton = createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 200, "New Game");
    Button quitButton = createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 260, "Quit");

    // Create size selection buttons
    std::vector<Button> sizeButtons = {
        createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 150, "Small (5x5)"),
        createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 200, "Medium (8x8)"),
        createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 250, "Big (10x10)"),
        createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 300, "Custom")
    };

    // Create difficulty selection buttons
    std::vector<Button> difficultyButtons = {
        createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 150, "Easy (10% mines)"),
        createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 200, "Normal (20% mines)"),
        createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 250, "Hard (30% mines)"),
        createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 300, "Custom")
    };

    // Game control buttons
    Button backToMenuButton = createButton(20, 20, "Main Menu");

    // Main loop
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEMOTION) {
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;

                // Update button hover states based on current GUI state
                if (guiState == GuiState::MainMenu) {
                    newGameButton.isHovered = isPointInRect(mouseX, mouseY, newGameButton.rect);
                    quitButton.isHovered = isPointInRect(mouseX, mouseY, quitButton.rect);
                }
                else if (guiState == GuiState::SizeSelection) {
                    for (auto& button : sizeButtons) {
                        button.isHovered = isPointInRect(mouseX, mouseY, button.rect);
                    }
                }
                else if (guiState == GuiState::DifficultySelection) {
                    for (auto& button : difficultyButtons) {
                        button.isHovered = isPointInRect(mouseX, mouseY, button.rect);
                    }
                }
                else if (guiState == GuiState::InGame) {
                    backToMenuButton.isHovered = isPointInRect(mouseX, mouseY, backToMenuButton.rect);
                }
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;

                    // Handle clicks based on current GUI state
                    if (guiState == GuiState::MainMenu) {
                        if (isPointInRect(mouseX, mouseY, newGameButton.rect)) {
                            guiState = GuiState::SizeSelection;
                        }
                        else if (isPointInRect(mouseX, mouseY, quitButton.rect)) {
                            quit = true;
                        }
                    }
                    else if (guiState == GuiState::SizeSelection) {
                        for (int i = 0; i < sizeButtons.size(); i++) {
                            if (isPointInRect(mouseX, mouseY, sizeButtons[i].rect)) {
                                selectedSize = static_cast<Size>(i + 1);

                                if (selectedSize == Size::Custom) {
                                    handleCustomSizeInput(customRows, customCols);
                                }

                                guiState = GuiState::DifficultySelection;
                                break;
                            }
                        }
                    }
                    else if (guiState == GuiState::DifficultySelection) {
                        for (int i = 0; i < difficultyButtons.size(); i++) {
                            if (isPointInRect(mouseX, mouseY, difficultyButtons[i].rect)) {
                                selectedDifficulty = static_cast<Difficulty>(i + 1);

                                if (selectedDifficulty == Difficulty::Custom) {
                                    customMines = handleCustomMinesInput(selectedSize, customRows, customCols);
                                }

                                // Apply settings and start game
                                game.applyGameSettings(selectedSize, customRows, customCols, selectedDifficulty, customMines);
                                game.play();
                                guiState = GuiState::InGame;
                                break;
                            }
                        }
                    }
                    else if (guiState == GuiState::InGame) {
                        if (isPointInRect(mouseX, mouseY, backToMenuButton.rect)) {
                            guiState = GuiState::MainMenu;
                        }
                        else {
                            // Handle board click if game is in playing state
                            if (game.getState() == GameState::Playing) {
                                handleMouseClick(mouseX, mouseY, game);
                            }
                        }
                    }
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255); // Dark gray background
        SDL_RenderClear(renderer);

        // Render UI based on current state
        if (guiState == GuiState::MainMenu) {
            // Render title
            SDL_Color titleColor = { 255, 255, 255, 255 };
            renderText(renderer, font, "Minesweeper Game", WINDOW_WIDTH / 2 - 80, 100, titleColor);

            // Render main menu buttons
            renderButton(renderer, font, newGameButton);
            renderButton(renderer, font, quitButton);

            // Render current total scores if any
            if (game.getPlayer1Total() > 0 || game.getPlayer2Total() > 0) {
                SDL_Color scoreColor = { 200, 200, 200, 255 };
                std::string totalScoreText = "Total Score - P1: " + std::to_string(game.getPlayer1Total()) +
                    " | P2: " + std::to_string(game.getPlayer2Total());
                renderText(renderer, font, totalScoreText, WINDOW_WIDTH / 2 - 120, 350, scoreColor);
            }
        }
        else if (guiState == GuiState::SizeSelection) {
            // Render size selection title
            SDL_Color titleColor = { 255, 255, 255, 255 };
            renderText(renderer, font, "Select Board Size", WINDOW_WIDTH / 2 - 80, 100, titleColor);

            // Render size buttons
            for (auto& button : sizeButtons) {
                renderButton(renderer, font, button);
            }
        }
        else if (guiState == GuiState::DifficultySelection) {
            // Render difficulty selection title
            SDL_Color titleColor = { 255, 255, 255, 255 };
            renderText(renderer, font, "Select Difficulty", WINDOW_WIDTH / 2 - 80, 100, titleColor);

            // Render difficulty buttons
            for (auto& button : difficultyButtons) {
                renderButton(renderer, font, button);
            }
        }
        else if (guiState == GuiState::InGame) {
            // Render game board
            renderBoard(renderer, font, game);

            // Render UI elements
            renderUI(renderer, font, game, guiState);

            // Render back to menu button
            renderButton(renderer, font, backToMenuButton);
        }

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

// Handle custom size input from the console (can be replaced with GUI input boxes in a more advanced version)
void handleCustomSizeInput(int& customRows, int& customCols) {
    std::cout << "Enter number of rows (min 5): ";
    customRows = getValidNumber<int>(5);
    std::cout << "Enter number of columns (min 5): ";
    customCols = getValidNumber<int>(5);
}

// Handle custom mines input from the console
int handleCustomMinesInput(Size sizeChoice, int customRows, int customCols) {
    int maxMines = 0;

    if (sizeChoice == Size::Custom) {
        maxMines = customRows * customCols - 1;
    }
    else if (sizeChoice == Size::Small) {
        maxMines = 5 * 5 - 1;
    }
    else if (sizeChoice == Size::Medium) {
        maxMines = 8 * 8 - 1;
    }
    else if (sizeChoice == Size::Big) {
        maxMines = 10 * 10 - 1;
    }

    std::cout << "Enter number of mines (1-" << maxMines << "): ";
    return getValidNumber<int>(1, maxMines);
}

// Create a button with given position and text
Button createButton(int x, int y, const std::string& text) {
    Button button;
    button.rect = { x, y, BUTTON_WIDTH, BUTTON_HEIGHT };
    button.text = text;
    button.isHovered = false;
    return button;
}

// Check if a point is inside a rectangle
bool isPointInRect(int x, int y, const SDL_Rect& rect) {
    return (x >= rect.x && x < rect.x + rect.w &&
        y >= rect.y && y < rect.y + rect.h);
}

// Render a text string at the given position
void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (textSurface != nullptr) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture != nullptr) {
            SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

// Render a button
void renderButton(SDL_Renderer* renderer, TTF_Font* font, Button& button) {
    // Button background
    if (button.isHovered) {
        SDL_SetRenderDrawColor(renderer, 100, 100, 180, 255); // Highlighted color
    }
    else {
        SDL_SetRenderDrawColor(renderer, 70, 70, 120, 255); // Normal color
    }
    SDL_RenderFillRect(renderer, &button.rect);

    // Button border
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderDrawRect(renderer, &button.rect);

    // Button text
    SDL_Color textColor = { 255, 255, 255, 255 }; // White
    int textX = button.rect.x + (button.rect.w - (button.text.length() * 8)) / 2; // Approximate center
    int textY = button.rect.y + (button.rect.h - 16) / 2; // Approximate center
    renderText(renderer, font, button.text, textX, textY, textColor);
}

// Render the game board
void renderBoard(SDL_Renderer* renderer, TTF_Font* font, MinesweeperGame& game) {
    GameBoard* board = game.getBoard();
    if (!board) return;

    int rows = board->getRows();
    int cols = board->getCols();

    // Draw board background
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Gray
    SDL_Rect boardRect = {
        BOARD_OFFSET_X - 1,
        BOARD_OFFSET_Y - 1,
        cols * CELL_SIZE + 2,
        rows * CELL_SIZE + 2
    };
    SDL_RenderFillRect(renderer, &boardRect);

    // Draw cells
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            SDL_Rect cellRect = {
                BOARD_OFFSET_X + col * CELL_SIZE,
                BOARD_OFFSET_Y + row * CELL_SIZE,
                CELL_SIZE - 1,
                CELL_SIZE - 1
            };

            if (board->isCellVisible(row, col)) {
                if (board->isCellMine(row, col)) {
                    // Mine cell
                    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255); // Red
                    SDL_RenderFillRect(renderer, &cellRect);

                    // Draw mine symbol (a circle)
                    filledCircleRGBA(
                        renderer,
                        BOARD_OFFSET_X + col * CELL_SIZE + CELL_SIZE / 2,
                        BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE / 2,
                        CELL_SIZE / 4,
                        0, 0, 0, 255
                    );
                }
                else {
                    // Revealed cell
                    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255); // Light gray
                    SDL_RenderFillRect(renderer, &cellRect);

                    // Draw number if it's not zero
                    int value = board->getCellValue(row, col);
                    if (value > 0) {
                        // Choose color based on number value
                        SDL_Color numColor;
                        switch (value) {
                        case 1: numColor = { 0, 0, 255, 255 }; break; // Blue when its just 1 mine around it
                        case 2: numColor = { 0, 128, 0, 255 }; break; // Grey when its 2 mine around
                        case 3: numColor = { 255, 0, 0, 255 }; break; // Red for 3
                        case 4: numColor = { 128, 0, 128, 255 }; break; // Purple for 4
                        case 5: numColor = { 128, 0, 0, 255 }; break; // Maroon  for 5
                        case 6: numColor = { 0, 128, 128, 255 }; break; // Teal for 6
                        case 7: numColor = { 0, 0, 0, 255 }; break; // Black for 7
                        case 8: numColor = { 128, 128, 128, 255 }; break; // Gray for 8
                        default: numColor = { 0, 0, 0, 255 }; break; // 9 isnt possible, this is if no mine around it.
                        }

                        // Render the number
                        std::string numStr = std::to_string(value);
                        renderText(
                            renderer, font, numStr,
                            BOARD_OFFSET_X + col * CELL_SIZE + CELL_SIZE / 2 - 5,
                            BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE / 2 - 8,
                            numColor
                        );
                    }
                }
            }
            else {
                // Unrevealed cell
                SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255); // Dark gray
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }
}

// Render UI elements (scores, player turn, etc.)
void renderUI(SDL_Renderer* renderer, TTF_Font* font, MinesweeperGame& game, GuiState state) {
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color player1Color = { 100, 200, 255, 255 }; // Light blue
    SDL_Color player2Color = { 255, 200, 100, 255 }; // Light orange

    // Game title at the top
    renderText(renderer, font, "Minesweeper", 20, 70, white);

    // Player scores - moved to left side of screen
    std::string p1Score = "Player 1: " + std::to_string(game.getPlayer1Score());
    std::string p2Score = "Player 2: " + std::to_string(game.getPlayer2Score());

    renderText(renderer, font, p1Score, 20, 100, player1Color);
    renderText(renderer, font, p2Score, 20, 120, player2Color);

    // Current player indicator - moved to avoid overlap with board
    if (game.getState() == GameState::Playing) {
        std::string turnText = "Current Turn: Player " +
            std::to_string(static_cast<int>(game.getCurrentPlayer()));
        SDL_Color currentColor = (game.getCurrentPlayer() == Player::One) ? player1Color : player2Color;
        renderText(renderer, font, turnText, BOARD_OFFSET_X, BOARD_OFFSET_Y - 30, currentColor);
    }
    else {
        // Game over message
        renderText(renderer, font, "Game Over", BOARD_OFFSET_X, BOARD_OFFSET_Y - 30, white);
    }

    // Total scores at the bottom
    std::string totalScoreText = "Total Score - P1: " + std::to_string(game.getPlayer1Total()) +
        " | P2: " + std::to_string(game.getPlayer2Total());
    renderText(renderer, font, totalScoreText, 20, WINDOW_HEIGHT - 40, white);
}

// Handle mouse click on the board
void handleMouseClick(int x, int y, MinesweeperGame& game) {
    GameBoard* board = game.getBoard();
    if (!board) return;

    // Check if click is within board boundaries
    if (x < BOARD_OFFSET_X || y < BOARD_OFFSET_Y) return;

    int col = (x - BOARD_OFFSET_X) / CELL_SIZE;
    int row = (y - BOARD_OFFSET_Y) / CELL_SIZE;

    if (row >= 0 && row < board->getRows() && col >= 0 && col < board->getCols()) {
        // Valid board position
        if (!board->isCellVisible(row, col)) {
            // Process click on an unrevealed cell
            Player currentPlayer = game.getCurrentPlayer();

            if (board->isCellMine(row, col)) {
                // Mine clicked
                game.getUI()->printMineHit(currentPlayer);

                // Update scores
                if (currentPlayer == Player::One) {
                    game.updatePlayer1Score(-2);
                    game.updatePlayer2Score(2);
                }
                else {
                    game.updatePlayer2Score(-2);
                    game.updatePlayer1Score(2);
                }

                board->revealAllMines();
                game.setState(GameState::Ended);
            }
            else {
                // Safe cell clicked
                board->revealCell(row, col);

                if (currentPlayer == Player::One) {
                    game.updatePlayer1Score(1);
                    game.getUI()->printSurvived(Player::One);
                }
                else {
                    game.updatePlayer2Score(1);
                    game.getUI()->printSurvived(Player::Two);
                }

                if (board->checkWin() == ResultState::Win) {
                    game.getUI()->printWin(currentPlayer);

                    if (currentPlayer == Player::One) {
                        game.updatePlayer1Score(3);
                    }
                    else {
                        game.updatePlayer2Score(3);
                    }

                    game.setState(GameState::Ended);
                }
                else {
                    game.setCurrentPlayer((currentPlayer == Player::One) ? Player::Two : Player::One);
                }
            }

            // If game ended, update total scores
            if (game.getState() == GameState::Ended) {
                game.updateTotalScores();
            }
        }
    }
}