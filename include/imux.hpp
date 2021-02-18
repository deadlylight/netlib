#pragma once
#include <cstdint>
#include <memory>

using namespace std;

class IAddr;
class ITcpConnectionHandler;

class IMux
{
public:
    virtual ~IMux() = default;
    virtual bool startMux() = 0;

    virtual bool registerTcpServer(shared_ptr<const IAddr>, shared_ptr<ITcpConnectionHandler>) = 0;
    virtual bool registerTcpClient(shared_ptr<const IAddr>, shared_ptr<const IAddr>, shared_ptr<ITcpConnectionHandler>) = 0;
    virtual bool registerTcpConnection(shared_ptr<const IAddr>, shared_ptr<const IAddr>, shared_ptr<ITcpConnectionHandler>) = 0;
};
