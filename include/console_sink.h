#pragma once

#include <sink.h>
class ConsoleSink : public Sink
{
public:
    void log(LogMessage& message) override;
};