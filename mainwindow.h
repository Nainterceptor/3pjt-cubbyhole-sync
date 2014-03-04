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
    void setIcon();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon* icon;

public slots:
    void login();
    void inscription();
    void finishedSlot(QNetworkReply* reply);
    void explorer();
};

#endif // MAINWINDOW_H
