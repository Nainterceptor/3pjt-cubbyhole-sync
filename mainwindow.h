#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "iconbarre.h"
#include "synchro.h"
#include <QMainWindow>
#include <QtNetwork>
#include <QSystemTrayIcon>
#include <QWidget>

class QNetworkAccessManager;
class QSystemTrayIcon;
class IconBarre;
class Synchro;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString getToken();
    void setIconBarre(bool view, QString title, QString message);

private:
    Ui::MainWindow *ui;
    QString *token;
    QNetworkReply *reply;
    IconBarre *myIconBarre;
    Synchro *synchro;

public slots:
    void login();
    void inscription();
    void successLogin();
    void finishedSlot(QNetworkReply *reply);
    void quit();
};

#endif // MAINWINDOW_H
