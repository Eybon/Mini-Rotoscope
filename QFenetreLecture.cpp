#include "QFenetreLecture.h"
#include <unistd.h>


QFenetreLecture::QFenetreLecture(std::vector<QImage*> list){

    listImage = list;
    setFixedSize(800, 600);
    compteur = 0;

    QVBoxLayout *l = new QVBoxLayout();
    current = new QImage();
    label = new QLabel("");
    label->setPixmap(QPixmap::fromImage(*current));
    label->adjustSize();
    l->addWidget(label);
    setLayout(l);

}

void QFenetreLecture::lecture(){
    int time = 200;
    qDebug() << "size : " << listImage.size();
    for(int i=0;i<listImage.size();i++)
    {
        qDebug() << "lecture de l'image : " << i;
        //setImage(*(listImage.at(i)));
        QTimer *timer = new QTimer();
        connect(timer, SIGNAL(timeout()), this, SLOT(setNextImage()));
        timer->start(time);
        time += 2000;
    }
}

void QFenetreLecture::setImage(QImage img)
{
    current = new QImage(img);
    current = new QImage(current->scaled(this->size()));
    label->setPixmap(QPixmap::fromImage(*current));
    this->update();
}

void QFenetreLecture::setNextImage()
{
    if(compteur < listImage.size())
    {
        qDebug() << "valeur du compteur :" << compteur;
        setImage(*(listImage.at(compteur)));
        compteur++;
    }
    /*else
    {
        sleep(1);
        close();
    }*/

}

void QFenetreLecture::close()
{
    this->close();
}
