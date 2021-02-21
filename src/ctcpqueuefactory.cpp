#include <ctcpqueuefactory.hpp>
#include "ctcpconnectionqueue.hpp"
#include "ctcpmsgqueue.hpp"

shared_ptr<ITcpConnectionQueue> CTcpQueueFactory::createTcpConnectionQueue()
{
    return make_shared<CTcpConnectionQueue>();
}

shared_ptr<ITcpMsgQueue> CTcpQueueFactory::createTcpMsgQueue()
{
    return make_shared<CTcpMsgQueue>();
}
