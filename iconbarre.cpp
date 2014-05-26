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
    myDir = new QDir();

    QString path = QDir::toNativeSeparators(QApplication::applicationDirPath());
    myDir->setPath(".");

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
    if (myDir->exists()) {
        QDesktopServices::openUrl(QUrl("."));
    } else {
        this->showMessage("Répertoire introuvable", "Le répertoire " + myDir->path() + " est introuvable");
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
