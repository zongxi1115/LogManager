#pragma once
#include <fstream>
#include <string>
#include <sink.h>


class FileSink : public Sink
{
    std::ofstream ofs;
    size_t maxSize = 1024 * 1024 * 10; // 10MB
    int curSuffix = 0;
    std::string filename = "";

public:
    FileSink(const std::string &filename);
    void log(LogMessage& msg) override;
    void setMaxSize(size_t size) { maxSize = size; }
    ~FileSink() override = default;
};