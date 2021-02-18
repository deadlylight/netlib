#include "ctcpclientfactory.hpp"
#include "ctcpclient.hpp"

shared_ptr<IMuxEvent> CTcpClientFactory::createTcpClient(shared_ptr<const IAddr> inBindAddr, shared_ptr<const IAddr> inRemoteAddr, shared_ptr<ITcpConnectionHandler> inTcpHandler)
{
    return make_shared<CTcpClient>(inBindAddr, inRemoteAddr, inTcpHandler);
}
