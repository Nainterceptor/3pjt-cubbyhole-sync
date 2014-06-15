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
    token = (QString)w->getToken();
    QByteArray tokenData = token.toUtf8();

    QUrl url("http://localhost:3000/files/list");

    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("token", tokenData);

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

    myDir->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    foreach (QFileInfo fileInfo, myDir->entryInfoList())
    {
        QFile file(fileInfo.absoluteFilePath());
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        QCryptographicHash md5(QCryptographicHash::Md5);
        md5.addData(data);

        localFileNames.append(fileInfo.fileName());
        mapLocalFiles.insert(fileInfo.fileName(), fileInfo.created().toString());
    }

    foreach (const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();

        apiFileNames.append(obj["filename"].toString());
        mapApiFiles.insert(obj["filename"].toString(), obj["_id"].toString());
    }

    foreach (QString apiFile, apiFileNames)
    {
        if (!mapLocalFiles.contains(apiFile))
        {
            doDownload(apiFile);
        }
    }

    foreach (QString localFile, localFileNames)
    {
        if (!mapApiFiles.contains(localFile))
        {
            doUpload(localFile);
        }
    }
}

void Synchro::doDownload(QString apiFile)
{
    QByteArray tokenData = token.toUtf8();

    QString apiFileId = mapApiFiles[apiFile];
    file = apiFile;

    QUrl url("http://localhost:3000/file/download/" + apiFileId);
    QNetworkRequest request(url);
    request.setRawHeader("token", tokenData);

    QNetworkAccessManager *net = new QNetworkAccessManager;
    reply = net->get(request);

    connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedDownload(QNetworkReply*)));
}

void Synchro::doUpload(QString localFile)
{
    QByteArray tokenData = token.toUtf8();

    QUrl url("http://localhost:3000/file/upload");

    QFileInfo fileInfo(myDir->absoluteFilePath(localFile));
    QFile *file = new QFile(fileInfo.absoluteFilePath());

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; filename=\"" + fileInfo.fileName() + "\""));
    file->open(QIODevice::ReadOnly);
    filePart.setBodyDevice(file);
    file->setParent(multiPart);

    multiPart->append(filePart);

    QNetworkRequest request(url);
    request.setRawHeader("token", tokenData);

    QNetworkAccessManager *net = new QNetworkAccessManager;
    reply = net->post(request, multiPart);
    multiPart->setParent(reply);

    connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

void Synchro::finished(QNetworkReply *reply)
{
    QString sReply = (QString)reply->readAll();
    qDebug() << sReply;
    reply->deleteLater();
}

void Synchro::finishedDownload(QNetworkReply *reply)
{
    QFile file(myDir->path() + "/" + file.fileName());
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();
    reply->deleteLater();
}

Synchro::~Synchro()
{
    delete this;
}
