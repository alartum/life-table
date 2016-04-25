#ifndef FIELDMODEL_H
#define FIELDMODEL_H

#include <QAbstractTableModel>
#include "tile.h"
#include <QTimer>

class FieldModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FieldModel(int height = 1, int width = 1, int tickDelay = 200, QObject *parent = 0);
    ~FieldModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    // Очищаем память, выделенную под поле.
    void deleteField ();
    // Выделяем память на новое поле.
    void createField (int height, int width);
    // Установить новый тайл на позицию (row; column).
    void setTile (const Tile& tile, int row, int column);
    // Перегруженная функция установки тайла для удобства.
    void setTile (int type, const QColor& color, int row, int column);
    //Говорим высоту
    int height();
    //Говорим ширину
    int width ();
    // Изменить размеры поля.
    void resize (int height, int width);
    // Заполняем поле данным тайлом
    void fillField (const Tile& tile);
    // Заполняем поле тайлом с данными параметрами
    void fillField (int type, const QColor& color);
    // Очищаем поле
    void clearField ();

    // Начинаем симуляцию
    void startSimulationField();
    // Прекращаем симуляцию
    void stopSimulationField();
public slots:
    // Полностью обновляем поле
    void tickField();
    // Устанавливаем задержку
    void setDelay (float seconds);
private:
    // Высота поля в ячейках.
    int mFieldHeight;
    // Ширина поля в ячейках.
    int mFieldWidth;
    // Матрица, представляющая поле: каждый тайл характеризуется
    Tile** mField;
    // Матрица с предыдущего шага
    Tile** mCashField;
    // Тикает, вызывая обновления
    QTimer mLifeTimer;
    // Время, через которое повторяется тик
    int mTickDelay;

    // Обновляем данную клеточку
    void updateTile (int row, int column);
    // Считаем соседей данной клетки
    int countNeighbours(int row, int column);
signals:
    void fieldResized(int height, int width);
};

#endif // FIELDMODEL_H
