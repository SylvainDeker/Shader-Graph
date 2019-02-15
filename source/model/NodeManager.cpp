//
// Created by Valentin on 2019-02-06.
//

#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QFile>

#include "../core/Core.h"

#include "NodeManager.h"

bool ShaderGraph::NodeManager::loadNodeStyle(const QString filename)
{
    QFile file;

    if (!filename.isEmpty()) // check if the file exist
    {
        QString variable;
        file.setFileName(filename);

        if (!file.open(QFile::ReadOnly | QFile::Text)) // the file cannot be read
        {
            LOG_ERROR << "Unable to open the file : " << filename.toStdString() << NEWLINE;
            return false;

        } else { // file opened and ready to read from
            QTextStream in(&file);
            const QString text = in.readAll();
            m_codeStyleFilename = filename;
            setNodeStyle(text);
        }
        return true;
    }

    LOG_ERROR << "Unable to find the file : " << filename.toStdString() << NEWLINE;
    return false;
}
