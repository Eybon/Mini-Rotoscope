#include "projectinfotab.h"
#include <QLabel>
#include <QVBoxLayout>

ProjectInfoTab::ProjectInfoTab(QWidget *parent) :
    QWidget(parent)
{
    QLabel *fileNameLabel = new QLabel(tr("File Name:"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileNameLabel);

    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
