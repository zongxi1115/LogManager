#include <log_level.h>
#include <log_manager.h>
#include <iostream>
#include <string>
#include <console_sink.h>
#include <file_sink.h>
#include <algorithm>
using namespace std;
int main()
{
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
    LOG_FATAL("OMG, something went wrong!");
    LOG_INFO("just a log info");
    for (auto i = 1; i < 100; i++)
    {
        // random debug-fatal
        if (rand() % 2 == 0)
        {
            LOG_DEBUG(to_string(i));
        }
        else
        {
            LOG_INFO(to_string(i));
        }
    }
    return 0;
}