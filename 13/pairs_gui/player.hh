/* Taken from the earlier project and modified to suit the program's needs.
 */

#ifndef PLAYER_HH
#define PLAYER_HH

#include "card.hh"

class Player
{
public:

    /**
     * @brief Player
     * @param name
     * Constructor: creates a player with the given name and zero cards.
     */
    Player(const QString& name);

    /**
     * @brief getName
     * @return Returns the name of the player.
     */
    QString getName() const;

    /**
     * @brief numberOfPairs
     * @return Returns the number of pairs collected by the player so far.
     */
    unsigned int numberOfPairs() const;

    /**
     * @brief addCard
     * @param card, to be added
     * Moves the given card from the game board to the player,
     * i.e. inserts it to the collected cards of the player.
     */
    void addCard(Card* card);

private:

    QString name_;
    int cards_;

    // What cards are collected.
    std::vector<Card*> collectedCards_;

};

#endif // PLAYER_HH
