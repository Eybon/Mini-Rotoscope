#ifndef GENERALTAB_H
#define GENERALTAB_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    GeneralTab(QWidget *parent = 0);
    QString getFilename();

private slots:
    void ask_video_path();

signals:
    void changeFilename(QString);

private:
    QPushButton *button;
    QLineEdit *lineEdit;
    QString filename;

};

#endif // GENERALTAB_H
