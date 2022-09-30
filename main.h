
#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H

#include <qmainwindow.h>
#include <qsplitter.h>
#include <qtabwidget.h>
#include "tree.h"

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow();
    virtual ~MainWindow();

private:
    QSplitter mSplitter;
    Tree mTree;
    QTabWidget mTabSlave;
};

#endif // _MAIN_WINDOW_H
