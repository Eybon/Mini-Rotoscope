#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QWidget>
#include <QTabWidget>
#include <QTimer>

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

private slots:
    void allow_tab_two(QString);
    void allow_ending();
    void render_project_from_settings();
    void video_rendering_step();
    void project_file_step();
    void cancel();

private:
    MainWindow  *parent;
    QTabWidget  *tabWidget;
    GeneralTab  *generalTab;
    ProjectInfoTab *projectinfoTab;
    RenderingTab *renderingTab;
    Project     *project;

    QProgressDialog *dialog;
    QTimer *timer;
signals:
    void video_rendered();
    void project_file_created();

};

#endif // NEWPROJECT_H
