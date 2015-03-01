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
    int getCurrentImageIndex(QString);
    QString getImageForIndex(int);
    QString convertToFramePath(QString);
    void initialisationImage(QImage *img);
    int getImagesAmount();
private:
    Project *project;
    std::map<QString, QImage*> drawings;
    bool m_fondActive;
    QImage *m_image;
    QImage *m_dessin;
	int m_actif;
	QPoint *m_position;
    QPen pen;

    bool m_onionsActive;
    int m_onionsLayerNumber;

    int indice;
    int images_amount;


signals:
    void draw();

public slots:
    void previous_image();
    void next_image();
    void saveProject();
    void lecture(int);
    void activateOnions();
    void go_to(int);
    void onions_changed(int);
};

#endif
