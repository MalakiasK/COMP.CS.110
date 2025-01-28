#include "card.hh"

Card::Card():
    visibility_(EMPTY)
{

}

void Card::setFrontImage(const QString png)
{
    frontImage_ = png;
}

void Card::showImage(const QString png)
{
    QPixmap pixmap("Resources/PelikortitPNG/" + png);
    QIcon Icon;
    Icon.addPixmap(pixmap, QIcon::Normal, QIcon::Off);
    setIcon(Icon);
    setIconSize(QSize(100, 100));
}

void Card::setVisibility(const VisibilityType visibility)
{
    visibility_ = visibility;
}

QString Card::getFrontImage() const
{
    return frontImage_;
}

VisibilityType Card::getVisibility() const
{
    return visibility_;
}

bool Card::turn()
{
    if(visibility_ == HIDDEN)
    {
        visibility_ = OPEN;

        showImage(frontImage_);
        return true;
    }
    else if(visibility_ == OPEN)
    {
        visibility_ = HIDDEN;

        showImage(backImage_);
        return true;
    }
    else // if(visibility_ == EMPTY)
    {
        return false;
    }
}

void Card::removeFromGameBoard()
{
    visibility_ = EMPTY;
    showImage("");
}
