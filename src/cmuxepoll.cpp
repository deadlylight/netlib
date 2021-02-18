#include <unistd.h>
#include <sys/epoll.h>
#include "cmuxepoll.hpp"
#include "imuxevent.hpp"
#include "ctcpserverfactory.hpp"
#include "ctcpclientfactory.hpp"

CMuxEpoll::CMuxEpoll()
: mPollFd(-1), mStopped(false)
{

}

CMuxEpoll::~CMuxEpoll()
{
    close(mPollFd);
}

bool CMuxEpoll::createPollFd()
{
    mPollFd = epoll_create(1024);
    if (mPollFd < 0)
    {
        return false;
    }
    return true;
}

bool CMuxEpoll::invokeMainLoop()
{
    while (!mStopped)
    {
        epoll_event vEvent = {0};
        int vRet = epoll_wait(mPollFd, &vEvent, 1, -1);
        if (vRet < 0)
        {
            if (errno == EINTR)
            {
                continue;
            }
            else
            {
                mStopped = true;
                return false;
            }
        }
        else if (vRet == 0)
        {
            // timeout
        }
        else
        {
            hanldeEvent(vEvent);
        }
    }
    return true;
}

void CMuxEpoll::hanldeEvent(epoll_event &inEvent)
{
    shared_ptr<IMuxEvent> *vMuxEvent = reinterpret_cast<shared_ptr<IMuxEvent> *>(inEvent.data.ptr);
    if (inEvent.events & EPOLLERR)
    {
        (*vMuxEvent)->onError();
    }
    else if (inEvent.events & EPOLLIN)
    {
        (*vMuxEvent)->onReadable();
    }
    else if (inEvent.events & EPOLLOUT)
    {
        (*vMuxEvent)->onWritable();
    }
}

bool CMuxEpoll::startMux()
{
    bool vRet = createPollFd();
    if (!vRet)
    {
        return false;
    }
    return invokeMainLoop();  
}

bool CMuxEpoll::registerMuxEvent(shared_ptr<IMuxEvent> &inMuxEvent, uint32_t inEventBits)
{
    shared_ptr<IMuxEvent> *vMuxEvent = new shared_ptr<IMuxEvent>;
    *vMuxEvent = inMuxEvent;

    epoll_event vEvent = {0};
    vEvent.events = inEventBits;
    vEvent.data.ptr = vMuxEvent;
    int vRet = epoll_ctl(mPollFd, EPOLL_CTL_ADD, (*vMuxEvent)->getFd(), &vEvent);
    if (vRet < 0)
    {
        delete vMuxEvent;
        return false;
    }
    return true;
}

bool CMuxEpoll::registerTcpServer(shared_ptr<const IAddr> inAddr, shared_ptr<ITcpConnectionHandler> inTcpHandler)
{
    shared_ptr<IMuxEvent> vMuxEvent = CTcpServerFactory::createTcpServer(inAddr, inTcpHandler);
    return registerMuxEvent(vMuxEvent, EPOLLIN);
}

bool CMuxEpoll::registerTcpClient(shared_ptr<const IAddr> inBindAddr, shared_ptr<const IAddr> inRemoteAddr, shared_ptr<ITcpConnectionHandler> inTcpHandler)
{
    shared_ptr<IMuxEvent> vMuxEvent = CTcpClientFactory::createTcpClient(inBindAddr, inRemoteAddr, inTcpHandler);
    return registerMuxEvent(vMuxEvent, EPOLLOUT);
}
