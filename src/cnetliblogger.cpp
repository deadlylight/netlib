#include <iostream>
#include <ctime>
#include <netlibassert.hpp>
#include <cstdarg>
#include <cnetliblogger.hpp>

using namespace std;

static shared_ptr<CNetLibLogger> sNetLibLogger = nullptr;
static ELogLevel sLogLevel = ELogNone;

void CNetLibLogger::setLogger(shared_ptr<CNetLibLogger> in)
{
    sNetLibLogger = in;
}

void CNetLibLogger::setLogLevel(ELogLevel in)
{
    sLogLevel = in;
}

static const uint32_t gMaxLogLen = 1024;

CNetLibLogger::CNetLibLogger()
{
}

CNetLibLogger::~CNetLibLogger()
{
}

void CNetLibLogger::log(const char *in)
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

void CNetLibLogger::log(ELogLevel inLevel, const char *inFmt, ...)
{
    if (inLevel >= ELogMax)
    {
        nl_assert(0);
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
    static shared_ptr<CNetLibLogger> getDefaultLogger();

public:
    CDefaultLogger();
};

CDefaultLogger::CDefaultLogger()
{
    CNetLibLogger::setLogger(getDefaultLogger());
    CNetLibLogger::setLogLevel(ELogDebug);
}

shared_ptr<CNetLibLogger> CDefaultLogger::getDefaultLogger()
{
    static shared_ptr<CNetLibLogger> sLogger = make_shared<CNetLibLogger>();
    return sLogger;
}

static CDefaultLogger sDefualtLogger;
