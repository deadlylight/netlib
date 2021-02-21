#pragma once
#include <memory>
#include <string>

using namespace std;

class ITcpServer;
class ITcpConnection;

class IMux
{
public:
    virtual ~IMux() = default;
    virtual void stopMux() = 0;
    virtual shared_ptr<ITcpServer> makeTcpServer(uint16_t, const string = string()) = 0;
    virtual shared_ptr<ITcpConnection> makeTcpClient(uint16_t, const string &, const string = string()) = 0;
};
