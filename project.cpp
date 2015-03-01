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

    // <program>
    QDomElement program = doc.createElement("program");
    site.appendChild(program);
    QDomText programText = doc.createTextNode(this->videoProcessingFolder);
    program.appendChild(programText);

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

Project* Project::fromFile(QString filename) {
    Project *project = new Project();

    QFile file(filename);
    file.open(QFile::ReadOnly | QFile::Text);

    QDomDocument doc;
    //we don't care about the namespace(s)
    doc.setContent(&file, false);

    //<project>
    QDomElement root = doc.documentElement();

    //<settings> or other global group
    root = root.firstChildElement();

    while(!root.isNull())
    {
        // <settings>
        if(root.tagName() == "settings")
        {
            QDomElement element = root.firstChildElement();

            // foreach child
            while(!element.isNull())
            {
                // <name>
                if(element.tagName() == "name")
                {
                   project->setName(element.text());
                }
                // <program>
                else if(element.tagName() == "program")
                {
                    project->setVideoProcessingFolder(element.text());
                }
                // <video>
                else if(element.tagName() == "video")
                {
                    project->setMovieFile(element.text());
                }
                // <folder>
                else if(element.tagName() == "folder")
                {
                    project->setProjectFolder(element.text());
                }
                // <images>
                else if(element.tagName() == "images")
                {
                    project->setImagesFolder(element.text());
                }
                // <framerate>
                else if(element.tagName() == "framerate")
                {
                    project->setFramerate(element.text().toInt());
                }
                // <definition>
                else if(element.tagName() == "definition")
                {
                    project->setDefinition(element.text().toInt());
                }
                element = element.nextSiblingElement();
            }
        }

        root = root.nextSiblingElement();
    }

    return project;
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
