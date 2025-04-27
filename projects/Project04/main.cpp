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
const int BOARD_OFFSET_X = 220;  // Increased x offset
const int BOARD_OFFSET_Y = 100;  // Increased y offset
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 40;

// Game states for the GUI
enum class GuiState {
    MainMenu,
    SizeSelection,
    DifficultySelection,
    CustomInput,
    InGame,
    GameEnd  // New state for game end screen
};

enum class CustomInputType {
    Rows,
    Columns,
    Mines
};
// Structure for buttons
struct Button {
    SDL_Rect rect;
    std::string text;
    bool isHovered;
};

struct ButtonConfig {    // for custom button lining
    int maxButtonCount;  // Maximum number of buttons to display
    int minValue;        // Minimum value
    int maxValue;        // Maximum value
    int increment;       // Increment between button values
};

struct NumericInput {
    std::string label;
    int currentValue;
    int minValue;
    int maxValue;
    std::vector<Button> buttons;
    CustomInputType inputType;
};

// Function prototypes
void renderBoard(SDL_Renderer* renderer, TTF_Font* font, MinesweeperGame& game);
void renderUI(SDL_Renderer* renderer, TTF_Font* font, MinesweeperGame& game, GuiState state);
void renderButton(SDL_Renderer* renderer, TTF_Font* font, Button& button);
void handleMouseLeftClick(int x, int y, MinesweeperGame& game);
void handleMouseRightClick(int x, int y, MinesweeperGame& game);
Button createButton(int x, int y, const std::string& text);
bool isPointInRect(int x, int y, const SDL_Rect& rect);
void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color);
void renderSizeSelection(SDL_Renderer* renderer, TTF_Font* font, std::vector<Button>& sizeButtons);
void renderDifficultySelection(SDL_Renderer* renderer, TTF_Font* font, std::vector<Button>& difficultyButtons);
void handleCustomSizeInput(int& customRows, int& customCols);
int handleCustomMinesInput(Size sizeChoice, int customRows, int customCols);
void renderGameEnd(SDL_Renderer* renderer, TTF_Font* font, MinesweeperGame& game, Button& backToMenuButton, Button& playAgainButton);
void renderNumericInput(SDL_Renderer* renderer, TTF_Font* font, NumericInput& input, Button& continueButton);

bool handleNumericInputClick(int mouseX, int mouseY, NumericInput& input, Button& continueButton,
    CustomInputType& currentInput, int& customRows, int& customCols, int& customMines,
    GuiState& guiState, Size selectedSize = Size::Small) {

    // Check if any number button was clicked
    for (auto& button : input.buttons) {
        if (isPointInRect(mouseX, mouseY, button.rect)) {
            input.currentValue = std::stoi(button.text);
            return true;
        }
    }

    // Check if continue button was clicked
    if (isPointInRect(mouseX, mouseY, continueButton.rect)) {
        // Save the current value and move to next input
        if (currentInput == CustomInputType::Rows) {
            customRows = input.currentValue;
            currentInput = CustomInputType::Columns;
            return true;
        }
        else if (currentInput == CustomInputType::Columns) {
            customCols = input.currentValue;
            // If we're setting custom size, go to difficulty selection
            guiState = GuiState::DifficultySelection;
            return true;
        }
        else if (currentInput == CustomInputType::Mines) {
            customMines = input.currentValue;
            // If we're setting custom mines, start the game
            guiState = GuiState::InGame;
            return true;
        }
    }

    return false;
}

ButtonConfig calculateButtonConfig(int minValue, int maxValue, int maxButtonCount = 13) {
    ButtonConfig config;
    config.minValue = minValue;
    config.maxValue = maxValue;
    config.maxButtonCount = maxButtonCount;

    // If range fits within button count, use regular increments of 1
    if ((maxValue - minValue + 1) <= maxButtonCount) {
        config.increment = 1;
    }
    else {
        // Calculate required increment to fit range into maxButtonCount buttons
        config.increment = (maxValue - minValue + 1 + maxButtonCount - 2) / (maxButtonCount - 1);
        // Ensure the increment is at least 1
        config.increment = std::max(1, config.increment);
    }

    return config;
}

NumericInput createNumericInput(const std::string& label, int minValue, int maxValue, int defaultValue = 5, CustomInputType inputType = CustomInputType::Rows) {
    NumericInput input;
    input.label = label;
    input.currentValue = defaultValue;
    input.minValue = minValue;
    input.maxValue = maxValue;
    input.inputType = inputType;

    // Get button configuration
    ButtonConfig config = calculateButtonConfig(minValue, maxValue);
    int increment = config.increment;

    // Create buttons for each value with appropriate increments
    int buttonWidth = 40;
    int buttonHeight = 40;
    std::vector<int> buttonValues;

    // Generate button values
    for (int val = minValue; val < maxValue; val += increment) {
        buttonValues.push_back(val);
    }
    // Always include the max value as the last button
    if (buttonValues.empty() || buttonValues.back() != maxValue) {
        buttonValues.push_back(maxValue);
    }

    // Calculate start position for centered buttons
    int startX = WINDOW_WIDTH / 2 - (buttonValues.size() * buttonWidth) / 2;
    int y = 250;

    // Create the actual buttons
    for (int i = 0; i < buttonValues.size(); i++) {
        int value = buttonValues[i];
        Button btn = createButton(startX + i * buttonWidth, y, std::to_string(value));
        btn.rect.w = buttonWidth;
        btn.rect.h = buttonHeight;
        input.buttons.push_back(btn);
    }

    return input;
}



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
    CustomInputType currentCustomInput = CustomInputType::Rows;
    int customRows = 5, customCols = 5, customMines = 3;
    bool customSizeSelected = false;
    bool customDifficultySelected = false;

    // Create main menu buttons
    Button newGameButton = createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 200, "New Game");
    Button quitButton = createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 260, "Quit");

    NumericInput rowInput = createNumericInput("Select number of rows:", 1, 13, 5, CustomInputType::Rows);
    NumericInput colInput = createNumericInput("Select number of columns:", 1, 13, 5, CustomInputType::Columns);
    NumericInput mineInput = createNumericInput("Select number of mines:", 1, 13, 3, CustomInputType::Mines);

    Button continueButton = createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 350, "Continue");

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
    Button playAgainButton = createButton(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, WINDOW_HEIGHT - 150, "Play Again");

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
                else if (guiState == GuiState::CustomInput) {
                    // Update hover state for the numeric input buttons
                    NumericInput* currentInput = nullptr;
                    if (currentCustomInput == CustomInputType::Rows) {
                        currentInput = &rowInput;
                    }
                    else if (currentCustomInput == CustomInputType::Columns) {
                        currentInput = &colInput;
                    }
                    else if (currentCustomInput == CustomInputType::Mines) {
                        currentInput = &mineInput;
                    }

                    if (currentInput) {
                        for (auto& button : currentInput->buttons) {
                            button.isHovered = isPointInRect(mouseX, mouseY, button.rect);
                        }
                    }

                    continueButton.isHovered = isPointInRect(mouseX, mouseY, continueButton.rect);
                }
                else if (guiState == GuiState::InGame) {
                    backToMenuButton.isHovered = isPointInRect(mouseX, mouseY, backToMenuButton.rect);
                }
                else if (guiState == GuiState::GameEnd) {
                    backToMenuButton.isHovered = isPointInRect(mouseX, mouseY, backToMenuButton.rect);
                    playAgainButton.isHovered = isPointInRect(mouseX, mouseY, playAgainButton.rect);
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
                                    // Switch to custom input mode for rows first
                                    currentCustomInput = CustomInputType::Rows;
                                    guiState = GuiState::CustomInput;
                                }
                                else {
                                    guiState = GuiState::DifficultySelection;
                                }
                                break;
                            }
                        }
                    }
                    else if (guiState == GuiState::DifficultySelection) {
                        for (int i = 0; i < difficultyButtons.size(); i++) {
                            if (isPointInRect(mouseX, mouseY, difficultyButtons[i].rect)) {
                                selectedDifficulty = static_cast<Difficulty>(i + 1);

                                if (selectedDifficulty == Difficulty::Custom) {
                                    // Set maximum mines based on board size
                                    int maxMines = 0;
                                    if (selectedSize == Size::Custom) {
                                        maxMines = customRows * customCols - 1;  // Maximum possible mines
                                        int recommendedMax = (customRows * customCols) / 2;  // Half of the board size
                                        maxMines = std::min(maxMines, recommendedMax);  // Use the smaller value
                                    }
                                    else if (selectedSize == Size::Small) {
                                        maxMines = 5 * 5 - 1;
                                        maxMines = std::min(maxMines, (5 * 5) / 2);
                                    }
                                    else if (selectedSize == Size::Medium) {
                                        maxMines = 8 * 8 - 1;
                                        maxMines = std::min(maxMines, (8 * 8) / 2);
                                    }
                                    else if (selectedSize == Size::Big) {
                                        maxMines = 10 * 10 - 1;
                                        maxMines = std::min(maxMines, (10 * 10) / 2);
                                    }

                                    // Create mine input with correct max value - no more arbitrary limit of 15
                                    mineInput = createNumericInput("Select number of mines:", 1, maxMines,
                                        std::min(3, maxMines), CustomInputType::Mines);
                                    currentCustomInput = CustomInputType::Mines;
                                    guiState = GuiState::CustomInput;
                                }
                                else {
                                    // Apply settings and start game
                                    game.applyGameSettings(selectedSize, customRows, customCols, selectedDifficulty, customMines);
                                    game.play();
                                    guiState = GuiState::InGame;
                                }
                                break;
                            }
                        }
                    }
                    else if (guiState == GuiState::CustomInput) {
                        // Handle custom input based on what we're currently inputting
                        NumericInput* currentInput = nullptr;
                        if (currentCustomInput == CustomInputType::Rows) {
                            currentInput = &rowInput;
                        }
                        else if (currentCustomInput == CustomInputType::Columns) {
                            currentInput = &colInput;
                        }
                        else if (currentCustomInput == CustomInputType::Mines) {
                            currentInput = &mineInput;
                        }

                        if (currentInput) {
                            if (handleNumericInputClick(mouseX, mouseY, *currentInput, continueButton, currentCustomInput,
                                customRows, customCols, customMines, guiState, selectedSize)) {
                                // If we moved to InGame state, apply settings and start game
                                if (guiState == GuiState::InGame) {
                                    game.applyGameSettings(selectedSize, customRows, customCols, selectedDifficulty, customMines);
                                    game.play();
                                }
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
                                handleMouseLeftClick(mouseX, mouseY, game);
                            }
                        }
                    }
                    else if (guiState == GuiState::GameEnd) {
                        if (isPointInRect(mouseX, mouseY, backToMenuButton.rect)) {
                            guiState = GuiState::MainMenu;
                        }
                        else if (isPointInRect(mouseX, mouseY, playAgainButton.rect)) {
                            // Skip the main menu and go straight to size selection
                            guiState = GuiState::SizeSelection;
                        }
                    }

                }
                else if (e.button.button == SDL_BUTTON_RIGHT) {
                    std::cout << "Right click detected at: " << e.button.x << ", " << e.button.y << std::endl;
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;

                    if (guiState == GuiState::InGame && game.getState() == GameState::Playing) {
                        handleMouseRightClick(mouseX, mouseY, game);
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
        else if (guiState == GuiState::CustomInput) {
            // Set the background
            SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255); // Dark gray background
            SDL_RenderClear(renderer);

            // Render title
            SDL_Color titleColor = { 255, 255, 255, 255 };
            std::string titleText;

            if (currentCustomInput == CustomInputType::Rows) {
                renderNumericInput(renderer, font, rowInput, continueButton);
                titleText = "Custom Board Size - Step 1/2";
            }
            else if (currentCustomInput == CustomInputType::Columns) {
                renderNumericInput(renderer, font, colInput, continueButton);
                titleText = "Custom Board Size - Step 2/2";
            }
            else if (currentCustomInput == CustomInputType::Mines) {
                renderNumericInput(renderer, font, mineInput, continueButton);
                titleText = "Custom Difficulty";
            }

            renderText(renderer, font, titleText, WINDOW_WIDTH / 2 - 120, 100, titleColor);
        }

        else if (guiState == GuiState::InGame) {
            // Render game board
            renderBoard(renderer, font, game);

            // Render UI elements
            renderUI(renderer, font, game, guiState);

            // Render back to menu button
            renderButton(renderer, font, backToMenuButton);

            // Check if game has ended and transition to GameEnd state
            if (game.getState() == GameState::Ended) {
                guiState = GuiState::GameEnd;
            }
        }
        else if (guiState == GuiState::GameEnd) {
            // First render the game board in the background
            renderBoard(renderer, font, game);

            // Then render the game end overlay
            renderGameEnd(renderer, font, game, backToMenuButton, playAgainButton);
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
    std::cout << "Enter number of rows (1-13): ";
    customRows = getValidNumber<int>(1,13);
    std::cout << "Enter number of columns (1-13): ";
    customCols = getValidNumber<int>(1,13);
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
                if (board->isCellFlagged(row, col)) {
                    // Flagged cell
                    SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255); // Red
                    SDL_RenderFillRect(renderer, &cellRect);

                    // Optionally draw a flag symbol (like a small triangle)
                    Sint16 xPoints[3] = {
                        static_cast<Sint16>(BOARD_OFFSET_X + col * CELL_SIZE + CELL_SIZE / 4),
                        static_cast<Sint16>(BOARD_OFFSET_X + col * CELL_SIZE + CELL_SIZE * 3 / 4),
                        static_cast<Sint16>(BOARD_OFFSET_X + col * CELL_SIZE + CELL_SIZE / 4)
                    };
                    Sint16 yPoints[3] = {
                        static_cast<Sint16>(BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE / 4),
                        static_cast<Sint16>(BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE / 2),
                        static_cast<Sint16>(BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE * 3 / 4)
                    };
                    filledPolygonRGBA(renderer, xPoints, yPoints, 3, 255, 255, 255, 255);
                }
                else {
                    // Normal unrevealed cell
                    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255); // Dark gray
                    SDL_RenderFillRect(renderer, &cellRect);
                }
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

// Render the game end screen with overlay
void renderGameEnd(SDL_Renderer* renderer, TTF_Font* font, MinesweeperGame& game, Button& backToMenuButton, Button& playAgainButton) {
    // Draw semi-transparent overlay
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180); // Semi-transparent black
    SDL_Rect overlayRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    SDL_RenderFillRect(renderer, &overlayRect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    // Draw game end panel
    SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255); // Dark blue-gray
    SDL_Rect panelRect = { WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 200, 400, 350 };
    SDL_RenderFillRect(renderer, &panelRect);

    // Draw panel border
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Light gray
    SDL_RenderDrawRect(renderer, &panelRect);

    // Determine winner and set colors
    SDL_Color titleColor = { 255, 255, 255, 255 }; // White
    SDL_Color player1Color = { 100, 200, 255, 255 }; // Light blue
    SDL_Color player2Color = { 255, 200, 100, 255 }; // Light orange
    SDL_Color winnerColor;

    std::string winnerText;
    if (game.getPlayer1Score() > game.getPlayer2Score()) {
        winnerText = "Player 1 Wins!";
        winnerColor = player1Color;
    }
    else if (game.getPlayer2Score() > game.getPlayer1Score()) {
        winnerText = "Player 2 Wins!";
        winnerColor = player2Color;
    }
    else {
        winnerText = "It's a Tie!";
        winnerColor = titleColor;
    }

    // Render game end title
    renderText(renderer, font, "Game Over!", panelRect.x + 150, panelRect.y + 30, titleColor);

    // Render winner
    renderText(renderer, font, winnerText, panelRect.x + 150, panelRect.y + 70, winnerColor);

    // Render scores
    int textY = panelRect.y + 120;
    renderText(renderer, font, "Round Scores:", panelRect.x + 150, textY, titleColor);

    textY += 40;
    std::string p1ScoreText = "Player 1: " + std::to_string(game.getPlayer1Score()) + " points";
    std::string p2ScoreText = "Player 2: " + std::to_string(game.getPlayer2Score()) + " points";
    renderText(renderer, font, p1ScoreText, panelRect.x + 150, textY, player1Color);

    textY += 30;
    renderText(renderer, font, p2ScoreText, panelRect.x + 150, textY, player2Color);

    // Render total scores
    textY += 50;
    renderText(renderer, font, "Total Scores:", panelRect.x + 150, textY, titleColor);

    textY += 40;
    std::string p1TotalText = "Player 1: " + std::to_string(game.getPlayer1Total()) + " points";
    std::string p2TotalText = "Player 2: " + std::to_string(game.getPlayer2Total()) + " points";
    renderText(renderer, font, p1TotalText, panelRect.x + 150, textY, player1Color);

    textY += 30;
    renderText(renderer, font, p2TotalText, panelRect.x + 150, textY, player2Color);

    // Render buttons
    renderButton(renderer, font, backToMenuButton);
    renderButton(renderer, font, playAgainButton);
}

// Handle mouse click on the board
void handleMouseLeftClick(int x, int y, MinesweeperGame& game) {
    std::cout << "handleMouseLeftClick called for position: " << x << ", " << y << std::endl;
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


void handleMouseRightClick(int x, int y, MinesweeperGame& game) {
    std::cout << "handleMouseRightClick called for position: " << x << ", " << y << std::endl;
    GameBoard* board = game.getBoard();
    if (!board) return;

    // Check if click is within board boundaries
    if (x < BOARD_OFFSET_X || y < BOARD_OFFSET_Y) return;

    int col = (x - BOARD_OFFSET_X) / CELL_SIZE;
    int row = (y - BOARD_OFFSET_Y) / CELL_SIZE;

    if (row >= 0 && row < board->getRows() && col >= 0 && col < board->getCols()) {
        // Toggle flag on unrevealed cell
        board->toggleFlag(row, col);
    }
}


void renderNumericInput(SDL_Renderer* renderer, TTF_Font* font, NumericInput& input, Button& continueButton) {
    // Render label
    SDL_Color white = { 255, 255, 255, 255 };
    renderText(renderer, font, input.label, WINDOW_WIDTH / 2 - 100, 180, white);

    // Render current value
    std::string valueText = "Current value: " + std::to_string(input.currentValue);
    renderText(renderer, font, valueText, WINDOW_WIDTH / 2 - 100, 210, white);

    // Render buttons
    for (auto& button : input.buttons) {
        // Highlight the button if it's the current value
        if (button.text == std::to_string(input.currentValue)) {
            SDL_Rect highlightRect = button.rect;
            highlightRect.x -= 2;
            highlightRect.y -= 2;
            highlightRect.w += 4;
            highlightRect.h += 4;
            SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255); // Gold color
            SDL_RenderDrawRect(renderer, &highlightRect);
        }
        renderButton(renderer, font, button);
    }

    // Render continue button
    renderButton(renderer, font, continueButton);
}



