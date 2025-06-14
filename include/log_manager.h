
#pragma once
#include <memory>
#include "log_level.h"
#include "sink.h"
#include "console_sink.h"
#include <vector>
#include <log_mesage.h>
using namespace std;
class LogManager
{
private:
    vector<shared_ptr<Sink>> m_sinks;
    Level globalLevel = Level::INFO;
    LogManager();

public:
    // 单例模式
    static LogManager &getInstance();
    // void addSink(shared_ptr<ConsoleSink> sink){m_sink = sink;};
    void addSink(shared_ptr<Sink> sink) { m_sinks.push_back(sink); };
    void setGlobalLevel(Level level) { globalLevel = level; };
    void log(Level level, LogMessage message);
    /**
     * @brief Get the Historys object
     * @param filterLevel  筛选等级
     * @param limit  筛选多少条
     * @param reverse  默认倒序
     */
    vector<LogMessage> getHistorys(Level filterLevel = Level::DEBUG, int limit = 10, bool reverse = true, string date = "");
    void printLogs(vector<LogMessage> logs);
};

#define LOG_DEBUG(message) LogManager::getInstance().log(Level::DEBUG, LogMessage(Level::DEBUG, message, std::chrono::system_clock::now(), __FILE__, __LINE__))
#define LOG_INFO(message) LogManager::getInstance().log(Level::INFO, LogMessage(Level::INFO, message, std::chrono::system_clock::now(), __FILE__, __LINE__))
#define LOG_WARNING(message) LogManager::getInstance().log(Level::WARNING, LogMessage(Level::WARNING, message, std::chrono::system_clock::now(), __FILE__, __LINE__))
#define LOG_ERROR(message) LogManager::getInstance().log(Level::ERROR, LogMessage(Level::ERROR, message, std::chrono::system_clock::now(), __FILE__, __LINE__))
#define LOG_FATAL(message) LogManager::getInstance().log(Level::FATAL, LogMessage(Level::FATAL, message, std::chrono::system_clock::now(), __FILE__, __LINE__))