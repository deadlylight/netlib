#pragma once
#include <memory>

using namespace std;

class IMsgIn;
class INetStreamConn;

class INetStreamReader
{
public:
    virtual ~INetStreamReader() = default;
    virtual void onRead(shared_ptr<IMsgIn>) = 0;
    virtual void onConn(shared_ptr<INetStreamConn>) = 0;
    virtual void onDisconn() = 0;
    virtual void onTimeout() = 0;
    virtual void onError() = 0;
};
