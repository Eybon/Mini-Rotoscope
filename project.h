#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QFile>
#include <QProcess>

class Project : public QObject
{
    Q_OBJECT

public:
    Project();
    ~Project();

    static const int DEFAULT_FRAMERATE = 8;
    static Project* fromFile(QString filename);

    void setName(QString name);
    void setMovieFile(QString movieFile);
    void setProjectFolder(QString projectFolder);
    void setImagesFolder(QString imagesFolder);
    void setVideoProcessingFolder(QString videoProcessingFolder);
    void setFramerate(int framerate);
    void setDefinition(int definition);

    QString getName();
    QString getMovieFile();
    QString getProjectFolder();
    QString getImagesFolder();
    QString getVideoProcessingFolder();

    int getFramerate();
    int getDefinition();

    QString toFile(QFile*);
    void processVideo();

private:
    QString name;
    QString movieFile;
    QString projectFolder;
    QString imagesFolder;
    QString videoProcessingFolder;

    int framerate;
    int definition;

    QProcess *process;

signals:
    void video_process_finished();
};

#endif // PROJECT_H
