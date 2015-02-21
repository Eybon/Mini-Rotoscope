#include <QFileInfo>
#include <QStringList>
#include <QProcess>

#include "videoprocess.h"
#include "project.h"

VideoProcess::VideoProcess(Project *project) : QObject()
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
