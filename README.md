# life-table
The well-known Conway's Game of Life in QTableView shell.

## Info
This app was written to show a non-usual usage of [Qt Model/View Programming](http://doc.qt.io/qt-4.8/model-view-programming.html). Briefly, the architecture is like this:


| Super Class | Subclass | Info |
| --- | --- | --- |
| *QAbstractTableModel* | *FieldModel* | The model which represents the game field and provides interfaces to obtain the information about itself. Its data can be treated in many different ways by different views. |
| *QTableView* | *FieldWidget* | View of the model. It represents the data of *FieldModel* as a set of colored cells. |


## Dependences
*Qt5*  libraries are needed. You can install them by:
``` bash
 sudo apt-get install qt5-default
```

If you still receive an error, installation of *qt-sdk* may fix it:
``` bash
sudo apt-get install qt-sdk
```
 
Then you may need to **reinstall** *qt5-default*, as *qt-sdk* replaces qt5 libraries with the qt4 ones. So run it again: 
``` bash
sudo apt-get install qt5-default
```

## Build
Run in the project's directory:
``` bash
qmake
make all
```
