#include <sys/epoll.h>
#include <unistd.h>
#include <thread>
#include <cmuxgeneral.hpp>

CMuxGeneral::CMuxGeneral()
    : mFdCount(0), mStopped(false)
{
}

CMuxGeneral::~CMuxGeneral()
{
}

bool CMuxGeneral::startMuxGeneral(weak_ptr<CMuxGeneral> inMux)
{
    shared_ptr<CMuxGeneral> vMuxGeneral = inMux.lock();
    thread vThread(muxLoop, vMuxGeneral);
    vThread.detach();
}

void CMuxGeneral::muxLoop(shared_ptr<CMuxGeneral> inMuxGeneral)
{
    inMuxGeneral->muxLoop();
}

void CMuxGeneral::stopMuxGeneral()
{
    mStopped = true;
}

bool CMuxGeneral::registerMuxEvent(shared_ptr<IMuxEvent> inMuxEvent)
{
    int vFd = inMuxEvent->getFd();
    if (!registerMux(vFd))
    {
        return false;
    }
    setMuxEvent(inMuxEvent);
    return true;
}

void CMuxGeneral::handleEvent(int inFd, uint32_t inType)
{
    shared_ptr<IMuxEvent> vMuxEvent = getMuxEvent(inFd);
    if (inType & EMuxEventError)
    {
        vMuxEvent->onError();
        return; // stop when error happens
    }
    if (inType & EMuxEventRead)
    {
        vMuxEvent->onReadable();
    }
    if (inType & EMuxEventWrite)
    {
        vMuxEvent->onWritable();
    }
}

shared_ptr<IMuxEvent> CMuxGeneral::getMuxEvent(int inFd)
{
    return mFd2Events[inFd];
}

void CMuxGeneral::addMuxEvent(shared_ptr<IMuxEvent> inMuxEvent)
{
    mFd2Events[inMuxEvent->getFd()] = inMuxEvent;
}
