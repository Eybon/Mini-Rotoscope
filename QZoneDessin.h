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
    void ajouterFond();
    void activerFond();
private:
    QImage *m_imageFond;
    bool m_fondActive;
    QImage *m_image;
    QImage *m_dessin;
	int m_actif;
	QPoint *m_position;


signals:
    void draw();


};

#endif
