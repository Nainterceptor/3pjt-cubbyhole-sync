#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>

static const char *REQUEST_URL = "http://localhost:3000/user/login";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    network = new QNetworkAccessManager(this);
    QNetworkRequest request;

    request.setUrl(QUrl(REQUEST_URL));
    QNetworkReply *reply = network->get(request);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
