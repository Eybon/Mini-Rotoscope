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
    newProject->resize(800,500);
    newProject->show();

    QVBoxLayout *vbox = new QVBoxLayout(newProject);

    QTabWidget *tw = new QTabWidget(newProject);
    vbox->addWidget(tw);

    QWidget *step1 = new QWidget();
    /*QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));*/

    std::string toto = "Etape 1";
    tw->addTab(step1, QString(toto.c_str()));

    QWidget *step2 = new QWidget();
    toto = "Etape 2";
    tw->addTab(step2, QString(toto.c_str()));

    QWidget *step3 = new QWidget();
    toto = "Etape 3";
    tw->addTab(step3, QString(toto.c_str()));

    QWidget *step4 = new QWidget();
    toto = "Etape 4";
    tw->addTab(step4, QString(toto.c_str()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
