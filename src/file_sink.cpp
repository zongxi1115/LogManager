#include "file_sink.h"
#include <iostream>
#include <sstream>
#include <string>
#include <log_mesage.h>

FileSink::FileSink(const std::string &filename)
    : filename(filename)
{
    ofs.open("./logs/" + filename + "_" + std::to_string(curSuffix) + ".log", std::ios::app);
}

void FileSink::log(LogMessage &msg)
{
    if (ofs.tellp() > static_cast<std::streampos>(maxSize))
    {
        curSuffix++;
        ofs.close();
        ofs.open("./logs/" + filename + "_" + std::to_string(curSuffix) + ".log", std::ios::out | std::ios::app);
    }
    // ofs << '[' << l2str(level) << "] " << message << std::endl;
    ofs << msg.parse() << std::endl;
    ofs.flush();
}