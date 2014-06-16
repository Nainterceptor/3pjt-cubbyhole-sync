#include "iconbarre.h"
#include "synchro.h"
#include "mainwindow.h"
#include <QSystemTrayIcon>
#include <QWidget>
#include <QMenu>
#include <QDesktopServices>
#include <QDir>
#include <QApplication>

IconBarre::IconBarre(MainWindow *w, QWidget *parent) :
    QSystemTrayIcon(parent)
{
    menu = new QMenu();
    myDir = new QDir();
    myDir->setPath("./Synchro");

    QIcon image("../cubbyhole-sync/1.ico");
    QIcon move("../cubbyhole-sync/2.ico");
    this->setIcon(image);

    QAction* synchro = new QAction(move, "Sync Now", this);
    QAction* explore = new QAction("Open Cubbyhole's Folder", this);
    QAction* quit = new QAction("Quit", this);

    menu->addAction(synchro);
    menu->addAction(explore);
    menu->addAction(quit);

    this->setContextMenu(menu);

    connect(synchro, SIGNAL(triggered()), w, SLOT(successLogin()));
    connect(explore, SIGNAL(triggered()), this, SLOT(explorer()));
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(explorer(QSystemTrayIcon::ActivationReason)));
    connect(quit, SIGNAL(triggered()), w, SLOT(quit()));
}

void IconBarre::explorer()
{
    if (myDir->exists())
    {
        QDesktopServices::openUrl(QUrl("."));
    }
}

void IconBarre::explorer(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::DoubleClick:
        explorer();
        break;
    }
}

IconBarre::~IconBarre()
{
    delete this;
}
