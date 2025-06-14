#include <log_level.h>
#include <string>
#include <stdexcept>

std::string l2str(Level level)
{
    switch (level)
    {
    case Level::DEBUG:
        return "DEBUG";
    case Level::INFO:
        return "INFO";
    case Level::WARNING:
        return "WARNING";
    case Level::ERROR:
        return "ERROR";
    case Level::FATAL:
        return "FATAL";
    default:
        return "UNKNOWN";
    }
}

Level str2l(string level)
{
    if (level == "DEBUG")
    {
        return Level::DEBUG;
    }
    else if (level == "INFO")
    {
        return Level::INFO;
    }
    else if (level == "WARNING")
    {
        return Level::WARNING;
    }
    else if (level == "ERROR")
    {
        return Level::ERROR;
    }
    else if (level == "FATAL")
    {
        return Level::FATAL;
    }
    else
    {
        // 处理未知的字符串级别，或者抛出异常
        throw invalid_argument("Unknown level");
    }
}
