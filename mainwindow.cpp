#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(login()));
}

void MainWindow::login()
{
    QByteArray postData;
    postData.append("email=<" + ui->lineEdit->text() + ">&");
    postData.append("password=<" + ui->lineEdit_2->text() + ">");

    QNetworkRequest request( QUrl("localhost:3000/user/login") );
           request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkAccessManager* net = new QNetworkAccessManager;
    QNetworkReply* reply = net->post(request, postData);

    connect(reply, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
}

void MainWindow::finishedSlot(QNetworkReply* reply)
{
    QVariant statusCodeV =
            reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if(reply->error() == QNetworkReply::NoError)
    {
        ui->label_3->setText("Connexion ok");
    }
    else
    {
        ui->label_3->setText("Connexion fail");
    }

    delete reply;
}

MainWindow::~MainWindow()
{
    delete ui;
}
