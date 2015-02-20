#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QWidget>
#include <QTabWidget>
#include <QTimer>
#include <QThread>

#include "project.h"
#include "generaltab.h"
#include "projectinfotab.h"
#include "renderingtab.h"

#include "mainwindow.h"

class NewProject : public QWidget
{
    Q_OBJECT

public:
    NewProject(MainWindow *parent);
    ~NewProject();
    void delay(int);

private slots:
    void allow_tab_two(QString);
    void allow_ending();
    void render_project_from_settings();
    void cancel();
    void end_processing();
    void next_step();

private:
    MainWindow  *parent;
    QTabWidget  *tabWidget;
    GeneralTab  *generalTab;
    ProjectInfoTab *projectinfoTab;
    RenderingTab *renderingTab;
    Project     *project;

    QProgressDialog *dialog;
    QTimer *timer;
    QThread *videoProcessingThread;

    int steps;

signals:
    void start_video_processing();
    void video_rendered();
    void project_file_created();

};

#endif // NEWPROJECT_H
