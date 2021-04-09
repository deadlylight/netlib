#pragma once
#include <memory>

using namespace std;

class INetLibLogger
{
public:
    enum ELogLevel
    {
        ELogNone,
        ELogError,
        ElogWarn,
        ELogInfo,
        ELogDebug,
        ELogLast = ELogDebug,
    };

public:
    virtual ~INetLibLogger() = default;
    virtual void log(const char *) = 0;

    static void enableLog(shared_ptr<INetLibLogger>);
    static void setLogLevel(ELogLevel);
};
