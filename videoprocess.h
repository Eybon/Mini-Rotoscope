#ifndef VIDEOPROCESS_H
#define VIDEOPROCESS_H

#include <QtCore>
#include <QObject>

#include "project.h"

class VideoProcess : public QObject
{
    Q_OBJECT

public:
    VideoProcess(Project*);
    ~VideoProcess();

private:
    Project *project;

private slots:
    //Listen for the beginning of the video processing
    void start_video_processing();

signals:
    //emit when video processing is over
    void finished();
    void step_passed();
};

#endif // VIDEOPROCESS_H
