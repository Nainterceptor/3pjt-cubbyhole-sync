#include "synchro.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iconbarre.h"
#include <QtNetwork>
#include <QSystemTrayIcon>
#include <QNetworkAccessManager>
#include <QWaitCondition>
#include <QStringList>

Synchro::Synchro(IconBarre *ic, QWidget *parent) :
    QNetworkAccessManager(parent)
{
    myDir = new QDir();
    myDir->setPath("./Synchro");

    myIconBarre = ic;
}

bool Synchro::isEmpty()
{
    if(myDir->entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0)
    {
        return true;
    }
    else return false;
}

void Synchro::startSynchro(MainWindow *w)
{
    token = (QString)w->getToken();
    doList();
}

void Synchro::doList()
{ 
    qDebug() << "Début analyse...";
    tokenData = token.toUtf8();

    QUrl url("http://localhost:3000/files/list");

    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("token", tokenData);

    QNetworkAccessManager *net = new QNetworkAccessManager;
    QNetworkReply *reply = net->get(request);

    connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(doCheck(QNetworkReply*)));
}

void Synchro::doCheck(QNetworkReply *reply)
{
    QList<QAction*> filesAction = myIconBarre->getSubMenuActions();
    QString sReply = (QString)reply->readAll();
    QJsonDocument jReply = QJsonDocument::fromJson(sReply.toUtf8());

    QJsonObject jsonObj = jReply.object();
    QJsonArray jsonArray = jsonObj["files"].toArray();

    delete reply;

    myDir->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    foreach (QFileInfo fileInfo, myDir->entryInfoList())
    {
        localFileNames.append(fileInfo.fileName());
        mapLocalFiles.insert(fileInfo.fileName(), fileInfo.created().toString());  
    }

    myIconBarre->addFiles(localFileNames);
    for (int i = 0; i < filesAction.size(); i++)
    {
        if (!filesAction.at(i)->isChecked())
        {
            localFileNames.removeAt(i);
        }
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

    filesAction.clear();
    mapApiFiles.clear();
    mapLocalFiles.clear();
    apiFileNames.clear();
    localFileNames.clear();
}

void Synchro::doDownload(QString apiFile)
{
    QUrl url("http://localhost:3000/file/download/" + mapApiFiles[apiFile]);

    QNetworkRequest request(url);
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("token", tokenData);

    QNetworkAccessManager *net = new QNetworkAccessManager;
    QNetworkReply *reply = net->get(request);

    connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedDownload(QNetworkReply*)));
}

void Synchro::doUpload(QString localFile)
{
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
    QNetworkReply *reply = net->post(request, multiPart);
    multiPart->setParent(reply);

    connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
}

void Synchro::finished(QNetworkReply *reply)
{
    qDebug() << "Upload done";
    reply->deleteLater();

    doList();
}

QByteArray Synchro::fileNameFromContentDisposition(const QByteArray &header)
{
    foreach(QByteArray item, header.split(';') )
    {
        int equalSignPos = item.indexOf('=');
        if (equalSignPos == -1)
            continue;
        QString key = item.left(equalSignPos).trimmed();
        if(key.compare("filename", Qt::CaseInsensitive) != 0)
            continue;

        QByteArray value = item.mid(equalSignPos+1).trimmed();
        if(value.startsWith('\"') && value.endsWith('\"'))
        {
            value = value.mid(1,value.length()-2);
        }
        return QByteArray::fromPercentEncoding(value);
    }
    return QByteArray();
}

void Synchro::finishedDownload(QNetworkReply *reply)
{
    QString dlFileName = fileNameFromContentDisposition(reply->rawHeader("Content-Disposition"));

    QFile file(myDir->path() + "/" + dlFileName);
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();

    qDebug() << "Download done";
    reply->deleteLater();

    doList();
}

Synchro::~Synchro()
{
    delete this;
}
