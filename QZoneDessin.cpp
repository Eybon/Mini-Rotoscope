#include "QZoneDessin.h"
#include "project.h"

#include <QImageWriter>
#include <iostream>
#include <map>
#include <string>
#include <unistd.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>

#include "QFenetreLecture.h"

QZoneDessin::QZoneDessin(QWidget * parent)
{
    QWidget(parent,0);
    m_image = NULL;
    m_dessin = NULL;
    m_actif = 0;
    m_position = NULL;
    m_fondActive = true;
    drawings = std::map<QString, QImage*>();

    project = NULL;

    indice = 0;
    images_amount = 0;

    m_onionsActive = false;
    m_onionsLayerNumber = 3;

    m_image = new QImage();
    setColorPen(Qt::black);
    setSizePen(10);
}

void QZoneDessin::resizeEvent(QResizeEvent * e)
{
    if(m_dessin == NULL)
    {
        m_dessin = new QImage(e->size(),QImage::Format_ARGB32);
        QPainter p(m_dessin);
        p.fillRect(0,0,m_dessin->width(),m_dessin->height(),Qt::white);
    }
    m_dessin = new QImage(m_dessin->scaled(e->size()));
    m_image = new QImage(m_image->scaled(e->size()));
    this->update();

}

void QZoneDessin::paintEvent(QPaintEvent * e)
{
    QPainter p(this);
    if(m_fondActive == true)
    {
        p.setOpacity(1);
        p.drawImage(0,0,*m_image);
        p.setOpacity(0.5);
        p.drawImage(0,0,*m_dessin);
    }
    else
    {
        p.setOpacity(0);
        p.drawImage(0,0,*m_image);
        p.setOpacity(1);
        p.drawImage(0,0,*m_dessin);
    }
}


void QZoneDessin::mousePressEvent(QMouseEvent *event)
{
    m_position = new QPoint(event->pos() );
    m_actif = 1;
}

void QZoneDessin::mouseMoveEvent(QMouseEvent *event)
{
    if (m_actif==1)
    {
        QPoint * position = new QPoint(event->pos());
        QLine * l = new QLine(*m_position,*position);
        QPainter painter(m_dessin);
        painter.setPen(pen);
        painter.drawLine(*l);
        delete m_position;
        m_position = new QPoint(*position);
        delete position;
        delete l;
        this->update();
    }
}

void QZoneDessin::mouseReleaseEvent(QMouseEvent *event)
{
    //std::cout << "relache" << std::endl;
    delete m_position;
    m_actif = 0;
}

void QZoneDessin::clearDessin()
{
    QSize s(m_dessin->size());
    delete m_dessin;
    m_dessin = new QImage(s,QImage::Format_Mono);
    QPainter painter(m_dessin);
    painter.fillRect(0,0,m_dessin->width(),m_dessin->height(),Qt::white);
    this->update();
}

void QZoneDessin::setSizePen(int size)
{
    pen.setWidth(size);
}

void QZoneDessin::setColorPen(QColor color)
{
    pen.setColor(color);
}

void QZoneDessin::setImageFond(QString img)
{
    m_image = new QImage(img);
    m_dessin = drawings[img];
    //m_dessin = new QImage(m_dessin->scaled(this->size()));
    //m_image = new QImage(m_image->scaled(this->size()));

    indice = getCurrentImageIndex(img);
    qDebug() << "Nouvel indice : " << indice;

    this->update();
}

void QZoneDessin::activeFond()
{
    m_fondActive= !m_fondActive;
    this->update();
}

void QZoneDessin::activateOnions() {
    m_onionsActive = !m_onionsActive;
}

void QZoneDessin::loadProject(Project *project) {
    QStringList filter("*.png");
    QDir folder(project->getImagesFolder());
    folder.setFilter(QDir::Files);
    folder.setSorting(QDir::Name);

    QFileInfoList movieFiles = folder.entryInfoList(filter);

    if (!folder.cd("frames")) {
        qDebug() << "mkdir frames required";
        if (folder.mkdir("frames")) {
            folder.cd("frames");
        }
        else
        {
            //TODO
            qDebug() << "Unable to create the subdirectory 'frames' into " << project->getImagesFolder();
        }
    }

    qDebug() << "Frames directory available";

    QFileInfoList drawfiles = folder.entryInfoList(filter);

    QProgressDialog progress("Chargement de la zone de dessin...", "Annuler", 0, movieFiles.size() - drawfiles.size(), this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setValue(0);
    progress.show();

    int j = 0;

    for (int i=0; i < movieFiles.size(); i++) {
        QFileInfo fileInfo = movieFiles.at(i);
        QFile drawFile(folder.filePath(fileInfo.baseName()) + ".png");
        if (!drawFile.exists()) {
            qDebug() << "Need to create picture named : " << drawFile.fileName();

            QImage actualImage = QImage(fileInfo.absoluteFilePath());
            QImage picture = QImage(actualImage.size(), QImage::Format_RGB32);
            picture.fill(32);
            picture.setAlphaChannel(picture);

            QImageWriter imagefile;
            imagefile.setFileName(drawFile.fileName() + ".png");
            imagefile.setFormat("png");
            imagefile.setQuality(100);
            imagefile.write(picture);

            progress.setValue(++j);
        }
        drawings[fileInfo.absoluteFilePath()] = new QImage(drawFile.fileName());
        qDebug() << "Drawing added for file " << fileInfo.absoluteFilePath();
        images_amount++;
    }

    this->project = project;
}

int QZoneDessin::getCurrentImageIndex(QString img) {
    int i = 0;
    for (auto it=drawings.begin(); it!=drawings.end(); it++) {
        qDebug() << "Comparing " << img << " and " << it->first;
        if (img == it->first) {
            qDebug() << "Yes !";
            return i;
        }
        i++;
    }
    return -1;
}

QString QZoneDessin::getImageForIndex(int index) {
    int i = 0;
    for (auto it=drawings.begin(); it!=drawings.end(); it++) {
        if (i == index) {
            return it->first;
        }
        i++;
    }
    return NULL;
}

void QZoneDessin::previous_image() {
    if (project != NULL) {
        qDebug() << "Indice " << indice;
        QString img = getImageForIndex( (indice > 0) ? indice-1 : indice);
        qDebug() << "Image à récupérer : " <<  img;
        setImageFond(img);
    }
    else
    {
        qDebug() << "No project opened !";
    }
}


void QZoneDessin::next_image() {
    if (project != NULL) {
        qDebug() << "Indice " << indice;
        QString img = getImageForIndex( (indice < drawings.size() - 1) ? indice+1 : indice);
        qDebug() << "Image à récupérer : " <<  img;
        setImageFond(img);
    }
    else
    {
        qDebug() << "No project opened !";
    }
}

void QZoneDessin::saveProject()
{
    int i=0;
    for(auto it=drawings.begin();it!=drawings.end();it++)
    {

        QImageWriter imagefile(convertToFramePath(it->first)+".png");
        imagefile.setFormat("png");
        imagefile.setQuality(100);
        qDebug() << "Image à enregistrer : " <<  convertToFramePath(it->first);
        imagefile.write(*(it->second));
        i++;
    }
}

QString QZoneDessin::convertToFramePath(QString s){
    QStringList list = s.split('/');
    QString tmp = list.at(list.length()-1);
    list.insert(list.length()-1,"frames");

    return list.join("/");
}

void QZoneDessin::lecture(){
    std::vector<QImage*> list;
    int size = drawings.size();
    qDebug() << "Nombre d'image : " << size;
    for(int i=0;i<size;i++)
    {
        QString current = getImageForIndex(i);
        QImage *img = drawings[current];
        list.push_back(img);
        qDebug() << "image : " << current ;
    }
    qDebug() << "Chargement pour lecture ok !";
    QFenetreLecture *lecture = new QFenetreLecture(list);
    lecture->show();
    lecture->lecture();
    /*for(int i=0;i<list.size();i++)
    {
        lecture->setImage(*(list.at(i)));
        sleep(1);
    }*/
}
