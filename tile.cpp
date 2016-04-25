#include "tile.h"
#include <QDebug>

Tile::Tile(int type, QColor color)
    : mColor(color),
      mType(type)
{
    // Выставляем цвет.
    switch (mType)
    {
    case 1:
        mColor = QColor("palegreen");
        break;
    case 0:
        mColor = Qt::white;
    }
}
void Tile::setType(int type)
{
    mType = type;
}

int Tile::type() const
{
    return mType;
}

QColor Tile::color() const
{
    return mColor;
}

Tile& Tile::operator = (const Tile& tile)
{
    mType = tile.type();
    mColor = tile.color();

    return *this;
}

