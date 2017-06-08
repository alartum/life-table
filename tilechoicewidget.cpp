#include "tilechoicewidget.h"
#include <QHeaderView>
#include <QDebug>

TileChoiceWidget::TileChoiceWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this, SLOT(handleNewSelection(QTreeWidgetItem*,QTreeWidgetItem*)));
    setColumnCount(3);

    QStringList list;

    list << "Название" << "Цвет" << "Тип";
    setHeaderLabels(list);
    // Ставим режим выбора: одновременно может быть выбран лишь 1 тайл.
    setSelectionMode(QAbstractItemView::SingleSelection);
    for (int i = 0; i < 3; ++i) {
        // Ставим выравнивание по центру.
        headerItem()->setTextAlignment(i, Qt::AlignCenter);
        // Расширяем колонки под содержимое.
        resizeColumnToContents(i);
    }
    // Устанавливаем размер.
    setFixedWidth(200);
}

void TileChoiceWidget::addTile(const QColor &color, const QString &name, int type)
{
    // Новый тайл.
    QTreeWidgetItem* item = new QTreeWidgetItem;

    // Новое имя.
    item->setData(0, Qt::DisplayRole, name);
    // Пишем новый цвет.
    item->setData(1, Qt::BackgroundRole, QBrush(color));
    // И новый тип.
    item->setData(2, Qt::DisplayRole, type);
    item->setData (0, Qt::TextAlignmentRole, Qt::AlignCenter);

    // Делаем его активным с возможностью выбора.
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    // Выравниваем по центру 2 и 3 колонки.
    for (int i = 0; i < 3; ++i)
        item->setTextAlignment(i, Qt::AlignCenter);
    // Добавляем к проходимым тайлам.
    addTopLevelItem(item);
    // Имя может быть длинным, так что расширяем, если требуется, первый столбец.
    resizeColumnToContents(0);
}

void TileChoiceWidget::handleNewSelection(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    // Забираем даные.
    int type;

    type = current->data(2, Qt::DisplayRole).toInt();
    // Забираем цвет через конвертацию в QBrush, а оттуда - в QColor.
    // Цвет тайла.
    QColor color = current->data(1, Qt::BackgroundRole).value<QBrush>().color();
    Tile tileToSend (type, color);
    // Отправляем сигнал.
    emit tileBrushSelected(tileToSend);
}

TileChoiceWidget::~TileChoiceWidget ()
{
}
