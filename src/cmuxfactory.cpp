#include <cmuxfactory.hpp>
#include "cmuxepoll.hpp"

shared_ptr<IMux> CMuxFactory::createMux(const string &inMuxName)
{
    if (inMuxName == "epoll")
    {
        shared_ptr<CMuxEpoll> vMux = make_shared<CMuxEpoll>();
        vMux->mSelf = vMux;
        vMux->startMux();
        return vMux;
    }
    return nullptr;
}
