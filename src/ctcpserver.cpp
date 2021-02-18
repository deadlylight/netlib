#include <cassert>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <iaddr.hpp>
#include "ctcpserver.hpp"

CTcpServer::CTcpServer()
    : mReady(false), mSk(-1), mLastError(0)
{
}

CTcpServer::~CTcpServer()
{
}

bool CTcpServer::initTcpServer()
{
    mSk = socket(AF_INET, SOCK_STREAM, 0);
    if (mSk < 0)
    {
        mLastError = errno;
        return false;
    }
    int vRet = fcntl(mSk, F_SETFL, O_NONBLOCK);
    if (vRet < 0)
    {
        mLastError = errno;
        return false;
    }
    sockaddr *vSockAddr = nullptr;
    uint32_t vSockSize = 0;
    sockaddr_in vSockAddr4 = {0};
    sockaddr_in6 vSockAddr6 = {0};
    if (mAddr->getType() == IAddr::EAddrIpv4)
    {
        vSockAddr = &vSockAddr4;
        vSockSize = sizeof(vSockAddr4);
        vSockAddr4.sin_family = AF_INET;
        vSockAddr4.sin_addr.s_addr = inet_addr(mAddr->getAddr().c_str());
        vSockAddr4.sin_port = htons(mAddr->getPort());
    }
    else
    {
        //TODO
        assert(0);
    }
    vRet = bind(mSk, vSockAddr, vSockSize);
    if (vRet < 0)
    {
        mLastError = errno;
        return false;
    }
    vRet = listen(mSk, 99);
    if (vRet < 0)
    {
        mLastError = errno;
        return false;
    }
    
    isReady = true;
    return true;
}

int CTcpServer::getFd()
{
    return mSk;
}

void CTcpServer::onError()
{
}

void CTcpServer::onReadable()
{
    sockaddr vSockAddr;
    uint32_t vSockSize;
    int vNewSk = accept(mSk, &vSockAddr, &vSockSize);
    if (vNewSk < 0)
    {
        mLastError = errno;
        return;
    }
    shared_ptr<ITcpConnection> vTcpConnection = CTcpConnectionFactory::createTcpConnection(mSk, vSockAddr, vSockSize);
}

void CTcpServer::onWritable()
{
    assert(0);
}
