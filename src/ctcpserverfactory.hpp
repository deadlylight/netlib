#pragma once
#include <memory>

using namespace std;

class IAddr;
class IMuxEvent;
class ITcpConnectionHandler;

class CTcpServerFactory
{
public:
    static shared_ptr<IMuxEvent> createTcpServer(shared_ptr<const IAddr>, shared_ptr<ITcpConnectionHandler>);
};
