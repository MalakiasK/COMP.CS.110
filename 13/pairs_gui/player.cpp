#include "player.hh"

Player::Player(const QString& name):
    name_(name), cards_(0)
{

}

QString Player::getName() const
{
    return name_;
}

unsigned int Player::numberOfPairs() const
{
    if ( cards_ == 0 ) { return 0; }
    return cards_ / 2;
}

void Player::addCard(Card* card)
{
    cards_ += 1;
    collectedCards_.push_back(card);
}
