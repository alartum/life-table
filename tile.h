#ifndef TILE_H
#define TILE_H

#include <QColor>

class Tile
{
public:
    explicit Tile (int type = 0, QColor color = Qt::white);
    void setType(int type);
    int type() const;
    QColor color() const;
    Tile& operator = (const Tile& tile);
private:
    // Цвет данного тайла (впоследствии возможно использование текстур).
    QColor mColor;
    // Тип тайла: 1, если живой. 0 - в противном случае.
    int mType;
};

#endif // TILE_H
