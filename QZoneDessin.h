#ifndef QZoneDessin_h
#define QZoneDessin_h

#include <QtWidgets>
#include <map>
#include <string>

#include "project.h"

class QZoneDessin : public QWidget
{
	Q_OBJECT

public:
	QZoneDessin(QWidget * parent);
	void resizeEvent(QResizeEvent * e);
	void paintEvent(QPaintEvent * e);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void clearDessin();
    void setSizePen(int size);
    void setColorPen(QColor color);
    void setImageFond(QString s);
    void activeFond();
    void loadProject(Project*);

private:
    std::map<QString, QImage*> drawings;
    bool m_fondActive;
    QImage *m_image;
    QImage *m_dessin;
	int m_actif;
	QPoint *m_position;
    QPen pen;

    bool m_onionsActive;
    int m_onionsLayerNumber;


signals:
    void draw();

public slots:

};

#endif
