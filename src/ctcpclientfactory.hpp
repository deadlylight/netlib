#pragma once
#include <memory>

using namespace std;

class IAddr;
class IMuxEvent;
class ITcpConnectionHandler;

class CTcpClientFactory
{
public:
    static shared_ptr<IMuxEvent> createTcpClient(shared_ptr<const IAddr>, shared_ptr<const IAddr>, shared_ptr<ITcpConnectionHandler>);
};
