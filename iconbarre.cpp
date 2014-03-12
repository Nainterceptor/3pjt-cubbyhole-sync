#include "iconbarre.h"
#include <QSystemTrayIcon>
#include <QWidget>
#include <QMenu>
#include <QDesktopServices>
#include <QDir>
#include <QApplication>

IconBarre::IconBarre(QWidget *parent) :
    QSystemTrayIcon(parent)
{
    menu = new QMenu();

    QAction* explore = new QAction("Ouvrir le dossier Cubbyhole", this);
    QAction* quit = new QAction("Quitter", this);

    menu->addAction(explore);
    menu->addAction(quit);

    this->setContextMenu(menu);

    QIcon image("1.jpg");
    this->setIcon(image);

    connect(explore, SIGNAL(triggered()), this, SLOT(explorer()));
    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(explorer(QSystemTrayIcon::ActivationReason)));
    connect(quit, SIGNAL(triggered()), this, SLOT(quit()));
}

void IconBarre::explorer()
{
    QDesktopServices::openUrl(QUrl("D:/Qt/cubbyfile"));
}

void IconBarre::explorer(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::DoubleClick:
            QDesktopServices::openUrl(QUrl("D:/Qt/cubbyfile"));
        break;
    }
}

void IconBarre::quit()
{
    login = new MainWindow;
    login->close();
}

IconBarre::~IconBarre()
{
    delete this;
}
