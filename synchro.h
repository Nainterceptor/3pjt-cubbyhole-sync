#ifndef SYNCHRO_H
#define SYNCHRO_H

#include "mainwindow.h"
#include <QNetworkAccessManager>
#include <QWidget>

class QNetworkAccessManager;

class Synchro : public QNetworkAccessManager
{
    Q_OBJECT

public:
    explicit Synchro(QWidget *parent = 0);
    ~Synchro();

private:
    MainWindow *myMain;
};

#endif // SYNCHRO_H
