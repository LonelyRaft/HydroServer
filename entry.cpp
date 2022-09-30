
#include <qapplication.h>
#include "main.h"
#include "tree.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // MainWindow mWindow;
    // mWindow.show();
    Tree tree;
    tree.show();
    return app.exec();
}