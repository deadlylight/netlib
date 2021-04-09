#include <poll.h>
#include <cassert>
#include <algorithm>
#include "inetio.hpp"
#include "cmux.hpp"
#include "clogger.hpp"
#include "cnetstreamconn.hpp"

static const uint32_t gMaxFdCount = 10000;
static const int gPollTimeout = 100;
static const int gTimeoutcheckDuration = 1000;

CMux::CMux()
    : mIos(),
      mPollFds(new pollfd[gMaxFdCount]),
      mPollFdsCount(0),
      mStopTime()
{
}

CMux::~CMux()
{
}

void CMux::stopMux()
{
    mStopTime = chrono::system_clock::now() - chrono::milliseconds(1000);
}

bool CMux::stopped()
{
    if (mIos.empty())
    {
        return true;
    }
    return chrono::system_clock::now() >= mStopTime;
}

void CMux::run(uint32_t vInterval)
{
    LOGINFO("Run mux with interval=%u seconds\n", vInterval);
    if (vInterval)
    {
        mStopTime = chrono::system_clock::now() + chrono::milliseconds(vInterval * 1000);
    }
    else
    {
        mStopTime = chrono::system_clock::now().max();
    }
    while (!stopped())
    {
        collectFds();
        poll();
    }
    LOGINFO("Run mux completes\n");
}

void CMux::poll()
{
    int vRet = ::poll(mPollFds.get(), mPollFdsCount, gPollTimeout);
    if (vRet < 0)
    {
        assert(0); //could not recover from poll failure
        stopMux();
        return;
    }
    chrono::system_clock::time_point vNow = chrono::system_clock::now();
    bool vTimeoutCheck = (vNow > (mLastUpdateTime + chrono::milliseconds(gTimeoutcheckDuration)));
    if ((vRet > 0) || vTimeoutCheck)
    {
        checkFds();
        mLastUpdateTime = vNow;
    }
}

void CMux::collectFds()
{
    mPollFdsCount = 0;
    assert(mIos.size() <= gMaxFdCount);
    for (auto &vIt : mIos)
    {
        shared_ptr<INetIo> &vIo = vIt.second;
        assert(vIt.first == vIo->getFd());
        short vEvent = 0;
        if (vIo->forRead())
        {
            vEvent |= POLLIN;
        }
        if (vIo->forWrite())
        {
            vEvent |= POLLOUT;
        }
        addPollFd(vIo->getFd(), vEvent);
    }
}

void CMux::checkFds()
{
    uint32_t vSize = mIos.size();
    for (uint32_t i = 0; (i < vSize); ++i)
    {
        const pollfd &vPollFd = mPollFds[i];
        checkFd(vPollFd);
    }
}

void CMux::checkFd(const pollfd &inPollFd)
{
    short rEvent = inPollFd.revents;
    auto vIt = mIos.find(inPollFd.fd);
    if (vIt == mIos.end())
    {
        assert(0);
        return;
    }

    shared_ptr<INetIo> &vIo = vIt->second;
    if (rEvent == 0)
    {
        vIo->onTimeout();
        return;
    }
    if (rEvent & POLLERR)
    {
        vIo->onError();
        return;
    }

    if (rEvent & POLLIN)
    {
        vIo->onRead();
    }
    if (rEvent & POLLOUT)
    {
        vIo->onWrite();
    }
    
}

void CMux::addPollFd(int inFd, short inEvent)
{
    mPollFds[mPollFdsCount].fd = inFd;
    mPollFds[mPollFdsCount].events = inEvent;
    mPollFds[mPollFdsCount].revents = 0;
    ++mPollFdsCount;
}

bool CMux::addNetIo(shared_ptr<INetIo> inIo)
{
    if (mIos.size() >= gMaxFdCount)
    {
        return false;
    }
    assert(mIos.find(inIo->getFd()) == mIos.end());
    mIos[inIo->getFd()] = inIo;
    return true;
}

bool CMux::removeNetIo(shared_ptr<INetIo> inIo)
{
    auto vIt = mIos.find(inIo->getFd());
    if (vIt == mIos.end())
    {
        assert(0);
        return false;
    }
    mIos.erase(vIt);
    return true;
}

void CMux::checkTimeout()
{
}
