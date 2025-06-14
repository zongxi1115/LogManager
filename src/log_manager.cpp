#include "log_manager.h"
#include "log_mesage.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <unordered_map>

namespace fs = std::filesystem;
LogManager::LogManager()
{
    m_sinks = {};
}

LogManager &LogManager::getInstance()
{
    static LogManager instance;
    return instance;
}

void LogManager::log(Level level, LogMessage message)
{
    if (level < globalLevel)
        return;
    // LogMessage logmessage(level, message);
    // m_sink->log(level, message);
    for (auto &sink : m_sinks)
    {
        sink->log(message);
    }
}

vector<LogMessage> LogManager::getHistorys(Level maxLevel, int limit, bool is_reverse, const std::string date)
{
    // YYYY-MM-DD转换为time对象
    vector<LogMessage> historys;
    // 文件
    vector<fs::path> files;
    // 检测所有.log结尾文件
    for (const auto &entry : fs::directory_iterator("logs"))
    {
        if (entry.path().extension() == ".log" && entry.is_regular_file())
        {
            files.push_back(entry.path());
        }
    }
    // 文件名排序
    sort(files.begin(), files.end());
    if (is_reverse)
        reverse(files.begin(), files.end());
    // 读取文件内容
    int total = 0;
    for (const auto &file : files)
    {
        // 读取文件内容
        std::ifstream ifs(file.string());
        std::string line;
        while (std::getline(ifs, line))
        {
            if (total >= limit)
            {
                break;
            }
            else
            {
                total++;
            }
            // auto pos = line.find("] -");
            // if (pos == std::string::npos)
            //     continue;

            // auto level = str2l(line.substr(1, pos - 1));
            // cout << l2str(level) << " - " << l2str(maxLevel) << endl;
            // if (level < maxLevel)
            //     continue;

            // auto time_str = line.substr(pos + 4, 24);
            // auto message_str = line.substr(pos + 29);
            // 正则读 [DEBUG] - Thu Jun 12 18:56:45 2025 - D:\projs\aaaakeshe\examples\test.cpp:27 - 6
            std::regex pattern(R"(\[(\w+)\]\s*-\s*([^\-]+?)\s*-\s*(.*?):(\d+)\s*-\s*(.*))");
            std::smatch matches;

            // 尝试匹配
            if (std::regex_match(line, matches, pattern))
            {
                LogMessage entry;

                // 提取各个部分
                entry.level = str2l(matches[1].str());
                if (entry.level < maxLevel)
                    continue;
                std::string time_str = matches[2].str();
                std::istringstream ss(time_str);
                std::tm tm;
                ss >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y");
                entry.time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                if (!date.empty())
                {
                    // 将date字符串转换为time_point并与entry.time比较
                    std::tm tm = {};
                    std::istringstream ss(date);
                    ss >> std::get_time(&tm, "%Y-%m-%d");
                    tm.tm_hour = 0;
                    tm.tm_min = 0;
                    tm.tm_sec = 0;
                    tm.tm_isdst = -1;
                    auto date_time_t = std::mktime(&tm);
                    if (date_time_t == -1)
                    {
                        std::cerr << "Failed to convert date: " << date << std::endl;
                        continue;
                    }
                    auto date_time_point = std::chrono::system_clock::from_time_t(date_time_t);
                    // 如果entry.time早于date，则跳过
                    if (entry.time < date_time_point)
                        continue;
                }
                // entry.time = chrono::parse();
                entry.filePath = matches[3].str();
                entry.lineNo = std::stoi(matches[4].str());
                entry.message = matches[5].str();
                historys.push_back(entry);
            }

            // historys.push_back(LogMessage(level, message_str));
        }
    }
    return historys;
}

std::vector<size_t> calcWidths(const std::vector<LogMessage> &logs)
{
    std::vector<size_t> widths(4, 0);

    // 列标题宽度
    widths[0] = std::max(widths[0], std::string("Level").length());
    widths[1] = std::max(widths[1], std::string("Time").length());
    widths[2] = std::max(widths[2], std::string("Path").length());
    // widths[3] = std::max(widths[3], std::string("").length());
    widths[3] = std::max(widths[3], std::string("Message").length());

    // 计算每条日志的最大宽度
    for (const auto &log : logs)
    {
        std::string paths = log.filePath + ":" + std::to_string(log.lineNo);
        widths[0] = std::max(widths[0], l2str(log.level).length());
        widths[1] = std::max(widths[1], time2str(log.time).length());
        widths[2] = std::max(widths[2], paths.length());
        // widths[3] = std::max(widths[3], std::to_string(log.lineNo).length());
        widths[3] = std::max(widths[3], log.message.length());
    }

    return widths;
}
// 打印表格分隔线
void printSeparator(const std::vector<size_t> &widths)
{
    std::cout << "+";
    for (size_t i = 0; i < widths.size(); ++i)
    {
        std::cout << std::string(widths[i] + 2, '-') << "+";
    }
    std::cout << std::endl;
}

// 打印日志表格

void LogManager::printLogs(vector<LogMessage> logs)
{
    if (logs.empty())
    {
        std::cout << "NO logs to print." << std::endl;
        return;
    }

    auto widths = calcWidths(logs);

    // 打印表头
    printSeparator(widths);
    std::cout << "| " << std::left << std::setw(widths[0]) << "Level" << " | "
              << std::left << std::setw(widths[1]) << "Time" << " | "
              << std::left << std::setw(widths[2]) << "Path" << " | "
              << std::left << std::setw(widths[3]) << "Message" << " |" << std::endl;
    printSeparator(widths);

    // 打印日志记录
    std::unordered_map<Level, int> level_count;

    for (const auto &log : logs)
    {
        std::string paths = log.filePath + ":" + std::to_string(log.lineNo);
        std::cout << "| " << std::left << std::setw(widths[0]) << l2str(log.level) << " | "
                  << std::left << std::setw(widths[1]) << time2str(log.time) << " | "
                  << std::left << std::setw(widths[2]) << paths << " | "
                  << std::left << std::setw(widths[3]) << log.message << " |" << std::endl;

        level_count[log.level]++;
    }

    // 打印表尾
    printSeparator(widths);
    cout << endl
         << "Total:" << endl;
    for (auto it = level_count.begin(); it != level_count.end(); ++it)
    {
        cout << l2str(it->first) << ":" << it->second << endl;
    }
}

std::string time2str(const std::chrono::system_clock::time_point &time_t_obj)
{
    // 使用 std::ctime 转换时间，并去掉末尾的换行符
    std::time_t time_t = std::chrono::system_clock::to_time_t(time_t_obj);

    std::string time_str = std::ctime(&time_t);
    time_str.pop_back(); // 去掉'\n'
    return time_str;
}