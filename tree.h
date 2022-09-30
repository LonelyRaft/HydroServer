
#ifndef _Tree_H
#define _Tree_H

#include <qpushbutton.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include <qtreeview.h>
#include <qstandarditemmodel.h>
#include <qtcpsocket.h>
#include <qtoolbar.h>
#include "tcpsvr.h"

class Tree : public QWidget
{
public:
    explicit Tree(QWidget *parent = 0);
    virtual ~Tree();

public slots:
    void addSlave(QTcpSocket *socket);
    void newServer();

private:
    QVBoxLayout mLayout;
    // tool bar
    QHBoxLayout mTools;
    QLabel mName;
    QPushButton mNew;
    QPushButton mExpand;
    QPushButton mCollapse;

    TcpServer *mMaster;
    QPushButton mStart;
    QPushButton mStop;
    QPushButton mDebug;
    QGridLayout mGrid;
    // tree
    QTreeView mTree;
    QStandardItemModel mModel;
};

#endif // _Tree_H
