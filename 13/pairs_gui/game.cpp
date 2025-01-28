#include "game.hh"
#include "utilities.hh"
#include "ui_mainwindow.h"

#include <random>
#include <QTimer>

Game::Game(Ui::MainWindow* ui, uint cardPairs, std::vector<QString> playerNames,
           int seed):
    ui_(ui), seed_(seed), cardPairs_(cardPairs), playerNames_(playerNames)
{

}

void Game::startGame()
{
    gameState_ = RUNNING;

    setPlayers();

    currentTurn_ = 0;
    updateLabels();

    initializeCards();
    shuffleCards();

    ui_->stackedWidget->setCurrentIndex(2);
}

void Game::endGame()
{
    // Future updates...
    // Show players' collected cards...
    // Create leaderboard...

    gameState_ = ENDED;
    updateLabels();
    getWinner();

    collectedCards_.erase(collectedCards_.begin(), collectedCards_.end());

    ui_->gameOptionGrid->addWidget(saveScoresButton_);
    saveScoresButton_->setText("Save High Scores");
    connect(saveScoresButton_, &QPushButton::clicked, this, &Game::saveScores);
}

void Game::setPlayers()
{
    for ( QString name : playerNames_ )
    {
        Player* player = new Player(name);
        players.push_back(player);
    }
}

void Game::clearPlayers()
{
    for ( Player* player : players )
    {
        delete player;
    }
    players.erase(players.begin(), players.end());
}

void Game::initializeCards()
{
    std::vector<int> dimensions = utilities::getClosestFactors(cardPairs_ * 2);
    columns_ = dimensions.at(0);
    rows_ = dimensions.at(1);

    for ( int y = 0; y < rows_; y++ )
    {

        for ( int x = 0; x < columns_; x++ )
        {

            Card* cardButton = new Card;

            cardButton->setFixedSize(70, 100);

            // Backside of card.
            cardButton->showImage("bicycle_back.png");

            connect(cardButton, &Card::clicked, this,
                    [=]() { this->twoCards(cardButton); });

            cardButton->setObjectName("cardButton_"
                                      + QString::number(x) + "_"
                                      + QString::number(y));

            ui_->gameBoardGrid->addWidget(cardButton, x, y);
            cardButtons.push_back(cardButton);
        }
    }
}

void Game::shuffleCards()
{
    std::default_random_engine randomEngine(seed_);
    std::uniform_int_distribution<int> locationDistr(0, rows_ * columns_ - 1);
    locationDistr(randomEngine);

    std::uniform_int_distribution<int> imageDistr(0, playingCards.size() - 1);

    int pairs = (columns_ * rows_) / 2;
    for ( int i = 0; i < pairs; i++ )
    {
        QString png = playingCards.at(imageDistr(randomEngine));

        for ( int j = 0; j < 2; j++ )
        {
            int card = locationDistr(randomEngine);
            card = nextFree(card);
            cardButtons.at(card)->setFrontImage(png);
            cardButtons.at(card)->setVisibility(HIDDEN);
        }
    }
}

int Game::nextFree(int start)
{
    for ( int i = start; i < rows_ * columns_ - 1; i++ )
    {
        if ( cardButtons.at(i)->getVisibility() == EMPTY )
        {
            return i;
        }
    }
    for ( int i = 0; i < rows_ * columns_ - 1; i++ )
    {
        if ( cardButtons.at(i)->getVisibility() == EMPTY )
        {
            return i;
        }
    }

    // Shouldn't end up here.
    return rows_ * columns_ - 1;
}

void Game::clearBoard()
{
    // Reset game board.
    int cards = (columns_ * rows_) - 1;
    for ( int i = 0; i < cards; i++ )
    {
        ui_->gameBoardGrid->removeWidget(cardButtons.back());
        delete cardButtons.back();
        cardButtons.pop_back();
    }
}

void Game::twoCards(Card* cardButton)
{
    // To disable a user's manic behaviour.
    // Only two cards can be shown at any given time.
    if ( turnedCards_.size() == 2 )
    {
        return;
    }

    if ( not cardButton->turn() )
    {
        // Card has already been collected.
        return;
    }

    turnedCards_.push_back(cardButton);

    if (turnedCards_.size() == 2)
    {
        if ( isPair() )
        {
            QTimer::singleShot(CARD_DELAY, this, SLOT(collectCards()));
            return;
        }
        QTimer::singleShot(CARD_DELAY, this, SLOT(resetTurnedCards()));
        // Update labels.
        if ( gameState_ == RUNNING )
        {
            QTimer::singleShot(UPDATE_DELAY, this, SLOT(updateLabels()));
        }
    }
}

bool Game::isPair()
{
    // Check pair.
    if ( turnedCards_.at(0)->getFrontImage() ==
         turnedCards_.at(1)->getFrontImage() )
    {
        ui_->pairMatchLabel->setText("Pair found.");

        // Continue player turn.
        return true;
    }
    // Cards aren't a pair.
    ui_->pairMatchLabel->setText("Pair not found.");

    // Next player's turn.
    ++currentTurn_;

    if ( currentTurn_ == players.size() )
    {
        currentTurn_ = 0;
    }
    return false;
}

void Game::getWinner()
{
    std::vector<Player*> winners;
    for ( unsigned int i = 0; i < players.size(); ++i )
    {
        if ( winners.empty() )
        {
            winners.push_back(players.at(i));
        }
        else if ( players.at(i)->numberOfPairs() > winners.at(0)->numberOfPairs() )
        {
            winners.erase(winners.begin(), winners.end());
            winners.push_back(players.at(i));
        }
        else if ( players.at(i)->numberOfPairs() == winners.at(0)->numberOfPairs() )
        {
            winners.push_back(players.at(i));
        }
    }

    if ( winners.size() == 1 )
    {
        ui_->playerTurnLabel->setText("Player " + winners.at(0)->getName()
                                      + " won!");

        ui_->playerPairCountLabel->setText("Player " + winners.at(0)->getName()
                                           + " found "
                                           + QString::number(winners.at(0)
                                                             ->numberOfPairs())
                                           + " pairs!");
    }
    else if ( winners.size() > 1 )
    {
        QString tieText = "It's a tie between; ";
        for ( Player* player : winners )
        {
            tieText += player->getName() + " ";
        }
        ui_->playerTurnLabel->setText(tieText);
        ui_->playerPairCountLabel->setText("Players tied with "
                                           + QString::number(winners.at(0)
                                                             ->numberOfPairs())
                                           + " pairs!");
    }
}

GameState Game::getGameState()
{
    return gameState_;
}

void Game::setSaveScoresButton(QPushButton*& saveScoresButton)
{
    saveScoresButton_ = saveScoresButton;
}

void Game::collectCards()
{
    turnedCards_.at(0)->removeFromGameBoard();
    turnedCards_.at(1)->removeFromGameBoard();

    // Add to player's collection.
    players.at(currentTurn_)->addCard(turnedCards_.at(0));
    players.at(currentTurn_)->addCard(turnedCards_.at(1));

    // Add to game's collected cards.
    collectedCards_.push_back(turnedCards_.at(0));
    collectedCards_.push_back(turnedCards_.at(1));

    // Clear <turnedCards_>.
    turnedCards_.erase(turnedCards_.begin(), turnedCards_.end());

    if ( collectedCards_.size() == cardPairs_ * 2 )
    {
        endGame();
    }
    // Update labels.
    if ( gameState_ == RUNNING )
    {
        QTimer::singleShot(UPDATE_DELAY, this, SLOT(updateLabels()));
    }
}

void Game::resetTurnedCards()
{
    for ( Card* card : turnedCards_ )
    {
        card->setVisibility(HIDDEN);
        card->showImage("bicycle_back.png");
    }
    // Clear <turnedCards_>.
    turnedCards_.erase(turnedCards_.begin(), turnedCards_.end());
}

void Game::updateLabels()
{
    Player* currentPlayer = players.at(currentTurn_);

    ui_->playerPairCountLabel->setText("Player " + currentPlayer->getName()
                                       + " has "
                                       + QString::number(currentPlayer
                                                         ->numberOfPairs())
                                       + " pairs.");

    if ( gameState_ == ENDED ) { return; }

    ui_->playerTurnLabel->setText("Player " + currentPlayer->getName()
                                  + "'s turn:");

    ui_->pairMatchLabel->setText("");
}

void Game::saveScores()
{
    utilities::saveToHighScoreFile(HIGH_SCORES, players);

    delete saveScoresButton_;
}
