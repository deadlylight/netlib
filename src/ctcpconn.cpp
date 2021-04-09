#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <imsgin.hpp>
#include "ctcpconn.hpp"

CTcpConn::CTcpConn(CMux &inMux)
    : CNetStreamConn(inMux),
      mPort(0),
      mAddr(),
      mBindAddr()
{
}

CTcpConn::~CTcpConn()
{
}

bool CTcpConn::connect(uint16_t inPort, string inAddr, string inBindAddr)
{
    mPort = inPort;
    mAddr = inAddr;
    mBindAddr = inBindAddr;
    mSk = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (mSk < 0)
    {
        mError = errno;
        return false;
    }

    int vRet = 0;
    if (mBindAddr.length())
    {
        sockaddr_in vBindAddr;
        vBindAddr.sin_family = AF_INET;
        vBindAddr.sin_addr.s_addr = inet_addr(mBindAddr.c_str());
        vBindAddr.sin_port = 0;
        vRet = ::bind(mSk, reinterpret_cast<sockaddr *>(&vBindAddr), sizeof(vBindAddr));
        if (vRet < 0)
        {
            mError = errno;
            return false;
        }
    }

    sockaddr_in vAddr;
    vAddr.sin_family = AF_INET;
    vAddr.sin_addr.s_addr = inet_addr(mAddr.c_str());
    vAddr.sin_port = htons(mPort);
    vRet = ::connect(mSk, reinterpret_cast<sockaddr *>(&vAddr), sizeof(vAddr));
    if ((vRet < 0) && (errno != EINPROGRESS))
    {
        mError = errno;
        return false;
    }
    markWrite();
    return true;
}
