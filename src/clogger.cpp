#include <iostream>
#include <ctime>
#include <cassert>
#include <cstdarg>
#include "clogger.hpp"

using namespace std;

static shared_ptr<INetLibLogger> sNetLibLogger = nullptr;
static INetLibLogger::ELogLevel sLogLevel = INetLibLogger::ELogNone;

void INetLibLogger::enableLog(shared_ptr<INetLibLogger> in)
{
    sNetLibLogger = in;
}

void INetLibLogger::setLogLevel(ELogLevel in)
{
    sLogLevel = in;
}

static const uint32_t gMaxLogLen = 1024;

CLogger::CLogger()
{
}

CLogger::~CLogger()
{
}

void CLogger::log(const char *in)
{
    cout << in;
}

static const char* sLogeLevelstr[] = {
    "None",
    "Err ",
    "Warn",
    "Info",
    "DBG ",
};

void CLogger::log(ELogLevel inLevel, const char *inFmt, ...)
{
    if (inLevel > ELogLast)
    {
        assert(0);
        return;
    }
    if (inLevel > sLogLevel)
    {
        return;
    }
    if (!sNetLibLogger)
    {
        return;
    }

    unique_ptr<char []> vBuf = make_unique<char []>(gMaxLogLen);
    time_t vNow = time(nullptr);
    tm *vTm = localtime(&vNow);
    int vRet = 0;
    vRet += strftime(vBuf.get(), gMaxLogLen, "%Y%m%d-%H%M%S ", vTm);

    vRet += snprintf(vBuf.get() + vRet, gMaxLogLen - vRet, "Netlib-%s ", sLogeLevelstr[inLevel]);

    va_list vArgs;
    va_start(vArgs, inFmt);
    vsnprintf(vBuf.get() + vRet, gMaxLogLen - vRet, inFmt, vArgs);
    va_end(vArgs);
    sNetLibLogger->log(vBuf.get());
}

class CDefaultLogger
{
private:
    static shared_ptr<CLogger> getDefaultLogger();

public:
    CDefaultLogger();
};

CDefaultLogger::CDefaultLogger()
{
    INetLibLogger::enableLog(getDefaultLogger());
    INetLibLogger::setLogLevel(INetLibLogger::ELogLast);
}

shared_ptr<CLogger> CDefaultLogger::getDefaultLogger()
{
    static shared_ptr<CLogger> sLogger = make_shared<CLogger>();
    return sLogger;
}

static CDefaultLogger sDefualtLogger;
