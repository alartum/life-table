#include "fieldeditwidget.h"
#include "fieldmodel.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FieldEditWidget w;
    w.show();
    return a.exec();
}
