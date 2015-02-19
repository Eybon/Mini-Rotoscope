#include "newproject.h"
#include "renderingtab.h"
#include "projectinfotab.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

RenderingTab::RenderingTab(QWidget *parent) : QWidget(parent)
{

    QLabel *label = new QLabel();
    label->setText(tr("Une fois que vous êtes satisfaits de vos réglages, cliquez sur le bouton ci-dessous :"));

    this->button = new QPushButton();
    this->button->setText(tr("Terminer"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(button);

    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

RenderingTab::~RenderingTab()
{

}

QPushButton*  RenderingTab::getButton() {
    return this->button;
}
