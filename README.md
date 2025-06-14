# 面向对象程序设计课程作业

`Author`:Zongxi
`projName`: 软件日志记录和分析工具 v1.0


---
虽然说写的比较烂而且还很稚嫩，甚至连玩具都算不上，希望通过四年的学习，不断完善它。选择这个题目我就是打算做一些有意义的工作，而不是弄一些坦克大战、图书管理系统等无聊且没有用处的东西。

## 快速上手
```sh
git clone 'https://github.com/zongxi1115/LogManager.git'
cd LogManager
# 编译项目
make
# 运行程序
./build/analyser.exe
```

输出日志
```cpp
#include <log_level.h>
#include <log_manager.h>
#include <iostream>
#include <string>
#include <console_sink.h>
#include <file_sink.h>

int main(){
    LogManager &l = LogManager::getInstance();
    l.setGlobalLevel(Level::DEBUG);
    l.addSink(make_shared<ConsoleSink>());
    // l.addSink(shared_ptr<FileSink>(new FileSink("log")));
    shared_ptr<FileSink> fs = make_shared<FileSink>("log");
    fs.get()->setMaxSize(1024 * 1024);
    l.addSink(fs);
    int a = 10;
    // l.log(Level::INFO, to_string(a + 5));
    LOG_INFO(to_string(a + 5));

    LOG_WARNING("This is a warning message");
    LOG_ERROR("This is an error message");
}
```




## 简单分析工具命令行参数说明(`./build/analyser.exe`)


本程序是一个日志分析工具 `Analyser`，通过命令行参数可以灵活配置日志分析的条件。以下是对命令行参数的详细说明。

### 命令行选项参数
#### `-d, --date`
- **说明**：指定分析的日期范围，格式为 `YYYY-MM-DD`。该参数为可选参数。
- **示例**：`-d 2025-06-13` 表示分析从 2025 年 6 月 13 日开始的日志。

#### `-r, --reverse`
- **说明**：指定是否反转日志顺序。该参数为可选参数，默认值为 `false`。
- **示例**：`-r true` 表示反转日志顺序。

#### `-n, --number`
- **说明**：指定过滤的日志数量。该参数为可选参数，默认值为 `30`。
- **示例**：`-n 50` 表示过滤出 50 条日志。

#### `-l, --level`
- **说明**：指定过滤的日志级别。该参数为可选参数，默认值为 `INFO`。
- **示例**：`-l ERROR` 表示只过滤出 `ERROR` 级别的日志。

## 使用示例
以下是一个完整的命令行使用示例：
```sh
./build/analyser.exe -d 2025-06-10 -r true -n 50 -l ERROR
```
该命令表示分析从 2025 年 6 月 10 日开始的日志，反转日志顺序，过滤出 50 条 `ERROR` 级别的日志。

## 错误处理
如果命令行参数解析出错，程序会输出错误信息并打印使用说明，然后退出程序。例如：
```
parse error: [具体错误信息]
[使用说明]
```
