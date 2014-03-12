#include "synchro.h"
#include "mainwindow.h"
#include <QNetworkAccessManager>

Synchro::Synchro(QWidget *parent) :
    QNetworkAccessManager(parent)
{

}

Synchro::~Synchro()
{
    delete this;
}
