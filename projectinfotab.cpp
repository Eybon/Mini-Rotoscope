#include <iostream>

#include "projectinfotab.h"
#include "project.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QURL>
#include <QFileDialog>
#include <QRadioButton>
#include <QGroupBox>
#include <QMessageBox>

using namespace std;

ProjectInfoTab::ProjectInfoTab(QWidget *parent) :
    QWidget(parent)
{
    /* Basic information */
    this->filename = new QLineEdit();
    filename->setEnabled(false);

    this->projectFolder = new QLineEdit();
    projectFolder->setEnabled(false);

    this->imagesFolder = new QLineEdit();
    imagesFolder->setEnabled(false);

    this->videoProcessingFolder = new QLineEdit();
    videoProcessingFolder->setEnabled(false);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QPushButton *buttonProjectFolder = new QPushButton("Sélectionner dossier pour stockage du projet ...");
    connect(buttonProjectFolder, SIGNAL(released()), this, SLOT(select_project_folder()));

    QPushButton *buttonImagesFolder = new QPushButton("Sélectionner dossier pour stockage des images ...");
    connect(buttonImagesFolder, SIGNAL(released()), this, SLOT(select_images_folder()));

    QPushButton *buttonVideoProcessingFolder = new QPushButton("Sélectionner l'emplacement d'avconv ...");
    connect(buttonVideoProcessingFolder, SIGNAL(released()), this, SLOT(select_video_processing_folder()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(new QLabel(tr("Fichier vidéo :")), 0, 0);
    layout->addWidget(filename, 0, 1);

    layout->addWidget(buttonProjectFolder, 1, 0);
    layout->addWidget(projectFolder, 1, 1);

    layout->addWidget(buttonImagesFolder, 2, 0);
    layout->addWidget(imagesFolder, 2, 1);

    layout->addWidget(buttonVideoProcessingFolder, 3, 0);
    layout->addWidget(videoProcessingFolder, 3, 1);

    mainLayout->addLayout(layout);

    /* Settings concerning rendering */
    /* 1 - Framerate */

    QGroupBox *framerateBox = new QGroupBox(tr("Framerate"));

    this->hintFramerateButton = new QRadioButton(tr("&Conseillé"));
    this->customFramerateButton = new QRadioButton(tr("&Personnaliser..."));

    connect(hintFramerateButton, SIGNAL(released()), this, SLOT(choose_advised_framerate()));
    connect(customFramerateButton, SIGNAL(released()), this, SLOT(choose_custom_framerate()));

    hintFramerateButton->setChecked(true);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(hintFramerateButton);
    vbox->addWidget(customFramerateButton);
    vbox->addStretch(1);
    framerateBox->setLayout(vbox);

    this->customFramerateBox = new QGroupBox(tr("Définition souhaitée"));
    this->customFramerateSix = new QRadioButton(tr("&6 images/seconde"));
    this->customFramerateHeight = new QRadioButton(tr("&8 images/seconde"));
    this->customFramerateTen = new QRadioButton(tr("&10 images/seconde"));

    QVBoxLayout *vboxCustomFramerate = new QVBoxLayout;
    vboxCustomFramerate->addWidget(customFramerateSix);
    vboxCustomFramerate->addWidget(customFramerateHeight);
    vboxCustomFramerate->addWidget(customFramerateTen);
    vboxCustomFramerate->addStretch(1);
    customFramerateBox->setLayout(vboxCustomFramerate);
    customFramerateBox->hide();

    /*  2 -Definition */

    QGroupBox *definitionBox = new QGroupBox(tr("Définition"));

    this->hintDefinitionButton = new QRadioButton(tr("C&onseillée"));
    this->customDefinitionButton = new QRadioButton(tr("P&ersonnaliser..."));

    connect(hintDefinitionButton, SIGNAL(released()), this, SLOT(choose_advised_definition()));
    connect(customDefinitionButton, SIGNAL(released()), this, SLOT(choose_custom_definition()));

    hintDefinitionButton->setChecked(true);
    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(hintDefinitionButton);
    vbox2->addWidget(customDefinitionButton);
    vbox2->addStretch(1);
    definitionBox->setLayout(vbox2);

    /* CONTINUE TO THE NEXT STEP */

    /* rendering */

    continueButton = new QPushButton();
    continueButton->setText(tr("Suivant"));
    continueButton->hide();

    connect(continueButton, SIGNAL(released()), this, SLOT(continue_to_rendering()));

    mainLayout->addWidget(framerateBox);
    mainLayout->addWidget(customFramerateBox);
    mainLayout->addWidget(definitionBox);
    mainLayout->addWidget(continueButton);

    setLayout(mainLayout);
}

void ProjectInfoTab::fill_filename(QString string) {
    filename->setText(string);
}

void ProjectInfoTab::select_project_folder() {
    QString projectFolderUrl = QFileDialog::getExistingDirectory(this, tr("Sélectionnez le répertoire dans lequel stocker le projet"), "");
    projectFolder->setText(projectFolderUrl);
}

void ProjectInfoTab::select_images_folder() {
    QString imagesFolderUrl = QFileDialog::getExistingDirectory(this, tr("Sélectionnez le répertoire dans lequel stocker les images en sortie"), "");
    imagesFolder->setText(imagesFolderUrl);
}

void ProjectInfoTab::select_video_processing_folder() {
    QString videoProcessingFolderUrl = QFileDialog::getOpenFileName(this, tr("Sélectionnez l'emplacement d'avconv"), "");
    videoProcessingFolder->setText(videoProcessingFolderUrl);
    continueButton->show();
}

void ProjectInfoTab::choose_advised_framerate() {
    this->customFramerateBox->hide();
}

void ProjectInfoTab::choose_custom_framerate() {
    this->customFramerateBox->show();
}

void ProjectInfoTab::choose_advised_definition() {
    //TODO
}

void ProjectInfoTab::choose_custom_definition() {
    //INCOMING FEATURE
    this->hintDefinitionButton->click();
    QMessageBox::information(
        this,
        tr("HoHoHo !"),
        tr("Cette fonctionnalité n'est pas disponible pour le moment :(")
    );
}

void ProjectInfoTab::continue_to_rendering() {
    emit settings_completed();
}

QString ProjectInfoTab::getProjectFolder() {
    return this->projectFolder->text();
}

QString ProjectInfoTab::getImagesFolder() {
    return this->imagesFolder->text();
}

QString ProjectInfoTab::getVideoProcessingFolder() {
    return this->videoProcessingFolder->text();
}

int ProjectInfoTab::getFramerate() {
    if (this->customFramerateBox->isChecked()) {
        return Project::DEFAULT_FRAMERATE;
    }
    else
    {
        if (this->customFramerateSix->isChecked()) {
            return 6;
        }
        else if (this->customFramerateHeight->isChecked()) {
            return 8;
        }
        else if (this->customFramerateTen->isChecked()) {
            return 10;
        }
        else
        {
            return Project::DEFAULT_FRAMERATE;
        }
    }
}

int ProjectInfoTab::getDefinition() {
    //TODO
    return 0;
}
