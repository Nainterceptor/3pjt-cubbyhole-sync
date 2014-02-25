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
    QUrl url;

    QByteArray email = ui->lineEdit->text().toLatin1();
    QByteArray password = ui->lineEdit_2->text().toLatin1();

    QByteArray postData = "{\"email\":\"" + email + "\",\"password\":\"" + password + "\"}";

    url.setUrl("http://localhost:3000/user/login");

    qDebug() << postData.data();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager* net = new QNetworkAccessManager;
    QNetworkReply* reply = net->post(request, postData);

    connect(net, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
}

void MainWindow::finishedSlot(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
            //success
            qDebug() << "Success" <<reply->readAll();
            delete reply;
        }
        else {
            //failure
            qDebug() << "Failure" <<reply->errorString();
            delete reply;
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}
