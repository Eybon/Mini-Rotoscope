#include <QFileInfo>
#include <QStringList>
#include <QProcess>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>

#include "videoprocess.h"
#include "project.h"

VideoProcess::VideoProcess(Project *project) : QObject(0)
{
    this->project = project;
}

VideoProcess::~VideoProcess()
{

}

void VideoProcess::start_video_processing() {

    qDebug() << "Video processing started";

    QFileInfo selectedFile = QFileInfo(this->project->getMovieFile());

    this->project->setName(selectedFile.baseName());

    QStringList args;
    args << "-i" << this->project->getMovieFile();
    args << "-r" << QString::number(this->project->getFramerate());
    args << selectedFile.baseName() + "-%3d.png";

    QProcess command;
    command.setWorkingDirectory(this->project->getImagesFolder());
    command.start(this->project->getVideoProcessingFolder(), args);
    command.waitForFinished(-1);

    qDebug() << "Video processing finished";
    emit step_passed();

    //2. Create a project file made of XML containing the project data

    QFile file( QDir(this->project->getProjectFolder()).filePath("projet.rtscp") );
    this->project->toFile( &file );
    qDebug() << "Project file written at " << file.fileName();

    emit step_passed();

    emit finished();
}

void VideoProcess::start_video_rendering(QString outputfile) {

    qDebug() << "Video rendering started";

    if(!outputfile.endsWith(".mp4")){
        outputfile += ".mp4";
    }

    // Export
    QStringList args;
    args << "-r" << QString::number(project->getFramerate());
    args << "-i" << "projet-%03d.png";
    args << outputfile;

    QProcess command;
    QDir dir(this->project->getImagesFolder());
    dir.cd("frames");

    command.setWorkingDirectory(dir.absolutePath());
    command.start(this->project->getVideoProcessingFolder(), args);
    command.waitForFinished(-1);

    qDebug() << "Video rendering finished";
}
