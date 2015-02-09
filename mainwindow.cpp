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
    newProject();
}

void MainWindow::lancer()
{
    /*QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/comptes/E130110Z/Desktop/chrome_japan.mpg"));
    player->play();

    QVideoWidget *videoWidget = new QVideoWidget;
    player->setVideoOutput(videoWidget);*/

    QWidget *widget = new QWidget(this);
    QWidget *test = new QWidget(widget);
    test->setMinimumWidth(widget->width()/4);
    QVBoxLayout *vbox = new QVBoxLayout(widget);
    QHBoxLayout *hbox = new QHBoxLayout(widget);

    vbox->addLayout(hbox);

    //hbox->addWidget(videoWidget);
    hbox->addWidget(test);

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

MainWindow::~MainWindow()
{
    delete ui;
}
