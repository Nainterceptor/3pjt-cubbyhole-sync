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
    myDir = new QDir();
    myDir->setPath("./Synchro");
}

bool Synchro::isEmpty()
{
    if(myDir->entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0)
    {
        return true;
    }
    else return false;
}

void Synchro::doCheck()
{
    myDir->setFilter(QDir::NoDotAndDotDot | QDir::Files);

    foreach (QFileInfo fileInfo, myDir->entryInfoList())
    {
        QFile file(fileInfo.absoluteFilePath());
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        QCryptographicHash md5(QCryptographicHash::Md5);
        md5.addData(data);
        QByteArray hah = md5.result();
        QString attrMD5 = hah.toHex();
    }
}

Synchro::~Synchro()
{
    delete this;
}
