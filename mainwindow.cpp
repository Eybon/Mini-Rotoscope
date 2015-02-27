//avconv -i chrome_japan.mpg -r 1 image-%3d.jpeg

#include <QRect>
#include <QSize>
#include <QDesktopWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QWidget>
#include <QFileInfo>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabWidget>
#include "thumbnailpicture.h"
#include "framescontainerwindow.h"
#include "newproject.h"
#include "project.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lancer();
    createActions();
    createMenus();
    createDockWindows();
    //newProject();

}

void MainWindow::lancer()
{

    zoneDessin = new QZoneDessin(this);
    setCentralWidget(zoneDessin);

}

void MainWindow::createDockWindows()
{
        /*Panel de gauche -> options de dessin */
    QDockWidget *dock = new QDockWidget(tr(""), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

        QWidget *widget = new QWidget(dock);
        QGridLayout *panel = new QGridLayout();

        QPushButton *crayon = new QPushButton();
        crayon->setIcon(QIcon("./resource/crayon.png"));
        crayon->setMinimumSize(QSize(60,60));
        crayon->setIconSize( QSize( 60,60 ));

        QPushButton *gomme = new QPushButton();
        gomme->setIcon(QIcon("./resource/gomme.png"));
        gomme->setMinimumSize(QSize(60,60));
        gomme->setIconSize( QSize( 60,60 ));

        QPushButton *prec = new QPushButton();
        prec->setIcon(QIcon("./resource/gauche.png"));
        prec->setMinimumSize(QSize(60,60));
        prec->setIconSize( QSize( 60,60 ));

        QPushButton *suiv = new QPushButton();
        suiv->setIcon(QIcon("./resource/droite.png"));
        suiv->setMinimumSize(QSize(60,60));
        suiv->setIconSize( QSize( 60,60 ));

        QPushButton *small = new QPushButton("o");
        //gomme->setIcon(QIcon("./resource/gomme.png"));
        small->setMinimumSize(QSize(60,60));
        small->setIconSize( QSize( 60,60 ));

        QPushButton *big = new QPushButton("O");
        //gomme->setIcon(QIcon("./resource/gomme.png"));
        big->setMinimumSize(QSize(60,60));
        big->setIconSize( QSize( 60,60 ));

        palette = new QColorDialog(widget);

        QPushButton *couleur = new QPushButton();
        couleur->setIcon(QIcon("./resource/palette.png"));
        couleur->setMinimumSize(QSize(60,120));
        couleur->setIconSize( QSize( 60,120 ));

        panel->addWidget(prec,0,0);
        panel->addWidget(suiv,0,1);
        panel->addWidget(crayon,1,0);
        panel->addWidget(gomme,2,0);
        panel->addWidget(couleur,3,0,1,2);
        panel->addWidget(small,1,1);
        panel->addWidget(big,2,1);
        panel->setRowStretch(4,15);
        widget->setLayout(panel);

    dock->setWidget(widget);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    connect(prec, SIGNAL(clicked()), zoneDessin, SLOT(previous_image()));
    connect(suiv, SIGNAL(clicked()), zoneDessin, SLOT(next_image()));
    connect(crayon, SIGNAL(clicked()), this, SLOT(write()));
    connect(gomme, SIGNAL(clicked()), this, SLOT(clear()));
    connect(couleur, SIGNAL(clicked()), this, SLOT(openPalette()));
    connect(small, SIGNAL(clicked()), this, SLOT(smallPen()));
    connect(big, SIGNAL(clicked()), this, SLOT(bigPen()));
    connect(palette, SIGNAL(colorSelected(QColor)), this, SLOT(color(QColor)));

        /* panel de droite -> options du projet */
    QDockWidget *dockConf = new QDockWidget(tr(""), this);
    dockConf->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

        QWidget *widgetConf = new QWidget(dock);
        QVBoxLayout *panelConf = new QVBoxLayout();

        QPushButton *pelureOignons = new QPushButton();
        pelureOignons->setMinimumSize(QSize(60,60));
        pelureOignons->setIcon(QIcon("./resource/oignons.png"));
        pelureOignons->setIconSize( QSize( 60,60 ));

        QPushButton *lectureVideo = new QPushButton("");
        lectureVideo->setMinimumSize(QSize(60,60));
        lectureVideo->setIcon(QIcon("./resource/play.png"));
        lectureVideo->setIconSize( QSize( 60,60 ));

        QPushButton *imageFond = new QPushButton();
        imageFond->setMinimumSize(QSize(60,60));
        imageFond->setIcon(QIcon("./resource/paysage.PNG"));
        imageFond->setIconSize( QSize( 60,60 ));

        QPushButton *exportVideo = new QPushButton("Exp");
        exportVideo->setMinimumSize(QSize(60,60));
        //exportVideo->setIcon(QIcon("./resource/oignons.png"));

        QPushButton *aide = new QPushButton("");
        aide->setMinimumSize(QSize(60,60));
        aide->setIcon(QIcon("./resource/help.png"));
        aide->setIconSize( QSize( 60,60 ));
        aide->setEnabled(false);

        panelConf->addStretch();
        panelConf->addWidget(pelureOignons);
        panelConf->addWidget(lectureVideo);
        panelConf->addWidget(imageFond);
        panelConf->addWidget(exportVideo);
        panelConf->addStretch();
        panelConf->addWidget(aide);
        panelConf->addStretch();
        widgetConf->setLayout(panelConf);

    dockConf->setWidget(widgetConf);
    addDockWidget(Qt::RightDockWidgetArea, dockConf);

    connect(imageFond, SIGNAL(clicked()), this, SLOT(activeFond()));
    connect(lectureVideo, SIGNAL(clicked()), zoneDessin, SLOT(lecture()));

    /* panel du bas  */
    QDockWidget *dockSlide = new QDockWidget(tr(""), this);
    dockSlide->setAllowedAreas(Qt::BottomDockWidgetArea);

    this->framesContainer = new FramesContainerWindow();
    framesContainer->verticalScrollBar()->close();
    connect(framesContainer, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(change_frame(QListWidgetItem*)));
    connect(pelureOignons, SIGNAL(clicked()), zoneDessin, SLOT(activateOnions()));
    /*
    for (int i = 0; i < 10; i++) {
        framesContainer->addItem(new QListWidgetItem(QIcon("./resource/thumb/riot.png"),"Riot"));
    }
*/

    dockSlide->setWidget(framesContainer);
    addDockWidget(Qt::BottomDockWidgetArea, dockSlide);

}

void MainWindow::createMenus()
{
     fileMenu = menuBar()->addMenu(tr("&Fichier"));
     fileMenu->addAction(nouveauAct);
     fileMenu->addAction(ouvrirAct);
     fileMenu->addAction(enregistrerAct);
     fileMenu->addAction(enregistrerSousAct);
     fileMenu->addAction(exporterAct);
     fileMenu->addSeparator();
     fileMenu->addAction(quitterAct);

     editMenu = menuBar()->addMenu(tr("&Edition"));
     editMenu->addAction(annulerAct);
     editMenu->addAction(revenirAct);
     editMenu->addAction(zoomAct);
     editMenu->addAction(copierAct);
     editMenu->addAction(collerAct);

}

void MainWindow::createActions()
{
    //menu fichier -> nouveau
    nouveauAct = new QAction(tr("&Nouveau"), this);
    nouveauAct->setShortcuts(QKeySequence::New);
    nouveauAct->setStatusTip(tr("Crée un projet"));
    nouveauAct->setShortcut( QKeySequence( tr("Ctrl+N") ) );
    connect(nouveauAct, SIGNAL(triggered()), this, SLOT(newFile()));

    //menu fichier -> ouvrir
    ouvrirAct = new QAction(tr("&Ouvrir"), this);
    ouvrirAct->setShortcuts(QKeySequence::New);
    ouvrirAct->setStatusTip(tr("Ouvrir un projet"));
    ouvrirAct->setShortcut( QKeySequence( tr("Ctrl+O") ) );
    connect(ouvrirAct, SIGNAL(triggered()), this, SLOT(openFile()));

    //menu fichier -> enregistrer
    enregistrerAct = new QAction(tr("&Enregistrer"), this);
    enregistrerAct->setShortcuts(QKeySequence::New);
    enregistrerAct->setStatusTip(tr("Enregistrer le projet"));
    enregistrerAct->setShortcut( QKeySequence( tr("Ctrl+S") ) );
    connect(enregistrerAct, SIGNAL(triggered()), zoneDessin, SLOT(saveProject()));

    //menu fichier -> enregistrer sous
    enregistrerSousAct = new QAction(tr("&Enregistrer sous ... "), this);
    enregistrerSousAct->setShortcuts(QKeySequence::New);
    enregistrerSousAct->setStatusTip(tr("Enregistrer le projet"));
    enregistrerSousAct->setShortcut( QKeySequence( tr("Ctrl+Alt+S") ) );
    connect(enregistrerSousAct, SIGNAL(triggered()), this, SLOT(newFile()));
    enregistrerSousAct->setEnabled(false);

    //menu fichier -> exporter
    exporterAct = new QAction(tr("&Exporter"), this);
    exporterAct->setShortcuts(QKeySequence::New);
    exporterAct->setStatusTip(tr("Exporter le projet"));
    exporterAct->setShortcut( QKeySequence( tr("Ctrl+E") ) );
    connect(exporterAct, SIGNAL(triggered()), this, SLOT(newFile()));
    exporterAct->setEnabled(false);

    //menu fichier -> quitter
    quitterAct = new QAction(tr("&Quitter"), this);
    quitterAct->setShortcuts(QKeySequence::New);
    quitterAct->setStatusTip(tr("Quitter l'application"));
    quitterAct->setShortcut( QKeySequence( tr("Ctrl+W") ) );
    connect(quitterAct, SIGNAL(triggered()), this, SLOT(newFile()));
    quitterAct->setEnabled(false);

    //menu fichier -> annuler
    annulerAct = new QAction(tr("&Annuler"), this);
    annulerAct->setShortcuts(QKeySequence::New);
    annulerAct->setStatusTip(tr("Annuler"));
    annulerAct->setShortcut( QKeySequence( tr("Ctrl+Z") ) );
    connect(annulerAct, SIGNAL(triggered()), this, SLOT(newFile()));
    annulerAct->setEnabled(false);

    //menu fichier -> revenir
    revenirAct = new QAction(tr("&Revenir"), this);
    revenirAct->setShortcuts(QKeySequence::New);
    revenirAct->setStatusTip(tr("Revenir"));
    revenirAct->setShortcut( QKeySequence( tr("Ctrl+Y") ) );
    connect(revenirAct, SIGNAL(triggered()), this, SLOT(newFile()));
    revenirAct->setEnabled(false);

    //menu fichier -> zoom
    zoomAct = new QAction(tr("&Zoom"), this);
    zoomAct->setShortcuts(QKeySequence::New);
    zoomAct->setStatusTip(tr("Zoom"));
    zoomAct->setShortcut( QKeySequence( tr("") ) );
    connect(zoomAct, SIGNAL(triggered()), this, SLOT(newFile()));
    zoomAct->setEnabled(false);

    //menu fichier -> copier
    copierAct = new QAction(tr("&Copier"), this);
    copierAct->setShortcuts(QKeySequence::New);
    copierAct->setStatusTip(tr("Copier"));
    copierAct->setShortcut( QKeySequence( tr("Ctrl+C") ) );
    connect(copierAct, SIGNAL(triggered()), this, SLOT(newFile()));
    copierAct->setEnabled(false);

    //menu fichier -> coller
    collerAct = new QAction(tr("&Coller"), this);
    collerAct->setShortcuts(QKeySequence::New);
    collerAct->setStatusTip(tr("Coller"));
    collerAct->setShortcut( QKeySequence( tr("Ctrl+V") ) );
    connect(collerAct, SIGNAL(triggered()), this, SLOT(newFile()));
    collerAct->setEnabled(false);
}

void MainWindow::newFile() {
    NewProject *newProject = new NewProject(this);
    newProject->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    newProject->setMinimumWidth(600);
    newProject->setWindowTitle(tr("Nouveau projet"));
    newProject->setWindowModality(Qt::WindowModal);
    newProject->show();
}

void MainWindow::openFile() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Sélectionnez le fichier de projet"), "", tr("Rotoskopia (*.rtscp)"));
    //QFileInfo infos = QFileInfo(filename);

    //Let's admit first that the file is correct, so does the project
    Project *project = Project::fromFile(filename);
    qDebug() << "Project opened : " << project->getName();

    framesContainer->loadProject(project);
    zoneDessin->loadProject(project);
}

void MainWindow::change_frame(QListWidgetItem *item) {
    qDebug() << "[focus] " << item->data(Qt::DisplayRole).toString();
    this->zoneDessin->setImageFond(item->data(Qt::DisplayRole).toString());
}

MainWindow::~MainWindow()
{
    delete ui;
}
