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

    QAction* synchro = new QAction(move, "Synchroniser maintenant", this);
    QAction* explore = new QAction("Ouvrir le dossier Cubbyhole", this);
    QAction* quit = new QAction("Quitter", this);

    menu->addAction(synchro);
    menu->addAction(explore);
    menu->addAction(quit);

    this->setContextMenu(menu);

    connect(synchro, SIGNAL(triggered()), w, SLOT(successLogin()));
    connect(explore, SIGNAL(triggered()), this, SLOT(explorer()));
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(explorer(QSystemTrayIcon::ActivationReason)));
    connect(quit, SIGNAL(triggered()), this, SLOT(quit()));
}

void IconBarre::explorer()
{
    if (myDir->exists())
    {
        QDesktopServices::openUrl(QUrl("."));
    }
    else
    {
        MainWindow *myMain;
        myMain->setIconBarre(true, "Répertoire introuvable", "Le répertoire " + myDir->path() + " est introuvable");
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

void IconBarre::quit()
{
    MainWindow *login = new MainWindow;
    login->close();
}

IconBarre::~IconBarre()
{
    delete this;
}
