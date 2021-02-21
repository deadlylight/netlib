#include <unistd.h>
#include <sys/socket.h>
#include <cassert>
#include <itcpqueue.hpp>
#include <ctcpqueuefactory.hpp>
#include "ctcpserver.hpp"
#include "ctcpconnection.hpp"

CTcpServer::CTcpServer(int inSk)
    : mListenSk(inSk), mQueue(CTcpQueueFactory::createTcpConnectionQueue())
{
}

CTcpServer::~CTcpServer()
{
    close(mListenSk);
    mListenSk = -1;
}

void CTcpServer::addNewSk(int inSk)
{
    lock_guard<mutex> vGuard(mMutex);
    mQueue->push(makeNewConnection(inSk));
}

shared_ptr<ITcpConnection> CTcpServer::makeNewConnection(int inSk)
{
    shared_ptr<CTcpConnection> vConn = make_shared<CTcpConnection>(inSk);
    return vConn;
}

shared_ptr<ITcpConnectionQueue> CTcpServer::getQueue()
{
    lock_guard<mutex> vGuard(mMutex);
    return mQueue;
}
void CTcpServer::setQueue(shared_ptr<ITcpConnectionQueue> inQueue)
{
    lock_guard<mutex> vGuard(mMutex);
    //inQueue->move(*mQueue);
    mQueue = inQueue;
}

void CTcpServer::shutdownTcpServer()
{
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