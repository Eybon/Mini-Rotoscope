#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

#include "QZoneDessin.h"
#include "framescontainerwindow.h"
#include "project.h"

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
    Project *project;

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

    QLineEdit *gotoVal;
    QLineEdit *onionsAmount;

    QZoneDessin *zoneDessin;
    QColorDialog *palette;

signals:
    void send_goto_signal(int);
    void send_onions_changed_signal(int);
    void send_lecture_signal(int);
    void start_video_rendering(QString);

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
    void prepare_goto_signal();
    void prepare_onions_changed_signal();
    void prepare_lecture_signal();
    void change_frame(QListWidgetItem*);
    void exportMovie();
    void end_export_movie();

};

#endif // MAINWINDOW_H
