#include <iostream>

#include "project.h"
#include <QtXml>
#include <QString>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QDomText>
#include <QIODevice>
#include <QTextStream>
#include <QFile>
#include <QProcess>
#include <QObject>

Project::Project() : QObject(0)
{
    this->process = new QProcess();
}

Project::~Project()
{

}

/** Setters */

void Project::setMovieFile(QString movieFile) {
    this->movieFile = movieFile;
}

void Project::setProjectFolder(QString projectFolder) {
    this->projectFolder = projectFolder;
}

void Project::setImagesFolder(QString imagesFolder) {
    this->imagesFolder = imagesFolder;
}

void Project::setVideoProcessingFolder(QString videoProcessingFolder) {
    this->videoProcessingFolder = videoProcessingFolder;
}

void Project::setFramerate(int framerate) {
    this->framerate = framerate;
}

void Project::setDefinition(int definition) {
    this->definition = definition;
}

/** Getters */

QString Project::getMovieFile() {
    return this->movieFile;
}

QString Project::getProjectFolder() {
    return this->projectFolder;
}

QString Project::getImagesFolder() {
    return this->imagesFolder;
}

QString Project::getVideoProcessingFolder() {
    return this->videoProcessingFolder;
}

int Project::getFramerate() {
    return this->framerate;
}

int Project::getDefinition() {
    return this->definition;
}

QString Project::toFile( QFile *file ) {
    QString output;

    // Objet de base servant à la création de notre fichier XML
    QDomDocument doc;

    QDomNode xmlNode = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.insertBefore(xmlNode, doc.firstChild());

    QDomElement root = doc.createElement("project");
    doc.appendChild(root);

    // settings group
    QDomElement site = doc.createElement("settings");

    // On ajoute l'élément <settings> en tant que premier enfant de l'élément <root>
    root.appendChild(site);

    // Création de l'élément <video>
    QDomElement nom = doc.createElement("video");
    site.appendChild(nom);

    // Création du texte qui sera entre les balises <video> </video>
    /** TODO */
    QDomText nomText = doc.createTextNode(this->movieFile);
    nom.appendChild(nomText);

    // Création de l'élément <folder>
    QDomElement url = doc.createElement("folder");
    site.appendChild(url);

    /** TODO */
    QDomText urlText = doc.createTextNode(this->projectFolder);
    url.appendChild(urlText);

    // Création de l'élément <images>
    QDomElement images = doc.createElement("images");
    site.appendChild(images);

    /** TODO */
    QDomText urlImages = doc.createTextNode(this->imagesFolder);
    images.appendChild(urlImages);

    // Création de l'élément <framerate>
    QDomElement framerate = doc.createElement("framerate");
    site.appendChild(framerate);

    /** TODO */
    QDomText valueFramerate = doc.createTextNode(QString::number(this->framerate));
    framerate.appendChild(valueFramerate);

    // Création de l'élément <definition>
    QDomElement definition = doc.createElement("definition");
    site.appendChild(definition);

    /** TODO */
    QDomText valueDefinition = doc.createTextNode(QString::number(this->definition));
    definition.appendChild(valueDefinition);

    file->open(QIODevice::WriteOnly);

    QTextStream ts(file);

    int indent = 4;

    doc.save(ts, indent);

    return output;
}

void Project::processVideo() {
    QFile file( QDir(this->imagesFolder).filePath("frame%d.jpg") );
    QString command = "-i "+ this->movieFile +" -r "+ QString::number(this->framerate) +" -y "+ file.fileName();

    std::cout << "Programme : " << this->videoProcessingFolder.toUtf8().constData() << std::endl;
    std::cout << "Commande : " << command.toUtf8().constData() << std::endl;

    //this->process->setWorkingDirectory(QDir(this->videoProcessingFolder).path());
    this->process->start(this->videoProcessingFolder, QStringList() << command);

    if ( !this->process->waitForFinished() ) {
        std::cout << this->process->errorString().toUtf8().constData() << std::endl;
        std::cout << "error while processing" << std::endl;
    }
    QObject::connect(this->process,SIGNAL(finished(int)),this,SLOT(end_video_process()));
    //emit(this->video_process_finished());
}

void Project::end_video_process()
{
    std::cout << "Process terminé" << std::endl;
    emit(this->video_process_finished());
}
