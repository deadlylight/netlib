#include <unistd.h>
#include <sys/socket.h>
#include <cassert>
#include "ctcpserver.hpp"
#include "ctcpconnection.hpp"

CTcpServer::CTcpServer(int inSk)
    : mListenSk(inSk)
{
}

CTcpServer::~CTcpServer()
{
    close(mListenSk);
    mListenSk = -1;
    while (!mNewSks.empty())
    {
        int vSk = mNewSks.front();
        mNewSks.pop();
        close(vSk);
    }
}

void CTcpServer::addNewSk(int inSk)
{
    unique_lock<mutex> vLock(mSksMutex);
    mNewSks.push(inSk);
    mSksCond.notify_one();
}

int CTcpServer::getOneSk(bool inNonBlock)
{
    unique_lock<mutex> vLock(mSksMutex);
    while (mNewSks.size() == 0)
    {
        if (inNonBlock)
        {
            return -1;
        }
        else
        {
            mSksCond.wait(vLock);
        }
    }
    int vSk = mNewSks.front();
    mNewSks.pop();
    return vSk;
}

shared_ptr<ITcpConnection> CTcpServer::makeNewConnection(int inSk)
{
    shared_ptr<CTcpConnection> vConn = make_shared<CTcpConnection>(inSk);
    return vConn;
}

shared_ptr<ITcpConnection> CTcpServer::getNewConnection(bool inNonBlock)
{
    int vSk = getOneSk(inNonBlock);
    if (vSk < 0)
    {
        return nullptr;
    }
    return makeNewConnection(vSk);
}

int CTcpServer::getFd()
{
    return mListenSk;
}

uint32_t CTcpServer::getMuxEvents()
{
    return EMuxEventRead;
}

void CTcpServer::onError()
{
}

void CTcpServer::onReadable()
{
    int vSk = accept(mListenSk, nullptr, nullptr);
    if (vSk < 0)
    {
        return;
    }
    addNewSk(vSk);
}

void CTcpServer::onWritable()
{
    assert(0);
}