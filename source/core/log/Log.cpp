#include "Log.h"

namespace ShaderGraph
{
    /// Redirect the std::clog to logFile.
    void Log::redirectCLog(QString logFile);
    {
        m_logFile = std::ofstream(logFile.toStdString());

        if (m_logFile.is_open())
        {
            m_clogbuf = std::clog.rdbuf(); // save old buf
            std::clog.rdbuf(m_logFile.rdbuf()); // redirect std::clog to m_logFile
        } else {
            // TODO : Log error
        }
    }

    /// Log function.
    void Log::log(ELogLevel logLevel, QString message, bool hideToClient)
    {
        if (logLevel > m_logLevel) return; // ignore the message

        // TODO : Build log format
        m_logFile << message << std::endl;
        if (!hideToClient) m_logPanel->append(message);
    }
}

