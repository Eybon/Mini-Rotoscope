#include "generaltab.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>

GeneralTab::GeneralTab(QWidget *parent) : QWidget(parent)
{
    this->button = new QPushButton();
    this->button->setText(tr("Choix d'un fichier"));

    this->lineEdit = new QLineEdit();
    this->lineEdit->setReadOnly(true);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(lineEdit);
    mainLayout->addWidget(button);

    connect(this->button, SIGNAL(released()), this, SLOT(ask_video_path()));

    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void GeneralTab::ask_video_path() {
    this->filename = QFileDialog::getOpenFileName(this, tr("Choisissez un fichier vidéo"), "", tr("Vidéo (*.mp4 *.mpg)"));
    this->lineEdit->setText(this->filename);
    emit changeFilename(this->filename);
}

QString GeneralTab::getFilename() {
    return this->filename;
}
