#include <stdarg.h>
#include "clogger.hpp"

CLogger::CLogger()
    : mLogLevel(ELogError)
{
}

void CLogger::log(int inLogLevel, char const *inFmt, ...)
{
    if (inLogLevel > mLogLevel)
    {
        return;
    }
    va_list vArgs;
    va_start(vArgs, inFmt);
    vprintf(inFmt, vArgs);
    va_end(vArgs);
}

void CLogger::level(int inLevel)
{
    mLogLevel = inLevel;
}

ILogger &ILogger::inst()
{
    static CLogger sLogger;
    return sLogger;
}
