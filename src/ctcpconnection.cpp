#include <unistd.h>
#include <itcpqueue.hpp>
#include "ctcpconnection.hpp"

CTcpConnection::CTcpConnection(int inSk)
    : mSk(inSk)
{
}

CTcpConnection::~CTcpConnection()
{
    close(mSk);
    mSk = -1;
}

void CTcpConnection::setQueue(shared_ptr<ITcpMsgQueue> inQueue)
{
    lock_guard<mutex> vGuard(mMutex);
    //inQueue->move(*mQueue);
    mQueue = inQueue;
}

shared_ptr<ITcpMsgQueue> CTcpConnection::getQueue()
{
    lock_guard<mutex> vGuard(mMutex);
    return mQueue;
}

bool CTcpConnection::writeMsg(shared_ptr<IMsgOut>)
{
    return true;
}

void CTcpConnection::closeTcpConnection()
{
    close(mSk);
    mSk = -1;
}

int CTcpConnection::getFd()
{
    return mSk;
}

uint32_t CTcpConnection::getMuxEvents()
{
    return EMuxEventRead;
}

void CTcpConnection::onError()
{
}

void CTcpConnection::onReadable()
{
}

void CTcpConnection::onWritable()
{
}
