#include "synchro.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iconbarre.h"
#include <QtNetwork>
#include <QSystemTrayIcon>
#include <QNetworkAccessManager>

Synchro::Synchro(QWidget *parent) :
    QNetworkAccessManager(parent)
{
    QDir *myDir = new QDir();
    IconBarre *myIconBarre = new IconBarre();
    myDir->setPath(".");

    if(myDir->exists())
    {
        myIconBarre->explorer();
    }
}

Synchro::~Synchro()
{
    delete this;
}
