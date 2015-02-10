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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabWidget>
#include "generaltab.h"
#include "projectinfotab.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lancer();
    createActions();
    createMenus();
    newProject();
}

void MainWindow::lancer()
{
    QWidget *widget = new QWidget(this);

    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox = new QHBoxLayout();

    /*QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QMediaContent(QUrl::fromLocalFile(QFileInfo("Google_Chrome_Japan.mpg").absoluteFilePath())));
    player->play();

    QVideoWidget *videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);*/

    zoneDessin = new QZoneDessin(this);
    zoneDessin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    //panelDessin = new QPanelDessin(this);
    //panelDessin->setMinimumSize(widget->minimumWidth(),widget->minimumHeight());

    /*Panel de dessin */

    QVBoxLayout *panel = new QVBoxLayout();

    QPushButton *crayon = new QPushButton();
    crayon->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    crayon->setGeometry(0,0,128,56);
    crayon->setIcon(QIcon("/home/antoine/Téléchargements/Projet/resource/crayon.png"));

    QPushButton *gomme = new QPushButton();
    gomme->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    gomme->setGeometry(0,0,128,56);
    gomme->setIcon(QIcon("/home/antoine/Téléchargements/Projet/resource/gomme.png"));

    panel->addWidget(crayon);
    panel->addWidget(gomme);
    panel->addStretch();


    /*Panel de configuration */
    QVBoxLayout *panelConf = new QVBoxLayout();

    QPushButton *oignons = new QPushButton();
    oignons->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    oignons->setGeometry(0,0,128,56);
    oignons->setIcon(QIcon("/home/antoine/Téléchargements/Projet/resource/oignons.png"));

    panelConf->addWidget(oignons);
    panelConf->addStretch();

    hbox->addLayout(panel);
    //hbox->addWidget(panelDessin);
    hbox->addWidget(zoneDessin);
    hbox->addLayout(panelConf);

    vbox->addLayout(hbox);
    widget->setLayout(vbox);

    setCentralWidget(widget);
}

void MainWindow::newProject()
{
    QWidget *newProject = new QWidget();
    //newProject->resize(800,500);
   // newProject->show();

    QTabWidget *tw = new QTabWidget(newProject);

    //ETAPE 1
    /*QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));*/

    tw->addTab(new GeneralTab(), tr("Etape 1"));
    tw->addTab(new ProjectInfoTab(), tr("Etape 2"));
    //tw->addTab(new GeneralTab(), toto.c_str());

    QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
     mainLayout->addWidget(tw);
     newProject->setLayout(mainLayout);
     newProject->show();
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
    connect(enregistrerAct, SIGNAL(triggered()), this, SLOT(newFile()));

    //menu fichier -> enregistrer sous
    enregistrerSousAct = new QAction(tr("&Enregistrer sous ... "), this);
    enregistrerSousAct->setShortcuts(QKeySequence::New);
    enregistrerSousAct->setStatusTip(tr("Enregistrer le projet"));
    enregistrerSousAct->setShortcut( QKeySequence( tr("Ctrl+Alt+S") ) );
    connect(enregistrerSousAct, SIGNAL(triggered()), this, SLOT(newFile()));

    //menu fichier -> exporter
    exporterAct = new QAction(tr("&Exporter"), this);
    exporterAct->setShortcuts(QKeySequence::New);
    exporterAct->setStatusTip(tr("Exporter le projet"));
    exporterAct->setShortcut( QKeySequence( tr("Ctrl+E") ) );
    connect(exporterAct, SIGNAL(triggered()), this, SLOT(newFile()));

    //menu fichier -> quitter
    quitterAct = new QAction(tr("&Quitter"), this);
    quitterAct->setShortcuts(QKeySequence::New);
    quitterAct->setStatusTip(tr("Quitter l'application"));
    quitterAct->setShortcut( QKeySequence( tr("Ctrl+W") ) );
    connect(quitterAct, SIGNAL(triggered()), this, SLOT(newFile()));

    //menu fichier -> annuler
    annulerAct = new QAction(tr("&Annuler"), this);
    annulerAct->setShortcuts(QKeySequence::New);
    annulerAct->setStatusTip(tr("Annuler"));
    annulerAct->setShortcut( QKeySequence( tr("Ctrl+Z") ) );
    connect(annulerAct, SIGNAL(triggered()), this, SLOT(newFile()));

    //menu fichier -> revenir
    revenirAct = new QAction(tr("&Revenir"), this);
    revenirAct->setShortcuts(QKeySequence::New);
    revenirAct->setStatusTip(tr("Revenir"));
    revenirAct->setShortcut( QKeySequence( tr("Ctrl+Y") ) );
    connect(revenirAct, SIGNAL(triggered()), this, SLOT(newFile()));

    //menu fichier -> zoom
    zoomAct = new QAction(tr("&Zoom"), this);
    zoomAct->setShortcuts(QKeySequence::New);
    zoomAct->setStatusTip(tr("Zoom"));
    zoomAct->setShortcut( QKeySequence( tr("") ) );
    connect(zoomAct, SIGNAL(triggered()), this, SLOT(newFile()));

    //menu fichier -> copier
    copierAct = new QAction(tr("&Copier"), this);
    copierAct->setShortcuts(QKeySequence::New);
    copierAct->setStatusTip(tr("Copier"));
    copierAct->setShortcut( QKeySequence( tr("Ctrl+C") ) );
    connect(copierAct, SIGNAL(triggered()), this, SLOT(newFile()));

    //menu fichier -> coller
    collerAct = new QAction(tr("&Coller"), this);
    collerAct->setShortcuts(QKeySequence::New);
    collerAct->setStatusTip(tr("Coller"));
    collerAct->setShortcut( QKeySequence( tr("Ctrl+V") ) );
    connect(collerAct, SIGNAL(triggered()), this, SLOT(newFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
