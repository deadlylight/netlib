#pragma once
#include <memory>

using namespace std;

class IAddr;
class ITcpConnection;

class ITcpConnectionHandler
{
public:
    virtual ~ITcpConnectionHandler() = default;
    virtual void onConnection(shared_ptr<ITcpConnection>) = 0;
};
