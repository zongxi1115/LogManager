#include "arg_parser.h"
#include <iostream>
#include <log_manager.h>
using namespace std;
int main(int argc, char *argv[])
{
    // 创建参数解析器
    cli::ArgParser parser("Analyser", "Log analyser tool");
    parser.addOption("d", "date", "Analysis Date From(YYYY-MM-DD)", false);
    parser.addOption("r", "reverse", "Reverse logs", true, "false"); // 无默认值
    parser.addOption("n", "number", "Filter Numbers", false, "30");  // 可选参数
    parser.addOption("l", "level", "Filter Level", false, "INFO");

    // 添加位置参数（非选项参数）
    // parser.addPositionalArgument("input_file", "input file path", true);
    // parser.addPositionalArgument("output_file", "output file path", false);

    // 解析命令行参数
    try
    {
        parser.parse(argc, argv);
    }
    catch (const exception &e)
    {
        cerr << "parse error: " << e.what() << endl;
        parser.printUsage();
        return 1;
    }

    // 获取选项值
    string date = parser.getOptionValue("date");
    bool reverse = parser.getOptionValue("reverse") == "true";
    int total = stoi(parser.getOptionValue("n"));
    string level = parser.getOptionValue("level");

    // 获取位置参数
    // string inputFile = parser.getPositionalArgument(0);
    // string outputFile;
    // if (parser.getPositionalArgumentsCount() > 1)
    // {
    //     outputFile = parser.getPositionalArgument(1);
    // }

    // 打印解析结果
    LogManager &manager = LogManager::getInstance();
    auto old_historys = manager.getHistorys(str2l(level), total, reverse,date);
    // for (auto hist : old_historys)
    // {
    //     cout << hist.parse() << endl;
    // }
    manager.printLogs(old_historys);

    //     << "===== resp =====" << endl;
    // cout << "date: " << date << endl;
    // cout << "reverse: " << (reverse ? "true" : "false") << endl;
    // cout << "total: " << total << endl;

    return 0;
}
