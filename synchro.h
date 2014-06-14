#ifndef SYNCHRO_H
#define SYNCHRO_H

#include "mainwindow.h"
#include "iconbarre.h"
#include <QNetworkAccessManager>
#include <QSystemTrayIcon>
#include <QtNetwork>
#include <QWidget>

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
    QNetworkReply *reply;

public slots:
    void doList(MainWindow *w);
    void doCheck(QNetworkReply *reply);
};

#endif // SYNCHRO_H
