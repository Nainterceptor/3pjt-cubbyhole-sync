#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QSystemTrayIcon>
#include <QWidget>

class QNetworkAccessManager;
class QSystemTrayIcon;

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

private:
    Ui::MainWindow *ui;
    QString *token;

public slots:
    void login();
    void inscription();
    void finishedSlot(QNetworkReply *reply);
};

#endif // MAINWINDOW_H
