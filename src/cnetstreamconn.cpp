#include <unistd.h>
#include <cassert>
#include <imsgin.hpp>
#include <imsgout.hpp>
#include <inetstreamreader.hpp>
#include <cmux.hpp>
#include "cnetstreamconn.hpp"

CTimeout::CTimeout()
    : mConnTimeout(5),
      mIoTimeout(20),
      mIdleTimeout(600),
      mTimerInterval(0)
{
}

CNetStreamConn::CNetStreamConn(CMux &inMux)
    : mMux(inMux),
      mIsWrite(false),
      mIsRead(false),
      mIsConnecting(false),
      mTimeout(),
      mReader(nullptr),
      mSk(-1),
      mError(0)
{
}

CNetStreamConn::~CNetStreamConn()
{
    //mMux.removeTcpConn(shared_from_this());
    ::close(mSk);
    mSk = -1;
}

void CNetStreamConn::markWrite(bool in)
{
    mIsWrite = in;
}

void CNetStreamConn::markRead(bool in)
{
    mIsRead = in;
}

bool CNetStreamConn::forWrite()
{
    return mIsWrite;
}

bool CNetStreamConn::forRead()
{
    return mIsRead;
}

int CNetStreamConn::getFd()
{
    return mSk;
}

bool CNetStreamConn::isConnecting() const
{
    return mIsConnecting;
}

bool CNetStreamConn::sendMsg(shared_ptr<IMsgIn> inMsg)
{
    mMsgs.push(inMsg);
    markWrite();
    return true;
}

bool CNetStreamConn::isBad()
{
    return mError != 0;
}

void CNetStreamConn::onWrite()
{
    markWrite(false);
    while (mMsgs.size())
    {
        shared_ptr<IMsgIn> vMsg = mMsgs.front();
        if (!sendOneMsg(vMsg))
        {
            return;
        }
        mMsgs.pop();
    }
}

bool CNetStreamConn::sendOneMsg(shared_ptr<IMsgIn> &inMsg)
{
    const uint32_t vIoSize = 8192;

    while (inMsg->getSize())
    {
        uint32_t vSize = 0;
        const void *vBuf = inMsg->preRead(vIoSize, vSize);
        ssize_t vRet = ::write(mSk, vBuf, vSize);
        if (vRet > 0)
        {
            inMsg->commitRead(static_cast<uint32_t>(vRet));
        }
        else if (vRet == 0)
        {
            markWrite();
            return true;
        }
        else
        {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
            {
                markWrite();
                return true;
            }
            else
            {
                mError = errno;
                return false;
            }
        }
    }
    return true;
}

void CNetStreamConn::onRead()
{
    shared_ptr<IMsgOut> vMsg;
    mReader->onRead(vMsg->getMsgIn());
}

void CNetStreamConn::onConn()
{
    mReader->onConn(shared_from_this());
}

void CNetStreamConn::onDisconn()
{
    mReader->onDisconn();
}

void CNetStreamConn::onTimeout()
{
    uint64_t vTimeout;
    if (forRead() || forWrite())
    {
        vTimeout = isConnecting() ? mTimeout.mConnTimeout : mTimeout.mIoTimeout;
    }
    else
    {
        vTimeout = mTimeout.mIdleTimeout;
    }
    chrono::system_clock::time_point vExpireTime = mLastUpdateTime + chrono::milliseconds(vTimeout);
    if (chrono::system_clock::now() > vExpireTime)
    {
        mReader->onTimeout();
    }
}

void CNetStreamConn::onError()
{
    mReader->onError();
}
