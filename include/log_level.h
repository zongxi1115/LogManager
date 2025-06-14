#pragma once

#include <string>
using namespace std;
enum class Level
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};
string l2str(Level level);
Level str2l(string level);