#ifndef ProjectInfoTab_H
#define ProjectInfoTab_H

#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QGroupBox>
#include <QPushButton>

class ProjectInfoTab : public QWidget
{
    Q_OBJECT
public:
    ProjectInfoTab(QWidget *parent = 0);
    QString getProjectFolder();
    QString getImagesFolder();
    QString getVideoProcessingFolder();

    int getFramerate();
    int getDefinition();

private slots:
    void fill_filename(QString);
    void select_project_folder();
    void select_images_folder();
    void select_video_processing_folder();

    void choose_advised_framerate();
    void choose_custom_framerate();
    void choose_advised_definition();
    void choose_custom_definition();
    void continue_to_rendering();

signals:
    void settings_completed();

private:
    QLineEdit *filename;
    QLineEdit *projectFolder;
    QLineEdit *imagesFolder;
    QLineEdit *videoProcessingFolder;

    QRadioButton *hintFramerateButton;
    QRadioButton *customFramerateButton;

    QGroupBox *customFramerateBox;
    QRadioButton *customFramerateSix;
    QRadioButton *customFramerateHeight;
    QRadioButton *customFramerateTen;

    QRadioButton *hintDefinitionButton;
    QRadioButton *customDefinitionButton;

    QPushButton *continueButton;

    /*
        INCOMING FUTURE

        QGroupBox *customDefinitionBox;
        QRadioButton *customDefinition;
        QRadioButton *customDefinitionHeight;
        QRadioButton *customDefinitionTen;
    */

};

#endif // ProjectInfoTab_H
