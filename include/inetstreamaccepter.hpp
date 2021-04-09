#pragma once
#include <memory>

using namespace std;

class INetStreamConn;
class INetStreamReader;

class INetStreamAccepter
{
public:
    virtual ~INetStreamAccepter() = default;
    virtual void onServerStarted(shared_ptr<INetStreamServer>) = 0;
    virtual shared_ptr<INetStreamReader> onNewConn() = 0;
};
