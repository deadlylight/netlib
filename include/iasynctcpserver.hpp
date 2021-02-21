#pragma once
#include <cstdint>
#include <memory>

using namespace std;

class IASyncTcpConn;

class IAsyncTcpServer
{
public:
    virtual ~IAsyncTcpServer() = default;
    virtual uint16_t getTcpPort() = 0;
    virtual void onNewTcpConn(shared_ptr<IASyncTcpConn>) = 0;
    virtual void onShutdown() = 0;
};
