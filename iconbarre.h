#ifndef ICONBARRE_H
#define ICONBARRE_H

#include "mainwindow.h"
#include "synchro.h"
#include <QSystemTrayIcon>
#include <QWidget>
#include <QDir>

class QSystemTrayIcon;
class Synchro;
class MainWindow;

class IconBarre : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit IconBarre(MainWindow *w, QWidget *parent = 0);
    ~IconBarre();

private:
    QMenu *menu;
    QDir *myDir;

public slots:
    void explorer();
    void explorer(QSystemTrayIcon::ActivationReason);
};

#endif // ICONBARRE_H
