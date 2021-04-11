#include <cnetlibmux.hpp>
#include <netlibassert.hpp>
#include <cnetliblogger.hpp>
#include "imuxobject.hpp"
#include "cnetlibmuximpl.hpp"

static uint32_t gMaxFdCount = 10240;
static const uint32_t cMuxObjectTimeoutDuration = 1000; // milliseconds
static const uint32_t cPollTimeout = 100;   // milliseconds

CNetLibMuxImpl::CNetLibMuxImpl()
    : mMux(new CNetLibMux),
      mMuxObjects(),
      mPollFds(new pollfd[gMaxFdCount]),
      mPollFdCount(0),
      mLastCheckTime(chrono::system_clock::now())
{
}

CNetLibMuxImpl::~CNetLibMuxImpl()
{
}

void CNetLibMuxImpl::run()
{
    LOGINFO("Mux started\n");
    while (!mMuxObjects.empty())
    {
        collectFds();
        poll();
    }
    LOGINFO("Mux stopped\n");
}

void CNetLibMuxImpl::collectFds()
{
    mPollFdCount = 0;
    for (auto &x : mMuxObjects)
    {
        shared_ptr<IMuxObject> &vObj = x.second;
        nl_assert(x.first == vObj->getFd());
        collectFd(vObj);
    }
}

void CNetLibMuxImpl::collectFd(shared_ptr<IMuxObject> &inObj)
{
    short vEvents = 0;
    if (inObj->forRead())
    {
        vEvents = POLLIN;
    }
    if (inObj->forWrite())
    {
        vEvents = POLLOUT;
    }
    pollfd &vPollfd = mPollFds[mPollFdCount];
    ++mPollFdCount;
    vPollfd.fd = inObj->getFd();
    vPollfd.events = vEvents;
    vPollfd.revents = 0;
}

void CNetLibMuxImpl::poll()
{
    int vRet = ::poll(mPollFds.get(), mPollFdCount, cPollTimeout);
    if (vRet < 0)
    {
        stop();
    }
    else
    {
        checkFds(static_cast<uint32_t>(vRet));
    }
}

void CNetLibMuxImpl::stop()
{
    LOGINFO("Stopping mux\n");
    for (auto &x : mMuxObjects)
    {
        shared_ptr<IMuxObject> &vObj = x.second;
        vObj->onError();
    }
    mMuxObjects.clear();
}

void CNetLibMuxImpl::checkFds(uint32_t inActiveFdCount)
{
    bool vCheckTimeout = needCheckTimeout();
    uint32_t vCheckCount = vCheckTimeout ? mPollFdCount : inActiveFdCount;
    for (uint32_t i = 0; (i < mPollFdCount) && (vCheckCount > 0); ++i)
    {
        const pollfd &vPFd = mPollFds[i];
        shared_ptr<IMuxObject> vMuxObject = mMuxObjects[vPFd.fd];

        if (vPFd.revents & POLLIN)
        {
            vMuxObject->onRead();
        }
        if (vPFd.revents & POLLOUT)
        {
            vMuxObject->onWrite();
        }
        if (vPFd.revents & POLLERR)
        {
            vMuxObject->onError();
        }

        if (vPFd.revents != 0)
        {
            --vCheckCount;
        }
        else if (vCheckTimeout)
        {
            vMuxObject->onTimeoutCheck();
        }
    }
}

bool CNetLibMuxImpl::needCheckTimeout()
{
    chrono::system_clock::time_point vNow = chrono::system_clock::now();
    if (vNow < (mLastCheckTime + chrono::milliseconds(cMuxObjectTimeoutDuration)))
    {
        return false;
    }
    mLastCheckTime = vNow;
    return true;
}

CNetLibMuxImpl &CNetLibMuxImpl::getInstance()
{
    static CNetLibMuxImpl sMuxImpl;
    return sMuxImpl;
}

void CNetLibMuxImpl::addMuxObject(shared_ptr<IMuxObject> inObj)
{
    if (mMuxObjects.size() >= gMaxFdCount)
    {
        LOGWARN("addMuxObject: fd count exceed %u\n", gMaxFdCount);
        return;
    }

    int vFd = inObj->getFd();
    nl_assert(mMuxObjects.find(vFd) == mMuxObjects.end());
    mMuxObjects[vFd] = inObj;
}

void CNetLibMuxImpl::removeMuxObject(shared_ptr<IMuxObject> inObj)
{
    int vFd = inObj->getFd();
    auto vIt = mMuxObjects.find(vFd);
    nl_assert(vIt != mMuxObjects.end());
    mMuxObjects.erase(vIt);
}
