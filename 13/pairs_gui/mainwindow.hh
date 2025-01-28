#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "game.hh"
#include <QMainWindow>
#include <QLabel>

const int MAXIMUM_PLAYER_AMOUNT = 6;
const int TOP_HIGH_SCORES = 10;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief closeProgram
     * Closes the program.
     */
    void closeProgram();

    /**
     * @brief prepareGame
     * Goes hand in hand with EnterPlayerName();
     * Prepares window for player name prompt.
     */
    void prepareGame();

    /**
     * @brief QuitToMainMenu
     * Quits to the main menu, from the game screen.
     */
    void QuitToMainMenu();

    /**
     * @brief showHighScores
     * Gets high scores and shows them.
     */
    void showHighScores();

    /**
     * @brief ToMainMenu
     * Goes back to main menu, from the high scores screen.
     */
    void ToMainMenu();

    /**
     * @brief EnterPlayerName
     * Gets player names, and ultimately starts the game.
     */
    void EnterPlayerName();

private:
    Ui::MainWindow *ui;
    Game* game_;

    int seed;
    int cardPairs;

    std::vector<QString> playerNames;

    std::vector<QLabel*> highScoreLabels;

    QPushButton* saveScoresButton_;

};
#endif // MAINWINDOW_HH
