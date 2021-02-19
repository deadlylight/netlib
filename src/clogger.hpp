#pragma once
#include "ilogger.hpp"

class CLogger : public ILogger
{
    friend class ILogger;

private:
    int mLogLevel;

private:
    CLogger();

public:
    void log(int, char const *, ...) override;
    void level(int) override;
};
