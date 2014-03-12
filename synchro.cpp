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
    QDir *monDir = new QDir();
    monDir->setPath("D:/Qt/cubbyfile/test");

    if(monDir->exists())
    {
        qDebug() << "oui";
    }
    else
    {
        MainWindow *myMain = new MainWindow();
        myMain->show();
        myMain->setIconBarre(false, "Cubbyhole", "application connectée");
        //Ui::MainWindow *ui = new Ui::MainWindow;
        //ui->label_3->setText("Dossier " + monDir->path() + " introuvable.\nModifiez le dans fichier->option.");
    }
}

Synchro::~Synchro()
{
    delete this;
}
