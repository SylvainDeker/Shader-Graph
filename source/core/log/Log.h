#ifndef SHADERGRAPH_LOG_H
#define SHADERGRAPH_LOG_H

#include <queue>
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

#define LOGGER_FLUSH_DELAY 1000

namespace ShaderGraph
{
    class Logger : public QObject
    {
        Q_OBJECT

    public:
        Logger() = default;
        ~Logger() = default;

        /// Initialize the logger.
        /// @file : The path to where the log should be write.
        /// @logPanel : The GUI where the log are displayed.
        void init(const char * file, QTextEdit * logPanel);

        /// Log a debug message.
        /// @fmt : The log message.
        template<typename T>
        inline void debug(const T& message)
        {
            log(spdlog::level::debug, message);
        }

        /// Log a info message.
        /// @fmt : The log message
        template<typename T>
        inline void info(const T& message)
        {
            log(spdlog::level::info, message);
        }

        /// Log a warning message.
        /// @fmt : The log message.
        template<typename T>
        inline void warn(const T& message)
        {
            log(spdlog::level::warn, message);
        }

        /// Log a error message.
        /// @fmt : The log message.
        template<typename T>
        inline void error(const T& message)
        {
            log(spdlog::level::err, message);
        }

        /// Log a critical message.
        /// @fmt : The log message.
        /// @warning : A critical log exit the program.
        template<typename T>
        inline void critical(const T& message)
        {
            log(spdlog::level::critical, message);
        }

        /// Log a debug message.
        /// @fmt : The format of the log message.
        ///        The format uses "{<index>}" to make a reference to the argument at the index <index>.
        ///        The argument index start with 0.
        /// @args : A list of arguments, can be empty.
        template<typename ... Args>
        inline void debug(const char * fmt, const Args&... args)
        {
            log(spdlog::level::debug, fmt, args...);
        }

        /// Log a info message.
        /// @fmt : The format of the log message.
        ///        The format uses "{<index>}" to make a reference to the argument at the index <index>.
        ///        The argument index start with 0.
        /// @args : A list of arguments, can be empty.
        template<typename ... Args>
        inline void info(const char * fmt, const Args&... args)
        {
            log(spdlog::level::info, fmt, args...);
        }

        /// Log a warning message.
        /// @fmt : The format of the log message.
        ///        The format uses "{<index>}" to make a reference to the argument at the index <index>.
        ///        The argument index start with 0.
        /// @args : A list of arguments, can be empty.
        template<typename ... Args>
        inline void warn(const char * fmt, const Args&... args)
        {
            log(spdlog::level::warn, fmt, args...);
        }

        /// Log a error message.
        /// @fmt : The format of the log message.
        ///        The format uses "{<index>}" to make a reference to the argument at the index <index>.
        ///        The argument index start with 0.
        /// @args : A list of arguments, can be empty.
        template<typename ... Args>
        inline void error(const char * fmt, const Args&... args)
        {
            log(spdlog::level::err, fmt, args...);
        }

        /// Log a critical message.
        /// @fmt : The format of the log message.
        ///        The format uses "{<index>}" to make a reference to the argument at the index <index>.
        ///        The argument index start with 0.
        /// @args : A list of arguments, can be empty.
        /// @warning : A critical log exit the program.
        template<typename ... Args>
        inline void critical(const char * fmt, const Args&... args)
        {
            log(spdlog::level::critical, fmt, args...);
            exit(EXIT_FAILURE);
        }

    public slots:
        /// Set the log level to @lvl.
        /// This mean that all the log with a level greater will be ignored.
        void setLevel(int lvl);

    private:
        /// The path to where the log messages should be written.
        const char * m_file;

        /// A logger from spdlog.
        std::shared_ptr<spdlog::logger> m_logger;

        /// The GUI where the log are displayed.
        QTextEdit * m_logPanel = nullptr;

        /// Log a message.
        template<typename T>
        void log(spdlog::level::level_enum lvl, const T& message)
        {
            m_logger->log(lvl, message);

            std::string header; buildHeader(lvl, header);
            std::string formattedMessage = header + message;

            // Display the log message on the log panel.
            const QString qMessage = QString::fromLocal8Bit(formattedMessage.c_str());
            if (m_logPanel) m_logPanel->append(qMessage);
        }

        /// Log a variadic log message.
        template<typename... Args>
        void log(spdlog::level::level_enum lvl, const char * fmt, const Args &... args)
        {
            fmt::memory_buffer membuf;
            format_to(membuf, fmt, args...);
            std::string message = to_string(membuf);

            m_logger->log(lvl, message);

            std::string header; buildHeader(lvl, header);
            std::string formattedMessage = header + message;

            // Display the log message on the log panel.
            const QString qMessage = QString::fromLocal8Bit(formattedMessage.c_str());
            if (m_logPanel) m_logPanel->append(qMessage);
        }

        /// Build the log header (for the log panel only).
        /// Format : [day-month-year h:m:s] [level].
        void buildHeader(spdlog::level::level_enum lvl, std::string& header);
    };

    extern Logger * g_logger;
}

/* ============================================================ */
/* The logger */
/* ============================================================ */
#define LOGGER ShaderGraph::g_logger

#define LOG_INIT(_file_, _panel_) \
do \
{ \
   LOGGER = new ShaderGraph::Logger(); \
   LOGGER->init(_file_, _panel_); \
   SET_LOG_LEVEL_TO_DEBUG; \
   LOG_INFO("Log system : [OK]"); \
} while(false) \

#define LOG_DESTROY delete LOGGER;

#define LOG_CONNECT(_combo_box_) \
    connect(_combo_box_, SIGNAL(currentIndexChanged(int)), \
            LOGGER,              SLOT(setLevel(int)));

/* ============================================================ */
/* Log */
/* ============================================================ */
#define LOG_DEBUG(...)      if (LOGGER != nullptr) LOGGER->debug(__VA_ARGS__);
#define LOG_INFO(...)       if (LOGGER != nullptr) LOGGER->info(__VA_ARGS__);
#define LOG_WARN(...)       if (LOGGER != nullptr) LOGGER->warn(__VA_ARGS__);
#define LOG_ERROR(...)      if (LOGGER != nullptr) LOGGER->error(__VA_ARGS__);
#define LOG_CRITICAL(...)   if (LOGGER != nullptr) LOGGER->critical(__VA_ARGS__);

/* ============================================================ */
/* Set Log Level */
/* ============================================================ */
#define SET_LOG_LEVEL_TO_DEBUG    spdlog::set_level(spdlog::level::debug);
#define SET_LOG_LEVEL_TO_INFO     spdlog::set_level(spdlog::level::info);
#define SET_LOG_LEVEL_TO_WARN     spdlog::set_level(spdlog::level::warn);
#define SET_LOG_LEVEL_TO_ERROR    spdlog::set_level(spdlog::level::err);
#define SET_LOG_LEVEL_TO_CRITICAL spdlog::set_level(spdlog::level::critical);
#define SET_LOG_LEVEL_TO_OFF      spdlog::set_level(spdlog::level::off);

#endif //SHADERGRAPH_LOG_H
