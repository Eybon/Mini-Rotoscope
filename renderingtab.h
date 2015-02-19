#ifndef RENDERINGTAB_H
#define RENDERINGTAB_H

#include <QWidget>
#include <QPushButton>

class RenderingTab : public QWidget
{
    Q_OBJECT
public:
    RenderingTab(QWidget *parent = 0);
    ~RenderingTab();
    QPushButton* getButton();

private slots:

signals:

private:
    QPushButton *button;

};

#endif // RENDERINGTAB_H
