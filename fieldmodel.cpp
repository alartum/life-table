#include <QColor>
#include <QSize>
#include <QDebug>
#include "fieldmodel.h"

FieldModel::FieldModel (int height, int width, int tickDelay, QObject *parent) :
    QAbstractTableModel (parent),
    mTickDelay (tickDelay)
{
    createField(height, width);
    fillField(0, Qt::white);
    connect (&mLifeTimer, SIGNAL(timeout()), this, SLOT(tickField()));
}

void FieldModel::deleteField()
{
    // Если массив пуст, то не удаляем.
    if (mField== 0)
        return;
    // Очищаем память.
    for (int i = 0; i < mFieldHeight; ++i) {
        delete[] mField[i];
        mField[i] = 0;
        delete[] mCashField[i];
        mCashField[i] = 0;
    }
    delete[] mField;
    delete[] mCashField;
    mField = 0;
    mCashField = 0;
    // Новые размеры поля.
    mFieldHeight = 0;
    mFieldWidth = 0;
}

void FieldModel::createField(int height, int width)
{
    // Меняем размеры поля.
    mFieldHeight = height;
    mFieldWidth = width;

    // Заново выделяем память.
    mField = new Tile* [mFieldHeight];
    mCashField = new Tile* [mFieldHeight];

    for(int i = 0; i < mFieldHeight; ++i) {
        mField[i] = new Tile [mFieldWidth];
        mCashField[i] = new Tile [mFieldWidth];
    }
}

void FieldModel::resize(int height, int width)
{
    // Удаляем старое поле.
    deleteField();
    // Создаём новое.
    createField(height, width);
    fillField(0, Qt::white);

    QModelIndex topLeft, bottomRight;
    topLeft = createIndex(0, 0);
    bottomRight = createIndex(height - 1, width - 1);
    emit dataChanged(topLeft, bottomRight);
    emit fieldResized(height, width);
}

QVariant FieldModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    Tile currentTile = mField [index.row()][index.column()];
    switch (role)
    {
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
        break;
    case Qt::BackgroundRole:
        return currentTile.color();
        break;
    default:
        return QVariant();
    }
}

int FieldModel::rowCount(const QModelIndex & /* parent */) const
{
    return mFieldHeight;
}

int FieldModel::columnCount(const QModelIndex & /* parent */) const
{
    return mFieldWidth;
}

QVariant FieldModel::headerData(int /* section */,
                                Qt::Orientation /* orientation */,
                                int role) const
{
    if (role == Qt::SizeHintRole)
        return QSize(1, 1);
    return QVariant();
}

void FieldModel::setTile (const Tile &tile, int row, int column)
{
    // Записываем новый.
    mField[row][column] = tile;
    mCashField[row][column] = tile;

    QModelIndex indexOfChanges;

    dataChanged(indexOfChanges, indexOfChanges);
}

void FieldModel::setTile (int type, const QColor& color, int row, int column)
 {

    Tile tileToAdd(type, color);
    setTile (tileToAdd, row, column);
 }

int FieldModel::height()
 {
     return mFieldHeight;
 }

int FieldModel::width ()
 {
     return mFieldWidth;
 }

FieldModel::~FieldModel()
{
    deleteField();
}

void FieldModel::fillField(const Tile &tile)
{
    beginResetModel();
    for (int i = 0; i < mFieldHeight; ++i) {
        for (int j = 0; j < mFieldWidth; ++j) {
            setTile(tile, i, j);
        }
    }
    endResetModel();
}

void FieldModel::fillField(int type, const QColor &color)
{
    Tile tile(type, color);

    fillField(tile);
}

void FieldModel::clearField()
{
    fillField(0, Qt::white);
    stopSimulationField();
}

void FieldModel::tickField()
{
    beginResetModel();
    for (int i = 0; i < mFieldHeight; ++i) {
        for (int j = 0; j < mFieldWidth; ++j) {
            updateTile(i, j);
        }
    }
    endResetModel();
    for (int i = 0; i < mFieldHeight; ++i) {
        for (int j = 0; j < mFieldWidth; ++j) {
            mCashField[i][j] = mField[i][j];
        }
    }
}

void FieldModel::updateTile (int row, int column)
{
    int neighbours = countNeighbours(row, column);
    Tile cell = mField[row][column];

    if (cell.type() == 0)
    {
        if (neighbours == 3)
        {
            Tile newCell (1, "palegreen");
            mField[row][column] = newCell;
        }
    }
    else
    {
        if (neighbours < 3 || neighbours > 4)
        {
            Tile newCell (0, Qt::white);
            mField[row][column] = newCell;
        }
    }
}

int FieldModel::countNeighbours (int row, int column)
{
    int counter = 0;

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int newRow =    (row + i < 0)? row + i + mFieldHeight: (row + i) % mFieldHeight,
            newColumn = (column + j < 0)? column + j + mFieldWidth: (column + j) % mFieldWidth;

            Tile cell = mCashField[newRow][newColumn];
            if (cell.type() == 1)
                counter++;
        }
    }

    return counter;
}

void FieldModel::startSimulationField()
{
    mLifeTimer.start(100);
}

void FieldModel::stopSimulationField()
{
    mLifeTimer.stop();
}

void FieldModel::setDelay(float seconds)
{
    mTickDelay = (int) seconds * 1000;
}
