#include "framescontainerwindow.h"
#include "project.h"

#include <QtCore>
#include <string>
#include <QDir>
#include <QFileInfoList>
#include <QProgressDialog>
#include <QVariant>

#include "mainwindow.h"

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

void FramesContainerWindow::loadProject(Project *project) {
    QStringList filter("*.png");
    QDir folder(project->getImagesFolder());
    folder.setFilter(QDir::Files);
    folder.setSorting(QDir::Name);

    QFileInfoList files = folder.entryInfoList(filter);
    qDebug() << files.size() << " elements";

    this->clear();

    QProgressDialog progress("Chargement des images...", "Annuler", 0, files.size(), this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setValue(0);
    progress.show();

    for (int i=0; i < files.size(); i++) {
        QFileInfo fileInfo = files.at(i);

        QListWidgetItem *item = new QListWidgetItem(QIcon(fileInfo.absoluteFilePath()),tr("test"));
        this->addItem(item);
        item->setData(Qt::DisplayRole, QVariant(fileInfo.absoluteFilePath()));

        progress.setValue(i);
    }
    /*
    foreach (const QString &str, files) {
        //qDebug() << str;
        QFile file( folder.filePath(str) );
        this->addItem(new QListWidgetItem(QIcon(file.fileName()),str));
    }
    */
}
