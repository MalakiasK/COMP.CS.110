/* Memory game
 *
 * Description:
 *
 * This program is a memory game. It can have ranging amounts of playing cards
 * and players. Card locations are randomized by using the computer clock to
 * generate a seed. Players take turns to try and find a pair. If a pair is
 * found, tose cards are added to that player's score and they can continue
 * turning cards. When a player can't find a pair, turn changes to the next
 * player. The winner(s) is/are the player(s) with the most found pairs.
 * So, the game can even possibly end in a tie.
 *
 * Ohjelman kirjoittaja:
 *
 * Nimi: Malakias Kosonen
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * Ohjelmassa on muutamia lainattuja funktioita kurssin aikaisemmista
 * projekteista, kuten split()-funktio. Luokat Card ja Player ovat
 * lainattu aikaisemmista projekteista, muuta niitä on modifioitu huomattavasti.
 * */

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
