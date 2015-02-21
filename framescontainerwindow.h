#ifndef FRAMESCONTAINERWINDOW_H
#define FRAMESCONTAINERWINDOW_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QScrollArea>

#include "project.h"

class FramesContainerWindow : public QListWidget
{
    Q_OBJECT

public:
    FramesContainerWindow();
    ~FramesContainerWindow();
    QScrollArea* getScrollArea();
    void addItem(QListWidgetItem*);
    void loadProject(Project*);

signals:
    void change_frame(QListWidgetItem*);

private:
    QScrollArea* scrollArea;

};

#endif // FRAMESCONTAINERWINDOW_H
