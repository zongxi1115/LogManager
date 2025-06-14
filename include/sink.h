#pragma once

#include "log_level.h"
#include <string>
#include "log_mesage.h"
class Sink
{
public:
    virtual void log(LogMessage& message) = 0;
    virtual ~Sink() {};
};