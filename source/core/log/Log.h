#ifndef SHADERGRAPH_LOG_H
#define SHADERGRAPH_LOG_H

#include <string>
#include <memory>
#include <cstdlib>
#include <iostream>

#include <QTimer>
#include <QObject>
#include <QTextEdit>
#include <QTextStream>
#include <QPlainTextEdit>

#include <vendor/spdlog/spdlog.h>
#include <vendor/spdlog/sinks/basic_file_sink.h>
#include <vendor/spdlog/sinks/stdout_color_sinks.h>
#include <vendor/spdlog/details/fmt_helper.h>

#define LOGGER_FLUSH_DELAY 500

namespace ShaderGraph
{
    class Logger : public QObject
    {
        Q_OBJECT

    public:
        Logger() = default;
        ~Logger() = default;

        void init(const char * file, QTextEdit * logPanel);

    public slots:
        void setLevel(int lvl);

    protected:
        void timerEvent(QTimerEvent *event);

    private:
        /// A QtTimer id, use to flush every second the logger.
        int m_timerId;

        /// A logger from spdlog.
        std::shared_ptr<spdlog::logger> m_logger;

        /// The path to where the log should be write.
        const char * m_file;

        /// The GUI where the log are displayed.
        QTextEdit * m_logPanel = nullptr;
    };

    static Logger g_logger;
}

#define LOGGER g_logger

#define LOG_INIT(_file_, _logpanel_) \
do \
{ \
    ShaderGraph::g_logger.init(_file_, _logpanel_); \
} while(false)

#define LOG_DEBUG(...) \
do \
{ \
    spdlog::debug(__VA_ARGS__); \
} while(false)

#define LOG_INFO(...) \
do \
{ \
    spdlog::info(__VA_ARGS__); \
} while(false)

#define LOG_WARN(...) \
do \
{ \
    spdlog::warn(__VA_ARGS__); \
} while(false)

#define LOG_ERROR(...) \
do \
{ \
    spdlog::error(__VA_ARGS__); \
} while(false)

#define LOG_CRITICAL(...) \
do \
{ \
    spdlog::critical(__VA_ARGS__); \
    exit(EXIT_FAILURE); \
} while(false)


#define SET_LOG_LEVEL_TO_DEBUG() \
do \
{ \
    spdlog::set_level(spdlog::level::debug); \
} while(false)

#define SET_LOG_LEVEL_TO_INFO() \
do \
{ \
    spdlog::set_level(spdlog::level::info); \
} while(false)

#define SET_LOG_LEVEL_TO_WARN() \
do \
{ \
    spdlog::set_level(spdlog::level::warn); \
} while(false)

#define SET_LOG_LEVEL_TO_ERROR() \
do \
{ \
    spdlog::set_level(spdlog::level::err); \
} while(false)

#define SET_LOG_LEVEL_TO_CRITICAL() \
do \
{ \
    spdlog::set_level(spdlog::level::critical); \
} while(false)

#define DISABLE_LOG() \
do \
{ \
    spdlog::set_level(spdlog::level::off); \
} while(false)

#endif //SHADERGRAPH_LOG_H
