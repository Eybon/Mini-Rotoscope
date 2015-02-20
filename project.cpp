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
#include <QFileInfo>

Project::Project() : QObject(0)
{
    this->process = new QProcess();
}

Project::~Project()
{

}

/** Setters */

void Project::setName(QString name) {
    this->name = name;
}

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

QString Project::getName() {
    return this->name;
}

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

    // <name>
    QDomElement name = doc.createElement("name");
    site.appendChild(name);
    QDomText nameText = doc.createTextNode(this->name);
    name.appendChild(nameText);

    // <video>
    QDomElement video = doc.createElement("video");
    site.appendChild(video);
    QDomText videoText = doc.createTextNode(this->movieFile);
    video.appendChild(videoText);

    // <folder>
    QDomElement folder = doc.createElement("folder");
    site.appendChild(folder);
    QDomText folderText = doc.createTextNode(this->projectFolder);
    folder.appendChild(folderText);

    // <images>
    QDomElement images = doc.createElement("images");
    site.appendChild(images);
    QDomText urlImages = doc.createTextNode(this->imagesFolder);
    images.appendChild(urlImages);

    // <framerate>
    QDomElement framerate = doc.createElement("framerate");
    site.appendChild(framerate);
    QDomText valueFramerate = doc.createTextNode(QString::number(this->framerate));
    framerate.appendChild(valueFramerate);

    //<definition>
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

/*
void Project::processVideo() {

    QFileInfo selectedFile = QFileInfo(this->movieFile);

    this->name = selectedFile.baseName();

    QStringList args;
    args << "-i" << this->movieFile;
    args << "-r" << QString::number(this->framerate);
    args << selectedFile.baseName() + "-%3d.jpeg";

    QProcess command;
    command.setWorkingDirectory(this->imagesFolder);
    command.start(this->videoProcessingFolder, args);
    command.waitForFinished();

   emit video_process_finished();
}
*/
