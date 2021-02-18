#include "ctcpserverfactory.hpp"
#include "ctcpserver.hpp"

shared_ptr<IMuxEvent> CTcpServerFactory::createTcpServer(shared_ptr<const IAddr> inAddr, shared_ptr<ITcpConnectionHandler> inTcpHandler)
{
    shared_ptr<ctcpserver> vTcpServer = make_shared<CTcpServer>(inAddr, inTcpHandler);
    vTcpServer->mAddr = inAddr;
    vTcpServer->mTcpConnectionHandler = inTcpHandler;
    vTcpServer->initTcpServer();
    return vTcpServer;
}
