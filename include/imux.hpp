#pragma once
#include <string>

using namespace std;

class IMux
{
public:
    virtual ~IMux() = default;
    virtual void addBindAddr(const string &) = 0;
    virtual void removeBindAddr(const string &) = 0;
    virtual bool stopMux() = 0;
};
