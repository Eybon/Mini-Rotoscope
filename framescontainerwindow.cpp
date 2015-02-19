#include "framescontainerwindow.h"
#include <string>

using namespace std;

FramesContainerWindow::FramesContainerWindow() : QListWidget()
{
    this->setWrapping(false);
    this->setViewMode(QListWidget::IconMode);
    this->setIconSize(QSize(200,200));
    this->setDragEnabled(false);
}

FramesContainerWindow::~FramesContainerWindow()
{

}

QScrollArea* FramesContainerWindow::getScrollArea()
{
    return this->scrollArea;
}

void FramesContainerWindow::addItem(QListWidgetItem *item)
{
    QListWidget::addItem(item);
}

void FramesContainerWindow::loadFromFolder(string folder) {

}
