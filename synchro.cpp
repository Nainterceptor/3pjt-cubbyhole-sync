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

void Synchro::doList(MainWindow *w)
{
    QString token = (QString)w->getToken();
    QByteArray tokenData = token.toUtf8();

    QUrl url("http://localhost:3000/files/list");

    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("token", tokenData );

    QNetworkAccessManager *net = new QNetworkAccessManager;
    reply = net->get(request);

    connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(doCheck(QNetworkReply*)));
}

void Synchro::doCheck(QNetworkReply *reply)
{
    QString sReply = (QString)reply->readAll();
    QJsonDocument jReply = QJsonDocument::fromJson(sReply.toUtf8());

    QJsonObject jsonObj = jReply.object();
    QJsonArray jsonArray = jsonObj["files"].toArray();

    QStringList attrMD5;
    QStringList attrName;

    QStringList fileMD5;
    QStringList fileName;

    myDir->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    foreach (QFileInfo fileInfo, myDir->entryInfoList())
    {
        QFile file(fileInfo.absoluteFilePath());
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        QCryptographicHash md5(QCryptographicHash::Md5);
        md5.addData(data);
        QByteArray hah = md5.result();
        attrMD5.append(hah.toHex());
        attrName.append(fileInfo.baseName());
    }

    foreach (const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();

        fileMD5.append(obj["md5"].toString());
        fileName.append(obj["filename"].toString());
    }

    foreach (QString file, fileName)
    {
        foreach (QString localFile, attrName)
        {
            if (file == localFile)
            {
                qDebug() << "same";
            }
        }
    }
}

Synchro::~Synchro()
{
    delete this;
}
