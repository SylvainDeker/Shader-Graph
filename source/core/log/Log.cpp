#include "Log.h"

#include <vector>
#include <string>

#include <QtGui>

namespace ShaderGraph
{
    void Logger::init(const char * file, QTextEdit * logPanel)
    {
        // Step 0 : Set the variables.
        m_file = file;
        m_logPanel = logPanel;

        // Step 1 : Setup the console for logging event.
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        // Step 2 :Setup the file sink (clear the file and link it) for logging event.
        QFile qfile(m_file);
        qfile.open(QFile::WriteOnly | QFile::Text);
        qfile.resize(0); // clear the content of the log file.
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file, true);

        // Step 3 : Setup the spdlog::logger
        m_logger = std::make_shared<spdlog::logger>("Logger", consoleSink);
        m_logger->sinks().push_back(fileSink); // Register the file sink.
        spdlog::set_default_logger(m_logger); // Set this logger has the default logger.

        // Step 4 : Start a new timer that will flush every LOGGER_FLUSH_DELAY the logger.
        m_timerId = startTimer(LOGGER_FLUSH_DELAY);

        spdlog::info("Log system : [OK]", 12);
    }

    void  Logger::timerEvent(QTimerEvent *event)
    {
        (void) event; // shutdown the warning

        // Step 1 : Flush the logger content in the file.
        m_logger->flush();

        // Step 2 : "Flush" the GUI, if it exists.
        if (m_logPanel != nullptr)
        {
            QFile file(m_file);
            file.open(QFile::ReadOnly | QFile::Text);
            QTextStream readFile(&file);
            m_logPanel->setText(readFile.readAll());

            // FIXME : impossible to scroll the logPanel
            m_logPanel->moveCursor(QTextCursor::End);
        }
    }

    void Logger::setLevel(int lvl)
    {
        // TODO : find a way to remove this "magic number".
        switch (lvl)
        {
            case 0 :
                SET_LOG_LEVEL_TO_DEBUG();
                break;

            case 1 :
                SET_LOG_LEVEL_TO_INFO();
                break;

            case 2 :
                SET_LOG_LEVEL_TO_WARN();
                break;

            case 3:
                SET_LOG_LEVEL_TO_ERROR();
                break;
            case 4 :
                SET_LOG_LEVEL_TO_CRITICAL();
                break;

            case 5 :
                DISABLE_LOG();
                break;

            default:
                SET_LOG_LEVEL_TO_INFO();
                LOG_ERROR("Invalid log level : {0}, set to <Info> by default.", lvl);
                break;
        }
    }
}

