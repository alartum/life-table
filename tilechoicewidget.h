#ifndef TILECHOICEWIDGET_H
#define TILECHOICEWIDGET_H

#include <QTreeWidget>
#include "tile.h"

class TileChoiceWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit TileChoiceWidget(QWidget *parent = 0);
    ~TileChoiceWidget();
    void addTile   (const QColor& color, const QString& name, int type);
private slots:
    // Обработка нового выделенного участка и отправка сигнала
    // tileBrushSelected
    void handleNewSelection(QTreeWidgetItem* current, QTreeWidgetItem* previous);
signals:
    // Возвращаем цвет и тип тайла.
    void tileBrushSelected(const Tile& tileBrush);
};

#endif // TILECHOICEWIDGET_H
