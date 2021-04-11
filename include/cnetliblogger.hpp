#pragma once
#include <memory>

using namespace std;

enum ELogLevel
{
    ELogNone,
    ELogError,
    ELogWarn,
    ELogInfo,
    ELogDebug,
    ELogMax,
};

class CNetLibLogger
{
public:
    CNetLibLogger();
    ~CNetLibLogger();

    static void log(ELogLevel, const char *, ...);
    static void setLogger(shared_ptr<CNetLibLogger>);
    static void setLogLevel(ELogLevel);

    virtual void log(const char *);
};

#define LOGERROR(...) CNetLibLogger::log(ELogError, __VA_ARGS__)
#define LOGWARN(...) CNetLibLogger::log(ELogWarn, __VA_ARGS__)
#define LOGINFO(...) CNetLibLogger::log(ELogInfo, __VA_ARGS__)
#define LOGDEBUG(...) CNetLibLogger::log(ELogDebug, __VA_ARGS__)
