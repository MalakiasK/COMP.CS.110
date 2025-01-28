/* Taken from the earlier project and modified to suit the program's needs.
 */

#ifndef CARD_HH
#define CARD_HH

#include <vector>
#include <QPushButton>

enum VisibilityType {OPEN, HIDDEN, EMPTY};
const char HIDDEN_CHAR = '#';
const char EMPTY_CHAR = '.';

// Playing card images' names in the <Resources/PelikortitPNG> directory.
// Can be improved with directory reading...
const std::vector<QString> playingCards = {
                                "2_of_clubs.png", "2_of_diamonds.png",
                                "2_of_hearts.png", "2_of_spades.png",
                                "3_of_clubs.png", "3_of_diamonds.png",
                                "3_of_hearts.png", "3_of_spades.png",
                                "4_of_clubs.png", "4_of_diamonds.png",
                                "4_of_hearts.png", "4_of_spades.png",
                                "5_of_clubs.png", "5_of_diamonds.png",
                                "5_of_hearts.png", "5_of_spades.png",
                                "6_of_clubs.png", "6_of_diamonds.png",
                                "6_of_hearts.png", "6_of_spades.png",
                                "7_of_clubs.png", "7_of_diamonds.png",
                                "7_of_hearts.png", "7_of_spades.png",
                                "8_of_clubs.png", "8_of_diamonds.png",
                                "8_of_hearts.png", "8_of_spades.png",
                                "9_of_clubs.png", "9_of_diamonds.png",
                                "9_of_hearts.png", "9_of_spades.png",
                                "10_of_clubs.png", "10_of_diamonds.png",
                                "10_of_hearts.png", "10_of_spades.png",
                                "ace_of_clubs.png", "ace_of_diamonds.png",
                                "ace_of_hearts.png", "ace_of_spades.png",
                                "jack_of_clubs2.png", "jack_of_diamonds2.png",
                                "jack_of_hearts2.png", "jack_of_spades2.png",
                                "queen_of_clubs2.png", "queen_of_diamonds2.png",
                                "queen_of_hearts2.png", "queen_of_spades2.png",
                                "king_of_clubs2.png", "king_of_diamonds2.png",
                                "king_of_hearts2.png", "king_of_spades2.png"
};

class Card : public QPushButton
{
public:

    // Default constructor: creates an empty card.
    Card();

    /**
     * @brief setFrontImage
     * @param png, filename of the .png
     * Sets the card face for the card.
     */
    void setFrontImage(const QString png);

    /**
     * @brief showImage
     * @param png, filename of the .png
     * Changes the card's image -> backside or frontside.
     */
    void showImage(const QString png);

    /**
     * @brief setVisibility
     * @param visibility
     */
    void setVisibility(const VisibilityType visibility);

    /**
     * @brief getFrontImage
     * @return filename, .png
     * Used to check for matching pairs.
     */
    QString getFrontImage() const;

    /**
     * @brief getVisibility
     * @return visibility
     */
    VisibilityType getVisibility() const;

    /**
     * @brief turn
     * @return bool, if card was turned.
     * Turns the card -> changes image on the card.
     */
    bool turn();

    /**
     * @brief removeFromGameBoard
     * Removes a card from the game board: changes the visibility to empty.
     */
    void removeFromGameBoard();

private:

    VisibilityType visibility_;

    const QString backImage_ = "bicycle_back.png";
    QString frontImage_;
};

#endif // CARD_HH
