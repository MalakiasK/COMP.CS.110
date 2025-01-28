#ifndef GAME_HH
#define GAME_HH

#include "card.hh"
#include "player.hh"

#include <QMainWindow>

const int CARD_DELAY = 1000; // 1000 ms = 1 second
const int UPDATE_DELAY = 2000; // 2000 ms = 2 second
const std::string HIGH_SCORES = "Resources/highscores.txt";

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum GameState {RUNNING, ENDED};

class Game : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Game
     * @param ui, MainWindow.
     * @param cardPairs, amount of pairs in the game.
     * @param playerNames, names of the players.
     * @param seed, used to randomize card placements.
     * Constructor: Creates a game with a given amount of cards and players.
     * Seed to randomize card placements.
     */
    Game(Ui::MainWindow* ui, uint cardPairs, std::vector<QString> playerNames,
         int seed);

    /**
     * @brief startGame
     * Starts the game, initializes cards and shuffles them, creates players
     * and updates labels.
     */
    void startGame();

    /**
     * @brief endGame
     * Ends the game, gets the winner(s), prepares high score saving.
     */
    void endGame();

    /**
     * @brief setPlayers
     * Creates players.
     */
    void setPlayers();

    /**
     * @brief clearPlayers
     * Deletes players.
     */
    void clearPlayers();

    /**
     * @brief initializeCards
     * Initializes cards to the grid.
     */
    void initializeCards();

    /**
     * @brief shuffleCards
     * Use the seed from the computer's clock to randomize card locations
     * and card faces.
     */
    void shuffleCards();

    /**
     * @brief nextFree
     * @param start, statring cell.
     * @return Returns the next free cell in the grid.
     */
    int nextFree(int start);

    /**
     * @brief clearBoard
     * Clears the board, deletes cards from the board.
     */
    void clearBoard();

    /**
     * @brief twoCards
     * @param cardButton, Card that has been clicked.
     * Main function in regards to gameplay.
     * If two cards are shown, checks for match, and follows accordingly.
     * Only two cards can be shown at any given time.
     */
    void twoCards(Card* cardButton);

    /**
     * @brief isPair
     * @return bool, True; if the turned cards are a match, False; if not.
     * Checks if the two cards turned are a match.
     */
    bool isPair();

    /**
     * @brief getWinner
     * Gets the winner(s) of the game and shows them on screen.
     * Shows their found pair amount also.
     */
    void getWinner();

    /**
     * @brief setSaveScoresButton
     * @param saveScoresButton
     * Small helper function.
     */
    void setSaveScoresButton(QPushButton*& saveScoresButton);

    /**
     * @brief getGameState
     * @return Returns the current game state.
     */
    GameState getGameState();

private slots:

    /**
     * @brief collectCards
     * Removes cards from the board and adds them to the player's score.
     */
    void collectCards();

    /**
     * @brief resetTurnedCards
     * Turns cards back that have been turned.
     */
    void resetTurnedCards();

    /**
     * @brief updateLabels
     * Updates labels, player's turn, found pairs.
     */
    void updateLabels();

    /**
     * @brief saveScores
     * Saves high scores to the file.
     */
    void saveScores();

private:

    Ui::MainWindow* ui_;

    GameState gameState_;

    int seed_;

    uint cardPairs_;

    uint currentTurn_;

    // Card Button Pointers
    std::vector<Card*> cardButtons;

    std::vector<QString> playerNames_;
    // Player pointers.
    std::vector<Player*> players;

    std::vector<Player*> winners;

    // Gameboard dimensions
    int columns_;
    int rows_;

    std::vector<Card*> turnedCards_;
    std::vector<Card*> collectedCards_;

    QPushButton* saveScoresButton_;
};

#endif // GAME_HH
