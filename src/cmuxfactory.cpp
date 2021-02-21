#include <cmuxfactory.hpp>
#include "cmuxepoll.hpp"

shared_ptr<IMux> CMuxFactory::createMux(const string &inMuxName, const string inBindAddr)
{
    if (inMuxName == "epoll")
    {
        shared_ptr<CMuxEpoll> vMux = make_shared<CMuxEpoll>();
        vMux->addBindAddr(inBindAddr);
        vMux->startMuxEpoll(vMux);
        return vMux;
    }
    return nullptr;
}
