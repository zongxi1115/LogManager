#include "console_sink.h"
#include <iostream>
#include "log_level.h"
using namespace std;

void ConsoleSink::log(LogMessage& msg)
{
    cout << msg.parse() << endl;
};