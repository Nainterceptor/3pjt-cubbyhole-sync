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
    QList<QAction*> getSubMenuActions();
    ~IconBarre();

private:
    QMenu *menu;
    QMenu *subMenu;
    QDir *myDir;
    QStringList *menuList;

public slots:
    void explorer();
    void explorer(QSystemTrayIcon::ActivationReason);
    void addFiles(QStringList files);
};

#endif // ICONBARRE_H
