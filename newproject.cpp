#include <iostream>

#include "newproject.h"
#include "project.h"

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QProgressDialog>
#include <QTime>
#include <QThread>

#include "generaltab.h"
#include "projectinfotab.h"
#include "renderingtab.h"
#include "mainwindow.h"
#include "videoprocess.h"

NewProject::NewProject(MainWindow *parent) : QWidget(), parent(parent)
{
    this->project = new Project();

    this->tabWidget = new QTabWidget(this);

    //ETAPE 1
    /*QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));*/

    this->generalTab = new GeneralTab();
    this->projectinfoTab = new ProjectInfoTab();
    this->renderingTab = new RenderingTab();

    tabWidget->addTab(generalTab, tr("Etape 1"));
    tabWidget->addTab(projectinfoTab, tr("Etape 2"));
    tabWidget->addTab(renderingTab, tr("Etape 3"));

    connect(generalTab, SIGNAL(changeFilename(QString)), this, SLOT(allow_tab_two(QString)));
    connect(generalTab, SIGNAL(changeFilename(QString)), projectinfoTab, SLOT(fill_filename(QString)));
    connect(projectinfoTab, SIGNAL(settings_completed()), this, SLOT(allow_ending()));
    connect(renderingTab->getButton(), SIGNAL(released()), this, SLOT(render_project_from_settings()));

    tabWidget->removeTab(1);
    tabWidget->removeTab(1);

    //tw->insertTab(1, projectinfoTab, tr("Etape 2"));

    //tw->addTab(new GeneralTab(), toto.c_str());

    QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->setSizeConstraint(QLayout::SetNoConstraint);

    mainLayout->addWidget(tabWidget);
    this->setLayout(mainLayout);
}

void NewProject::allow_tab_two(QString string) {
    this->project->setMovieFile(string);
    this->tabWidget->insertTab(1, projectinfoTab, tr("Etape 2"));
    //cout << string.toUtf8().constData() << endl;
}

void NewProject::allow_ending() {
    /** Retrieve informations */
    this->project->setProjectFolder(this->projectinfoTab->getProjectFolder());
    this->project->setImagesFolder(this->projectinfoTab->getImagesFolder());
    this->project->setVideoProcessingFolder(this->projectinfoTab->getVideoProcessingFolder());
    this->project->setFramerate(this->projectinfoTab->getFramerate());

    //Display the last tab
    this->tabWidget->insertTab(2, renderingTab, tr("Etape 3"));
    this->tabWidget->setCurrentIndex(2);
}

void NewProject::render_project_from_settings() {

    this->steps = 0;
    connect(this, SIGNAL(project_file_created()), this, SLOT(project_file_step()));

    this->dialog = new QProgressDialog("Création du projet.", "Annuler", 0, 2, this);
    this->dialog->setWindowModality(Qt::WindowModal);
    this->dialog->show();

    connect(dialog, SIGNAL(canceled()), this, SLOT(cancel()));

    qDebug() << "--- Creating a project : Start ---";

    this->videoProcessingThread = new QThread();
    VideoProcess *videoProcess = new VideoProcess(this->project);

    videoProcess->moveToThread(videoProcessingThread);
    connect(this, SIGNAL(start_video_processing()), videoProcess, SLOT(start_video_processing()));
    connect(videoProcess, SIGNAL(step_passed()), this, SLOT(next_step()));
    //connect(videoProcess, SIGNAL(finished()), this, SLOT(video_rendering_step()));
    connect(videoProcess, SIGNAL(finished()), this, SLOT(end_processing()));
    connect(videoProcess, SIGNAL(finished()), videoProcessingThread, SLOT(quit()));
    connect(videoProcess, SIGNAL(finished()), videoProcess, SLOT(deleteLater()));
    connect(videoProcess, SIGNAL(finished()), videoProcessingThread, SLOT(deleteLater()));

    videoProcessingThread->start();

    emit start_video_processing();

}

void NewProject::next_step() {
    this->dialog->setValue(++steps);
}

void NewProject::cancel() {
    QFile file( QDir(this->project->getProjectFolder()).filePath("projet.rtscp") );
    if (file.exists()) {
        file.remove();
    }
}

void NewProject::end_processing() {

    qDebug() << "Dialog closed and working thread ended";

    dialog->close();
    videoProcessingThread->quit();

    //3. Then open the freshly created project on the current panel
    //Ask the user to close (and save ?) the current project if one opened.

    qDebug() << "--- Project created ---";
}

void NewProject::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

NewProject::~NewProject()
{

}

