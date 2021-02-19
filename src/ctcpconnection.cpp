#include <unistd.h>
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

shared_ptr<IMsgIn> CTcpConnection::readMsg(bool)
{
    return nullptr;
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
