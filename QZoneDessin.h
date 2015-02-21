#ifndef QZoneDessin_h
#define QZoneDessin_h

#include <QtWidgets>

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

private:
    bool m_fondActive;
    QImage *m_image;
    QImage *m_dessin;
	int m_actif;
	QPoint *m_position;
    QPen pen;

signals:
    void draw();

public slots:

};

#endif
