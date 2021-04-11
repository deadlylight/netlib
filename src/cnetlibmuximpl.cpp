#include "imuxobject.hpp"
#include "cnetlibmuximpl.hpp"

CNetLibMuxImpl::CNetLibMuxImpl(CNetLibMux &inMux)
    : mMux(inMux),
    mMuxObjects(),
    mPollFds(nullptr),
    mPollFdCount(0)
{
}

CNetLibMuxImpl::~CNetLibMuxImpl()
{
}

void CNetLibMuxImpl::checkFds(uint32_t inActiveFdCount)
{
    uint32_t vCheckCount = needCheckTimeout() ? mPollFdCount : inActiveFdCount;
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
        else if (needCheckTimeout())
        {
            vMuxObject->onTimeoutCheck();
        }
    }
}

bool CNetLibMuxImpl::needCheckTimeout()
{
    return true;
}

void CNetLibMuxImpl::run()
{

}
