#pragma once
#include <memory>

using namespace std;

class IMsgIn;
class INetStreamReader;

class INetStreamConn
{
public:
    virtual ~INetStreamConn() = default;
    virtual bool sendMsg(shared_ptr<IMsgIn>) = 0;
    virtual bool isBad() = 0;
};
