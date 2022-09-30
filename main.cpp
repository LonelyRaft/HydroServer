
#include "main.h"

MainWindow::MainWindow() : QMainWindow()
{
    mSplitter.setLayoutDirection(Qt::LayoutDirection::LeftToRight);
    mSplitter.addWidget(&mTree);
    // mTabSlave.addTab(&mSlaveDemo, "demo");
    mSplitter.addWidget(&mTabSlave);
    setCentralWidget(&mSplitter);
}

MainWindow::~MainWindow()
{
}
