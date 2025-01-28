/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionInstructions;
    QAction *actionQuit;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *mainMenu;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *highScoresButton;
    QSpinBox *playerAmountSpinBox;
    QSpinBox *cardPairAmountSpinBox;
    QLabel *label_2;
    QLabel *label;
    QPushButton *startGameButton;
    QPushButton *exitButton;
    QLabel *label_3;
    QWidget *page;
    QLabel *label_5;
    QLabel *playerNameLabel;
    QLineEdit *playerNameLineEdit;
    QPushButton *enterPlayerNameButton;
    QWidget *gameBoard;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gameOptionGrid;
    QPushButton *quitMainMenuButton;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gameBoardGrid;
    QLabel *playerTurnLabel;
    QLabel *playerPairCountLabel;
    QLabel *pairMatchLabel;
    QWidget *highScoresPage;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QPushButton *toMainMenuButton;
    QPushButton *clearScoresButton;
    QWidget *gridLayoutWidget_5;
    QGridLayout *highScoreGrid;
    QLabel *label_6;
    QMenuBar *menubar;
    QMenu *menuGame;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(710, 484);
        actionInstructions = new QAction(MainWindow);
        actionInstructions->setObjectName(QString::fromUtf8("actionInstructions"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 691, 431));
        mainMenu = new QWidget();
        mainMenu->setObjectName(QString::fromUtf8("mainMenu"));
        gridLayoutWidget = new QWidget(mainMenu);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(50, 40, 591, 331));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        highScoresButton = new QPushButton(gridLayoutWidget);
        highScoresButton->setObjectName(QString::fromUtf8("highScoresButton"));

        gridLayout->addWidget(highScoresButton, 4, 1, 1, 1);

        playerAmountSpinBox = new QSpinBox(gridLayoutWidget);
        playerAmountSpinBox->setObjectName(QString::fromUtf8("playerAmountSpinBox"));

        gridLayout->addWidget(playerAmountSpinBox, 2, 1, 1, 1);

        cardPairAmountSpinBox = new QSpinBox(gridLayoutWidget);
        cardPairAmountSpinBox->setObjectName(QString::fromUtf8("cardPairAmountSpinBox"));

        gridLayout->addWidget(cardPairAmountSpinBox, 3, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAutoFillBackground(false);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 2);

        startGameButton = new QPushButton(gridLayoutWidget);
        startGameButton->setObjectName(QString::fromUtf8("startGameButton"));
        startGameButton->setEnabled(true);

        gridLayout->addWidget(startGameButton, 4, 0, 1, 1);

        exitButton = new QPushButton(gridLayoutWidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));

        gridLayout->addWidget(exitButton, 5, 0, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        stackedWidget->addWidget(mainMenu);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label_5 = new QLabel(page);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(100, 40, 201, 20));
        playerNameLabel = new QLabel(page);
        playerNameLabel->setObjectName(QString::fromUtf8("playerNameLabel"));
        playerNameLabel->setGeometry(QRect(100, 90, 63, 20));
        playerNameLineEdit = new QLineEdit(page);
        playerNameLineEdit->setObjectName(QString::fromUtf8("playerNameLineEdit"));
        playerNameLineEdit->setGeometry(QRect(170, 90, 113, 28));
        enterPlayerNameButton = new QPushButton(page);
        enterPlayerNameButton->setObjectName(QString::fromUtf8("enterPlayerNameButton"));
        enterPlayerNameButton->setGeometry(QRect(310, 90, 51, 28));
        stackedWidget->addWidget(page);
        gameBoard = new QWidget();
        gameBoard->setObjectName(QString::fromUtf8("gameBoard"));
        gridLayoutWidget_2 = new QWidget(gameBoard);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(50, 370, 301, 51));
        gameOptionGrid = new QGridLayout(gridLayoutWidget_2);
        gameOptionGrid->setObjectName(QString::fromUtf8("gameOptionGrid"));
        gameOptionGrid->setContentsMargins(0, 0, 0, 0);
        quitMainMenuButton = new QPushButton(gridLayoutWidget_2);
        quitMainMenuButton->setObjectName(QString::fromUtf8("quitMainMenuButton"));

        gameOptionGrid->addWidget(quitMainMenuButton, 0, 0, 1, 1);

        gridLayoutWidget_4 = new QWidget(gameBoard);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(50, 60, 591, 301));
        gameBoardGrid = new QGridLayout(gridLayoutWidget_4);
        gameBoardGrid->setObjectName(QString::fromUtf8("gameBoardGrid"));
        gameBoardGrid->setContentsMargins(0, 0, 0, 0);
        playerTurnLabel = new QLabel(gameBoard);
        playerTurnLabel->setObjectName(QString::fromUtf8("playerTurnLabel"));
        playerTurnLabel->setGeometry(QRect(50, 10, 411, 20));
        playerPairCountLabel = new QLabel(gameBoard);
        playerPairCountLabel->setObjectName(QString::fromUtf8("playerPairCountLabel"));
        playerPairCountLabel->setGeometry(QRect(50, 30, 411, 20));
        pairMatchLabel = new QLabel(gameBoard);
        pairMatchLabel->setObjectName(QString::fromUtf8("pairMatchLabel"));
        pairMatchLabel->setGeometry(QRect(540, 30, 101, 20));
        stackedWidget->addWidget(gameBoard);
        highScoresPage = new QWidget();
        highScoresPage->setObjectName(QString::fromUtf8("highScoresPage"));
        gridLayoutWidget_3 = new QWidget(highScoresPage);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(29, 310, 641, 80));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        toMainMenuButton = new QPushButton(gridLayoutWidget_3);
        toMainMenuButton->setObjectName(QString::fromUtf8("toMainMenuButton"));

        gridLayout_3->addWidget(toMainMenuButton, 0, 0, 1, 1);

        clearScoresButton = new QPushButton(gridLayoutWidget_3);
        clearScoresButton->setObjectName(QString::fromUtf8("clearScoresButton"));
        clearScoresButton->setEnabled(false);

        gridLayout_3->addWidget(clearScoresButton, 0, 1, 1, 1);

        gridLayoutWidget_5 = new QWidget(highScoresPage);
        gridLayoutWidget_5->setObjectName(QString::fromUtf8("gridLayoutWidget_5"));
        gridLayoutWidget_5->setGeometry(QRect(29, 39, 641, 251));
        highScoreGrid = new QGridLayout(gridLayoutWidget_5);
        highScoreGrid->setObjectName(QString::fromUtf8("highScoreGrid"));
        highScoreGrid->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(highScoresPage);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 10, 261, 20));
        stackedWidget->addWidget(highScoresPage);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 710, 25));
        menuGame = new QMenu(menubar);
        menuGame->setObjectName(QString::fromUtf8("menuGame"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuGame->menuAction());
        menuGame->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), exitButton, SLOT(click()));

        stackedWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionInstructions->setText(QCoreApplication::translate("MainWindow", "Instructions", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        highScoresButton->setText(QCoreApplication::translate("MainWindow", "Show High Scores", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Amount of Players:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Memory Match Game (Pairs)", nullptr));
        startGameButton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Amount of Card Pairs:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Please enter player names:", nullptr));
        playerNameLabel->setText(QCoreApplication::translate("MainWindow", "Player 1:", nullptr));
        enterPlayerNameButton->setText(QCoreApplication::translate("MainWindow", "Enter", nullptr));
        quitMainMenuButton->setText(QCoreApplication::translate("MainWindow", "Quit to Main Menu", nullptr));
        playerTurnLabel->setText(QCoreApplication::translate("MainWindow", "Player 1's turn:", nullptr));
        playerPairCountLabel->setText(QCoreApplication::translate("MainWindow", "Player <name> has pairs.", nullptr));
        pairMatchLabel->setText(QCoreApplication::translate("MainWindow", "Pair not found", nullptr));
        toMainMenuButton->setText(QCoreApplication::translate("MainWindow", "Main Menu", nullptr));
        clearScoresButton->setText(QCoreApplication::translate("MainWindow", "Clear High Scores", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "#. Name - High Score - Lifetime Score", nullptr));
        menuGame->setTitle(QCoreApplication::translate("MainWindow", "Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
