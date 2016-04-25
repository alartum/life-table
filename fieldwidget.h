#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QTableView>
#include "fieldmodel.h"

class FieldWidget : public QTableView
{
    Q_OBJECT
public:
    explicit FieldWidget(int height = 5, int width = 5, QWidget *parent = 0);
    ~FieldWidget();
    int modelWidth();
    int modelHeight();
private:
    FieldModel mModel;
    // Тайл-кисть, которым красим поле.
    Tile mTileBrush;
    // Размер ячейки поля.
    int mTileHeight;
    int mTileWidth;
    int mMaxHeight;
    int mMaxWidth;
public slots:
    // Начинаем симуляцию
    void startSimulation();
    // Прекращаем симуляцию
    void stopSimulation();
    void clearField ();
    void tick();
    void resizeField (int height, int width);
    void setHeight (int height);
    void setWidth (int width);
    void setTileBrush (const Tile& tileBrush);
private slots:
    // Обновляем тайл по индексу.
    void updateField (QModelIndex index);
    // Обновляем размеры отображения.
    void updateSize (int height, int width);
};

#endif // FIELDWIDGET_H
