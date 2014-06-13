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
    void doCheck();
    ~Synchro();

private:
    QDir *myDir;
};

#endif // SYNCHRO_H
