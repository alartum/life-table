#include "fieldwidget.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>

FieldWidget::FieldWidget(int height, int width, QWidget *parent) :
    QTableView(parent),
    mTileBrush(-1),
    mMaxHeight(700),
    mMaxWidth(700)
{
    // Изменяем внешний вид отображения.
    setShowGrid(false);
    horizontalHeader()->hide();
    verticalHeader()->hide();
    setModel(&mModel);
    resizeField (height, width);
    setSelectionMode(QAbstractItemView::NoSelection);
    setShowGrid(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Устанавливаем размер.
    updateSize(mModel.columnCount(), mModel.rowCount());
    // Связываем сигналы/слоты.
    connect(this, SIGNAL(entered(QModelIndex)), this, SLOT(updateField(QModelIndex)));
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(updateField(QModelIndex)));
    connect(&mModel, SIGNAL(fieldResized(int,int)), this, SLOT(updateSize(int,int)));
}

void FieldWidget::resizeField(int height, int width)
{
    mTileWidth = mMaxWidth / width;
    mTileHeight = mMaxHeight / height;
    mModel.resize(height, width);
}
void FieldWidget::setTileBrush(const Tile& tileBrush)
{
    // Устанавливаем новую.
    mTileBrush = tileBrush;
}

void FieldWidget::setHeight (int height)
{
    mTileHeight = mMaxHeight / height;
    mModel.resize(height, mModel.width());
}

void FieldWidget::setWidth (int width)
{
    mTileWidth = mMaxWidth / width;
    mModel.resize(mModel.height(), width);
}

void FieldWidget::updateSize(int height, int width)
{
    int adjust = 2;

    horizontalHeader()->setDefaultSectionSize(mTileWidth);
    verticalHeader()->  setDefaultSectionSize(mTileHeight);
    setFixedSize(width  * mTileWidth + adjust,
                 height * mTileHeight + adjust);
}

void FieldWidget::updateField(QModelIndex index)
{
    if (mTileBrush.type() == -1) {
        QMessageBox::warning(0, "Ошибка", "Не задан тип ячейки для изменения.");
        return;
    }
    Tile newTile(mTileBrush.type(),
                 mTileBrush.color());
    mModel.setTile(newTile,
                   index.row(),
                   index.column());
    update(index);
}

FieldWidget::~FieldWidget()
{
}

void FieldWidget::clearField()
{
    mModel.clearField();
}

void FieldWidget::tick()
{
    mModel.tickField();
}

void FieldWidget::startSimulation()
{
    mModel.startSimulationField();
}

void FieldWidget::stopSimulation()
{
    mModel.stopSimulationField();
}

int FieldWidget::modelWidth()
{
    return mModel.width();
}

int FieldWidget::modelHeight()
{
    return mModel.height();
}
