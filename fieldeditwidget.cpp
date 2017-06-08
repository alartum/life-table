#include "fieldeditwidget.h"
#include <QDebug>
#include <QSpinBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>

FieldEditWidget::FieldEditWidget(QWidget *parent) :
    QWidget(parent),
    mField (10, 10)
{
    // Соединяем сигнал выбора тайла с соответствующим слотом.
    connect(&mTileSelection, SIGNAL(tileBrushSelected(const Tile&)), &mField, SLOT (setTileBrush(const Tile&)));

    QLabel* width = new QLabel("Ширина");
    QLabel* height = new QLabel("Высота");
    QSpinBox* widthSpinBox = new QSpinBox;
    QSpinBox* heightSpinBox = new QSpinBox;
    widthSpinBox->setRange(1, 40);
    widthSpinBox->setValue(mField.modelWidth());
    heightSpinBox->setRange(1, 40);
    heightSpinBox->setValue(mField.modelHeight());
    QGridLayout* groupLayout = new QGridLayout;
    groupLayout->addWidget(width, 0, 0);
    groupLayout->addWidget(widthSpinBox, 0, 1);
    groupLayout->addWidget(height, 1, 0);
    groupLayout->addWidget(heightSpinBox, 1, 1);
    QGroupBox* sizeGroup = new QGroupBox("Изменение размера");
    sizeGroup->setLayout(groupLayout);

    QVBoxLayout* rightSide = new QVBoxLayout;
    QPushButton* clear = new QPushButton ("Очистить поле");
    QPushButton* tickButton = new QPushButton ("Тик!");

    mStartStopButton = new QPushButton ("Начали!");
    connect (mStartStopButton, SIGNAL (pressed()), &mField, SLOT (startSimulation()));
    connect (mStartStopButton, SIGNAL (pressed()), this, SLOT (createStop()));
    rightSide->addWidget(&mTileSelection);
    rightSide->addWidget(clear);
    rightSide->addWidget(tickButton);
    rightSide->addWidget(mStartStopButton);
    rightSide->addWidget(sizeGroup);
    // Разбираемся с положением этого всего в окне.
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(&mField);
    mainLayout->addLayout(rightSide);
    setLayout(mainLayout);
    setWindowTitle(tr("Life"));
    connect (widthSpinBox, SIGNAL(valueChanged(int)), &mField, SLOT(setWidth(int)));
    connect (heightSpinBox, SIGNAL(valueChanged(int)), &mField, SLOT(setHeight(int)));
    connect (clear, SIGNAL(pressed()), &mField, SLOT(clearField()));
    connect (tickButton, SIGNAL(pressed()), &mField, SLOT(tick()));
    // Добавляем некоторые тайлы.
    mTileSelection.addTile  ("palegreen", "Жизнь", 1);
    mTileSelection.addTile (Qt::white, "Пусто", 0);
}

FieldEditWidget::~FieldEditWidget()
{
    delete mStartStopButton;
}

void FieldEditWidget::createStart()
{
    mStartStopButton->disconnect();
    mStartStopButton->setText("Начали!");
    connect (mStartStopButton, SIGNAL (pressed()), &mField, SLOT (startSimulation()));
    connect (mStartStopButton, SIGNAL (pressed()), this, SLOT (createStop()));
}

void FieldEditWidget::createStop()
{
    mStartStopButton->disconnect();
    mStartStopButton->setText("Закончили!");
    connect (mStartStopButton, SIGNAL (pressed()), &mField, SLOT (stopSimulation()));
    connect (mStartStopButton, SIGNAL (pressed()), this, SLOT (createStart()));
}
