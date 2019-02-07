#ifndef SHADERGRAPH_LOG_H
#define SHADERGRAPH_LOG_H

#include <ctime>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "rang/rang.hpp" // use to set colorization of the clog text

#define LOG_TRACE \
    std::clog << rang::style::bold << "(" << ShaderGraph::nowTime() << ")" << rang::style::reset << \
    "[" << rang::fg::gray << "Trace" << rang::fg::black << "] "

#define LOG_INFO \
    std::clog << rang::style::bold << "(" << ShaderGraph::nowTime() << ")" << rang::style::reset << \
    "[" << rang::fg::green << "Info" << rang::fg::black << "] "

#define LOG_DEBUG \
    std::clog << rang::style::bold << "(" << ShaderGraph::nowTime() << ")" << rang::style::reset << \
    "[" << rang::fg::cyan << "Debug" << rang::fg::black << "] "

#define LOG_WARN \
    std::clog << rang::style::bold << "(" << ShaderGraph::nowTime() << ")" << rang::style::reset << \
    "[" << rang::fg::yellow << "Warn" << rang::fg::black << "] "

#define LOG_ERROR \
    std::clog << rang::style::bold << "(" << ShaderGraph::nowTime() << ")" << rang::style::reset << \
    "[" << rang::fg::red << "Error" << rang::fg::black << "] "

#define NEWLINE std::endl

namespace ShaderGraph
{
    /// Return the current time with the format : %H-%M-%S
    inline std::string nowTime()
    {
        std::ostringstream oss;
        const time_t t = std::time(nullptr);
        const struct tm * tm = std::localtime(&t);
        oss << std::put_time(tm, "%H-%M-%S");
        return oss.str();
    }
}

#endif //SHADERGRAPH_LOG_H
