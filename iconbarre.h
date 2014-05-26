#ifndef ICONBARRE_H
#define ICONBARRE_H

#include "mainwindow.h"
#include <QSystemTrayIcon>
#include <QWidget>
#include <QDir>

class QSystemTrayIcon;

class IconBarre : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit IconBarre(QWidget *parent = 0);
    ~IconBarre();

private:
    QMenu *menu;
    QDir *myDir;

public slots:
    void explorer();
    void explorer(QSystemTrayIcon::ActivationReason);
    void quit();
};

#endif // ICONBARRE_H
