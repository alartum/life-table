#ifndef FIELDEDITWIDGET_H
#define FIELDEDITWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "fieldwidget.h"
#include "tilechoicewidget.h"

class FieldEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FieldEditWidget(QWidget *parent = 0);
    ~FieldEditWidget();
private:
    FieldWidget mField;
    TileChoiceWidget mTileSelection;
    QPushButton *mStartStopButton;
signals:
    void clearButtonPressed();
private slots:
    void createStart ();
    void createStop ();
};

#endif // FIELDEDITWIDGET_H
