#ifndef FRAMESCONTAINERWINDOW_H
#define FRAMESCONTAINERWINDOW_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QScrollArea>

class FramesContainerWindow : public QListWidget
{
public:
    FramesContainerWindow();
    ~FramesContainerWindow();
    QScrollArea* getScrollArea();
    void addItem(QListWidgetItem*);
    void loadFromFolder(std::string);
private:
    QScrollArea* scrollArea;

};

#endif // FRAMESCONTAINERWINDOW_H
