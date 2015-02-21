#include "QZoneDessin.h"
#include <iostream>

QZoneDessin::QZoneDessin(QWidget * parent)
{
    QWidget(parent,0);
    m_image = NULL;
    m_dessin = NULL;
    m_actif = 0;
    m_position = NULL;
    m_fondActive = true;
    setImageFond("./resource/gomme.png");
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
}

void QZoneDessin::activeFond()
{
    if(m_fondActive == true)
    {
        m_fondActive = false;
    }
    else
    {
        m_fondActive = true;
    }
    this->update();
}


