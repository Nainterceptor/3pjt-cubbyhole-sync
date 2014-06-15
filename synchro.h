#ifndef SYNCHRO_H
#define SYNCHRO_H

#include "mainwindow.h"
#include "iconbarre.h"
#include <QNetworkAccessManager>
#include <QSystemTrayIcon>
#include <QtNetwork>
#include <QWidget>
#include <QMap>

class QNetworkAccessManager;

class Synchro : public QNetworkAccessManager
{
    Q_OBJECT

public:
    explicit Synchro(QWidget *parent = 0);
    bool isEmpty();
    ~Synchro();

private:
    QDir *myDir;
    QString file;
    QStringList apiFileNames;
    QStringList localFileNames;
    QMap<QString, QString> mapApiFiles;
    QMap<QString, QString> mapLocalFiles;
    QNetworkReply *reply;
    QString token;

public slots:
    void doList(MainWindow *w);
    void doCheck(QNetworkReply *reply);
    void doDownload(QString apiFile);
    void doUpload(QString attrFile);
    void finished(QNetworkReply *reply);
    void finishedDownload(QNetworkReply *reply);
};

#endif // SYNCHRO_H
