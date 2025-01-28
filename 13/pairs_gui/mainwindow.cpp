#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "utilities.hh"
#include "card.hh"

#include <time.h>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect Buttons and Fields to their respective functions.
    // Line length is over 80 due to better readability.
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::closeProgram);

    // High score related.
    connect(ui->highScoresButton, &QPushButton::clicked, this, &MainWindow::showHighScores);
    connect(ui->toMainMenuButton, &QPushButton::clicked, this, &MainWindow::ToMainMenu);

    // Gameplay related.
    connect(ui->startGameButton, &QPushButton::clicked, this, &MainWindow::prepareGame);
    connect(ui->enterPlayerNameButton, &QPushButton::clicked, this, &MainWindow::EnterPlayerName);
    connect(ui->quitMainMenuButton, &QPushButton::clicked, this, &MainWindow::QuitToMainMenu);

    // Set window size.
    this->setFixedSize(700, 500);

    // Set window title
    this->setWindowTitle("## Pairs ##");
    // Range for player amount.
    ui->playerAmountSpinBox->setMaximum(MAXIMUM_PLAYER_AMOUNT);
    ui->playerAmountSpinBox->setMinimum(1);

    // Range for card pair amount.
    ui->cardPairAmountSpinBox->setMaximum(playingCards.size());
    ui->cardPairAmountSpinBox->setMinimum(5);

    // Seed value init from computer clock.
    srand(time(0));

    // Set to start from the main menu.
    ui->stackedWidget->setCurrentIndex(0);

    ui->gameBoardGrid->setSpacing(0);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeProgram()
{
    close();
}

void MainWindow::prepareGame()
{
    this->setFixedSize(400, 200);

    ui->stackedWidget->setCurrentIndex(1); // see -> EnterPlayerName()

    return;
}

void MainWindow::QuitToMainMenu()
{
    ui->stackedWidget->setCurrentIndex(0);

    // Reset.
    game_->clearBoard();
    game_->clearPlayers();

    playerNames.erase(playerNames.begin(), playerNames.end());
    ui->playerNameLabel->setText("Player "
                                 + QString::number(playerNames.size() + 1)
                                 + ":");

    delete game_;
}

void MainWindow::showHighScores()
{
    ui->stackedWidget->setCurrentIndex(3);

    // Top high scores.
    unsigned int amountOfPlayers = TOP_HIGH_SCORES;
    std::vector<std::vector<std::string>> topPlayers;

    // Get highest scores, and sort them from greatest to lowest.
    utilities::getHighScores(HIGH_SCORES, amountOfPlayers, topPlayers);

    // Add high scores to screen.
    for ( unsigned int i = 0; i < amountOfPlayers; i++ )
    {
        QString position = QString::number(i + 1) + ". ";

        // Not enough players to fill list.
        if ( i >= topPlayers.size() )
        {
            QLabel* playerLabel = new QLabel;
            ui->highScoreGrid->addWidget(playerLabel);
            playerLabel->setText(position);

            highScoreLabels.push_back(playerLabel);
            continue;
        }

        // Add player data.
        QString name = QString::fromStdString(topPlayers.at(i).at(0));
        QString highScore = QString::fromStdString(topPlayers.at(i).at(1));
        QString lifetimeScore = QString::fromStdString(topPlayers.at(i).at(2));

        QLabel* playerLabel = new QLabel;
        ui->highScoreGrid->addWidget(playerLabel);
        playerLabel->setText(position + name + " - " +
                             highScore + " - " + lifetimeScore);

        highScoreLabels.push_back(playerLabel);
    }

}

void MainWindow::ToMainMenu()
{
    ui->stackedWidget->setCurrentIndex(0);

    for ( QLabel* label : highScoreLabels )
    {
        delete label;
    }
    highScoreLabels.erase(highScoreLabels.begin(), highScoreLabels.end());
}

void MainWindow::EnterPlayerName()
{

    QString playerName = ui->playerNameLineEdit->text();
    playerNames.push_back(playerName);
    ui->playerNameLabel->setText("Player "
                                 + QString::number(playerNames.size() + 1)
                                 + ":");

    ui->playerNameLineEdit->setText("");

    if ( playerNames.size() != ui->playerAmountSpinBox->text().toUInt() )
    {
        return;
    }

    cardPairs = ui->cardPairAmountSpinBox->text().toInt();

    seed = rand()%1000;

    game_ = new Game(ui, cardPairs, playerNames, seed);

    saveScoresButton_ = new QPushButton;
    game_->setSaveScoresButton(saveScoresButton_);

    this->setFixedSize(700, 500);

    game_->startGame();

}
