#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QDesktopServices>
#include <QSystemTrayIcon>
#include <QtScript/QScriptEngine>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(inscription()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(login()));
}

void MainWindow::inscription()
{
    QString link = "http://www.google.com";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::login()
{
    QUrl url;

    QByteArray email = ui->lineEdit->text().toLatin1();
    QByteArray password = ui->lineEdit_2->text().toLatin1();

    QByteArray postData = "{\"email\":\"" + email + "\",\"password\":\"" + password + "\"}";

    url.setUrl("http://localhost:3000/user/login");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager* net = new QNetworkAccessManager;
    QNetworkReply* reply = net->post(request, postData);

    connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
}

void MainWindow::finishedSlot(QNetworkReply* reply)
{
    QString sReply = (QString)reply->readAll();
    QJsonDocument jReply = QJsonDocument::fromJson(sReply.toUtf8());

    QJsonObject jsonObj = jReply.object();

    if (!jsonObj["success"].toBool()) {
        ui->label_3->setText("Identifiants incorrect");

        delete reply;
    }
    else if (reply->error() == QNetworkReply::NoError) {
        QSystemTrayIcon* icon = new QSystemTrayIcon;

        delete reply;
    }
    else {
        delete reply;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
