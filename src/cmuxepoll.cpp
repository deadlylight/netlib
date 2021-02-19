#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <thread>
#include <ilogger.hpp>
#include <cmuxepoll.hpp>

CMuxEpoll::CMuxEpoll()
    : mEpollFd(-1)
{
}

CMuxEpoll::~CMuxEpoll()
{
    close(mEpollFd);
}

bool CMuxEpoll::initMux()
{
    return makeEpollFd();
}

void CMuxEpoll::mainLoop()
{
    ILogger::inst().log(ELogDbg, "in CMuxEpoll::mainLoop, mEpollFd=%d\n", mEpollFd);
    epollMainLoop();
    ILogger::inst().log(ELogDbg, "out CMuxEpoll::mainLoop\n");
}

bool CMuxEpoll::registerMux(int inFd)
{
    return addFd(inFd);
}

bool CMuxEpoll::makeEpollFd()
{
    mEpollFd = epoll_create(1024);
    if (mEpollFd < 0)
    {
        return false;
    }
    return true;
}

void CMuxEpoll::epollMainLoop()
{
    while (!mStopped)
    {
        epoll_event vEvent;
        memset(&vEvent, 0, sizeof(vEvent));
        int vRet = epoll_wait(mFdCount, &vEvent, 1, -1);
        if (vRet < 0)
        {
            if (errno == EINTR)
            {
                ILogger::inst().log(ELogDbg, "epollMainLoop EINTR\n");
                continue;
            }
            else
            {
                ILogger::inst().log(ELogDbg, "epollMainLoop error=%d(%s)\n", errno, strerror(errno));
                mStopped = true;
                break;
            }
        }
        else if (vRet == 0)
        {
            continue;
        }
        else
        {
            handleEvent(reinterpret_cast<void *>(&vEvent));
        }
    }
}

void CMuxEpoll::handleEvent(void *inEvent)
{
    epoll_event *vEvent = reinterpret_cast<epoll_event *>(inEvent);
    int vFd = vEvent->data.fd;
    uint32_t events = vEvent->events;
    uint32_t vType = EMuxEventNone;
    if (events & EPOLLERR)
    {
        vType |= EMuxEventError;
    }
    else if (events & EPOLLIN)
    {
        vType |= EMuxEventRead;
    }
    else if (events & EPOLLOUT)
    {
        vType |= EMuxEventWrite;
    }
    if (vType == EMuxEventNone)
    {
        return;
    }
    CMuxGeneral::handleEvent(vFd, vType);
}

bool CMuxEpoll::addFd(int inFd)
{
    epoll_event vEvent = {0};
    vEvent.events = EPOLLIN;
    vEvent.data.fd = inFd;
    int vRet = epoll_ctl(mEpollFd, EPOLL_CTL_ADD, inFd, &vEvent);
    if (vRet < 0)
    {
        return false;
    }
    return true;
}
