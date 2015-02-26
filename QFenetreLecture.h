#ifndef QFenetreLecture_h
#define QFenetreLecture_h

#include <QtWidgets>
#include <map>
#include <string>

#include "project.h"

class QFenetreLecture : public QDialog
{
    Q_OBJECT
public:
    QFenetreLecture(std::vector<QImage*> list);
    void lecture();
    void setImage(QImage img);

private:
    std::vector<QImage*> listImage;
    QImage *current;
    QLabel *label;
    int compteur;

public slots:
    void setNextImage();
    void close();

};

#endif
