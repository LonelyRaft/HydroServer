
#include "tree.h"
#include <qdialog.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qhostinfo.h>

Tree::Tree(QWidget *parent) : QWidget(parent)
{
    // setup ui
    mName.setText("链接树");
    mNew.setText("新建");
    mExpand.setText("展开");
    mCollapse.setText("收起");
    mTools.addWidget(&mName);
    mTools.addWidget(&mNew);
    mTools.addWidget(&mExpand);
    mTools.addWidget(&mCollapse);
    mTree.setModel(&mModel);
    mLayout.addLayout(&mTools);
    mLayout.addWidget(&mTree);

    setLayout(&mLayout);
    // bind signal and slots
    connect(&mNew, &QPushButton::clicked, this, &Tree::newServer);
    connect(&mExpand, &QPushButton::clicked, &mTree, &QTreeView::expandAll);
    connect(&mCollapse, &QPushButton::clicked, &mTree, &QTreeView::collapseAll);
}

Tree::~Tree()
{
}

void Tree::newServer()
{
    QDialog dlgNewServer;
    QVBoxLayout vbxLayout;
    QComboBox cbProtocol;
    QLineEdit edtPort;
    QPushButton btnOkay;
    dlgNewServer.setWindowTitle("新建");
    edtPort.setPlaceholderText("服务器端口号");
    btnOkay.setText("确定");
    vbxLayout.addWidget(&cbProtocol);
    vbxLayout.addWidget(&edtPort);
    vbxLayout.addWidget(&btnOkay);
    connect(&btnOkay, &QPushButton::clicked,
            &dlgNewServer, &QDialog::accept);
    dlgNewServer.setLayout(&vbxLayout);
    if (dlgNewServer.exec() == QDialog::Accepted)
    {
        TcpServer *server =
            new TcpServer(edtPort.text().toUShort());
        connect(server, &TcpServer::getConnection, this, &Tree::addSlave);
        QString name = QString("%1:%2")
                           .arg(QHostInfo::localHostName())
                           .arg(edtPort.text());
        QStandardItem *item = new QStandardItem(name);
        mModel.appendRow(item);
    }
}

void Tree::addSlave(QTcpSocket *socket)
{
    TcpServer *server = qobject_cast<TcpServer *>(sender());
    QString name = QString("%1:%2")
                       .arg(socket->peerAddress().toString())
                       .arg(socket->peerPort());
    QStandardItem *item = new QStandardItem(name);
    for (int idx = 0; idx < mModel.rowCount(); idx++)
    {
        QStandardItem *serverItem = mModel.item(idx);
        TcpServer *serverValue =
            serverItem->data().value<TcpServer *>();
        if (serverValue == server)
        {
            serverItem->appendRow(item);
            break;
        }
    }
}
