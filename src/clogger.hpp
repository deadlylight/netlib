#pragma once
#include <inetliblogger.hpp>

class CLogger : public INetLibLogger, public enable_shared_from_this<CLogger>
{
public:
    CLogger();
    ~CLogger();

    static void log(ELogLevel, const char *, ...);

    void log(const char *) override;
};

#define LOGERROR( ...) CLogger::log(INetLibLogger::ELogError,  __VA_ARGS__)
#define LOGWARN( ...) CLogger::log(INetLibLogger::ELogWarn,  __VA_ARGS__)
#define LOGINFO( ...) CLogger::log(INetLibLogger::ELogInfo,  __VA_ARGS__)
#define LOGDEBUG( ...) CLogger::log(INetLibLogger::ELogDebug,  __VA_ARGS__)
