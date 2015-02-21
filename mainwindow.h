#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QZoneDessin.h"
#include "framescontainerwindow.h"

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
    FramesContainerWindow *framesContainer;

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

signals:


public slots:
    void newFile();
    void write(){zoneDessin->setColorPen(Qt::black);}
    void clear(){zoneDessin->setColorPen(Qt::white);}
    void openFile();
    void openPalette(){palette->open();}
    void smallPen(){zoneDessin->setSizePen(10);}
    void bigPen(){zoneDessin->setSizePen(30);}
    void color(QColor c){zoneDessin->setColorPen(c);}
    void activeFond(){zoneDessin->activeFond();}

};

#endif // MAINWINDOW_H
