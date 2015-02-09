#include "generaltab.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

GeneralTab::GeneralTab(QWidget *parent) : QWidget(parent)
{
    QPushButton *button = new QPushButton();
    button->setText(tr("Choix d'un fichier"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(button);

    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
