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
    void createMenus();
    void createActions();
    void createDockWindows();

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

    QPushButton *gomme;
    QPushButton *crayon;

    QPushButton *pelureOignons;
    QPushButton *lectureVideo;
    QPushButton *imageFond;
    QPushButton *exportVideo;
    QPushButton *aide;

    QPushButton *couleur;
    QColorDialog *palette;

public slots:
    void newFile();
    void clear(){zoneDessin->clearDessin();}
    void openPalette(){palette->open();}

};

#endif // MAINWINDOW_H
