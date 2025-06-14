#pragma once
#include <string>
#include <log_level.h>
#include <chrono>

std::string time2str(const std::chrono::system_clock::time_point &time_t_obj);

struct LogMessage
{
    Level level;
    std::string message;
    // 当前时间
    std::chrono::system_clock::time_point time;
    std::string filePath;
    int lineNo;

    LogMessage() = default;

    // 构造函数，初始化时间为当前时间
    LogMessage(Level log_level, const std::string log_message, const std::chrono::system_clock::time_point &log_time = std::chrono::system_clock::now(), const std::string &log_filePath = "", int log_lineNo = 0)
        : level(log_level), message(log_message), time(log_time), filePath(log_filePath), lineNo(log_lineNo) {}

    std::string parse()
    {
        // std::time_t time_t_obj = std::chrono::system_clock::to_time_t(time);
        // 使用 std::ctime 转换时间，并去掉末尾的换行符
        // std::string time_str = std::ctime(&time_t_obj);
        // time_str.pop_back(); // 去掉'\n'
        std::string time_str = time2str(time);
        // return '[' + l2str(level) + "] - " + time_str + " - " + message;
        return "[" + l2str(level) + "] - " + time_str + " - " + (!filePath.empty() ? filePath : "") + ":" + std::to_string(lineNo) + " - " + message;
    }
};
