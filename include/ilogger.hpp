#pragma once
#include <memory>

using namespace std;

enum
{
    ELogError,
    ELogInfo,
    ELogDbg,
};

class ILogger
{
public:
    virtual ~ILogger() = default;
    virtual void log(int, char const *, ...) = 0;
    virtual void level(int) = 0;
    static ILogger &inst();
};
