#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QZoneDessin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void lancer();
    void newProject();
    void createMenus();
    void createActions();

private:
    Ui::MainWindow *ui;

    /*Menu et Action des Menus File et Edit*/
    QMenu *fileMenu;
    QAction *nouveauAct;
    QAction *ouvrirAct;
    QAction *enregistrerAct;
    QAction *enregistrerSousAct;
    QAction *exporterAct;
    QAction *preferenceAct;
    QAction *quitterAct;
    QMenu *editMenu;
    QAction *annulerAct;
    QAction *revenirAct;
    QAction *zoomAct;
    QAction *copierAct;
    QAction *collerAct;

    QZoneDessin *zoneDessin;

};

#endif // MAINWINDOW_H
