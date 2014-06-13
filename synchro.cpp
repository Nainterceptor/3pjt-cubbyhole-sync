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
    QNetworkAccessManager networkManaget;
    QUrl url("http://localhost:3000/files/list");

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setUrl(url);

    QNetworkReply *reply = networkManaget.get(request);

    QString sReply = (QString)reply->readAll();
    QJsonDocument jReply = QJsonDocument::fromJson(sReply.toUtf8());

    QJsonObject jsonObj = jReply.object();
    qDebug() << sReply;

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
        qDebug() << fileInfo.baseName();
    }
}

Synchro::~Synchro()
{
    delete this;
}
