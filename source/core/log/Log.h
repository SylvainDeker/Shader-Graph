#ifndef SHADERGRAPH_LOG_H
#define SHADERGRAPH_LOG_H

#include <fstream>
#include <iostream>

#include <QTextBrowser>

namespace ShaderGraph
{
    enum ELogLevel { ERROR = 0, WARN = 1, INFO = 2, DEBUG = 3 };

    class Log
    {
    public:
        /// Constructor.
        Log(QTextBrowser * logPanel, QString logFile = "ShaderGraph.log");
        ~Log() = default;

        /// Restore the std::clog that was redirected in the constructor.
        inline void restoreCLog() { std::clog.rdbuf(m_clogbuf); }

        /// Redirect the std::clog to logFile.
        void redirectCLog(QString logFile);
//        {
//            m_logFile = std::ofstream(logFile.toStdString());
//
//            if (m_logFile.is_open())
//            {
//                m_clogbuf = std::clog.rdbuf(); // save old buf
//                std::clog.rdbuf(m_logFile.rdbuf()); // redirect std::clog to m_logFile
//            } else {
//                // TODO : Log error
//            }
//        }

        /// Log function.
        void log(ELogLevel logLevel, QString message, bool hideToClient = false);

        /// Get the maximum log level.
        inline const ELogLevel & getLogLevel()  const { return m_logLevel; }

        /// Set the maximum log level.
        /// @logLevel : the new maximum log level.
        inline void  setLogLevel(ELogLevel logLevel)  { m_logLevel = logLevel; }

    private:

        /// The UI Where the client log will be display.
        QTextBrowser * m_logPanel;

        /// The file where the core log will be redirect.
        std::ofstream m_logFile;

        /// Where the default clog file will be save.
        std::streambuf * m_clogbuf;

        /// Only the log level greater or equals to this ELogLevel will be display.
        ELogLevel m_logLevel;
    };
}

#endif //SHADERGRAPH_LOG_H
