#include "Log.h"

#include <string>
#include <fstream>

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

        // Step 2 : Setup the file sink (clear the file and link it) for logging event.
        std::fstream ofs;
        ofs.open(file, std::ios::out | std::ios::trunc);
        ofs.close(); // clear the file
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(file, true);

        // Step 3 : Setup the spdlog::logger
        m_logger = std::make_shared<spdlog::logger>("Logger", consoleSink);
        m_logger->sinks().push_back(fileSink); // Register the file sink.
        spdlog::set_default_logger(m_logger); // Set this logger has the default logger.
        spdlog::flush_every(std::chrono::seconds(LOGGER_FLUSH_DELAY)); // Flush the every LOGGER_FLUSH_DELAY.
    }

    void Logger::setLevel(int lvl)
    {
        // TODO : find a way to remove this "magic number".
        switch (lvl)
        {
            case 0 :
                SET_LOG_LEVEL_TO_DEBUG;
                break;

            case 1 :
                SET_LOG_LEVEL_TO_INFO;
                break;

            case 2 :
                SET_LOG_LEVEL_TO_WARN;
                break;

            case 3:
                SET_LOG_LEVEL_TO_ERROR;
                break;
            case 4 :
                SET_LOG_LEVEL_TO_CRITICAL;
                break;

            case 5 :
                SET_LOG_LEVEL_TO_OFF;
                break;

            default:
                SET_LOG_LEVEL_TO_INFO;
                break;
        }
    }

    void Logger::buildHeader(spdlog::level::level_enum lvl, std::string& header)
    {
        char buffer[80];
        time_t rawTime; time(&rawTime);
        struct tm * timeInfo = localtime(&rawTime);
        strftime(buffer,sizeof(buffer),"%Y-%m-%d %H:%M:%S", timeInfo);

        // TODO : Use the spdlog formatter.
        header = "[" + std::string(buffer) + "] " +
                 "[" + to_string(spdlog::level::to_string_view(lvl)) + "] ";
    }

    Logger * g_logger;
}
