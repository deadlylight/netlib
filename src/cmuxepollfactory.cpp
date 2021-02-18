#include "cmuxepollfactory.hpp"
#include "cmuxepoll.hpp"

CMuxEpollFactory::CMuxEpollFactory()
: CMuxFactoryImpl("epoll")
{

}

shared_ptr<IMux> CMuxEpollFactory::createMux()
{
    return make_shared<CMuxEpoll>();
}

static CMuxEpollFactory sMuxEpollFactory;